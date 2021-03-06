cmake_minimum_required(VERSION 3.16)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server
        src/server.cpp

        src/Model/algorithms/A_Star.h src/lib/json.hpp src/Model/algorithms/Bresenham.h src/Controller/GameManager.cpp src/Controller/GameManager.h src/Model/Board/Board.cpp src/Model/Board/Board.h src/Model/Board/Cell.cpp src/Model/Board/Cell.h src/Model/Board/Entity.cpp src/Model/Board/Entity.h src/Model/Spectres/Spectre.cpp src/Model/Spectres/Spectre.h src/Model/SimpleEnemies/SpectralEye.cpp src/Model/SimpleEnemies/SpectralEye.h src/Model/SimpleEnemies/Mouse.cpp src/Model/SimpleEnemies/Mouse.h src/Model/SimpleEnemies/Chuchu.cpp src/Model/SimpleEnemies/Chuchu.h src/Model/Objects/Jarron.cpp src/Model/Objects/Jarron.h src/Model/Objects/Treasure.cpp src/Model/Objects/Treasure.h src/Model/SimpleEnemies/SimpleEnemy.cpp src/Model/SimpleEnemies/SimpleEnemy.h src/Model/Objects/Objeto.cpp src/Model/Objects/Objeto.h src/Model/Board/Position.cpp src/Model/Board/Position.h src/Model/Board/Jugador.cpp src/Model/Board/Jugador.h

        src/Model/Genetic/GeneticManager
        src/Model/Genetic/Spectrum
        src/Model/Genetic/Tools/Utility
        src/Model/Genetic/Population
        src/Model/Genetic/Population

        )
if(WIN32)
    target_link_libraries(Server wsock32 ws2_32)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Server Threads::Threads)