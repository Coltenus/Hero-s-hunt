cmake_minimum_required(VERSION 3.23)
project(Hero-s-hunt)

set(CMAKE_CXX_STANDARD 20)

set(NO_CONSOLE_FLAGS ", -Wl,--subsystem,windows")
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -fexceptions -static -static-libgcc -static-libstdc++ -g -static-libgcc -static-libstdc++ -L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}${NO_CONSOLE_FLAGS}" )
if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
endif(DEBUG)

set(PROJECT_HEADERS
        game5/include/audio.h
        game5/include/characters.h
        game5/include/chooseRoom.h
        game5/include/common.h
        game5/include/info.h
        game5/include/items.h
        game5/include/rooms.h
        )
set(PROJECT_SOURCES
        game5/main.cpp
        game5/include/audio.cpp
        game5/include/abilities.cpp
        game5/include/chooseRoom.cpp
        game5/include/info.cpp
        game5/include/items.cpp
        game5/include/npcs.cpp
        game5/include/pcs.cpp
        game5/include/rooms.cpp
        )

add_executable(Hero-s-hunt ${PROJECT_SOURCES} ${PROJECT_HEADERS})

find_package(raylib CONFIG REQUIRED)
target_include_directories(Hero-s-hunt PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(Hero-s-hunt PRIVATE ${raylib_LIBRARIES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()