CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(LH_CONFIGURE_TEST)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${LH_CONFIGURE_TEST_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC")
SET(WORK_ROOT "../../../../..")

AUX_SOURCE_DIRECTORY(../src SOURCES)
AUX_SOURCE_DIRECTORY(. TEST_SOURCES)
SET(SRC_LIST ${SOURCES} ${TEST_SOURCES})

INCLUDE_DIRECTORIES(
    "../include"
    "${LH_CONFIGURE_TEST_SOURCE_DIR}/${WORK_ROOT}/third/boost/boost-1.56.0/include"
    "${LH_CONFIGURE_TEST_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/include"
)

LINK_DIRECTORIES(
    "${LH_CONFIGURE_TEST_SOURCE_DIR}/${WORK_ROOT}/third/boost/boost-1.56.0/lib"
    "${LH_CONFIGURE_TEST_SOURCE_DIR}/${WORK_ROOT}/google/gtest/gtest-1.6.0/lib"
)

ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
)

ADD_EXECUTABLE(lh_configure_test ${SRC_LIST})

TARGET_LINK_LIBRARIES(lh_configure_test
    boost_regex
    gtest
    pthread
)

ADD_CUSTOM_COMMAND(
    TARGET lh_configure_test
    POST_BUILD
    COMMAND cp -r ${LH_CONFIGURE_TEST_SOURCE_DIR}/../conf .
)
