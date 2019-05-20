/* 
 *  updated chuckie 2019.03.26.
 *  original code for matrix: https://create.arduino.cc/projecthub/SAnwandter1/programming-8×8-led-matrix-23475a
 *  DHT-11 library: https://github.com/adidax/dht11
 */

#include <dht11.h>
#define DHT11PIN 3

dht11 DHT11;

//kijelzes
int extr;
int egy;
int t;
//menu
volatile byte menu = 0;

//update from SAnwandter

#define ROW_1 12
#define ROW_2 13
#define ROW_3 A0
#define ROW_4 A1
#define ROW_5 A2
#define ROW_6 A3
#define ROW_7 A4
#define ROW_8 A5

#define COL_1 4
#define COL_2 5
#define COL_3 6
#define COL_4 7
#define COL_5 8
#define COL_6 9
#define COL_7 10
#define COL_8 11

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};
byte t_0[] = {B00011111,B01011111,B01011111,B01011111,B01011111,B01011111,B01011111,B00011111};
byte t_1[] = {B11011111,B11011111,B11011111,B11011111,B11011111,B11011111,B11011111,B11011111};
byte t_2[] = {B00011111,B11011111,B11011111,B00011111,B01111111,B01111111,B01111111,B00011111};
byte t_3[] = {B00011111,B11011111,B11011111,B00011111,B11011111,B11011111,B11011111,B00011111};
byte t_4[] = {B01111111,B01111111,B01111111,B00011111,B11011111,B11011111,B11011111,B11011111};
byte t_5[] = {B00011111,B01111111,B01111111,B00011111,B11011111,B11011111,B11011111,B00011111};
byte t_6[] = {B00011111,B01111111,B01111111,B00011111,B01011111,B01011111,B01011111,B00011111};
byte t_7[] = {B00011111,B11011111,B11011111,B11011111,B11011111,B11011111,B11011111,B11011111};
byte t_8[] = {B00011111,B01011111,B01011111,B00011111,B01011111,B01011111,B01011111,B00011111};
byte t_9[] = {B00011111,B01011111,B01011111,B00011111,B11011111,B11011111,B11011111,B00011111};
byte e_0[] = {B11110001,B11110101,B11110101,B11110101,B11110101,B11110101,B11110101,B11110001};
byte e_1[] = {B11111011,B11111011,B11111011,B11111011,B11111011,B11111011,B11111011,B11111011};
byte e_2[] = {B11110001,B11111101,B11111101,B11110001,B11110111,B11110111,B11110111,B11110001};
byte e_3[] = {B11110001,B11111101,B11111101,B11110001,B11111101,B11111101,B11111101,B11110001};
byte e_4[] = {B11110111,B11110111,B11110111,B11110001,B11111101,B11111101,B11111101,B11111101};
byte e_5[] = {B11110001,B11110111,B11110111,B11110001,B11111101,B11111101,B11111101,B11110001};
byte e_6[] = {B11110001,B11110111,B11110111,B11110001,B11110101,B11110101,B11110101,B11110001};
byte e_7[] = {B11110001,B11111101,B11111101,B11111101,B11111101,B11111101,B11111101,B11111101};
byte e_8[] = {B11110001,B11110101,B11110101,B11110001,B11110101,B11110101,B11110101,B11110001};
byte e_9[] = {B11110001,B11110101,B11110101,B11110001,B11111101,B11111101,B11111101,B11110001};
//byte potty[] = {B11111110,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
  byte eredmeny[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
  
float timeCount = 0;

void setup() 
{
    // Open serial port
    Serial.begin(9600);
    
    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    // the display will be very dim.
    for (byte i = 4; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);


  //menu gomb
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(0,valtas,RISING); // digital pin 2 // up

    delay(2000);
    int chk = DHT11.read(DHT11PIN);
}

//update chuckie for DHT
void valtas(){
    menu = (menu <= 1) ? menu+1 : 0;
    int chk = DHT11.read(DHT11PIN);
    delay(2000);
}

void  osszeadas(byte tizesek[], byte egyesek[]){
  for (byte i = 0; i< 9; i++) {
    eredmeny[i] = tizesek[i] + egyesek[i];
    if(menu == 0 && i==0) // if display temperature toggle top-right led 
      eredmeny[i] ^= 1; 
  }
}

void kijelzes(byte tizes, byte egyes){
    byte tizesek;
    byte egyesek;
    if(tizes == 0)
      tizesek = t_0;
    else if(tizes == 1)
      tizesek = t_1;
    else if(tizes == 2)
      tizesek = t_2;
    else if(tizes == 3)
      tizesek = t_3;
    else if(tizes == 4)
      tizesek = t_4;
    else if(tizes == 5)
      tizesek = t_5;
    else if(tizes == 6)
      tizesek = t_6;
    else if(tizes == 7)
      tizesek = t_7;
    else if(tizes == 8)
      tizesek = t_8;
    else if(tizes == 9)
      tizesek = t_9;
  
    if(egyes == 0)
      egyesek = e_0;
    else if(egyes == 1)
      egyesek = e_1;
    else if(egyes == 2)
      egyesek = e_2;
    else if(egyes == 3)
      egyesek = e_3;
    else if(egyes == 4)
      egyesek = e_4;
    else if(egyes == 5)
      egyesek = e_5;
    else if(egyes == 6)
      egyesek = e_6;
    else if(egyes == 7)
      egyesek = e_7;
    else if(egyes == 8)
      egyesek = e_8;
    else if(egyes == 9)
      egyesek = e_9;

     osszeadas(tizesek, egyesek);
     drawScreen(eredmeny);   

}

void loop() {
  delay(10);
  //update chuckie for DHT
     if(menu == 0)
        extr =  round((float)DHT11.temperature * 100.0) / 100.0;
      else
        extr = round((float)DHT11.humidity * 100.0) / 100.0;
        
      egy = extr % 10;
      t = (extr / 10) % 10;
      //ha 0
      egy = (egy == 0) ? 10 : egy;
      t = (t == 0) ? 10 : t;

    kijelzes(t, egy);
}
 void  drawScreen(byte buffer2[])
 { 
   // Turn on each row in series
    for (byte i = 0; i < 8; i++)        // count next row
     {
        digitalWrite(rows[i], HIGH);    //initiate whole row
        for (byte a = 0; a < 8; a++)    // count next row
        {
          // if You set (~buffer2[i] >> a) then You will have positive
          digitalWrite(col[a], (buffer2[i] >> a) & 0x01); // initiate whole column
          delayMicroseconds(100);       // uncoment deley for diferent speed of display
          digitalWrite(col[a], 1);      // reset whole column
        }
        digitalWrite(rows[i], LOW);     // reset whole row
        // otherwise last row will intersect with next row
    }
}
