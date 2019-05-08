cmake_minimum_required(VERSION 3.14)
project(SFMLDODGame)

set(CMAKE_CXX_STANDARD 17)
set(OPTIMIZATION_FLAGS "-O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -Wc++17-extensions -framework GLUT -framework sfml-audio  -framework sfml-graphics -framework sfml-window -framework sfml-system")
file(COPY assets DESTINATION ./)

add_executable(SFMLDODGame src/main.cpp src/core/game.cpp src/core/game.hpp src/core/entities/game_object.cpp src/core/entities/game_object.hpp src/core/functions/functions.hpp)