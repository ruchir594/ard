int i=0;
int j=0;
int k=0;
int ix=0;
int count=0;
int data_segments = 30;
const int total_data_points = 12*data_segments;
const int diff_data_points = 12*(data_segments-1);
int data[360] = {0};
int diff_data[336] = {0};
int data_f_start[12] = {0};
int data_r_end[12] = {0};
int data_fall_start = 0;
int data_rise_end = 0;
bool updateflag = true;
bool localflag;
int Dth = 150;


// dont use C9

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
    ix=1;
    digitalWrite(5, 1); // LSB
  } else if (i == 1){
    i=2;
    ix=2;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 1); // LSB 2
  } else if (i == 2){
    i=3;
    ix=3;
    digitalWrite(5, 1); // LSB
  } else if (i == 3){
    i=4;
    ix=4;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 0); // LSB 2
    digitalWrite(3, 1); 
  } else if (i == 4){
    i=5;
    ix=5;
    digitalWrite(5, 1); // LSB
  } else if (i == 5){
    i=6;
    ix=6;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 1); // LSB 2
  } else if (i == 6){
    i=7;
    ix=7;
    digitalWrite(5, 1); // LSB
  } else if (i == 7){
    i=8;
    ix=8;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 0); // LSB 2
    digitalWrite(3, 0); 
    digitalWrite(2, 1); // MSB
  } else if (i == 8){
    // NOT USING C9 SEE PHYSICAN CIRCUIT
    i=10;
    ix=9;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 1); // LSB 2
  } else if (i == 10){
    i=11;
    ix=10;
    digitalWrite(5, 1); // LSB
  } else if (i == 11){
    i=12;
    ix=11;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 0);
    digitalWrite(3, 1);
  } else if (i == 12){
    i=0;
    ix=0;
    digitalWrite(5, 0); // LSB
    digitalWrite(4, 0); // LSB 2
    digitalWrite(3, 0); 
    digitalWrite(2, 0); // MSB
  }
  delay(8);
  data[ix+ 12*count] = analogRead(A1);
  //Serial.println(data[ix + 12*count]);
  if (ix == 11){
    count += 1;
  }
  if (count == data_segments){
    count = 0;
    //Serial.println("got 30 -> now processing");
    // do MATLAB code processing
    // calculate diff(data)
    for (j=2; j<data_segments; ++j){
      for (k=0; k<12; ++k){
        diff_data[(j-2)*12 + k] = data[j*12 + k] - data[(j-2)*12 + k];
        //Serial.println(diff_data[(j-1)*12 + k]);
      }
    }
    // calculate data_f_start and data_r_end
    for(j=0; j<12; ++j){
      for(k=0; k<data_segments-2; k++){
        if (diff_data[k*12 + j] < -Dth){
          data_f_start[j] = k;
          break;
        }
      }
      for(k=0; k<data_segments-2; k++){
        if (diff_data[k*12 + j] > Dth){
          data_r_end[j] = k;
        }
      }
    }
    // data_fall_start / rise_end diff sum
    for (j=1; j<12; ++j){
      data_fall_start += data_f_start[j] - data_f_start[j-1];
      data_rise_end += data_r_end[j] - data_r_end[j-1];
    }
    // compare rest 
    Serial.println(data_fall_start);
    Serial.println(data_rise_end);
    if (data_fall_start<0 && data_rise_end<0){
      Serial.println("directiom guess: ");
      Serial.print(" 0");
      Serial.println(" ");
    } else if (data_fall_start>0 && data_rise_end>0){
      Serial.println("directiom guess: ");
      Serial.print(" 1");
      Serial.println(" ");
    }
    // reinitiliaze everything to null & 0
    data_fall_start = 0;
    data_rise_end = 0;
    for (j=0; j<12; ++j){
      data_f_start[j] = 0;
      data_r_end[j] = 0;
    }
    Serial.println("....reading again");
  }
}
