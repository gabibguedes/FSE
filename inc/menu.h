#ifndef MENU_H
#define MENU_H

void clear();
void invalid_option();
int show_menu();
void print_data_options(char *command);
int show_send_data_options();
int show_receive_data_options();
char *send_int();
char *send_float();
char *send_string();

#endif

