CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(Tower-Defence CXX)

ADD_DEFINITIONS(-Wall -g -O)

file(GLOB SourceFiles ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB HeaderFiles ${CMAKE_SOURCE_DIR}/src/*.h)

# Gamelogic
file(GLOB GameLogicSourceFiles ${CMAKE_SOURCE_DIR}/src/GameLogic/*.cpp)
file(GLOB GameLogicHeaderFiles ${CMAKE_SOURCE_DIR}/src/GameLogic/*.h)

# Renderer
file(GLOB RendererSourceFiles ${CMAKE_SOURCE_DIR}/src/Renderer/*.cpp)
file(GLOB RendererHeaderFiles ${CMAKE_SOURCE_DIR}/src/Renderer/*.h)

# EventHandler
file(GLOB EventHandlerSourceFiles ${CMAKE_SOURCE_DIR}/src/EventHandler/*.cpp)
file(GLOB EventHandlerHeaderFiles ${CMAKE_SOURCE_DIR}/src/EventHandler/*.h)

# InputHandler
file(GLOB InputHandlerSourceFiles ${CMAKE_SOURCE_DIR}/src/InputHandler/*.cpp)
file(GLOB InputHandlerHeaderFiles ${CMAKE_SOURCE_DIR}/src/InputHandler/*.h)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/utils )
#set(CMAKE_EXE_LINKER_FLAGS "")

set(SourceFiles ${SourceFiles} ${GameLogicSourceFiles} ${RendererSourceFiles} ${EventHandlerSourceFiles} ${InputHandlerSourceFiles} )
set(HeadereFiles ${HeaderFiles} ${GameLogicHeaderFiles} ${RendererSourceFiles} ${EventHandlerHeaderFiles} ${InputHandlerHeaderFiles} )

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
