PROJECT(LH_CONFIGURE)

INCLUDE_DIRECTORIES(
    "./include"
)
SET(SRC_LIST
    ./src/configure.cpp
    ./src/json_parser.cpp
)

ADD_LIBRARY(lh_configure ${SRC_LIST})
