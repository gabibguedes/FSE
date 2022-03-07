#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "store_data.h"

void open_csv(){
  FILE *file = fopen("store_data.csv", "w");
  if (file == NULL){
    printf("Error!");
    exit(1);
  }
  fprintf(file, "Temperatura interna, Temperatura externa, Temperatura de referencia, Resistencia, Ventoinha, Data\n");
  fclose(file);
}

void write_measures(float ti, float te, float tr, float pid){
  FILE *file = fopen("store_data.csv", "a");
  if (file == NULL){
    printf("Error!");
    exit(1);
  }
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  float resistor = 0.0;
  float fan = 0.0;

  if(pid > 0){
    resistor = pid;
  } else if(pid < 40) {
    fan = pid;
  }

  fprintf(file, "%.2f, %.2f, %.2f, %.2f, %.2f, %s", ti, te, tr, resistor, fan, asctime(timeinfo));
  fclose(file);
}

