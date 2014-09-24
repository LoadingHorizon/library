// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file logger.cpp
// @desc 日志类
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-09-22

#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include <iterator>

#include "logger_define.h"

namespace lh {
namespace log {

logger_info_t::logger_info_t() :
    open(false), mask(0), fp(NULL)
{}

std::vector<logger_info_t> Logger::_logger_infos = std::vector<logger_info_t>();
std::vector<std::string> Logger::_logger_level_strings = std::vector<std::string>(64);

const size_t Logger::kLogBufferSize    = 2048;
const size_t Logger::kFormatBufferSize = 2048;
const size_t Logger::kTimeBufferSize   = 64;
char* Logger::_log_buffer              = NULL;
char* Logger::_format_buffer           = NULL;
char* Logger::_time_buffer             = NULL;

// 初始化日志
int Logger::init(Configure& config)
{
    // 初始化日志级别
    _logger_level_strings[kDebug]   = "DEBUG";
    _logger_level_strings[kNotice]  = "NOTICE";
    _logger_level_strings[kTrace]   = "TRACE";
    _logger_level_strings[kWarning] = "WARNING";
    _logger_level_strings[kFatal]   = "FATAL";

    // 为日志行buffer分配空间
    _log_buffer = new(std::nothrow) char[kLogBufferSize];
    if (_log_buffer == NULL) {
        LOG_FATAL("alloc log buffer failed.");
        return -1;
    }
    _format_buffer = new(std::nothrow) char[kFormatBufferSize];
    if (_format_buffer == NULL) {
        LOG_FATAL("alloc format buffer failed.");
        return -1;
    }
    _time_buffer = new(std::nothrow) char[kTimeBufferSize];
    if (_time_buffer == NULL) {
        LOG_FATAL("alloc time buffer failed.");
        return -1;
    }

    std::string type;

    // 读取配置，初始化各个日志文件的信息 device
    _logger_infos.clear();
    int device_num = config["device"].size();
    if (device_num == 0) {
        LOG_WARNING("no log device found in configure.");
    }
    for (int device_idx = 0; device_idx < device_num; device_idx++) {
        logger_info_t logger_info;
        char key_path[1024];

        // 获取device.type
        snprintf(key_path, sizeof(key_path), "device[%d].type", device_idx);
        if (config.fetch<std::string>(key_path, type) != 0) {
            LOG_FATAL("device[%d].type is required.", device_idx);
            return -1;
        }
        // 日志文件
        if (type == "FILE") {
            logger_info.type = kTypeFile;
            // 获取日志文件路径 device.path
            snprintf(key_path, sizeof(key_path), "device[%d].path", device_idx);
            if (config.fetch<std::string>(key_path, logger_info.path) != 0) {
                LOG_FATAL("device[%d].path is required.", device_idx);
                return -1;
            }

            // 获取日志文件名 device.file
            snprintf(key_path, sizeof(key_path), "device[%d].file", device_idx);
            if (config.fetch<std::string>(key_path, logger_info.file) != 0) {
                LOG_FATAL("device[%d].file is required.", device_idx);
                return -1;
            }

            // 打开日志文件
            FILE* fp = fopen((logger_info.path + '/' + logger_info.file).c_str(), "w");
            if (fp == NULL) {
                LOG_FATAL("open log %s/%s failed.", logger_info.path.c_str(), logger_info.file.c_str());
                return -1;
            }
            logger_info.fp = fp;
        // 终端输出
        } else if (type == "TTY") {
            logger_info.type = kTypeTty;
            logger_info.fp = stdout;
        // 未知的日志类型
        } else {
            LOG_FATAL("unknow type %s", type.c_str());
            return -1;
        }

        // 获取是否打开日志 device.open
        std::string open;
        snprintf(key_path, sizeof(key_path), "device[%d].open", device_idx);
        if (config.fetch<std::string>(key_path, open) != 0) {
            LOG_FATAL("device[%d].open is required.", device_idx);
            return -1;
        }
        if (open == "true") {
            logger_info.open = true;
        } else if (open == "false") {
            logger_info.open = false;
        } else {
            LOG_FATAL("open value should be true or false.");
            return -1;
        }

        // 获取日志文件打印级别 device.level
        snprintf(key_path, sizeof(key_path), "device[%d].level", device_idx);
        int level_num = config[key_path].size();
        if (level_num == 0) {
            LOG_WARNING("device.level is null");
        }
        for (int level_idx = 0; level_idx < level_num; level_idx++) {
            std::string level;
            snprintf(key_path, sizeof(key_path), "device[%d].level[%d]", device_idx, level_idx);
            if (config.fetch<std::string>(key_path, level) != 0) {
                LOG_FATAL("get device[%d].level[%d] failed.", device_idx, level_idx);
                return -1;
            }
            // 把日志文件得级别记录到相应的日志级别掩码mask中
            if (level == "DEBUG") { 
                logger_info.mask |= (1 << kDebug);
            } else if (level == "TRACE") { 
                logger_info.mask |= (1 << kTrace);
            } else if (level == "NOTICE") {
                logger_info.mask |= (1 << kNotice);
            } else if (level == "WARNING") {
                logger_info.mask |= (1 << kWarning);
            } else if (level == "FATAL") {
                logger_info.mask |= (1 << kFatal);
            } else {
                LOG_FATAL("unknow type[%s] of level.", level.c_str());
                return -1;
            }
        }

        _logger_infos.push_back(logger_info);
    }

    return 0;
}

// 日志格式：
//  NOTICE: [2014-09-24 22:34:56] We'll walk this road together, through the storm
void Logger::log(uint64_t level, const char* format, ...)
{
    // 获取当前时间
    time_t time_now = time(0);
    strftime(_time_buffer, kTimeBufferSize, "%Y-%m-%d %H:%M:%S", localtime(&time_now));
    snprintf(_format_buffer, kFormatBufferSize, "%s: [%s] %s",
            _logger_level_strings[level].c_str(), _time_buffer, format);

    va_list parglist;
    va_start(parglist, _format_buffer);
    vsnprintf(_log_buffer, kLogBufferSize, _format_buffer, parglist);
    va_end(parglist);

    for (std::vector<logger_info_t>::iterator it = _logger_infos.begin();
            it != _logger_infos.end(); ++it) {
        if ((it->mask & (1 << level)) != 0) {
            fprintf(it->fp, "%s\n", _log_buffer);
        }
    }
}

// 退出日志
void Logger::destory()
{
    for (std::vector<logger_info_t>::iterator it = _logger_infos.begin();
            it != _logger_infos.end(); ++it) {
        if (!it->open || it->fp == NULL) {
            continue;
        }

        fclose(it->fp);
        it->fp = NULL;
        it->open = false;
        it->mask = 0;
    }
}

}  // log
}  // lh
