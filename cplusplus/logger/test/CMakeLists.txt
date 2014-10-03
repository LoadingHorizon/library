PROJECT(LH_LOGGER_TEST)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

SET(SRC_LIST
    "../src/logger.cpp"
    "./test_logger.cpp"
)

INCLUDE_DIRECTORIES(
    "../include"
    "../../../../../boost/boost-1.56.0/include"
    "../../../../../google/gtest/gtest-1.6.0/include"
    "../../../../../loadinghorizion/configure/configure-1.0.0/include"
)

LINK_DIRECTORIES(
    "../../../../../boost/boost-1.56.0/lib"
    "../../../../../google/gtest/gtest-1.6.0/lib"
    "../../../../../loadinghorizion/configure/configure-1.0.0/lib"
)

ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
)

ADD_EXECUTABLE(test_logger ${SRC_LIST})

TARGET_LINK_LIBRARIES(test_logger
    lh_configure
    boost_regex
    gtest
    pthread
)

ADD_CUSTOM_COMMAND(
    TARGET test_logger
    POST_BUILD
    COMMAND mkdir -p log
    COMMAND cp -r ${LH_LOGGER_TEST_SOURCE_DIR}/../conf .
)
