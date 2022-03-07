#ifndef GPIO_H
#define GPIO_H

#define PWM_MAX 100
#define PWM_MIN 0

#define FAN_MIN_VALUE 40

#define FAN_PIN 4
#define RESISTENCE_PIN 5

void initialize_gpio();
void use_fan(int pwm);
void use_resistence(int pwm);
void turn_off_fan();
void turn_off_resistence();
void turn_off_system();
void controll_temperature(int pid_result);

#endif