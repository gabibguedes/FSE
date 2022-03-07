#include <wiringPi.h>
#include <softPwm.h>
#include "gpio.h"

void initialize_gpio(){
  wiringPiSetup();
  softPwmCreate(FAN_PIN, PWM_MIN, PWM_MAX);
  softPwmCreate(RESISTENCE_PIN, PWM_MIN, PWM_MAX);
}


void use_fan(float pwm){
  if(pwm < FAN_MIN_VALUE)
    pwm = FAN_MIN_VALUE;

  softPwmWrite(FAN_PIN, (int) pwm);
}

void use_resistence(float pwm){
  softPwmWrite(RESISTENCE_PIN, (int) pwm);
}

void turn_off_fan(){
  softPwmWrite(FAN_PIN, PWM_MIN);
}

void turn_off_resistence(){
  softPwmWrite(RESISTENCE_PIN, PWM_MIN);
}

void turn_off_fan_and_resistence(){
  turn_off_fan();
  turn_off_resistence();
}

void controll_temperature(float pid_result){
  if(pid_result == 0){
    turn_off_fan_and_resistence();

  } else if(pid_result > 0){
    turn_off_fan();
    use_resistence(pid_result);

  } else {
    turn_off_resistence();
    use_fan(pid_result * (-1));
  }
}