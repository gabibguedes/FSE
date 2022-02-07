#include "menu.h"
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

char *send_int(){
  int num;
  char *bytes;

  bytes = malloc(sizeof(char) * 4);

  printf("Inteiro: ");
  scanf("%d", &num);

  memcpy(bytes, &num, 4);

  return bytes;
}

char *send_float(){
  float num;
  char *bytes;

  bytes = malloc(sizeof(char) * 4);

  printf("Float: ");
  scanf("%f", &num);

  memcpy(bytes, &num, 4);

  return bytes;
}

char *send_string(){
  char *str;
  str = malloc(sizeof(char) * 100);

  printf("String: ");
  scanf("%s", str);

  return str;
}
