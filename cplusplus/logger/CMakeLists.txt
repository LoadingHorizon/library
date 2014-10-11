PROJECT(LH_LOGGER)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

SET(SRC_LIST
    "./src/logger.cpp"
)

INCLUDE_DIRECTORIES(
    "./include"
    "../../../../loadinghorizion/configure/configure-1.0.0/include"
    "../../../../third/boost/boost-1.56.0/include"
)

ADD_LIBRARY(lh_logger ${SRC_LIST})

ADD_CUSTOM_COMMAND(
    TARGET lh_logger
    POST_BUILD
    COMMAND mkdir -p output
    COMMAND cp -r ${LH_LOGGER_SOURCE_DIR}/include output
    COMMAND cp -r lib output
)
