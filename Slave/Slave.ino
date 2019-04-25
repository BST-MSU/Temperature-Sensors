//assignes the module a slave number
#define SLAVE 10

//how many samples should it take, more = better accuracy but takes longer to read
#define NUMSAMPLES 5

//adjust each temperature to account for tolerance if desired.
//put a positive number to increase the reported temperature
//put a negative number to decrease the temperature
#define TEMP0_ADJUST 0
#define TEMP1_ADJUST 0
#define TEMP2_ADJUST 0
#define TEMP3_ADJUST 0
#define TEMP4_ADJUST 0
#define TEMP5_ADJUST 0


//--------------------------Do not alter below this point-------------------------------


//Defines the analog thermistor read pins
#define TEMP_PIN0 A0
#define TEMP_PIN1 A1
#define TEMP_PIN2 A2
#define TEMP_PIN3 A3
#define TEMP_PIN4 A6
#define TEMP_PIN5 A7

#include <Wire.h>

 float Fahrenheit=0;
 float Celcius=0;
 char data[64];
 int temp[7];


 const int resistance[126] = {14066, 13457, 12878, 12327, 11803, 11305, 10830, 10377, 9946, 9535, 9128, 8770, 8413, 8073, 7748, 7438, 7142, 6859, 6589, 6330, 6083, 5847, 5621, 5405, 
                            5198, 5000, 4810, 4628, 4454, 4287, 4128, 3975, 3828, 3687, 3552, 3423, 3299, 3179, 3065, 2955, 2850, 2749, 2652, 2558, 2469, 2382, 2300, 2220, 2144, 
                            2070, 2032, 1931, 1866, 1803, 1742, 1684, 1628, 1574, 1522, 1472, 1423, 1377, 1332, 1289, 1247, 1207, 1169, 1132, 1096, 1061, 1028, 996, 964, 935, 906, 
                            878, 851, 825, 800, 775, 752, 729, 708, 687, 666, 647, 627, 609, 591, 574, 558, 541, 526, 511, 496, 482, 469, 456, 443, 430, 419, 407, 396, 385, 374, 
                            364, 354, 345, 336, 327, 318, 310, 301, 293, 286, 278, 271, 264, 257, 251, 244, 238, 232, 226, 221, 215};

void setup() {
  analogReference(EXTERNAL);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Wire.begin(SLAVE);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {

  temp[0] = SLAVE;
  temp[1] = get_temp(0);
  temp[1] += TEMP0_ADJUST;
  temp[2] = get_temp(1);
  temp[2] += TEMP1_ADJUST;
  temp[3] = get_temp(2);
  temp[3] += TEMP2_ADJUST;
  temp[4] = get_temp(3);
  temp[4] += TEMP3_ADJUST;
  temp[5] = get_temp(4);
  temp[5] += TEMP4_ADJUST;
  temp[6] = get_temp(5);
  temp[6] += TEMP5_ADJUST;

  
  //Serial.println("");
  
    
  //Serial.println(data);
  
  delay(10);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write( (byte *) &temp, sizeof(temp));; // respond with message of 32 bytes, this is the max arduinos can send over i2c
  // as expected by master
   digitalWrite(13, HIGH);
   delay(100);
   digitalWrite(13, LOW);
}

int get_temp(int x){
  float temp;
  float average = 0;
  int thermistorpin[] = {TEMP_PIN0, TEMP_PIN1, TEMP_PIN2, TEMP_PIN3, TEMP_PIN4, TEMP_PIN5};
  int samples[NUMSAMPLES];
  average = 0;
  // take N samples in a row, with a slight delay 
  for (int i = 0; i < NUMSAMPLES; i++) {
    samples[i] = analogRead(thermistorpin[x]);
    delay(10); 
  }
  
  // average  the samples out
  for (int i = 0; i < NUMSAMPLES; i++) {
     average += samples[i];
  }
  average /= NUMSAMPLES;
  
  // convert the value to resistance 
  average = 1023 / average - 1;
  average = 4990 / average;
  //Serial.println(average);
  
  if (average > resistance[0]){
    temp = -999;
    return temp;
  }
  if (average < resistance[125]){
    temp = 999;
    return temp;
  }

  int temp_high = 0;
  for (int i = 0; i < 125; i++){
    if (average > resistance[i]){
      temp_high = i;
      break;
    }
  }
  
  int temp_low = temp_high - 1;
  temp = float( map(average, resistance[temp_low], resistance[temp_high], temp_low*100, temp_high*100) )/100;
  int ret = temp * 10;
  //Serial.println(ret);
  return ret;
}
