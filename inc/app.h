#ifndef APP_H
#define APP_H

#define REQUEST_TEMP 0xC1
#define REQUEST_TEMP_POT 0xC2
#define READ_USER_CMD 0xC3

#define SEND_CTRL_SIG 0xD1
#define SEND_REF_SIG 0xD2
#define SEND_SYSTEM_STATE 0xD3
#define SEND_CTRL_MODE 0xD4

#define BUFF_MIN_SIZE 2

#define MESSAGE_REQUEST_SIZE 0
#define MESSAGE_SYSTEM_STATE_SIZE 1
#define MESSAGE_SEND_SIGNAL_SIZE 4
#define MESSAGE_RECEIVED_SIZE 5

#define DO_NOTHING 0
#define TURN_ON 1
#define TURN_OFF 2
#define ACTIVATE_POTENTIOMETER 3
#define ACTIVATE_REFLOW_CURVE 4

typedef enum OnOffState
{
  ON = 1,
  OFF = 0
} OnOffState;

typedef enum ControlMode
{
  POTENTIOMETER = 0,
  REFLOW_CURVE = 1,
  TERMINAL = 2
} ControlMode;

typedef struct Config
{
  float kp;
  float ki;
  float kd;
  ControlMode mode;
  float temp;
} Config;

Config initial_config();
void app_main_loop(Config app_config);


int option_error(int opt_expected, int opt_received);
void start_app(Config app_config);
void turn_off_system();
void shut_down();

float request_internal_temperature();
float request_potentiometer_temperature();
void request_user_commands(Config app_config);
void send_control_signal(int control_signal);
void send_reference_signal(int reference_signal);
void send_system_status(OnOffState state);
void send_control_mode(ControlMode state);
float get_reference_temperature(Config app_config);
#endif