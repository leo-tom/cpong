project(cpong C)
set (CMAKE_BUILD_TYPE=Release)
cmake_minimum_required(VERSION 3.0)
add_executable(cpong main.c output.c play.c)
link_directories(/usr/lib)
target_link_libraries(cpong ncurses m)
install(TARGETS cpong RUNTIME DESTINATION bin)
