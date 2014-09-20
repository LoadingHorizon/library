// Copyright (c) 2014 LoadingHorizion. All Rights Reserved
//
// @file test_configure.cpp
// @desc 配置文件类单元测试
// @auth hatlonely(hatlonely@gmail.com)
// @vers 1.0
// @date 2014-08-23

#include <configure.h>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
 	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

class test_Configure_suite : public ::testing::Test{
    protected:
        test_Configure_suite(){};
        virtual ~test_Configure_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_Configure_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_Configure_suite, *)
        };
};

TEST_F(test_Configure_suite, load_case)
{
    hl::Configure conf;
    EXPECT_EQ(0, conf.load("./conf", "configure_sample.conf", "json"));
}
 
TEST_F(test_Configure_suite, get_string_case)
{
    hl::Configure conf;
    EXPECT_EQ(0, conf.load("./conf", "configure_sample.conf", "json"));

    std::string description;
    EXPECT_EQ(0, conf.fetch<std::string>("description", description));
    EXPECT_EQ("configure parser for c++, support json formation", description);

    std::string version;
    EXPECT_EQ(0, conf.fetch<std::string>("version", version));
    EXPECT_EQ("1.0", version);

    std::string date;
    EXPECT_EQ(0, conf.fetch<std::string>("date", date));
    EXPECT_EQ("2014-08-22", date);
}
 
TEST_F(test_Configure_suite, map_case)
{
    hl::Configure conf;
    EXPECT_EQ(0, conf.load("./conf", "configure_sample.conf", "json"));

    std::string author_name;
    EXPECT_EQ(0, conf.fetch<std::string>("author.name", author_name));
    EXPECT_EQ("hatlonely",author_name);

    std::string author_email;
    EXPECT_EQ(0, conf.fetch<std::string>("author.email", author_email));
    EXPECT_EQ("hatlonely@gmail.com", author_email);
}

TEST_F(test_Configure_suite, vector_case)
{
    hl::Configure conf;
    EXPECT_EQ(0, conf.load("./conf", "configure_sample.conf", "json"));

    std::string maintainers_1_name;
    EXPECT_EQ(0, conf.fetch<std::string>("maintainers[1].name", maintainers_1_name));
    EXPECT_EQ("playjokes", maintainers_1_name);

    std::string maintainers_1_email;
    EXPECT_EQ(0, conf.fetch<std::string>("maintainers[1].email", maintainers_1_email));
    EXPECT_EQ("playjokes@gmail.com", maintainers_1_email);
}

TEST_F(test_Configure_suite, operator_case)
{
    hl::Configure conf;
    EXPECT_EQ(0, conf.load("./conf", "configure_sample.conf", "json"));

    std::string maintainers_1_name;
    EXPECT_EQ(0, conf["maintainers[1]"].fetch<std::string>("name", maintainers_1_name));
    EXPECT_EQ("playjokes", maintainers_1_name);

    std::string maintainers_1_email;
    EXPECT_EQ(0, conf["maintainers"].fetch<std::string>("[1].email", maintainers_1_email));
    EXPECT_EQ("playjokes@gmail.com", maintainers_1_email);
}
