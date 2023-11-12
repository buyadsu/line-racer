void BLE_control() {
  if(Serial.available() > 0) {
    incomingByte = Serial.read();
    if(state == 1) {
      if(incomingByte == 'u')      {Kp += 0.03; Serial.println(Kp);}
      else if(incomingByte == 'd') {Kp -= 0.03; Serial.println(Kp);}   
    }
    else if(state == 2) {
      if(incomingByte == 'u')      {Ki += 0.0001; Serial.println(Kp);}
      else if(incomingByte == 'd') {Ki -= 0.0001; Serial.println(Kp);}
    }
    else if(state == 3) {
      if(incomingByte == 'u')      {Kd += 0.1; Serial.println(Kd);}
      else if(incomingByte == 'd') {Kd -= 0.1; Serial.println(Kd);}
    }
    else if(state == 4) {
      if(incomingByte == 'u')      {BASE_SPEED += 10; Serial.println(BASE_SPEED);}
      else if(incomingByte == 'd') {BASE_SPEED -= 10; Serial.println(BASE_SPEED);}    
    }
    else if(state == 5) {
      if(incomingByte == 'u')      {SERVO_SPEED += 2;  Serial.println(SERVO_SPEED);}
      else if(incomingByte == 'd') {SERVO_SPEED -= 2;  Serial.println(SERVO_SPEED);}
    }
    else if(state == 6) {
      if(incomingByte == 'u')      {decreasingSpeed += 50; Serial.println(decreasingSpeed); }
      else if(incomingByte == 'd') {decreasingSpeed -= 50; Serial.println(decreasingSpeed);}
    }

    switch( incomingByte ) {

      case 'P': {state = 1; Serial.println("P");} break;
      case 'I': {state = 2; Serial.println("I");} break;
      case 'D': {state = 3; Serial.println("D");} break;

      case 'b': {state = 4; Serial.println("Base Speed");} break;
      case 'e': {state = 5; Serial.println("Servo Speed");} break;
      case 'c': {state = 6; Serial.println("Decreasing Speed");} break;

      case 'Z': {enableEDF = true;} break;
      case 'z': {enableEDF = false; myservo.write(40);} break;
      // case 'O': { Motor(255, 255); delay(250); onoff = true; } break;
      case 'O': {enableMotor = true;} break;
      case 'X': {enableMotor = false; SERVO_SPEED = 40; motorsWrite(0,0); Serial.print("stoped");} break;
      case 'S': {serialSensor = !serialSensor;} break;  
      case 'Y': {Timer = !Timer;} break;
      case 'm1': {BASE_SPEED = 200; MAX_SPEED = 255; Serial.println("Base - 200, Max - 255");} break;
      case 'm2': {BASE_SPEED = 240; MAX_SPEED = 255; Serial.println("Base - 250, Max - 255");} break;
      
      default: break;
    }
    incomingByte=0;
  }
}

void serialSensorData() {
  if (isFollowLineBlack) {position = qtr.readLineBlack(sensorValues);}
  else                   {position = qtr.readLineWhite(sensorValues);}

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum
  // reflectance and 1000 means minimum reflectance, followed by the line position
  Serial.print(position);
  Serial.print('\t');
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print(' ');
  }
  Serial.println();
  delay(200);
}

void serialEncoderData() {
  Serial.print(leftCounter);
  Serial.print(" ");
  Serial.print(rightCounter);
}