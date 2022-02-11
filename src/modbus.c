#include "modbus.h"
#include "uart.h"
#include "crc.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void send_modbus_message (unsigned char *message, int message_size, int option) {
  int buffer_size = MIN_MODBUS_SIZE;
  int pos = 0; // Position to write on buffer
  unsigned char *message_buffer;

  buffer_size += message_size;
  message_buffer = (unsigned char*) malloc(buffer_size);

  message_buffer[pos++] = TO_DEVICE_CODE;

  if (message_size > 0)  // Message to send value
   message_buffer[pos++] = SEND_CODE_MODBUS;

  else  // Message to request value
   message_buffer[pos++] = REQUEST_CODE_MODBUS;


  message_buffer[pos++] = option;

  if (option == SEND_STR_CODE) // Add string size to message
    message_buffer[pos++] = message_size;

  for (int i = 0; i < message_size; i++)
    message_buffer[pos++] = message[i];

  // message_buffer[pos++] = 1;
  // message_buffer[pos++] = 6;
  // message_buffer[pos++] = 1;
  // message_buffer[pos++] = 2;

  short crc = calcula_CRC(message_buffer, pos);
  memcpy(&message_buffer[pos], &crc, CRC_SIZE);
  pos += CRC_SIZE;

  printf("Buffers de memória criados!\n");

  debug_in_hexa(message_buffer, buffer_size);

  write_in_uart(message_buffer, buffer_size);

  free(message_buffer);
}

