#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "app.h"
#include "modbus.h"
#include "ui.h"
#include "sensor.h"
#include "uart.h"
#include "display.h"
#include "store_data.h"
#include "gpio.h"

Config initial_config(){
  Config init;
  init.kp = 20.0;
  init.ki = 0.1;
  init.kd = 100.0;
  init.mode = TERMINAL;
  init.temp = 40.0;

  return init;
}

void start_app(Config app_config){
  initialize_uart();
  initialize_gpio();

  // send_system_status(ON);
  // send_control_mode(app_config.mode);
}

void shut_down(){
  // turn_off_system();
  //close_csv_file();
}

void turn_off_system(){
   turn_off_fan_and_resistence();
   send_system_status(OFF);
   print_system_off();
}

void app_main_loop(Config app_config){
  // printf("cade??\n");
  float te = get_external_temperature();
  printf("te: %.2f\n", te);
  // float ti = request_internal_temperature();
  // printf("te: %.2f\n", ti);
  // float tr = get_reference_temperature(app_config);
  // printf("te: %.2f\n", tr);
  // print_sensors_data_on_display(app_config.mode, ti, te, tr);
  
  // request_user_commands(app_config);

}

float get_reference_temperature(Config app_config){
  switch(app_config.mode){
    case TERMINAL:
      return app_config.temp;
    case POTENTIOMETER:
      return request_potentiometer_temperature();
    case REFLOW_CURVE:
      // TODO: Implementar leitura do arquivo csv
      return app_config.temp;
  }
  return app_config.temp;
}

float request_internal_temperature(){
  float ti;
  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  unsigned char *response = malloc(RECEIVE_DATA_SIZE);

  message[1] = REQUEST_TEMP;
  send_modbus_message(message, MESSAGE_REQUEST_SIZE);

  response = receive_modbus_message(REQUEST_TEMP);

  if(option_error(REQUEST_TEMP, response[0])){
    return request_internal_temperature();
  }

  memcpy(&ti, &response[1], 4);

  return ti;

}

float request_potentiometer_temperature(){
  float tr;
  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  unsigned char *response = malloc(RECEIVE_DATA_SIZE);
  message[1] = REQUEST_TEMP_POT;

  send_modbus_message(message, MESSAGE_REQUEST_SIZE);
  response = receive_modbus_message(REQUEST_TEMP_POT);

  if(option_error(REQUEST_TEMP_POT, response[0])){
    return request_potentiometer_temperature();
  }

  memcpy(&tr, &response[1], 4);

  return tr;
}

void request_user_commands(Config app_config){
  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  unsigned char *response = malloc(MESSAGE_RECEIVED_SIZE);

  message[1] = READ_USER_CMD;
  send_modbus_message(message, MESSAGE_REQUEST_SIZE);

  response = receive_modbus_message(READ_USER_CMD);
  printf("[OPÇÃO RECEBIDA] %x\n", response[0]);

  switch(response[0]){
    case TURN_ON:
      printf("on\n");
      send_system_status(ON);
      break;
    case TURN_OFF:
      printf("off\n");
      turn_off_system();
      break;
    case ACTIVATE_POTENTIOMETER:
      printf("potentiometer\n");
      app_config.mode = POTENTIOMETER;
      send_control_mode(POTENTIOMETER);
      break;
    case ACTIVATE_REFLOW_CURVE:
      printf("reflow\n");
      app_config.mode = REFLOW_CURVE;
      send_control_mode(REFLOW_CURVE);
      break;
  }
  
}

void send_control_signal(int control_signal){
  unsigned char *message = malloc(MESSAGE_SEND_SIGNAL_SIZE + 1);
  message[0] = SEND_CTRL_SIG;

  // TODO: Adicionar sinal de controle a mensagem

  send_modbus_message(message, MESSAGE_SYSTEM_STATE_SIZE);
}

void send_reference_signal(int reference_signal){
  unsigned char *message = malloc(MESSAGE_SEND_SIGNAL_SIZE + 1);
  message[0] = SEND_REF_SIG;

  // TODO: Adicionar sinal de referencia a mensagem

  send_modbus_message(message, MESSAGE_SYSTEM_STATE_SIZE);
}

void send_system_status(OnOffState state){
  unsigned char *message = malloc(MESSAGE_SYSTEM_STATE_SIZE + 1);
  message[0] = SEND_SYSTEM_STATE;
  message[1] = state;

  send_modbus_message(message, MESSAGE_SYSTEM_STATE_SIZE);
  receive_modbus_message(SEND_SYSTEM_STATE);
}

void send_control_mode(ControlMode state){
  unsigned char *message = malloc(MESSAGE_SYSTEM_STATE_SIZE + 1);
  message[0] = SEND_CTRL_MODE;
  message[1] = state;

  if(state == TERMINAL){
    message[1] = REFLOW_CURVE;
  }

  send_modbus_message(message, MESSAGE_SYSTEM_STATE_SIZE);
  receive_modbus_message(SEND_CTRL_MODE);
}



int option_error(int opt_expected, int opt_received) {
  if (opt_expected == opt_received)
    return 0;

  show_error("Opção", opt_expected, opt_received);
  return 1;
}
