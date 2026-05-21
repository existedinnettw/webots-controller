cmake_minimum_required(VERSION 3.23)
project(webots_controller LANGUAGES C CXX)

option(WEBOTS_CONTROLLER_NO_PLUGINS "Disable runtime plugin loading (dlopen/LoadLibrary paths)." ON)

add_subdirectory(src/controller)
