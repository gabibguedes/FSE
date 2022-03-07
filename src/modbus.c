#include "modbus.h"
#include "uart.h"
#include "crc.h"
#include "ui.h"
#include "app.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_modbus_message (unsigned char *message, int message_size) {
  int pos = 0;
  short crc;
  unsigned char *message_buffer;

  message_buffer = malloc(MIN_MODBUS_SIZE + message_size);

  message_buffer[pos++] = TO_DEVICE_CODE;
  message_buffer[pos++] = get_modbus_code_from_option(message[0]);
  message_buffer[pos++] = message[0];

  message_buffer[pos++] = 1;
  message_buffer[pos++] = 6;
  message_buffer[pos++] = 1;
  message_buffer[pos++] = 2;

  for (int i = 0; i < message_size; i++)
    message_buffer[pos++] = message[i+1];


  crc = calcula_CRC(message_buffer, pos);
  memcpy(&message_buffer[pos], &crc, CRC_SIZE);
  pos += CRC_SIZE;

  write_in_uart(message_buffer, pos);
}

int modbus_error(unsigned char *buffer, int modbus_code){
  int error = 0;

  if (buffer[0] != THIS_DEVICE_CODE) {
    show_error("Device", THIS_DEVICE_CODE, buffer[0]);
    error++;
  }

  if ( buffer[1] != modbus_code ) {
    show_error("Código MODBUS", modbus_code, buffer[1]);
    error++;
  }

  return error;
}

int get_modbus_code_from_option(int option){
  int code = REQUEST_CODE_MODBUS;
  if (option >= SEND_CTRL_SIG)
    code = SEND_CODE_MODBUS;

  return code;
}

int option_error(int opt_expected, int opt_received) {
  if (opt_expected == opt_received)
    return 0;

  show_error("Opção", opt_expected, opt_received);
  return 1;
}


unsigned char *receive_modbus_message(int option) {
  unsigned char *buffer, *message;
  int buffer_size = RECEIVE_DATA_SIZE;
  int modbus_code = get_modbus_code_from_option(option);

  buffer = read_uart();

  if (modbus_error(buffer, modbus_code))
    return NULL;

  if (crc_error(buffer, buffer_size))
    return NULL;

  message = malloc(buffer_size);
  memcpy(message, &buffer[2], buffer_size);

  return message;
}

