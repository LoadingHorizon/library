CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(LH_LOGGER_TEST)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${LH_LOGGER_TEST_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC")
SET(WORK_ROOT "../../../../..")

AUX_SOURCE_DIRECTORY(../src SOURCES)
AUX_SOURCE_DIRECTORY(. TEST_SOURCES)
SET(SRC_LIST ${SOURCES} ${TEST_SOURCES})

INCLUDE_DIRECTORIES(
    "../include"
    "${LH_LOGGER_TEST_SOURCE_DIR}/${WORK_ROOT}/third/boost/boost-1.56.0/include"
    "${LH_LOGGER_TEST_SOURCE_DIR}/${WORK_ROOT}/loadinghorizion/configure/configure-1.0.0/include"
    "${LH_LOGGER_TEST_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/include"
)

LINK_DIRECTORIES(
    "${LH_LOGGER_TEST_SOURCE_DIR}/${WORK_ROOT}/third/boost/boost-1.56.0/lib"
    "${LH_LOGGER_TEST_SOURCE_DIR}/${WORK_ROOT}/loadinghorizion/configure/configure-1.0.0/lib"
    "${LH_LOGGER_TEST_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/lib"
)

ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
)

ADD_EXECUTABLE(lh_logger_test ${SRC_LIST})

TARGET_LINK_LIBRARIES(lh_logger_test
    lh_configure
    boost_regex
    gtest
    pthread
)

ADD_CUSTOM_COMMAND(
    TARGET lh_logger_test
    POST_BUILD
    COMMAND mkdir -p log
    COMMAND cp -r ${LH_LOGGER_TEST_SOURCE_DIR}/../conf .
)
