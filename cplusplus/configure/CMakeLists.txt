PROJECT(LH_CONFIGURE)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

SET(SRC_LIST
    "./src/configure.cpp"
    "./src/json_parser.cpp"
)

INCLUDE_DIRECTORIES(
    "./include"
    "../../../../third/boost/boost-1.56.0/include"
)

ADD_LIBRARY(lh_configure ${SRC_LIST})

ADD_CUSTOM_COMMAND(
    TARGET lh_configure
    POST_BUILD
    COMMAND mkdir -p output
    COMMAND cp -r ${LH_CONFIGURE_SOURCE_DIR}/include output
    COMMAND cp -r lib output
)
