
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200); // msp430g2231 must use 4800
  pinMode(A1, INPUT);
  
  
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println(analogRead(A1));
  //Serial.println(5);
}
