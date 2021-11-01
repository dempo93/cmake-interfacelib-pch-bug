cmake_minimum_required(VERSION 3.21)
project(cmake_bug LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(COMPILE_WITH_WORKAROUND off)

add_library(lib1 OBJECT)
target_sources(lib1 PRIVATE ${CMAKE_SOURCE_DIR}/lib1/lib1.h ${CMAKE_SOURCE_DIR}/lib1/lib1.cpp)
target_precompile_headers(lib1 PRIVATE ${CMAKE_SOURCE_DIR}/lib1/precompiledheaders.h)
target_include_directories(lib1 PUBLIC ${CMAKE_SOURCE_DIR}/lib1)
add_library(lib1-interface INTERFACE)
if(NOT COMPILE_WITH_WORKAROUND)
    set(LIB1_TARGET_OBJECTS $<TARGET_OBJECTS:lib1>)
else()
    set(LIB1_TARGET_OBJECTS $<FILTER:$<TARGET_OBJECTS:lib1>,EXCLUDE,.*\\.gch>)
endif()
target_link_libraries(lib1-interface INTERFACE lib1 ${LIB1_TARGET_OBJECTS})
file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/debug CONTENT ${LIB1_TARGET_OBJECTS})


add_executable(cmake_bug main.cpp)
target_precompile_headers(cmake_bug REUSE_FROM lib1)
target_link_libraries(cmake_bug PRIVATE lib1-interface)
