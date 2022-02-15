#include "ui.h"
#include "uart.h"
#include "app.h"
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

int show_menu(){
  int choice;
  printf("Qual comando deseja executar?\n\n");
  printf("1 - Solicitar dado\n");
  printf("2 - Enviar dado\n\n");
  scanf("%d", &choice);

  switch (choice){
  case 1:
    clear();
    return show_send_data_options();
  case 2:
    clear();
    return show_receive_data_options();

  default:
    invalid_option();
    return show_menu();
  }
}

void print_data_options(char *command) {
  printf("Que tipo de dado deseja %s?\n\n", command);
  printf("1 - Inteiro\n");
  printf("2 - Float\n");
  printf("3 - String\n");
  printf("\n4 - Voltar ao menu principal\n\n");
}

int show_send_data_options(){
  int choice;
  print_data_options("solicitar");
  scanf("%d", &choice);

  if(choice > 0 && choice < 4)
    return (REQUEST_INT - 1) + choice;

  if (choice == 4){
    clear();
    return show_menu();
  }

  invalid_option();
  return show_send_data_options();
}

int show_receive_data_options(){
  int choice;
  print_data_options("enviar");
  scanf("%d", &choice);

  if (choice > 0 && choice < 4)
    return (SEND_INT - 1) + choice;

  if (choice == 4){
    clear();
    return show_menu();
  }

  invalid_option();
  return show_receive_data_options();
}

unsigned char *send_int(){
  int num;
  unsigned char *bytes;
  bytes = malloc(4);

  printf("Inteiro: ");
  scanf("%d", &num);

  memcpy(bytes, &num, 4);

  return bytes;
}

unsigned char *send_float(){
  float num;
  unsigned char *bytes;
  bytes = malloc(4);

  printf("Float: ");
  scanf("%f", &num);

  memcpy(bytes, &num, 4);

  return bytes;
}

unsigned char *send_string(){
  unsigned char *str;
  str = malloc(100);

  printf("String: ");
  scanf("%s", str);

  return str;
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
