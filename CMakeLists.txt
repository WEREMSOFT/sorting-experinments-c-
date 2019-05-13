cmake_minimum_required(VERSION 3.14)
project(SFMLDODGame)

set(CMAKE_CXX_STANDARD 17)
set(OPTIMIZATION_FLAGS "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -Wc++17-extensions -framework GLUT -framework sfml-audio  -framework sfml-graphics -framework sfml-window -framework sfml-system")
file(COPY assets DESTINATION ./)

add_executable(SFMLDODGame src/main.cpp src/game/game.hpp src/core/entities/game_object.hpp src/core/debug/fps_counter.hpp src/core/resources/resource_holder.hpp src/game/resource_definitions.hpp src/game/load_screen.hpp src/context.hpp src/core/utils.hpp src/core/resources/animation.hpp src/game/characters/cat.hpp src/game/characters/cat.hpp src/game/tables.hpp)