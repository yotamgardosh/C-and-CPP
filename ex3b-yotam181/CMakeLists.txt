cmake_minimum_required(VERSION 3.16)
project(ex3b_yotam181 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex3b_yotam181
        linked_list.c
        linked_list.h
        markov_chain.c
        markov_chain.h
#        snakes_and_ladders.c
        tweets_generator.c
        )
