#include <Wire.h>
#include <stdint.h>
#include <inttypes.h>

// (c) Michael Schoeffler 2016, http://www.mschoeffler.de
#include <SD.h> //Load SD library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int address;
int chipSelect = 4; //chip select pin for the MicroSD Card Adapter
int high_byte_pin = 2;    //IO2
int high_byte_pin2 = 3;    //IO3
uint32_t v;
byte v_arr[4];

#define W1_COLUMN 784
#define W1_ROW 64
#define W2_COLUMN 64
#define W2_ROW 10

union {
        float f;
        uint32_t u;
    } f2u;

File file; // file object that is used to read and write data
void setup()
{
  address = 114;
  pinMode(high_byte_pin, OUTPUT);
  pinMode(high_byte_pin2, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  //Serial.println("Verilog I2C Test\n\n");

  //--------------File--------------
  pinMode(chipSelect, OUTPUT); // chip select pin must be set to OUTPUT mode
  if (!SD.begin(chipSelect)) { // Initialize SD card
    Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
  }
  
  if (SD.exists("file.txt")) { // if "file.txt" exists, fill will be deleted
    Serial.println("File exists.");
    if (SD.remove("file.txt") == true) {
      Serial.println("Successfully removed file.");
    } else {
      Serial.println("Could not removed file.");  //Discord
    }
  }
  delay(1000);
}

void loop()
{
  //-----------read part------------------
  file = SD.open("weight1.dat", FILE_READ); // open "file.txt" to read data
  if(file) {
    Serial.println("- – Reading start – -");
    char character;
    char str[20];
    long int count = 0;
    float temp_data = 0;
    int i = 0;
    int error;
    Serial.println("Im in outside");
    while ((character = file.read())  != -1) { // this while loop reads data stored in "file.txt" and prints it to serial monitor
//      fscanf(file, "%f", character);
      Serial.print(character);
      
     if (character != ' '){
      str[i]=character;
      i=i+1;
      //Serial.println("Im in 1");
     }
       if (character == ' ' || character == '\n'){
         str[i]='\0';
         temp_data = atof(str);
         f2u.f = temp_data;
        Serial.println(" ");
        Serial.println("Im in 2");
        i=0;
        if(count < 50176) {
            Serial.print("Got a data:");
            Serial.print(f2u.u, HEX);
            Serial.print(" in Column: ");
            Serial.print(count/W1_ROW);
            Serial.print(", Row: ");
            Serial.println(count%W1_ROW);
            Serial.println("Im in 3");
            count++;
            v = f2u.u;
            v_arr[0] = v&0xFF;            // LSB
            v_arr[1] = (v>>8)&0xFF;       //
            v_arr[2] = (v>>16)&0xFF;      //  
            v_arr[3] = (v>>24)&0xFF;      //  MSB
            for(int k = 0; k < 4; k++) {
              if(k == 3) digitalWrite(high_byte_pin, HIGH);
              else digitalWrite(high_byte_pin, LOW);
              Wire.beginTransmission(address);
              Wire.write(v_arr[k]);
              error = Wire.endTransmission();
              
              //delay(1000);
              Serial.println("Im in 4");
            } 
          }
          delay(5000);
          Serial.println("Im in 5");
        }
      //delay(100);
    }
    file.close();
    Serial.println("Im in 6");
    Serial.println("- – Reading end – -");
    }else {
    Serial.println("Could not open file (reading).");
    }
  delay(5000);
  

   
}
