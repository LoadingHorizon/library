// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file json_parser.h
// @desc json配置文件解析类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#ifndef LH_CFG_JSON_PARSER_H
#define LH_CFG_JSON_PARSER_H

#include "config_parser.h"

#include <list>
#include <map>
#include <vector>
#include <string>

namespace lh {
namespace cfg {

// json配置文件解析类
class JsonParser : public ConfigParser {
typedef std::map<std::string, boost::any> MapStrAny;
typedef std::vector<boost::any> VectorAny;

public:
    virtual ~JsonParser() {}
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
            boost::any& container);
    // 配置文件中行的最大长度
    static const int kMaxLineLength;

private:
    // @desc 分析配置文件中的一行
    //
    // @param line 配置文件中的一行
    // @param elements 存储标识符
    //
    // @return 0成功，-1失败
    int _analysis_line(
            const std::string line,
            std::list<std::string>& elements);
    // @desc 解析的过程
    //
    // @param elements 标示符的集合
    // @param container 存储解析后的结构
    //
    // @return 0成功，-1失败
    int _process_parser(
        std::list<std::string>& elements,
        boost::any& container);
    // @desc 解析elements到一个map中
    //
    // @param elements 标示符的集合
    // @param container 存储解析后的结构
    //
    // @return 0成功，-1失败
    int _process_parser_map(
        std::list<std::string>& elements,
        boost::any& container);
    // @desc 解析elements到一个vector中
    //
    // @param elements 标示符的集合
    // @param container 存储解析后的结构
    //
    // @return 0成功，-1失败
    int _process_parser_vec(
        std::list<std::string>& elements,
        boost::any& container);

    inline bool _is_special_character(char ch);
    inline bool _is_space_character(char ch);
    inline bool _is_identifier_character(char ch);
};

/* class JsonParserException : std::exception { */
/*  */
/* }; */

}  // cfg
}  // lh

#endif // LH_CFG_JSON_PARSER_H
