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

add_executable(SFMLDODGame src/main.cpp src/core/debug/fps_counter.hpp src/core/resources/resource_holder.hpp src/game/resource_definitions.hpp src/game/screens/load_screen.hpp src/game/context.hpp src/core/utils.hpp src/core/resources/animation.hpp src/game/tables.hpp src/headers.hpp src/game/defines.hpp src/game/screens/game_screen.hpp src/game/screens/loading_screen.hpp src/game/screens/title_screen.hpp src/game/screens/game_screen_tile.hpp)