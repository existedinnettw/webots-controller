#include <stdbool.h>

#include "html_robot_window_private.h"
#include "remote_control_private.h"
#include "robot_window_private.h"

#include <stddef.h>

void robot_window_init(const char *library_name) {
  (void)library_name;
}

bool robot_window_is_initialized() {
  return false;
}

const char *robot_window_get_last_error() {
  return "plugins disabled";
}

void robot_window_pre_update_gui() {
}

void robot_window_update_gui() {
}

void robot_window_read_sensors() {
}

void robot_window_write_actuators() {
}

void robot_window_cleanup() {
}

void robot_window_show() {
}

void *wb_robot_window_custom_function(void *args) {
  (void)args;
  return NULL;
}

bool wb_robot_window_load_library(const char *name) {
  (void)name;
  return false;
}

void html_robot_window_init() {
}

void html_robot_window_step(int step) {
  (void)step;
}

void html_robot_window_cleanup() {
}

void remote_control_init(const char *library_name) {
  (void)library_name;
}

void remote_control_cleanup() {
}

bool remote_control_is_initialized() {
  return false;
}

const char *remote_control_get_last_error() {
  return "plugins disabled";
}

bool remote_control_start(const char *args) {
  (void)args;
  return false;
}

void remote_control_stop() {
}

void remote_control_stop_actuators() {
}

bool remote_control_has_failed() {
  return false;
}

void remote_control_step(int duration) {
  (void)duration;
}

WbRequest *remote_control_handle_messages(WbRequest *r) {
  return r;
}

void remote_control_handle_one_message(WbRequest *r, WbDeviceTag tag) {
  (void)r;
  (void)tag;
}

bool remote_control_is_function_defined(const char *function_name) {
  (void)function_name;
  return false;
}

void *wb_remote_control_custom_function(void *arg) {
  (void)arg;
  return NULL;
}
