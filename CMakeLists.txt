CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(Tower-Defence CXX)

ADD_DEFINITIONS(-Wall -g)

file(GLOB SourceFiles ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HeaderFiles ${CMAKE_SOURCE_DIR}/src/*.h)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/utils )

set(SourceFiles ${SourceFiles})
set(HeadereFiles ${HeaderFiles})

find_package ( SFML REQUIRED )

if( NOT SFML_FOUND )
     message( FATAL_ERROR "ERROR: SFML not found" )
else()
     message( STATUS "SFML found" )
endif( NOT SFML_FOUND )

ADD_EXECUTABLE(Tower-Defence ${SourceFiles} ${HeaderFiles})

set_target_properties(Tower-Defence PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
        TARGET_LINK_LIBRARIES(Tower-Defence sfml-system sfml-window sfml-graphics)
elseif (UNIX)
        TARGET_LINK_LIBRARIES(Tower-Defence sfml-system sfml-window sfml-graphics)
endif()
