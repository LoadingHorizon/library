// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file logger_define.h
// @desc logger∫Í∂®“Â
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-09-22

#ifndef LH_LOG_LOGGER_DEFINE_H
#define LH_LOG_LOGGER_DEFINE_H

#define LOG_LOG(fmt, arg...) \
    do { \
        fprintf(stderr, "[%s:%d][%s] "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##arg); \
    } while (0)

#define LOG_FATAL(fmt, arg...) LOG_LOG(fmt, ##arg)
#define LOG_WARNING(fmt, arg...) LOG_LOG(fmt, ##arg)

#ifdef NDEBUG
#define LOG_DEBUG(fmt, arg...)
#else
#define LOG_DEBUG(fmt, arg...) LOG_LOG(fmt, ##arg)
#endif  // NDEBUG

#endif // LH_LOG_LOGGER_DEFINE_H
