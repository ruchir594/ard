int i=0;
int j=0;
int count=0;
int data[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int data_std[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
float Dth = 0.5;
float dth = 0.1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogReadResolution(14);
  pinMode(2, OUTPUT); // MSB 
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); // LSB 
  pinMode(6, OUTPUT); // Enable on 4.3
  pinMode(A1, INPUT);
  
  digitalWrite(5, 0); // LSB
  digitalWrite(4, 0); // LSB 2
  digitalWrite(3, 0); 
  digitalWrite(2, 0); // MSB
  digitalWrite(6, 0); // 0 to enable

}

void loop() {
  // put your main code here, to run repeatedly: 
  if (i == 0){
    i=1;
    digitalWrite(5, 1); // LSB
  } else if (i == 1){
    i=2;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 1); // LSB 2
  } else if (i == 2){
    i=3;
    digitalWrite(5, 1); // LSB
  } else if (i == 3){
    i=4;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 0); // LSB 2
    digitalWrite(3, 1); 
  } else if (i == 4){
    i=5;
    digitalWrite(5, 1); // LSB
  } else if (i == 5){
    i=6;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 1); // LSB 2
  } else if (i == 6){
    i=7;
    digitalWrite(5, 1); // LSB
  } else if (i == 7){
    i=8;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 0); // LSB 2
    digitalWrite(3, 0); 
    digitalWrite(2, 1); // MSB
  } else if (i == 8){
    i=9;
    digitalWrite(5, 1); // LSB
  } else if (i == 9){
    i=10;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 1); // LSB 2
  } else if (i == 10){
    i=11;
    digitalWrite(5, 1); // LSB
  } else if (i == 11){
    i=0;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 0); // LSB 2
    digitalWrite(3, 0); 
    digitalWrite(2, 0); // MSB
  }
  delay(10);
  data[i] = analogRead(A1);

  // when i == 11, we have read everything once 

  // dont update when we gotta put a finger on it

  if (count % 200 == 1 and data[11] != 0){
    for (j=0; j<12; j++){
      data_std[j] = data[j];
    }
    Serial.println("updated data_std");
  }
  
  if (data_std[11] != 0 and i == 11) {
    for (j=0; j<12; j++){
      //Serial.println(data[j]);
      if (((float)data[j]/(float) data_std[j]) < Dth) {
        //Serial.println("prediction");
        Serial.println(j);
        //break;
      }
    }
  }
  count = count + 1;
  //Serial.println(count);
}
