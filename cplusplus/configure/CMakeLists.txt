CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(LH_CONFIGURE)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC")

AUX_SOURCE_DIRECTORY(src SOURCES)
SET(SRC_LIST
    ${SOURCES}
)

INCLUDE_DIRECTORIES(
    "./include"
    "../../../../../third/boost/boost-1.56.0/include"
    "../../../../../google/gtest/gtest-1.6.0/include"
)

ADD_LIBRARY(lh_configure ${SRC_LIST})

ADD_CUSTOM_COMMAND(
    TARGET lh_configure
    POST_BUILD
    COMMAND mkdir -p output
    COMMAND cp -r ${LH_CONFIGURE_SOURCE_DIR}/include output
    COMMAND cp -r lib output
)
