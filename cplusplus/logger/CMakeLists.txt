CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(LH_LOGGER)

SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(LIBRARY_OUTPUT_PATH ${LH_LOGGER_BINARY_DIR}/lib)
SET(CMAKE_CXX_FLAGS "-g -pipe -W -Wall -fPIC")

AUX_SOURCE_DIRECTORY(src SOURCES)
SET(SRC_LIST
    ${SOURCES}
)

INCLUDE_DIRECTORIES(
    "./include"
    "${LH_LOGGER_SOURCE_DIR}/../../../../loadinghorizion/configure/configure-1.0.0/include"
    "${LH_LOGGER_SOURCE_DIR}/../../../../third/boost/boost-1.56.0/include"
)

ADD_LIBRARY(lh_logger ${SRC_LIST})

ADD_CUSTOM_COMMAND(
    TARGET lh_logger
    POST_BUILD
    COMMAND mkdir -p output
    COMMAND cp -r ${LH_LOGGER_SOURCE_DIR}/include output
    COMMAND cp -r lib output
)
