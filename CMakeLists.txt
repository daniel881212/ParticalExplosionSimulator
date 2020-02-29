cmake_minimum_required(VERSION 3.15)
project(ParticalExplosionSimulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(ParticalExplosionSimulator main.cpp Screen.h Screen.cpp Particle.cpp Particle.h Swarm.cpp Swarm.h)

include_directories("/Users/chenpoyu/clionprojects/particalexplosionsimulator/include")
target_link_libraries(ParticalExplosionSimulator "/usr/local/lib/libSDL2.dylib")

