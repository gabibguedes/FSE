#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "store_data.h"

char time_str[20];

void open_csv(){
  FILE *file = fopen("store_data.csv", "w");
  fprintf(file, "Data, Temperatura interna, Temperatura externa, Temperatura de referencia, Resistencia, Ventoinha\n");
  fclose(file);
}

void get_time(){
  time_t raw_time;
  struct tm *timeinfo = malloc(sizeof(struct tm));

  raw_time = time(NULL);
  timeinfo = localtime(&raw_time);

  strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
}

void write_measures(float ti, float te, float tr, float pid){
  // get_time();
  FILE *file = fopen("store_data.csv", "a");

  float resistor = 0.0;
  float fan = 0.0;
  if(pid > 0){
    resistor = pid;
  } else if(pid < 40) {
    fan = pid * (-1);
  }

  fprintf(file, ", %.2f, %.2f, %.2f, %.2f, %.2f\n", ti, te, tr, resistor, fan);
  fclose(file);
}

