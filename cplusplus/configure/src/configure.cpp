// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file configure.cpp
// @desc 配置文件类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#include "configure.h"
#include "config_parser.h"
#include "json_parser.h"

namespace hl {

Configure::Configure() {}

Configure::Configure(boost::any &data) : _data(data) {}

int Configure::load(const std::string& path,
        const std::string& name,
        const std::string& type)
{
    int retval = 0;

    ConfigParser *parser = NULL;
    if (type == "json") {
        parser = new JsonParser();
        retval = parser->parse(path, name, _data);
    } else {
        retval = -1;
    }

    if (parser != NULL) {
        delete parser;
    }

    return retval;
}

int Configure::fetch_any(const std::string& key_path, boost::any& value)
{
    // eg: key[3]
    static boost::regex map_vec_reg("([a-zA-Z_]+[a-zA-Z0-9_]*)\\[([0-9]+)\\]");
    // eg: key
    static boost::regex map_reg("([a-zA-Z_]+[a-zA-Z0-9_]*)");
    // eg: [3]
    static boost::regex vec_reg("\\[([0-9]+)\\]");

    std::vector<std::string> keys;
    boost::split(keys, key_path, boost::is_any_of("."));

    boost::any anything = _data;

    for (std::vector<std::string>::iterator it = keys.begin();
            it != keys.end(); ++it) {
        boost::smatch m;
        if (boost::regex_match(*it, m, map_vec_reg)) {
            std::string key(m[1].first, m[1].second);
            std::string idx(m[2].first, m[2].second);
            uint32_t index = boost::lexical_cast<uint32_t>(idx);

            if (typeid(MapStrAny) != anything.type()) {
                return -1;
            }
            anything = boost::any_cast<MapStrAny>(anything)[key];

            if (typeid(VectorAny) != anything.type()) {
                return -1;
            }
            if (boost::any_cast<VectorAny>(anything).size() <= index) {
                return -1;
            }
            anything = boost::any_cast<VectorAny>(anything)[index];
        } else if (boost::regex_match(*it, m, map_reg)) {
            if (typeid(MapStrAny) != anything.type()) {
                return -1;
            }
            anything = boost::any_cast<MapStrAny>(anything)[*it];
        } else if (boost::regex_match(*it, m, vec_reg)) {
            std::string idx(m[1].first, m[1].second);
            uint32_t index = boost::lexical_cast<uint32_t>(idx);
            if (typeid(VectorAny) != anything.type()) {
                return -1;
            }
            if (boost::any_cast<VectorAny>(anything).size() <= index) {
                return -1;
            }
            anything = boost::any_cast<VectorAny>(anything)[index];
        } else {
            return -1;
        }
    }
    value = anything;

    return 0;
}

Configure Configure::operator[](const std::string& key_path)
{
    boost::any anything;
    if (fetch_any(key_path, anything) != 0) {
        return Configure();
    }
    return Configure(anything);
}

}  // hl
