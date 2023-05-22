// ================================ Motor and Sona control
void CW_motor(int PWM){
  ledcWrite(1, PWM); // this one means ledc channel 0 = 50% duty cycle
  ledcWrite(2, 0); // this one means ledc channel 1 = 0% duty cycle
}

void CCW_motor(int PWM){
  ledcWrite(1, 0); // this one means ledc channel 0 = 50% duty cycle
  ledcWrite(2, PWM); // this one means ledc channel 1 = 0% duty cycle
}

void stop_motor(){
  ledcWrite(1, 0); // this one means ledc channel 0 = 50% duty cycle
  ledcWrite(2, 0); // this one means ledc channel 1 = 0% duty cycle
}

float start_sona(){
   // Send a pulse to the ultrasonic sensor
  digitalWrite(sona_ping, LOW);
  delayMicroseconds(2);
  digitalWrite(sona_ping, HIGH);
  delayMicroseconds(10);
  digitalWrite(sona_ping, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(sona_echo, HIGH);

  // Calculate the distance in cm
  float distance_cm = duration / 2.0 * SOUND_SPEED;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Wait for 500ms before taking the next measurement
  delay(500);
  return distance_cm;
}

// ================================ Motor and Sona control
