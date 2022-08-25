cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(pixelate VERSION 0.2)

IF(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5.1 REQUIRED network audio graphics window system)

add_executable(pixelate src/main.cpp)
target_compile_options(pixelate PUBLIC -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion)
target_include_directories(pixelate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${SFML_INCLUDE_DIR})
target_link_libraries(pixelate PUBLIC ${SFML_LIBRARIES} sfml-graphics sfml-system sfml-window)

