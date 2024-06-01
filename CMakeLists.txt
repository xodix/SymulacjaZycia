cmake_minimum_required (VERSION 3.8)

project("SymulacjaZycia")

set(CMAKE_CXX_STANDARD 17)

# Make project compile with optimizations on both Windows and Linux.
if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    endif()
endif()

# MAIN EXECUTABLE
add_executable(SymulacjaZycia "SymulacjaZycia.cpp" "Headers/Rows.h" "Headers/Organism.h" "Headers/Grid.h" "Headers/Vicinity.h")

# TESTS
add_executable(TestRows "Tests/TestRows.cpp" "Headers/Rows.h" "Tests/TestingUtilities.h")


add_executable(TestReadWrite "Tests/TestReadWrite.cpp" "Headers/Vicinity.h" "Headers/Rows.h" "Headers/Organism.h" "Headers/Grid.h" "Tests/TestingUtilities.h")

enable_testing()

add_test(
    NAME TestRows
    COMMAND $<TARGET_FILE:TestRows>
)

add_test(
    NAME TestReadWrite
    COMMAND $<TARGET_FILE:TestReadWrite>
)
