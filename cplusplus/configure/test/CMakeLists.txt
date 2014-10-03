PROJECT(LH_CONFIGURE_TEST)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

SET(SRC_LIST
    "../src/configure.cpp"
    "../src/json_parser.cpp"
    "./test_configure.cpp"
)

INCLUDE_DIRECTORIES(
    "../include"
    "../../../../../boost/boost-1.56.0/include"
    "../../../../../google/gtest/gtest-1.6.0/include"
)

LINK_DIRECTORIES(
    "../../../../../google/gtest/gtest-1.6.0/lib"
    "../../../../../boost/boost-1.56.0/lib"
)

ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
)

ADD_EXECUTABLE(test_configure ${SRC_LIST})

TARGET_LINK_LIBRARIES(test_configure
    boost_regex
    gtest
    pthread
)

ADD_CUSTOM_COMMAND(
    TARGET test_configure
    POST_BUILD
    COMMAND cp -r ${LH_CONFIGURE_TEST_SOURCE_DIR}/../conf .
)
