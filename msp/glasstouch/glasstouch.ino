int i=0;
int j=0;
int count=0;
int data[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int data_std[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
//float Dth = 0.5;
float Dth[12] = {0.816814159292035,0.601501501501502,0.724624624624625,0.572560975609756,0.789552238805970,0.575609756097561,0.732530120481928,0.559214501510574,0.865217391304348,0.523312883435583,0.666765578635015,0.530722891566265};
float dth = 0.1;
bool updateflag = true;
bool localflag;

// dont use 10

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

  if (count % 200 == 1 and data[11] != 0 and updateflag == true){
    for (j=0; j<12; j++){
      data_std[j] = data[j];
    }
    Serial.println("updated data_std");
  }
  
  if (data_std[11] != 0 and i == 11) {
    localflag = false;
    for (j=0; j<12; j++){
      //Serial.println(data[j]);
      if (((float)data[j]/(float) data_std[j]) < Dth[j]) {
        //Serial.println("prediction");
        Serial.println(j);
        localflag = true;
        //break;
      }
    }
    if (localflag == true){
      updateflag = false;
    } else {
      updateflag = true;
    }

  }
  count = count + 1;
  //Serial.println(count);
}
