cmake_minimum_required(VERSION 3.10)
project(tinyexr)

set(TARGET tinyexr)
set(PUBLIC_HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PUBLIC_HDRS ${PUBLIC_HDR_DIR}/tinyexr.h)
set(SRCS tinyexr.cc)

include_directories(${PUBLIC_HDR_DIR})
add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})