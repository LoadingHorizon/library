// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file configure.h
// @desc 配置文件类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#ifndef _HL_CONFIGURE_H_
#define _HL_CONFIGURE_H_

#include <string>
#include <vector>
#include <iterator>

#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

namespace hl
{

class Configure {
typedef std::map<std::string, boost::any> MapStrAny;
typedef std::vector<boost::any> VectorAny;

public:
    explicit Configure();
    explicit Configure(boost::any &data);
    int load(const std::string& path, 
            const std::string& name, 
            const std::string& type);
    int fetch_any(const std::string& key_path, boost::any& anything);
    Configure operator[](const std::string& key_path);

    template <typename T> int fetch(std::string key_path, T &value);

private:
    boost::any _data;
};

template <typename T> int Configure::fetch(std::string key_path, T &value)
{
    boost::any anything;
    int ret = fetch_any(key_path, anything);
    if (ret != 0) {
        return ret;
    }

    if (typeid(std::string) != anything.type()) {
        return -1;
    }

    std::string str_val = boost::any_cast<std::string>(anything);
    value = boost::lexical_cast<T>(str_val);

    return 0;
}

}

#endif // _HL_CONFIGURE_H_
