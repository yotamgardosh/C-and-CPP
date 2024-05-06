cmake_minimum_required(VERSION 3.16)
project(ex3a_yotam181 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(ex3a_yotam181
        linked_list.c
        linked_list.h
        markov_chain.h
        markov_chain.c
        tweets_generator.c)
