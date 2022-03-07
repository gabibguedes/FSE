#ifndef SENSOR_H
#define SENSOR_H

#define I2C_FILE "/dev/i2c-1"

float get_external_temperature();
void show_data_on_display();
float get_sensor_temp(struct bme280_dev *dev);

#endif