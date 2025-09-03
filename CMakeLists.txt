# Preamble ###
#

cmake_minimum_required(VERSION 3.24.0)
project(CFTSolver)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Fields)
#add_subdirectory(Source/EulerLagrange)
#add_subdirectory(Source/Rendering)



add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp)
#target_link_libraries(${CMAKE_CURRENT_SOURCE_DIR} FieldsLib) 


