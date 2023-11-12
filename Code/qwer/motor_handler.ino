void initMotor() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void PID_control() {
  if ( isFollowLineBlack ) { position = qtr.readLineBlack(sensorValues); }
  else                     { position = qtr.readLineWhite(sensorValues); }

  int Error = 3000 - position; 
  PID = (Kp * Error) + (Kd * (Error - lastError) + (Ki * I));
  I = I + Error;
  pposition = position;
  lastError = Error;
  
  int rightSpeed = BASE_SPEED - PID;
  int leftSpeed  = BASE_SPEED + PID;
  
  // if(leftSpeed > MAX_SPEED)        leftSpeed = MAX_SPEED;
  // else if(leftSpeed < -30)   leftSpeed = -30;                           
  // if(rightSpeed > MAX_SPEED)       rightSpeed = MAX_SPEED;
  // else if(rightSpeed < -30)  rightSpeed = -30;

  if(leftSpeed > MAX_SPEED)        leftSpeed = MAX_SPEED;
  if(leftSpeed < 0)   leftSpeed = 0;                           
  if(rightSpeed > MAX_SPEED)       rightSpeed = MAX_SPEED;
  if(rightSpeed < 0)  rightSpeed = 0;

  // if(enableMotor)
  motorsWrite(leftSpeed, rightSpeed);
}
void motorsWrite(int zuun,int baruun) {
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  analogWrite(PWMA, zuun);
  analogWrite(PWMB, baruun);
}
// void motorsWrite(int speedLeft,int speedRight) {
//   if(speedLeft > 0){
//     digitalWrite(AIN1, LOW);
//     digitalWrite(AIN2, HIGH);
//     analogWrite(PWMA, speedLeft);
//   } else if(speedLeft < 0) {
//     digitalWrite(AIN1, HIGH);
//     digitalWrite(AIN2, LOW);
//     analogWrite(PWMA, abs(map(speedLeft,0,255,255,0)));
//   } else {
//     digitalWrite(AIN1, LOW);
//     digitalWrite(AIN2, LOW);
//     analogWrite(PWMA, speedLeft);
//   }
  
//   if(speedRight > 0) {
//     digitalWrite(BIN1, LOW);
//     digitalWrite(BIN2, HIGH);
//     analogWrite(PWMB, speedRight);
//   } else if(speedRight < 0) {
//     digitalWrite(PWMB, abs(map(speedRight,0,255,255,0)));
//     digitalWrite(BIN1, HIGH);
//     digitalWrite(BIN2, LOW);
//   } else {
//     digitalWrite(BIN1, LOW);
//     digitalWrite(BIN2, LOW);
//     analogWrite(PWMB, speedRight);
//   }
// }

void leftEncoder() {
  if(digitalRead(L_ENCB) == 0) leftCounter++;
  else if(digitalRead(L_ENCB) == 1) leftCounter--;
}
void rightEncoder() {
  if(digitalRead(R_ENCB) == 0) rightCounter++;
  else if(digitalRead(R_ENCB) == 1) rightCounter--;
}