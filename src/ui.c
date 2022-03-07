#include "ui.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear(){
  printf("\e[1;1H\e[2J");
}

void invalid_option(){
  getchar();
  clear();
  printf("\nOpção inválida! Tente novamente\n\n");
}

char* traslate_config_mode(ControlMode mode){
  switch (mode){
  case TERMINAL:
    return "Terminal";

  case REFLOW_CURVE:
    return "Curva Reflow";

  case POTENTIOMETER:
    return "Potenciometro";

  default:
    return "Modo não identificado";
  }
}

int show_menu(Config *program_config){
  int choice;

  printf("Configurações do programa:\n\n");

  printf("Kp = %.2f\n", program_config->kp);
  printf("Ki = %.2f\n", program_config->ki);
  printf("Kd = %.2f\n", program_config->kd);
  printf("Modo de Execução = %s\n", traslate_config_mode(program_config->mode));

  if(program_config->mode == TERMINAL){
    printf("Temperatura= %.2f\n", program_config->temp);
  }
  printf("\n");



  printf("1 - Editar constantes do PID\n");
  printf("2 - Editar modo de execução\n");
  printf("3 - Iniciar programa\n");

  if(program_config->mode == TERMINAL){
    printf("4 - Editar temperatura inicial via terminal\n");
  }
  scanf("%d", &choice);

  switch (choice){
  case 1:
    clear();
    return edit_pid_constants(program_config);
  case 2:
    clear();
    return edit_execution_mode(program_config);
  case 3:
    printf("INICIAR PROGRAMA!\n");
    break;
  case 4:
    clear();
    edit_temperature(program_config);
    break;

  default:
    invalid_option();
    return show_menu(program_config);
  }
  return 1;
}

int edit_temperature(Config *program_config){
  printf("Temperatura: ");
  scanf("%f", &program_config->temp);

  clear();
  return show_menu(program_config);
}

int edit_pid_constants(Config *program_config){
  printf("Digite os novos valores das constantes PID:\n");
  printf("Kp: ");
  scanf("%f", &program_config->kp);

  printf("Ki: ");
  scanf("%f", &program_config->ki);

  printf("Kd: ");
  scanf("%f", &program_config->kd);

  clear();
  return show_menu(program_config);
}

int start_temperature_from_terminal(Config *program_config){
  printf("Temperatura: ");
  scanf("%f", &program_config->temp);

  clear();
  return show_menu(program_config);
}

int edit_execution_mode(Config *program_config){
  int choice;

  printf("Escolha o modo de execução:\n");
  printf("1 - Potenciometro\n");
  printf("2 - Curva Reflow\n");
  printf("3 - Terminal\n\n");

  scanf("%d", &choice);

  if(choice < 1 || choice > 3){
    invalid_option();
    edit_execution_mode(program_config);
  }

  program_config->mode = choice - 1;

  clear();
  return show_menu(program_config);
}





void read_int(unsigned char *res){
  int number;
  memcpy(&number, res, 4);

  printf("Número recebido: %d\n", number);
}

void read_float(unsigned char *res){
  float number;
  memcpy(&number, res, 4);

  printf("Número recebido: %f\n", number);
}

void read_str(unsigned char *res){
  printf("%i Bytes lidos : %s\n", res[0], &res[1]);
}

void debug_in_hex(char* message, unsigned char *buffer, int size){
  printf("\n[DEBUG] %s\n", message);
  printf("[DEBUG] ");

  for (int i = 0; i < size; i++){
    printf("%x ", buffer[i]);
  }
  printf("\n\n");
}

void show_error(char *label, unsigned char expected, unsigned char received){
  printf("[ERRO] %s errado!\n", label);
  printf("[ERRO] Esperado: %x\n", expected);
  printf("[ERRO] Recebido: %x\n\n", received);
}
