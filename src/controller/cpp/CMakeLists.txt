set(WEBOTS_CONTROLLER_CPP_SOURCES
  Accelerometer.cpp
  Altimeter.cpp
  Brake.cpp
  Camera.cpp
  Compass.cpp
  Connector.cpp
  Device.cpp
  Display.cpp
  DistanceSensor.cpp
  Emitter.cpp
  Field.cpp
  GPS.cpp
  Gyro.cpp
  InertialUnit.cpp
  Joystick.cpp
  Keyboard.cpp
  LED.cpp
  Lidar.cpp
  LightSensor.cpp
  Motion.cpp
  Motor.cpp
  Mouse.cpp
  Node.cpp
  Pen.cpp
  PositionSensor.cpp
  Proto.cpp
  Radar.cpp
  RangeFinder.cpp
  Receiver.cpp
  Robot.cpp
  Skin.cpp
  Speaker.cpp
  Supervisor.cpp
  TouchSensor.cpp
  VacuumGripper.cpp
)

add_library(webots_cpp_controller ${WEBOTS_CONTROLLER_CPP_SOURCES})
add_library(webots-controller::webots_cpp_controller ALIAS webots_cpp_controller)

if(WIN32)
  set_target_properties(webots_cpp_controller PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

target_include_directories(webots_cpp_controller
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include/controller/c
    ${CMAKE_SOURCE_DIR}/include/controller/cpp
)

target_link_libraries(webots_cpp_controller
  PUBLIC
    webots_controller
)

install(TARGETS webots_cpp_controller)
