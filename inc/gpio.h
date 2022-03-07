#ifndef GPIO_H
#define GPIO_H

#define PWM_MAX 100
#define PWM_MIN 0

#define FAN_MIN_VALUE 40

#define FAN_PIN 5
#define RESISTENCE_PIN 4

void initialize_gpio();
void use_fan(float pwm);
void use_resistence(float pwm);
void turn_off_fan();
void turn_off_resistence();
void turn_off_fan_and_resistence();
void controll_temperature(float pid_result);

#endif