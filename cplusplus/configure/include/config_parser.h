// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file config_parser.h
// @desc 配置文件解析基类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#ifndef _HL_CONFIGURE_PARSER_H_
#define _HL_CONFIGURE_PARSER_H_

#include <boost/any.hpp>

namespace hl {

class ConfigParser {
public:
    virtual int parse(
        const std::string& path,
        const std::string& name,
        boost::any& container) = 0;
    virtual ~ConfigParser() {}
};

}  // hl

#endif // _HL_CONFIGURE_PARSER_H_
