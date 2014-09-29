// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file config_parser.h
// @desc 配置文件解析基类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#ifndef LH_CFG_CONFIGURE_PARSER_H
#define LH_CFG_CONFIGURE_PARSER_H

#include <string>
#include <boost/any.hpp>

namespace lh {
namespace cfg {

// 配置文件解析基类
class ConfigParser {
public:
    // @desc 解析path/name文件，将解析的结果存储在container对象中
    //
    // @param path 配置文件路径
    // @param name 配置文件名
    // @param container 配置的内存结构
    //      该any对象可能是map，也可能是vector
    //      也可能是其他任意的值类型，如int，double等
    //      而map，vector中的类型也为任意类型，这样可以实现嵌套
    //
    // @return 0成功，-1失败
    virtual int parse(
        const std::string& path,
        const std::string& name,
        boost::any& container) = 0;
    virtual ~ConfigParser() {}
};

}  // cfg
}  // lh

#endif // LH_CFG_CONFIGURE_PARSER_H
