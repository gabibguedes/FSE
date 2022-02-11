#ifndef ui_H
#define ui_H

void clear();
void invalid_option();

int show_menu();
void print_data_options(char *command);

int show_send_data_options();
int show_receive_data_options();

unsigned char *send_int();
unsigned char *send_float();
unsigned char *send_string();

void read_int(unsigned char *res);
void read_float(unsigned char *res);
void read_str(unsigned char *res);

void debug_in_hex(char *message, unsigned char *buffer, int size);

#endif

