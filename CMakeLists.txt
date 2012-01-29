CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(Tower-Defence CXX)

ADD_DEFINITIONS(-Wall -g)

file(GLOB SourceFiles ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HeaderFiles ${CMAKE_SOURCE_DIR}/src/*.h)

set(SourceFiles ${SourceFiles})
set(HeadereFiles ${HeaderFiles})

#Testing for finding a 3rd party libraries in windows
FIND_PATH(SDL_INCLUDE_DIR SDL.h
  HINTS
  $ENV{SDLDIR}
  PATH_SUFFIXES include/SDL include
  PATHS
  ${CMAKE_SOURCE_DIR}/deps/SDL
)

FIND_LIBRARY(SDL_LIBRARY_TEMP 
  NAMES SDL SDL-1.1 SDLmain
  HINTS
  $ENV{SDLDIR}
  PATH_SUFFIXES lib64 lib/x64
  PATHS
  ${CMAKE_SOURCE_DIR}/deps/SDL
)
FIND_LIBRARY(SDLMAIN_LIBRARY 
  NAMES SDLmain SDLmain-1.1
  HINTS
  $ENV{SDLDIR}
  PATH_SUFFIXES lib64 lib/x64
  PATHS
  ${CMAKE_SOURCE_DIR}/deps/SDL
)
# End of testing

find_package ( SDL REQUIRED )

if( NOT SDL_FOUND )
     message( FATAL_ERROR "ERROR: SDL not found" )
else()
     message( STATUS "SDL found" )
endif( NOT SDL_FOUND )

#INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/)

ADD_EXECUTABLE(Tower-Defence ${SourceFiles} ${HeaderFiles})

set_target_properties(Tower-Defence PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
        TARGET_LINK_LIBRARIES(Tower-Defence SDL)
elseif (UNIX)
        TARGET_LINK_LIBRARIES(Tower-Defence)
endif()
