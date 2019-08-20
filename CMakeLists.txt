cmake_minimum_required(VERSION 3.0)

project(win_ble)

add_executable(win_ble src/crimson_ble_win.cpp)
set_target_properties(win_ble PROPERTIES CXX_STANDARD 17)

# for co_await function
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /await")
