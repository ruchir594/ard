int i=0;
int j=0;
int k=0;
int ix=0;
int count=0;
int data_segments = 200;
const int total_data_points = 12*data_segments;
const int diff_data_points = 12*(data_segments-1);
int data[2400] = {0};
int diff_data[2376] = {0};
int data_f_start[12] = {0};
int data_r_end[12] = {0};
int data_fall_start = 0;
int data_rise_end = 0;
bool updateflag = true;
bool localflag;
int Dth = 150;
float sd;

int supercount = 0;


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
  delay(1);
  data[ix+ 12*count] = analogRead(A1);
  //Serial.println(data[ix + 12*count]);
  if (ix == 11){
    count += 1;
  }
  if (count == data_segments){
    count = 0;
    supercount += 1;
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
    } else {
      // No gesture was performed 
      // Update DTH
      Serial.println("No gesture performed, updating Dth");
      //Dth = (int) median(data)/5;
      //Serial.println(Dth);
    }

    

    // Use standard deviation instead of divide by 3. 
    // So if threshold is too high, we can print error message 
    // use SD. 

    // Make better Dth by median 
    Dth = (int) quick_select(data, 2400)/5;

    // Calculate standard deviation
    sd = standard_dev(data);
    
    Serial.println(Dth);
    Serial.println(sd);
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

int median(int data[2400]){
  int temp;
  for(int i=0; i<2400; ++i){
    for(int j=0; j<2400-i; ++j){
      if (data[j] > data[j+1]){
        temp = data[j];
        data[j] = data[j+1];
        data[j+1] = temp;
      }
    }
  }
  return data[1200];
}

float standard_dev(int data[2400]){
  float temp=0.0;
  float s=0.0;
  for (int i=0; i<2400; ++i){
    s += data[i];
  }
  s = (float)s/(float)2400;
  for (int i=0; i<2400; ++i){
    temp += (data[i] - s)*(data[i]-s);
  }
  temp = (float) temp / (float)2400;
  //Serial.println("inside sd");
  //Serial.println(s);
  //Serial.println(temp);
  return sqrt(temp);
}

#define ELEM_SWAP(a,b) { register int t=(a);(a)=(b);(b)=t; }

int quick_select(int arr[], int n) 
{
    int low, high ;
    int median;
    int middle, ll, hh;

    low = 0 ; high = n-1 ; median = (low + high) / 2;
    for (;;) {
        if (high <= low) /* One element only */
            return arr[median] ;

        if (high == low + 1) {  /* Two elements only */
            if (arr[low] > arr[high])
                ELEM_SWAP(arr[low], arr[high]) ;
            return arr[median] ;
        }

    /* Find median of low, middle and high items; swap into position low */
    middle = (low + high) / 2;
    if (arr[middle] > arr[high])    ELEM_SWAP(arr[middle], arr[high]) ;
    if (arr[low] > arr[high])       ELEM_SWAP(arr[low], arr[high]) ;
    if (arr[middle] > arr[low])     ELEM_SWAP(arr[middle], arr[low]) ;

    /* Swap low item (now in position middle) into position (low+1) */
    ELEM_SWAP(arr[middle], arr[low+1]) ;

    /* Nibble from each end towards middle, swapping items when stuck */
    ll = low + 1;
    hh = high;
    for (;;) {
        do ll++; while (arr[low] > arr[ll]) ;
        do hh--; while (arr[hh]  > arr[low]) ;

        if (hh < ll)
        break;

        ELEM_SWAP(arr[ll], arr[hh]) ;
    }

    /* Swap middle item (in position low) back into correct position */
    ELEM_SWAP(arr[low], arr[hh]) ;

    /* Re-set active partition */
    if (hh <= median)
        low = ll;
        if (hh >= median)
        high = hh - 1;
    }
}

#undef ELEM_SWAP
