set(WEBOTS_HEADERS_ROOT "${CMAKE_SOURCE_DIR}/include/controller/c")
set(WEBOTS_INCLUDE_ROOT "${CMAKE_SOURCE_DIR}/include")
set(WEBOTS_STB_DIR "${CMAKE_SOURCE_DIR}/src/stb")

if(NOT EXISTS "${WEBOTS_HEADERS_ROOT}/webots")
  message(FATAL_ERROR "Missing required repo path: ${WEBOTS_HEADERS_ROOT}/webots")
endif()

if(NOT EXISTS "${WEBOTS_STB_DIR}/stb_image.h")
  message(FATAL_ERROR "Missing required repo path: ${WEBOTS_STB_DIR}/stb_image.h")
endif()

set(WEBOTS_CONTROLLER_C_CORE_SOURCES
  abstract_camera.c
  accelerometer.c
  altimeter.c
  ansi_codes.c
  base64.c
  brake.c
  camera.c
  compass.c
  connector.c
  console.c
  default_robot_window.c
  device.c
  display.c
  distance_sensor.c
  emitter.c
  file.c
  g_image.c
  g_pipe.c
  gps.c
  gyro.c
  image.c
  inertial_unit.c
  joystick.c
  keyboard.c
  led.c
  lidar.c
  light_sensor.c
  microphone.c
  motion.c
  motor.c
  mouse.c
  node.c
  pen.c
  percent.c
  position_sensor.c
  radar.c
  range_finder.c
  receiver.c
  request.c
  robot.c
  scheduler.c
  sha1.c
  skin.c
  speaker.c
  string.c
  supervisor.c
  system.c
  tcp_client.c
  touch_sensor.c
  vacuum_gripper.c
)

set(WEBOTS_CONTROLLER_C_PLUGIN_SOURCES
  dynamic_library.c
  html_robot_window.c
  radio.c
  remote_control.c
  robot_window.c
)

set(WEBOTS_CONTROLLER_C_STUB_SOURCES
  no_plugins_stubs.c
)

set(WEBOTS_CONTROLLER_C_SOURCES ${WEBOTS_CONTROLLER_C_CORE_SOURCES})
if(WEBOTS_CONTROLLER_NO_PLUGINS)
  list(APPEND WEBOTS_CONTROLLER_C_SOURCES ${WEBOTS_CONTROLLER_C_STUB_SOURCES})
else()
  list(APPEND WEBOTS_CONTROLLER_C_SOURCES ${WEBOTS_CONTROLLER_C_PLUGIN_SOURCES})
endif()

# add_library without STATIC/SHARED follows BUILD_SHARED_LIBS automatically in cmake.
add_library(webots_controller ${WEBOTS_CONTROLLER_C_SOURCES})
add_library(webots-controller::webots_controller ALIAS webots_controller)

if(WIN32)
  set_target_properties(webots_controller PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_include_directories(webots_controller
  PRIVATE
    ${WEBOTS_HEADERS_ROOT}
    ${WEBOTS_INCLUDE_ROOT}
    ${WEBOTS_STB_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(webots_controller PRIVATE LIBCONTROLLER_VERSION="custom")
if(WEBOTS_CONTROLLER_NO_PLUGINS)
  target_compile_definitions(webots_controller PUBLIC WEBOTS_CONTROLLER_NO_PLUGINS=1)
endif()

if(UNIX)
  target_link_libraries(webots_controller PRIVATE m)
  if(NOT APPLE)
    target_link_libraries(webots_controller PRIVATE pthread rt)
    if(NOT WEBOTS_CONTROLLER_NO_PLUGINS)
      target_link_libraries(webots_controller PRIVATE dl)
    endif()
  endif()
endif()

install(TARGETS webots_controller)
