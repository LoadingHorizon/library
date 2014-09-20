// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file json_parser.h
// @desc json配置文件解析类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#ifndef _HL_JSON_PARSER_H_
#define _HL_JSON_PARSER_H_

#include "config_parser.h"

#include <list>
#include <map>
#include <vector>
#include <string>

namespace hl {

class JsonParser : public ConfigParser {

typedef std::map<std::string, boost::any> MapStrAny;
typedef std::vector<boost::any> VectorAny;

public:
    virtual int parse(
            const std::string& path,
            const std::string& name,
            boost::any& container);

    static const int kMaxLineLength;
    virtual ~JsonParser() {}

private:
    int _analysis_line(
            const std::string line,
            std::list<std::string>& elements);
    int _process_parser(
        std::list<std::string>& elements,
        boost::any& container);
    int _process_parser_map(
        std::list<std::string>& elements,
        boost::any& container);
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

}  // hl

#endif // _HL_JSON_PARSER_H_
