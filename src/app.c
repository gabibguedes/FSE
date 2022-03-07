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
#include "pid.h"

Config initial_config(){
  Config init;
  init.kp = 20.0;
  init.ki = 0.1;
  init.kd = 100.0;
  init.mode = POTENTIOMETER;
  init.temp = 40.0;
  init.state = ON;

  return init;
}

void start_app(Config *app_config){
  pid_configura_constantes(app_config->kp, app_config->ki, app_config->kd);
  initialize_uart();
  initialize_gpio();
  lcd_init();
  open_csv();

  send_system_status(ON);
  send_control_mode(app_config->mode);
}

void shut_down(Config *app_config){
  turn_off_system(app_config);
}

void turn_off_system(Config *app){
  app->state = OFF;
  turn_off_fan_and_resistence();
  send_system_status(OFF);
  print_system_off();
}

void app_main_loop(Config *app_config){
  while(1){
    if(app_config->state == ON){
      float te = get_external_temperature();
      float ti = request_internal_temperature();
      float tr = get_reference_temperature(app_config);

      pid_atualiza_referencia(tr);
      print_sensors_data_on_display(app_config->mode, ti, te, tr);

      float pid = pid_controle(ti);

      controll_temperature(pid);
      send_reference_signal(tr);
      send_control_signal((int) pid);
      // write_measures(ti,te,tr,pid);
    }
    
    request_user_commands(app_config);
  }

}

float get_reference_temperature(Config *app_config){
  float tr = 0.0;
  switch(app_config->mode){
    case TERMINAL:
      tr = app_config->temp;
      break;
    case POTENTIOMETER:
      tr = request_potentiometer_temperature();
      break;
    case REFLOW_CURVE:
      tr = app_config->temp;

      break;
  }
  return tr;
}

float request_internal_temperature(){
  float ti;
  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  unsigned char *response = malloc(RECEIVE_DATA_SIZE);

  message[0] = REQUEST_TEMP;
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
  message[0] = REQUEST_TEMP_POT;

  send_modbus_message(message, MESSAGE_REQUEST_SIZE);
  response = receive_modbus_message(REQUEST_TEMP_POT);

  if(option_error(REQUEST_TEMP_POT, response[0])){
    return request_potentiometer_temperature();
  }

  memcpy(&tr, &response[1], 4);

  return tr;
}

void request_user_commands(Config *app_config){
  unsigned char *message = malloc(MESSAGE_REQUEST_SIZE + 1);
  unsigned char *response = malloc(MESSAGE_RECEIVED_SIZE);

  message[0] = READ_USER_CMD;
  send_modbus_message(message, MESSAGE_REQUEST_SIZE);

  response = receive_modbus_message(READ_USER_CMD);

  switch(response[1]){
    case DO_NOTHING:
      break;
    case TURN_ON:
      printf("[COMANDO] Ligar sistema\n");
      app_config->state = ON;
      send_system_status(ON);
      break;
    case TURN_OFF:
      printf("[COMANDO] Desligar sistema\n");
      turn_off_system(app_config);
      break;
    case ACTIVATE_POTENTIOMETER:
      printf("[COMANDO] Modo Potenciometro\n");
      app_config->mode = POTENTIOMETER;
      send_control_mode(POTENTIOMETER);
      break;
    case ACTIVATE_REFLOW_CURVE:
      printf("[COMANDO] Modo Curva Reflow\n");
      app_config->mode = REFLOW_CURVE;
      send_control_mode(REFLOW_CURVE);
      break;
    default:
      break;
  }
  
}

void send_control_signal(int pid){
  unsigned char *message = malloc(MESSAGE_SEND_SIGNAL_SIZE + 1);
  message[0] = SEND_CTRL_SIG;
  int pid_aux = pid;
  if(pid > -40 && pid < 0){
    pid_aux = -40;
  }
  memcpy(&message[1], &pid_aux, 4);
  send_modbus_message(message, MESSAGE_SEND_SIGNAL_SIZE);
}

void send_reference_signal(float te){
  unsigned char *message = malloc(MESSAGE_SEND_SIGNAL_SIZE + 1);
  message[0] = SEND_REF_SIG;
  memcpy(&message[1], &te, 4);
  send_modbus_message(message, MESSAGE_SEND_SIGNAL_SIZE);
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
