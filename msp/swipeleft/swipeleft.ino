int i=0;
int j=0;
int k=0;
int count=0;
int data_segments = 30;
int total_data_points = 12*data_segments;
int data[total_data_points] = {0};
int diff_data[total_data_points-12] = {0};
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
  delay(8);
  data[i*(count+1)] = analogRead(A1);
  if (i == 11){
    count += 1;
  }
  if (count == data_segments){
    count = 0;
    Serial.println("got 30");
    // do MATLAB code processing
    // calculate diff(data)
    for (j=1; j<data_segments; ++j){
      for (k=0; k<12; ++k){
        diff_data[(j-1)*12 + k] = data[j*12 + k] - data[(j-1)*12 + k];
      }
    }
    //
  }
}
