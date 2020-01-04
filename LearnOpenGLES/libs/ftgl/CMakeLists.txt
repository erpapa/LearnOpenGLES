cmake_minimum_required(VERSION 3.10)
project(ftgl)

set(TARGET ftgl)
set(PUBLIC_HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PUBLIC_HDRS 
        ${PUBLIC_HDR_DIR}/ftgl.h
        ${PUBLIC_HDR_DIR}/Point.h
        ${PUBLIC_HDR_DIR}/Contour.h
        ${PUBLIC_HDR_DIR}/Vectoriser.h
)
set(SRCS 
        ${PUBLIC_HDR_DIR}/Point.cpp
        ${PUBLIC_HDR_DIR}/Contour.cpp
        ${PUBLIC_HDR_DIR}/Vectoriser.cpp
)

include_directories(${PUBLIC_HDR_DIR})
add_library(${TARGET} STATIC ${PUBLIC_HDRS} ${SRCS})

target_link_libraries(ftgl freetype2 poly2tri)