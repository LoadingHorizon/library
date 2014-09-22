// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file configure.h
// @desc 配置文件类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#ifndef LH_CFG_CONFIGURE_H
#define LH_CFG_CONFIGURE_H

#include <string>
#include <vector>
#include <iterator>

#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include "config_define.h"

namespace lh {
namespace cfg {

class Configure {
typedef std::map<std::string, boost::any> MapStrAny;
typedef std::vector<boost::any> VectorAny;

public:
    explicit Configure();
    explicit Configure(boost::any &data);
    // @desc 读取配置文件
    //
    // @param path 文件路径
    // @param name 文件名
    // @param type 文件类型
    //          "json"，json格式配置
    //
    // @return 0成功，-1失败
    int load(const std::string& path, 
            const std::string& name, 
            const std::string& type);
    // @desc 从_data中获取一个any对象
    //
    // @param key_path 对象的路径，eg:"maintainers[0].name"
    // @param anything 存储any对象
    //
    // @return 0成功，-1失败
    int fetch_any(const std::string& key_path, boost::any& anything);
    // @desc 获取子配置
    //
    // @param key_path 子配置的路径
    //
    // @return 0成功，-1失败
    Configure operator[](const std::string& key_path);
    // @desc 获取配置项
    //
    // @tparam T 配置项的类型
    // @param key_path 配置项的路径
    // @param value 配置项的值
    //
    // @return 0成功，-1失败
    template <typename T> int fetch(std::string key_path, T &value);

private:
    // 配置的内存结构
    // 该any对象可能是map，也可能是vector
    // 也可能是其他任意的值类型，如int，double等
    // 而map，vector中的类型也为任意类型，这样可以实现嵌套
    boost::any _data;
};

template <typename T> int Configure::fetch(std::string key_path, T &value)
{
    boost::any anything;
    int ret = fetch_any(key_path, anything);
    if (ret != 0) {
        CFG_WARNING("fetch any failed.");
        return ret;
    }

    if (typeid(std::string) != anything.type()) {
        CFG_WARNING("anything type is not string.");
        return -1;
    }

    try {
        std::string str_val = boost::any_cast<std::string>(anything);
        value = boost::lexical_cast<T>(str_val);
    } catch (boost::bad_any_cast& e) {
        CFG_WARNING("any cast failed. %s.", e.what());
        return -1;
    } catch (boost::bad_lexical_cast& e) {
        CFG_WARNING("lexical cast failed. %s.", e.what());
        return -1;
    }

    return 0;
}

}  // cfg
}  // lh

#endif // LH_CFG_CONFIGURE_H
