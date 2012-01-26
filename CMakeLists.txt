CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(Tower-Defence CXX)

ADD_DEFINITIONS(-Wall -g)

file(GLOB SourceFiles ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HeaderFiles ${CMAKE_SOURCE_DIR}/src/*.h)

set(SourceFiles ${SourceFiles})
set(HeadereFiles ${HeaderFiles})

#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/)

ADD_EXECUTABLE(Tower-Defence ${SourceFiles} ${HeaderFiles})

set_target_properties(Tower-Defence PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#if(WIN32)
#        TARGET_LINK_LIBRARIES(Tower-Defence)
#elseif (UNIX)
#        TARGET_LINK_LIBRARIES(Tower-Defence)
#endif()
