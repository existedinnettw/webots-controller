cmake_minimum_required(VERSION 3.21)
project(webots_controller VERSION 0.1.0 LANGUAGES C)

option(WEBOTS_CONTROLLER_NO_PLUGINS "Disable runtime plugin loading (dlopen/LoadLibrary paths)." ON)

add_subdirectory(src/controller)
