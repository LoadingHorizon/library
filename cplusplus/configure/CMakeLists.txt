PROJECT(HL_CONFIGURE)
SET(SRC_PATH `pwd | sed "s/cmake_workspace/git_workspace/"`)
SET(SRC_LIST
    src/configure.cpp
    src/json_parser.cpp
    test/test_configure.cpp
)
#AUX_SOURCE_DIRECTORY(src SRC_DIR)
#AUX_SOURCE_DIRECTORY(test TEST_DIR)
#SET(SRC_LIST ${SRC_DIR} ${TEST_DIR})
INCLUDE_DIRECTORIES(
    "./include"
    "../../../../third-64/boost/include"
    "../../../../third-64/gtest/include"
)
LINK_DIRECTORIES(
    "../../../../third-64/boost/lib"
    "../../../../third-64/gtest/lib"
)
ADD_EXECUTABLE(test_configure ${SRC_LIST})
TARGET_LINK_LIBRARIES(test_configure
    libboost_atomic.a
    libboost_regex.a
    libgtest.a
    libgtest_main.a
    pthread
)
ADD_CUSTOM_TARGET(output
    mkdir bin &&
    cp test_configure ./bin &&
    cp -r ${SRC_PATH}/conf . &&
    mkdir output &&
    cp -r ./conf output &&
    cp -r ./bin output
)
ADD_CUSTOM_TARGET(removeall
    rm -rf bin &&
    rm -rf conf &&
    rm -rf output
)
