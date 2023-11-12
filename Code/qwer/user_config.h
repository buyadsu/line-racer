
#define isFollowLineBlack  true

// Speed configure
int MAX_SPEED = 240;
int BASE_SPEED = 225;
int SERVO_SPEED = 40;

// constants won't change. They're used here to set pin numbers:
int pinButton = 7; // the number of the pushbutton pin
#define SHORT_PRESS_TIME  1000 // 1000 milliseconds
#define LONG_PRESS_TIME   1000 // 1000 milliseconds

float Kp = 0.086;
float Ki = 0.0000001;
float Kd = 1.3;

#define PWMA 9
#define AIN2 8
#define AIN1 7
#define BIN1 10
#define BIN2 12
#define PWMB 11

#define L_ENCA 3
#define L_ENCB 5
#define R_ENCA 2
#define R_ENCB 4

#define PIN_ESC 6

#define leftSensor  A6
#define rightSensor A7

#define buttonCalibrate 4
#define buttonStart     5

