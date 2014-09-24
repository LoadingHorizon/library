// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file test_logger.cpp
// @desc logger类单元测试
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-09-23

#include <gtest/gtest.h>
#include <logger.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

std::string conf_path = "./conf";
std::string conf_name = "logger.json.conf";
std::string conf_type = "json";
lh::cfg::Configure* conf = NULL;
class test_Logger_init_suite : public ::testing::Test {
protected:
    test_Logger_init_suite(){};
    virtual ~test_Logger_init_suite(){};
    virtual void SetUp() {
        conf = new lh::cfg::Configure();
        conf->load(conf_path, conf_name, conf_type);
    };
    virtual void TearDown() {
        delete conf;
    };
};

TEST_F(test_Logger_init_suite, case_name1)
{
    EXPECT_EQ(0, lh::log::Logger::init(*conf));
    EXPECT_EQ(3, lh::log::Logger::_logger_infos.size());
    // device.type
    EXPECT_EQ(lh::log::kTypeFile, lh::log::Logger::_logger_infos[0].type);
    EXPECT_EQ(lh::log::kTypeFile, lh::log::Logger::_logger_infos[1].type);
    EXPECT_EQ(lh::log::kTypeTty, lh::log::Logger::_logger_infos[2].type);
    // device.path
    EXPECT_EQ("log", lh::log::Logger::_logger_infos[0].path);
    EXPECT_EQ("log", lh::log::Logger::_logger_infos[1].path);
    // device.file
    EXPECT_EQ("sample.log", lh::log::Logger::_logger_infos[0].file);
    EXPECT_EQ("sample.log.wf", lh::log::Logger::_logger_infos[1].file);
    // device.open
    EXPECT_EQ(true, lh::log::Logger::_logger_infos[0].open);
    EXPECT_EQ(true, lh::log::Logger::_logger_infos[1].open);
    EXPECT_EQ(true, lh::log::Logger::_logger_infos[2].open);
    // device.level
    EXPECT_EQ((1 << lh::log::kTrace) | (1 << lh::log::kNotice),
            lh::log::Logger::_logger_infos[0].mask);
    EXPECT_EQ((1 << lh::log::kWarning) | (1 << lh::log::kFatal),
            lh::log::Logger::_logger_infos[1].mask);
    EXPECT_EQ((1 << lh::log::kWarning) | (1 << lh::log::kFatal) |
            (1 << lh::log::kTrace) | (1 << lh::log::kNotice),
            lh::log::Logger::_logger_infos[2].mask);

    // logger_level_strings
    EXPECT_EQ("DEBUG", lh::log::Logger::_logger_level_strings[lh::log::kDebug]);
    EXPECT_EQ("TRACE", lh::log::Logger::_logger_level_strings[lh::log::kTrace]);
    EXPECT_EQ("NOTICE", lh::log::Logger::_logger_level_strings[lh::log::kNotice]);
    EXPECT_EQ("WARNING", lh::log::Logger::_logger_level_strings[lh::log::kWarning]);
    EXPECT_EQ("FATAL", lh::log::Logger::_logger_level_strings[lh::log::kFatal]);
}

class test_Logger_log_suite : public ::testing::Test {
protected:
    test_Logger_log_suite(){};
    virtual ~test_Logger_log_suite(){};
    virtual void SetUp() {
        conf = new lh::cfg::Configure();
        conf->load(conf_path, conf_name, conf_type);
    };
    virtual void TearDown() {
        delete conf;
    };
};

TEST_F(test_Logger_log_suite, case_name1)
{
    ASSERT_EQ(0, lh::log::Logger::init(*conf));
    lh::log::Logger::log(lh::log::kTrace, "%s", "Just letting you know that you're not alone");
}

class test_Logger_destory_suite : public ::testing::Test {
protected:
    test_Logger_destory_suite(){};
    virtual ~test_Logger_destory_suite(){};
    virtual void SetUp() {
        conf = new lh::cfg::Configure();
        conf->load(conf_path, conf_name, conf_type);
    };
    virtual void TearDown() {
        delete conf;
    };
};

TEST_F(test_Logger_destory_suite, case_name1)
{
    ASSERT_EQ(0, lh::log::Logger::init(*conf));
    lh::log::Logger::destory();
}

