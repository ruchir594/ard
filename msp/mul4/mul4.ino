int x0=0;
int x1=0;
int i=0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(14);
  pinMode(26, OUTPUT); // MSB //4.4
  pinMode(27, OUTPUT); // 4.5
  pinMode(28, OUTPUT); //4.7
  pinMode(5, OUTPUT); // LSB //4.1
  pinMode(6, OUTPUT); //4.3
  pinMode(31, OUTPUT);
  pinMode(A1, INPUT);
  digitalWrite(5, 0); // LSB
  digitalWrite(28, 0); // LSB 2
  digitalWrite(6, 0); // 0 to enable

}

void loop() {
  //Serial.println(i);
  Serial.println(analogRead(A1));
  //Serial.print(x0);
  //Serial.println(x1);
  x0 = x0 ^ 1; // LSB
  digitalWrite(31, x0);
  if (i==0) {
    i=1;
    digitalWrite(5, HIGH);
  } else if(i==1) {
    i=2;
    digitalWrite(5, LOW);
    digitalWrite(28, HIGH);
  } else if (i==2) {
    i=3;
    digitalWrite(5, HIGH);
  } else if (i==3) {
    i=0;
    digitalWrite(5, LOW);
    digitalWrite(28, LOW);
  }
  delay(10);
  
}

