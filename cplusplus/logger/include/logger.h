// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file logger.h
// @desc 日志类
//      该类不能实例化，只有静态类函数
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-09-22

#ifndef LH_LOG_LOGGER_H
#define LH_LOG_LOGGER_H

#include <string>
#include <vector>
#include <configure.h>

namespace lh {
namespace log {

// 日志类型
enum LoggerType {
    kTypeFile = 0,  // 文件
    kTypeTty  = 1   // 终端，stdout
};

// 日志级别
enum LoggerLevel {
    kDebug   = 0,   // 调试日志
    kTrace   = 1,   // 普通输出
    kNotice  = 2,   // 重要输出
    kWarning = 3,   // 错误警告
    kFatal   = 4    // 致命错误
};

struct logger_info_t {
    LoggerType type;    // 日志的类型
    std::string path;   // 日志文件的路径
    std::string file;   // 日志文件的名字
    bool open;          // 是否处于打开状态
    uint64_t mask;      // 日志级别掩码，当mask & level != 0时，日志生效
    FILE* fp;           // 日志文件指针

    explicit logger_info_t();
};

class Logger {
typedef cfg::Configure Configure;

public:
    // @desc 日志初始化
    //
    // @param config 配置项
    //
    // @return 0成功，-1失败
    static int init(Configure& config);
    // @desc 打印日志
    //
    // @param level 日志的级别
    // @param format 日志的格式
    // @param ... 格式化参数
    //
    // @return 0成功，-1失败
    static void log(uint64_t level, const char* format, ...);
    // @desc 退出日志
    //
    // @return 0成功，-1失败
    static void destory();

private:
    // 日志文件信息
    static std::vector<logger_info_t> _logger_infos;
    // 日志文件级别对应字符串
    static std::vector<std::string> _logger_level_strings;

    // 日志行buffer
    static const size_t kLogBufferSize;
    static char* _log_buffer;
    // 日志行格式buffer
    static const size_t kFormatBufferSize;
    static char* _format_buffer;
    // 字符串时间buffer
    static const size_t kTimeBufferSize;
    static char* _time_buffer;

    // 不允许实例化
    Logger();
    Logger(const Logger&);
    Logger& operator=(const Logger&);
};

}  // log
}  // lh

#endif // LH_LOG_LOGGER_H
