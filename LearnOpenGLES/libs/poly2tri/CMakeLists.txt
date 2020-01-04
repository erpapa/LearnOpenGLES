cmake_minimum_required(VERSION 3.10)
project(poly2tri)

set(TARGET poly2tri)
set(PUBLIC_HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PUBLIC_HDRS 
        ${PUBLIC_HDR_DIR}/poly2tri.h
        ${PUBLIC_HDR_DIR}/common/*.h
        ${PUBLIC_HDR_DIR}/sweep/*.h
)
set(SRCS 
        common/*.cc
        sweep/*.cc
)

include_directories(${PUBLIC_HDR_DIR})
add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})

target_link_libraries(poly2tri freetype2)