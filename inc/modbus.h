#ifndef MODBUS_H
#define MODBUS_H

#define SEND_CODE_MODBUS 0x16
#define REQUEST_CODE_MODBUS 0x23

#define THIS_DEVICE_CODE 0x0
#define TO_DEVICE_CODE 0x01

#define SEND_STR_CODE 0xB3

#define MIN_MODBUS_SIZE 4
#define MIN_DATA_SIZE 5
#define STR_ARG_SIZE 5

void send_modbus_message(unsigned char *message, int size);
unsigned char *receive_modbus_message();
int modbus_error(unsigned char *buffer);

#endif