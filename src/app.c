#include "app.h"
#include "modbus.h"
#include "ui.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
  send_system_status(ON);
  send_control_mode(app_config.mode);
}

void app_main_loop(Config app_config){
    request_user_commands();
  // while(1){
  // }
}

void request_internal_temperature(){
  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  unsigned char *response = malloc(RECEIVE_DATA_SIZE);

  message[1] = REQUEST_TEMP;
  send_modbus_message(message, MESSAGE_REQUEST_SIZE);

  response = receive_modbus_message(REQUEST_TEMP);

}

void request_potentiometer_temperature(){
  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  message[1] = REQUEST_TEMP_POT;

  send_modbus_message(message, MESSAGE_REQUEST_SIZE);
}

void request_user_commands(){
  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  unsigned char *response = malloc(10);

  message[1] = READ_USER_CMD;
  send_modbus_message(message, MESSAGE_REQUEST_SIZE);

  response = receive_modbus_message(READ_USER_CMD);
  debug_in_hex("RECEBEU", response, 10);
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
