cmake_minimum_required(VERSION 3.16)
project(ex4_yotam181)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(main
#        main.cpp
        Matrix.cpp
        Activation.cpp
        Dense.cpp
        MlpNetwork.cpp
#        "oh_tests_const (1).cpp"
        "oh_tests_exceptions (2).cpp"
        )

add_executable(presubmit
        Matrix.cpp
        Activation.cpp
        Dense.cpp
        MlpNetwork.cpp
        presubmit.cpp)