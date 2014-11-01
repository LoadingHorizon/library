CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(LH_CONFIGURE_TEST)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC")

AUX_SOURCE_DIRECTORY(../src SOURCES)
AUX_SOURCE_DIRECTORY(. TEST_SOURCES)
SET(SRC_LIST
    ${SOURCES}
    ${TEST_SOURCES}
)

INCLUDE_DIRECTORIES(
    "../include"
    "../../../../../third/boost/boost-1.56.0/include"
    "../../../../../google/gtest/gtest-1.6.0/include"
)

LINK_DIRECTORIES(
    "../../../../../third/boost/boost-1.56.0/lib"
    "../../../../../google/gtest/gtest-1.6.0/lib"
)

ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
)

ADD_EXECUTABLE(lh_configure_test ${SRC_LIST})

TARGET_LINK_LIBRARIES(lh_configure_test
)

ADD_CUSTOM_COMMAND(
    TARGET lh_configure_test
    POST_BUILD
    COMMAND echo "${LH_CONFIGURE_TEST_SOURCE_DIR}"
    COMMAND echo "${LH_CONFIGURE_TEST_BINARY_DIR}"
)
