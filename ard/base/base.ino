int x0=0;
int x1=0;
  
void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT); // MSB
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); // LSB
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(2, 0); // LSB
  digitalWrite(3, 0); // LSB 2
  digitalWrite(6, 0); // 0 to enable

}

void loop() {
  Serial.println(analogRead(A0));
  //Serial.print(x0);
  //Serial.println(x1);
  x1 = x1 ^ x0; // LSB 2
  x0 = x0 ^ 1; // LSB
  digitalWrite(4, x1); // LSB 2
  digitalWrite(5, x0); // LSB
  //digitalWrite(2, x1); // LSB 2
  //digitalWrite(3, x0); // LSB
}
