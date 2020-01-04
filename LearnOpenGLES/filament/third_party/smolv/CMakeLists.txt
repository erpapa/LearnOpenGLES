cmake_minimum_required(VERSION 3.10)
project(smolv)

set(TARGET smolv)
set(PUBLIC_HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PUBLIC_HDRS ${PUBLIC_HDR_DIR}/smolv.h)
set(SRCS smolv.cpp)

include_directories(${PUBLIC_HDR_DIR})
add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})