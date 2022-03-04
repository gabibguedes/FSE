#ifndef STORE_DATA_H
#define STORE_DATA_H

void open_csv();
void write_measures(float temp, float pressure, float humidity);
void close_csv_file();

#endif