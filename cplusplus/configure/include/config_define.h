// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file config_define.h
// @desc configureºê
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-09-22

#ifndef LH_CFG_CONFIG_DEFINE_H
#define LH_CFG_CONFIG_DEFINE_H

#define CFG_LOG(fmt, arg...) \
    do { \
        fprintf(stderr, "[%s:%d][%s] "fmt, __FILE__, __LINE__, __FUNCTION__, ##arg); \
    } while (0)

#define CFG_FATAL(fmt, arg...) CFG_LOG(fmt, ##arg)
#define CFG_WARNING(fmt, arg...) CFG_LOG(fmt, ##arg)

#ifdef NDEBUG
#define CFG_DEBUG(fmt, arg...)
#else
#define CFG_DEBUG(fmt, arg...) CFG_LOG(fmt, ##arg)
#endif  // NDEBUG

#endif
