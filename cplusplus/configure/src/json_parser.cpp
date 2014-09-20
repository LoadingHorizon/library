// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file json_parser.cpp
// @desc json配置文件解析类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#include "json_parser.h"

#include <fstream>
#include <map>
#include <iterator>

#include <boost/algorithm/string.hpp>

namespace hl {


int JsonParser::parse(
        const std::string& path, 
        const std::string& name, 
        boost::any& container)
{
    std::ifstream file;
    file.open((path + "/" + name).c_str(), std::ifstream::in);

    if (!file.good()) {
        return -1;
    }

    char line_buff[kMaxLineLength];

    // 读取配置文件，分析文件中的语法元素
    std::list<std::string> elements;
    while (file.good()) {
        file.getline(line_buff, kMaxLineLength);
        std::string line(line_buff);
        _analysis_line(line, elements);
    }

    // 解析语法元素
    return _process_parser(elements, container);
}

int JsonParser::_analysis_line(const std::string line, std::list<std::string>& elements)
{
    int pos = 0;
    for (size_t i = 0; i < line.size(); i++) {
        // 特殊字符
        if (_is_special_character(line[i])) {
            elements.push_back(line.substr(i, 1));
            pos = i + 1;
        // 空白字符
        } else if (_is_space_character(line[i])) {
            pos = i + 1;
            continue;
        // 标识符或数值类型
        } else if (_is_identifier_character(line[i])) {
            pos = i;
            while (_is_identifier_character(line[++i]));
            elements.push_back(line.substr(pos, i - pos));
            i--;
        // 字符串，以引号包围的字符串
        } else if (line[i] == '\"' || line[i] == '\'') {
            pos = i;
            char quot = line[i];
            while (line[++i] != quot || line[i - 1] == '\\') {
                // 没有找到对应的引号，退出
                if (line[i] == '\0') {
                    return -1;
                }
            }
            std::string str = line.substr(pos, i - pos + 1);
            boost::trim_if(str, boost::is_any_of("\"\'"));
            elements.push_back(str);
        // 注释，忽略//后面的字符
        } else if (line[i] == '/') {
            if (line[++i] != '/') {
                return -1;
            }
            break;
        // 解析出错
        } else {
            return -1;
        }
    }

    return 0;
}

int JsonParser::_process_parser_map(
        std::list<std::string>& elements,
        boost::any& container)
{
    MapStrAny map_str_any;
    while (elements.size() > 0) {
        if (elements.front() == "}") {
            elements.pop_front();
            container = map_str_any;
            return 0;
        }
        // 获得key
        std::string key = elements.front();
        elements.pop_front();

        // 获取冒号
        std::string colon = elements.front();
        if (colon != ":") {
            return -1;
        }
        elements.pop_front();

        // 获取value
        std::string value = elements.front();
        if (value == "{" || value == "[") {
            map_str_any[key] = boost::any();
            if (_process_parser(elements, map_str_any[key]) != 0) {
                return -1;
            }
        } else {
            map_str_any[key] = value;
            elements.pop_front();
        }

        // 获取逗号
        std::string comma = elements.front();
        if (comma != ",") {
            // 若不是逗号是"}"
            if (comma == "}") {
                elements.pop_front();
                container = map_str_any;
                return 0;
            }

            return -1;
        }
        elements.pop_front();
    }
    container = map_str_any;

    return 0;
}

int JsonParser::_process_parser_vec(
        std::list<std::string>& elements,
        boost::any& container)
{
    VectorAny vector_any;
    int idx = 0;
    while (elements.size() > 0) {
        if (elements.front() == "]") {
            elements.pop_front();
            container = vector_any;
            return 0;
        }

        // 获取value
        std::string value = elements.front();
        if (value == "{" || value == "[") {
            vector_any.push_back(boost::any());
            if (_process_parser(elements, vector_any[idx]) != 0) {
                return -1;
            }
            idx++;
        } else {
            vector_any.push_back(value);
            elements.pop_front();
            idx++;
        }

        // 获取逗号
        std::string comma = elements.front();
        if (comma != ",") {
            if (comma == "]") {
                elements.pop_front();
                container = vector_any;
                return 0;
            }

            return -1;
        }
        elements.pop_front();
    }
    container = vector_any;

    return 0;
}

int JsonParser::_process_parser(
        std::list<std::string>& elements,
        boost::any& container)
{
    std::string current = elements.front();
    elements.pop_front();
    if (current == "{") {
        if (_process_parser_map(elements, container) != 0) {
            return -1;
        }
    } else if (current == "[") {
        if (_process_parser_vec(elements, container) != 0) {
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

bool JsonParser::_is_special_character(char ch)
{
    return ch == '{' || ch == '}' || ch == '[' 
        || ch == ']' || ch == ',' || ch == ':';
}

bool JsonParser::_is_space_character(char ch)
{
    return ch == ' ' || ch == '\t';
}

bool JsonParser::_is_identifier_character(char ch)
{
    return isalnum(ch) || ch == '_' || ch == '.';
}

const int JsonParser::kMaxLineLength = 1024;

}  // hl
