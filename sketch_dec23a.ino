int incomingByte = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    incomingByte = Serial.read();

    Serial.print("recieved: ");
    Serial.println(incomingByte, DEC);
  }
}
