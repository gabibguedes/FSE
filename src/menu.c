#include <stdio.h>
#include "menu.h"

#define A1 161 // Solicitação de dado inteiro : integer
#define A2 162 // Solicitação de dado real: float
#define A3 163 // Solicitação de dado do tipo string: char[]

#define B1 177 // Envio de um dado no formato integer
#define B2 178 // Envio de um dado no formato float
#define B3 179 // Envio de uma string: char[]

void clear(){
  printf("\e[1;1H\e[2J");
}

void invalid_option(){
  getchar();
  clear();
  printf("\nOpção invalida! Tente novamente\n\n");
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

  switch (choice){
  case 1:
    return A1;
  case 2:
    return A2;
  case 3:
    return A3;
  case 4:
    clear();
    return show_menu();

  default:
    invalid_option();
    return show_send_data_options();
  }
}

int show_receive_data_options(){
  int choice;
  print_data_options("enviar");
  scanf("%d", &choice);

  switch (choice){
  case 1:
    return B1;
  case 2:
    return B2;
  case 3:
    return B3;
  case 4:
    clear();
    return show_menu();

  default:
    invalid_option();
    return show_receive_data_options();
  }
}
