PROJECT(LH_LOGGER)

SET(SRC_LIST
    "./src/logger.cpp"
)

INCLUDE_DIRECTORIES(
    "../configure/include"
    "./include"
)

ADD_LIBRARY(lh_logger ${SRC_LIST})
