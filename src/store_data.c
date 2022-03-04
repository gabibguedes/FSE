#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "store_data.h"

static FILE *file;

void open_csv(){
  file = fopen("store_data.csv", "w");
  if (file == NULL){
    printf("Error!");
    exit(1);
  }
  fprintf(file, "Temperature, Pressure, Humidity, Date\n");
}

void write_measures(float temp, float pressure, float humidity){
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  fprintf(file, "%.2f C, %.2f hPa, %.2f %%, %s", temp, pressure, humidity, asctime(timeinfo));
}

void close_csv_file(){
  fclose(file);
}