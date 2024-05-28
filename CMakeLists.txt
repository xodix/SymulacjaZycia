# CMakeList.txt : CMake project for SymulacjaZycia, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project("SymulacjaZycia")

set(CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
add_executable(SymulacjaZycia "SymulacjaZycia.cpp" "Rows.h" "Organism.h" "Grid.h" "Vicinity.h")


# TODO: Add tests and install targets if needed.
