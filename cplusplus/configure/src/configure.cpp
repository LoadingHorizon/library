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

namespace lh {
namespace cfg {

Configure::Configure() {}

Configure::Configure(boost::any &data) : _data(data) {}

// 读取配置文件，存储在_data中
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
        CFG_FATAL("unknow configure type.");
        retval = -1;
    }

    if (parser != NULL) {
        delete parser;
    }

    return retval;
}

// 从_data中获取一个any对象存储到value中
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
    try {
        for (std::vector<std::string>::iterator it = keys.begin();
                it != keys.end(); ++it) {
            boost::smatch m;
            // map和数组类型，eg: "key[3]"
            if (boost::regex_match(*it, m, map_vec_reg)) {
                std::string key(m[1].first, m[1].second);
                std::string idx(m[2].first, m[2].second);
                uint32_t index = boost::lexical_cast<uint32_t>(idx);

                if (typeid(MapStrAny) != anything.type()) {
                    CFG_WARNING("anything is not a map.");
                    return -1;
                }
                anything = boost::any_cast<MapStrAny>(anything)[key];

                if (typeid(VectorAny) != anything.type()) {
                    CFG_WARNING("anything is not a vector.");
                    return -1;
                }
                if (boost::any_cast<VectorAny>(anything).size() <= index) {
                    CFG_WARNING("index[%d] is too large.", index);
                    return -1;
                }
                anything = boost::any_cast<VectorAny>(anything)[index];
            // map类型，eg: "key"
            } else if (boost::regex_match(*it, m, map_reg)) {
                if (typeid(MapStrAny) != anything.type()) {
                    CFG_WARNING("anthing is not a map.");
                    return -1;
                }
                anything = boost::any_cast<MapStrAny>(anything)[*it];
            // 数组类型，eg: "[3]"
            } else if (boost::regex_match(*it, m, vec_reg)) {
                std::string idx(m[1].first, m[1].second);
                uint32_t index = boost::lexical_cast<uint32_t>(idx);
                if (typeid(VectorAny) != anything.type()) {
                    CFG_WARNING("anything is not a vector.");
                    return -1;
                }
                if (boost::any_cast<VectorAny>(anything).size() <= index) {
                    CFG_WARNING("index[%d] is too large.", index);
                    return -1;
                }
                anything = boost::any_cast<VectorAny>(anything)[index];
            } else {
                CFG_WARNING("unknow key[%s] format", it->c_str());
                return -1;
            }
        }
    } catch (boost::bad_any_cast& e) {
        CFG_WARNING("any cast failed. %s.", e.what());
        return -1;
    } catch (boost::bad_lexical_cast& e) {
        CFG_WARNING("lexical cast failed. %s.", e.what());
        return -1;
    }
    value = anything;

    return 0;
}

Configure Configure::operator[](const std::string& key_path)
{
    boost::any anything;
    if (fetch_any(key_path, anything) != 0) {
        CFG_WARNING("fetch any failed.");
        return Configure();
    }
    return Configure(anything);
}

int Configure::size()
{
    try {
        if (typeid(VectorAny) == _data.type()) {
            return boost::any_cast<VectorAny>(_data).size();
        } else if (typeid(MapStrAny) == _data.type()) {
            return boost::any_cast<MapStrAny>(_data).size();
        } else if (typeid(std::string) == _data.type()) {
            return 1;
        } else {
            return -1;
        }
    } catch (boost::bad_any_cast& e) {
        CFG_WARNING("boost any cast failed. %s.", e.what());
        return -1;
    }

    return 0;
}

}  // cfg
}  // lh
