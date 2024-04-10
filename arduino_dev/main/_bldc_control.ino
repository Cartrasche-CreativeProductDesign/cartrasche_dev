int current_speed;

void initialize_bldc()
{
  pinMode(DIR1, OUTPUT);
  pinMode(START_STOP1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(START_STOP2, OUTPUT);
    
  pinMode(SPEED_IN1, OUTPUT);
  pinMode(SPEED_IN2, OUTPUT);

  analogWrite(SPEED_IN1, 125);
  analogWrite(SPEED_IN2, 125);
  digitalWrite(START_STOP1, HIGH); //stop
  digitalWrite(START_STOP2, HIGH); //stop

  Serial.println("BLDC Initialization Done");

}

void bldc_control(int speed)
{
  Serial.print("Speed = ");
  Serial.println(speed);
  current_speed = speed;

  // Turn motor on
  digitalWrite(START_STOP1, LOW);
  digitalWrite(START_STOP2, LOW);

  // Slowly increase motor speed
  for (int i = 150; i <= speed; i += 10) {
    analogWrite(SPEED_IN1, i);
    delay(250);
  }
}

void move_forward()
{
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  
  bldc_control(30);
}

void move_backward()
{
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  
  bldc_control(30);
}

void move_forward()
{
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  
  bldc_control(30);
}

void turn_off_motor()
{
  Serial.print("current speed at");
  Serial.println(current_speed);
  // Slowly decrease motor speed
  for (int i = current_speed; i >= 150; i -= 10) {
    analogWrite(SPEED_IN1, i);
    delay(250);
  }
  // Turn motor off
  digitalWrite(START_STOP1, HIGH);
  digitalWrite(START_STOP2, HIGH);
}
