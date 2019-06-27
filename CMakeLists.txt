cmake_minimum_required(VERSION 3.7.2)
project(SFMLDODGame)


set(OPTIMIZATION_FLAGS "")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -Wc++17-extensions -framework GLUT -framework sfml-graphics -framework sfml-window -framework sfml-system -v")
else()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -std=c++11 -I/home/pi/documents/sfml-pi/include -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread")
endif()
file(COPY assets DESTINATION ./)


FILE(GLOB sources src/*)

#FILE(GLOB external_includes libs/include/*)
FILE(GLOB lib_sources libs/src/spine/*)
#
#set(HEADER_FILES ${external_includes})

add_executable(SFMLDODGame ${sources} ${lib_sources})
target_include_directories(SFMLDODGame PRIVATE ./libs/include)
