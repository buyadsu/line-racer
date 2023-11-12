#include <QTRSensors.h>
#include <Servo.h>
#include "user_config.h"
#include "def_var.h"

QTRSensors qtr;
const uint8_t SensorCount = 7;
uint16_t sensorValues[SensorCount];
Servo myservo;

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int current;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
bool isPressing = false;
bool isLongDetected = false;



/*************************************************************************
* Buttons pins
*************************************************************************/
#define buttonCalibrate 4
#define buttonStart     5


void setup() {
  Serial.begin(9600);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A6, A0, A1, A2, A3, A4, A5}, SensorCount);

  initMotor();
  pinMode(L_ENCA, INPUT_PULLUP);
  pinMode(L_ENCB, INPUT_PULLUP);
  pinMode(R_ENCA, INPUT_PULLUP);
  pinMode(R_ENCB, INPUT_PULLUP);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor,INPUT);

  attachInterrupt(0, leftEncoder,  RISING);//2
  attachInterrupt(1, rightEncoder, RISING);//3

  myservo.attach(PIN_ESC); //myservo  itvehchvvleh 
  myservo.write(SERVO_SPEED);   //esc  hurd uguh

  pinMode(pinButton, INPUT_PULLUP);

  calibration();

  serialSensorData();
  serialEncoderData();
  motorsWrite(0,0);  
  Serial.println("Ready to start");
}

void loop() {
  // // put your main code here, to run repeatedly:
  // if(digitalRead(buttonStart) == HIGH) { // loop dotor ortson ucir while ashigalh shaardlaggu
  //   enableMotor =! enableMotor; // =! true baisan ymiig false bolgdog uildel
  //   if(enableMotor = true) {
  //     delay(1500);//
  //   } else {
  //     delay(50);
  //   }
  // }
  
  BLE_control();

  myservo.write(SERVO_SPEED);
  if(enableMotor) {PID_control();}
  if(enableEDF) {myservo.write(SERVO_SPEED);}
  if(serialSensor) {serialSensorData();}
  
  // if(Timer = true){
  //   detectInt();
  //   if( millis() - previousTime > decreasingSpeed ) {
  //     BASE_SPEED = 200;
  //     previousTime = millis();
  //   }
  //   if ( lineCount >= 2) {
  //     enableMotor = false; motorsWrite(0, 0); SERVO_SPEED = 40; lineCount = 0; previousTime = 0;
  //   }
  // }

}

void detectInt(){
  static long lastDetected = 0;

  if (millis() - lastDetected < 250) {
    return;
  }
  // if( sensorValues[0] <= 200 && sensorValues[7] <= 200){
  //   lastDetected = millis();

  //   lineCount++;
  // }
  // if (  sensorValues[0] >=800 && sensorValues[1] >=800 && sensorValues[6] >=800 && sensorValues[7] >=800 ){
  //   lastDetected = millis();

  //   lineCount++;
  // }
  if(  sensorValues[0] <= 200 && sensorValues[1] <= 200 && sensorValues[2] <= 200 && sensorValues[3] <= 200 && sensorValues[4] <= 200 && sensorValues[5] <= 200 && sensorValues[6] <= 200 && sensorValues[7] <= 200 ){
    lastDetected = millis();

    lineCount++;
  }
  // if( sensorValues[0] >=800 && sensorValues[7] >=800){
  //   lastDetected = millis();

  //   lineCount++;
  // }
}

int stateOfButton(int pinButton) {
  // read the state of the switch/button:
  current = digitalRead(pinButton);

  if(lastState == HIGH && current == LOW) {        // button is pressed
    pressedTime = millis();
    isPressing = true;
    isLongDetected = false;
  } else if(lastState == LOW && current == HIGH) { // button is released
    isPressing = false;
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if( pressDuration < SHORT_PRESS_TIME )
      Serial.println("A short press is detected");
  }

  if(isPressing == true && isLongDetected == false) {
    long pressDuration = millis() - pressedTime;

    if( pressDuration > LONG_PRESS_TIME ) {
      // Serial.println("A long press is detected");
      isLongDetected = true;
    }
  }

  // save the the last state
  lastState = current;
}

void calibration() {
  Serial.println();
  Serial.print("Calibration is starting");
  digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 1; i <= 200; i++) {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);

  // print the calibration minimum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(" ");
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();
  Serial.println("Calibration is done");
}