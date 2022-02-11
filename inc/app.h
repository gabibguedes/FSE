#ifndef APP_H
#define APP_H

#define REQUEST_INT 0xA1
#define REQUEST_FLOAT 0xA2
#define REQUEST_STR 0xA3
#define SEND_INT 0xB1
#define SEND_FLOAT 0xB2
#define SEND_STR 0xB3

#define BUFF_MIN_SIZE 2

unsigned char *get_message(int option);
void write_message(int option);
void receive_message();

#endif