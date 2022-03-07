#ifndef UI_H
#define UI_H


#include "app.h"

void clear();
void invalid_option();

char* traslate_config_mode(ControlMode mode);
int show_menu(Config *program_config);
int edit_pid_constants(Config *program_config);
int edit_execution_mode(Config *program_config);
int edit_temperature(Config *program_config);

void debug_in_hex(char *message, unsigned char *buffer, int size);
void show_error(char *label, unsigned char expected, unsigned char received);

#endif

