PROJECT(HL_CONFIGURE)
SET(SRC_PATH `pwd | sed "s/cmake_workspace/git_workspace/"`)
SET(SRC_LIST
    "../../configure/src/configure.cpp"
    "../../configure/src/json_parser.cpp"
    "../src/logger.cpp"
    "./test_logger.cpp"
)
#AUX_SOURCE_DIRECTORY(src SRC_DIR)
#AUX_SOURCE_DIRECTORY(test TEST_DIR)
#SET(SRC_LIST ${SRC_DIR} ${TEST_DIR})
INCLUDE_DIRECTORIES(
    "../../configure/include"
    "../include"
    "../../../../../third-64/boost/include"
    "../../../../../third-64/gtest/include"
)
LINK_DIRECTORIES(
    "../../../../../third-64/boost/lib"
    "../../../../../third-64/gtest/lib"
)
ADD_DEFINITIONS(
    -Dprivate=public
    -Dproctect=public
)
ADD_EXECUTABLE(test_logger ${SRC_LIST})
TARGET_LINK_LIBRARIES(test_logger
    libboost_atomic.a
    libboost_regex.a
    libgtest.a
    libgtest_main.a
    pthread
)
ADD_CUSTOM_TARGET(logger
    mkdir -p bin &&
    mkdir -p output &&
    cp test_logger ./bin &&
    cp -r ${SRC_PATH}/../conf . &&
    cp -r ./conf output &&
    cp -r ./bin output
)
ADD_CUSTOM_TARGET(clear
    rm -rf bin &&
    rm -rf conf &&
    rm -rf output
)
