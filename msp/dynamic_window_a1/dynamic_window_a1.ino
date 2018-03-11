int i=0;
int j=0;
int k=0;
int ix=0;
int count=0;

bool updateflag = true;
bool localflag;
int Dth = 150;
float sd;

int current[12] = {0};
int data[1200] = {0};

int supercount = 0;

// Stable Region Tweaker
float drop_percentage = 0.75; 

// Swipe Count Reference
int scr = -1;
int temp_segment_blast = 0;
String last = "prediction right swipe movement";
int scr_cnt = 0;
int blast_cnt = 0;

// -----------------------------------
// dont use C9 // see physical circuit
// -----------------------------------

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
  current[ix] = analogRead(A1);
  //Serial.println("-----------");
  //Serial.println(ix);
  //Serial.println(current[ix]);
  
  
  if (ix == 11){
    count += 1;
    temp_segment_blast = find_stable_segment(current);
    //Serial.println("~~~~~~");
    //    for (int i=0; i<12; i++){
    //      Serial.println(current[i]);
    //    }
    //Serial.println(temp_segment_blast);
  
    if (temp_segment_blast == -1){
      // do nothing 
      scr = -1;
      scr_cnt = 0;
      blast_cnt = 0;
    } else {
      if (scr == -1) {
        // set scr for first segment
        scr = temp_segment_blast;
        scr_cnt = 0;
        blast_cnt = 0;
      } else {
        // predict for subsequent segment
        if (temp_segment_blast < scr) {
          Serial.println(scr);
          Serial.println(temp_segment_blast);
          last = "prediction left swipe movement";
          scr_cnt += 1;
          blast_cnt += scr - temp_segment_blast;
          
        } 
        if (temp_segment_blast > scr) {
          Serial.println(scr);
          Serial.println(temp_segment_blast);
          last = "prediction right swipe movement";
          scr_cnt += 1;
          blast_cnt -= temp_segment_blast - scr;
        }
        scr = temp_segment_blast;
        //Serial.println("**~~~~~");
        //for (int i=0; i<12; i++){
        //  Serial.println(current[i]);
        // }
        //Serial.println("j");
        //Serial.println(temp_segment_blast);
        if (scr_cnt > 4) {
          
          if (blast_cnt < 0) {
            Serial.println("voted: prediction right swipe movement");
          } else {
            Serial.println("voted: prediction left swipe movement");
          }
          scr_cnt = 0;
          blast_cnt = 0;
        }
        Serial.println(last);
      }
    }
  }

  // Make better Dth by median 
  // Dth = (int) quick_select(current, 12)/5;

  // Calculate standard deviation
  // sd = standard_dev(current);
}

// ---------------------------------------------------------
// 
int find_stable_segment(int arr[12]){
  // return -1, if stable, else returns index of arr
  // always of length 12 
  int copy[12] = {0};
  for (int i=0; i<12; i++){
    copy[i] = arr[i];
  }
  float median = (float)quick_select(copy, 12);
  int j;
  median = median * drop_percentage;
  for (int i=0; i<12; i++){
    if (arr[i] < median){
      j = i;
      while (j < 11) {
        if (arr[j+1] < arr[j]) {
          j=j+1;
        } else {
          break;
        }
      }
      return j;
    }
  }
  return -1;
}




// ----------------------------------------------------------
// Math functions 
// ----------------------------------------------------------

float standard_dev(int arr[], int n){
  float temp=0.0;
  float s=0.0;
  for (int i=0; i<n; ++i){
    s += arr[i];
  }
  s = (float)s/(float)n;
  for (int i=0; i<n; ++i){
    temp += (arr[i] - s)*(arr[i]-s);
  }
  temp = (float) temp / (float)n;
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

//* Flexible window
//* natural gesture 
//* Block cell different threshold 
//* finger - No hand - No phone 
// differentiate from tree / other inter
//* All types of swiping - middle to end-middle to middle 
