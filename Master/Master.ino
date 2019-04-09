//defines the number of slaves on the I2C line,
//starts at slave 5 and increases the slave number by 1 each time
#define NUM_SLAVES 10


char data[NUM_SLAVES][64];
String buff = "";

#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(57600);  // start serial for output
  mySerial.begin(57600);
  Serial.println("I'm working");
}

void loop() {
  //---------get data from other arduinos on i2c bus--------------


  for (int r = 0; r < NUM_SLAVES; r++){
    //Serial.println(5 + r);
    bool record = false;
    for (int i = 0; i < 6; i++){
      Wire.requestFrom(5 + r, 32);
      while (Wire.available()) { // slave may send less than requested
        char c = Wire.read(); // receive a byte as character
        if (c == '<'){
          record = true;
        }
        if (record){
          buff += c;
        }
      }
      if (buff.indexOf(">") > 0){
        break;
      }
      delay(10);
    }
    buff.toCharArray(data[r], sizeof(data[r]));
    buff = "";
    //Serial.println(data[r]);
    delay(5);
  }
  //--------------finished getting data from other arduinos-------------

  //-----------------print out the data over serial--------------------
//  for (int i = 0; i < NUM_SLAVES; i++){
//    Serial.println(data[i]);
//  }
//  Serial.println("");


  //------------send out all revorded data over i2c for telecom--------
//  Wire.beginTransmission(3); //specify device with slave address 3
//  Wire.write(returndata);              //send 'returndata' to above address
//  Wire.endTransmission();    //stop sending


  //------------get or send serial data from radio to serial montior---------
  //mySerial.println("AT1");
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  while (Serial.available()) {
    mySerial.write(Serial.read());
    delay(100);
  }
   for (int i = 0; i < NUM_SLAVES; i++){
    mySerial.write(data[i]);
    delay(1);
    mySerial.write('\n');
    delay(1);
    Serial.write(data[i]);
    Serial.write('\n');
    delay(1);
  }
  //---------delay to let the temperature sensors keep up--------
  delay(1000);
}
