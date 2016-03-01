cmake_minimum_required(VERSION 3.3)
project(dsp_smqt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
set(SOURCE_FILES ${SOURCE_FILES}
        ${CMAKE_SOURCE_DIR}/adspImage.h
        ${CMAKE_SOURCE_DIR}/adspImage.cpp
        ${CMAKE_SOURCE_DIR}/Image.h
        ${CMAKE_SOURCE_DIR}/Image.cpp)

add_executable(dsp_smqt ${SOURCE_FILES})

set(OpenCV_FOUND 1)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(dsp_smqt ${OpenCV_LIBS}) # replace binary_name