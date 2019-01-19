void setup(){
  Serial.begin(9600); // Bluetooth module
}

void loop(){
/* Echo sent data */
  
  int s = Serial.read();
  while (Serial.available() > 0){
    Serial.write(s);
    s = Serial.read();
  }
  if(s != -1)
    Serial.write(s);
}
