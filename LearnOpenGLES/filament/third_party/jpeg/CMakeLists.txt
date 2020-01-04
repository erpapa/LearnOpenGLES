cmake_minimum_required(VERSION 3.10)
project(jpeg)

set(TARGET jpeg)
set(PUBLIC_HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PUBLIC_HDRS ${PUBLIC_HDR_DIR}/*.h)
set(SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${PUBLIC_HDR_DIR})
add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})