#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "html_robot_window_private.h"
#include "remote_control_private.h"
#include "robot_window_private.h"
#include "device_private.h"

#include <webots/radio.h>

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

static void radio_plugins_disabled(const char *function_name) {
  fprintf(stderr, "Error: %s(): radio support is unavailable because plugins are disabled.\n", function_name);
}

typedef struct {
  int length;
  char *body;
  char *destination;
} NoPluginsRadioMessage;

void wb_radio_init(WbDevice *d) {
  (void)d;
}

WbRadioMessage wb_radio_message_new(int length, const char *body, const char *destination) {
  if (length < 0 || (length > 0 && body == NULL) || destination == NULL) {
    fprintf(stderr, "Error: %s(): invalid argument.\n", __FUNCTION__);
    return NULL;
  }

  NoPluginsRadioMessage *msg = malloc(sizeof(NoPluginsRadioMessage));
  if (msg == NULL)
    return NULL;

  msg->length = length;
  msg->body = NULL;
  msg->destination = NULL;

  if (length > 0) {
    msg->body = malloc((size_t)length);
    if (msg->body == NULL) {
      free(msg);
      return NULL;
    }
    memcpy(msg->body, body, (size_t)length);
  }

  msg->destination = malloc(strlen(destination) + 1);
  if (msg->destination == NULL) {
    free(msg->body);
    free(msg);
    return NULL;
  }
  strcpy(msg->destination, destination);
  return msg;
}

void wb_radio_message_delete(WbRadioMessage msg) {
  NoPluginsRadioMessage *message = (NoPluginsRadioMessage *)msg;
  if (message == NULL)
    return;
  free(message->body);
  free(message->destination);
  free(message);
}

const char *wb_radio_message_get_destination(WbRadioMessage msg) {
  const NoPluginsRadioMessage *message = (const NoPluginsRadioMessage *)msg;
  return message ? message->destination : NULL;
}

int wb_radio_message_get_length(WbRadioMessage msg) {
  const NoPluginsRadioMessage *message = (const NoPluginsRadioMessage *)msg;
  return message ? message->length : 0;
}

const char *wb_radio_message_get_body(WbRadioMessage msg) {
  const NoPluginsRadioMessage *message = (const NoPluginsRadioMessage *)msg;
  return message ? message->body : NULL;
}

void wb_radio_enable(WbDeviceTag tag, int sampling_period) {
  (void)tag;
  (void)sampling_period;
  radio_plugins_disabled(__FUNCTION__);
}

void wb_radio_disable(WbDeviceTag tag) {
  (void)tag;
  radio_plugins_disabled(__FUNCTION__);
}

void wb_radio_set_address(WbDeviceTag tag, const char *address) {
  (void)tag;
  (void)address;
  radio_plugins_disabled(__FUNCTION__);
}

const char *wb_radio_get_address(WbDeviceTag tag) {
  (void)tag;
  radio_plugins_disabled(__FUNCTION__);
  return NULL;
}

void wb_radio_set_frequency(WbDeviceTag tag, double hz) {
  (void)tag;
  (void)hz;
  radio_plugins_disabled(__FUNCTION__);
}

double wb_radio_get_frequency(WbDeviceTag tag) {
  (void)tag;
  radio_plugins_disabled(__FUNCTION__);
  return NAN;
}

void wb_radio_set_channel(WbDeviceTag tag, int channel) {
  (void)tag;
  (void)channel;
  radio_plugins_disabled(__FUNCTION__);
}

int wb_radio_get_channel(WbDeviceTag tag) {
  (void)tag;
  radio_plugins_disabled(__FUNCTION__);
  return -1;
}

void wb_radio_set_bitrate(WbDeviceTag tag, int bits_per_second) {
  (void)tag;
  (void)bits_per_second;
  radio_plugins_disabled(__FUNCTION__);
}

int wb_radio_get_bitrate(WbDeviceTag tag) {
  (void)tag;
  radio_plugins_disabled(__FUNCTION__);
  return 0;
}

void wb_radio_set_rx_sensitivity(WbDeviceTag tag, double dBm) {
  (void)tag;
  (void)dBm;
  radio_plugins_disabled(__FUNCTION__);
}

double wb_radio_get_rx_sensitivity(WbDeviceTag tag) {
  (void)tag;
  radio_plugins_disabled(__FUNCTION__);
  return NAN;
}

void wb_radio_set_tx_power(WbDeviceTag tag, double dBm) {
  (void)tag;
  (void)dBm;
  radio_plugins_disabled(__FUNCTION__);
}

double wb_radio_get_tx_power(WbDeviceTag tag) {
  (void)tag;
  radio_plugins_disabled(__FUNCTION__);
  return NAN;
}

void wb_radio_set_callback(WbDeviceTag tag, void (*callback)(const WbRadioEvent)) {
  (void)tag;
  (void)callback;
  radio_plugins_disabled(__FUNCTION__);
}

WbDeviceTag wb_radio_event_get_radio(const WbRadioEvent event) {
  (void)event;
  radio_plugins_disabled(__FUNCTION__);
  return 0;
}

char *wb_radio_event_get_data(const WbRadioEvent event) {
  (void)event;
  radio_plugins_disabled(__FUNCTION__);
  return NULL;
}

int wb_radio_event_get_data_size(const WbRadioEvent event) {
  (void)event;
  radio_plugins_disabled(__FUNCTION__);
  return 0;
}

char *wb_radio_event_get_emitter(const WbRadioEvent event) {
  (void)event;
  radio_plugins_disabled(__FUNCTION__);
  return NULL;
}

double wb_radio_event_get_rssi(const WbRadioEvent event) {
  (void)event;
  radio_plugins_disabled(__FUNCTION__);
  return NAN;
}

void wb_radio_send(WbDeviceTag tag, const WbRadioMessage msg, double delay) {
  (void)tag;
  (void)msg;
  (void)delay;
  radio_plugins_disabled(__FUNCTION__);
}
