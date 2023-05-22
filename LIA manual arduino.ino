/* The following program is designed to create a controller using manual control. The 
The controller will output a signal to an LED, which will then be read by an LDR. The 
state of the LDR will be read as an analog input. The setpoint (Sp) will be what the 
light intensity of the LED should be and the LDR will output the process value (PV). 
Based on the results, the output to the LED will be controlled using an analog output, 
which will be controlled by a potentiometer that will determine the set point. The values
will then be printed on a serial and lcd monitor. */

#include <LiquidCrystal.h>    //include liquid crystal library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int LED= 6;           //set integer LED to 6       

void setup() {

pinMode(LED,OUTPUT);     //set LED as an output 
pinMode(A0, INPUT);     //set pin A0 (analog input 0) as an INPUT 
pinMode(A1, INPUT);     //set pin A1 (analog input 1) as an INPUT 
Serial.begin(9600);      //serial begin at 9600 bps 
lcd.begin(16, 2);        //lcd begin at 16 columns 2 rows 

}

void loop() {

int PV= analogRead(A0);         //set int PV to read the analog input of A0
Serial.print("PV= ");           //serial print "  PV= "
Serial.print(PV);               //serial print PV
lcd.setCursor(0,0);            //set the lcd cursor to column 0 row 0
lcd.print("PV= ");           //lcd print "PV= "  
lcd.print(PV);               //lcd print PV  

int Sp= analogRead(A1);         //set int Sp to read the analog input of A0 
Serial.print("   Sp= ");         //serial print "  Sp= "
Serial.print(Sp);                 //serial print Sp
lcd.setCursor(9,0);           //set the lcd cursor to column 9 row 0
lcd.print("Sp= ");           //lcd print "Sp= "  
lcd.print(Sp);               //lcd print Sp 


int CO= map(Sp, 0, 1023, 0, 255);      //set int CO to map the Sp from bits to analog values 
Serial.print("   CO= ");             //serial print "   CO= "
Serial.println(CO);                  //serial print CO
lcd.setCursor(0,1);                   //set lcd cursor to to column 0 row 1
lcd.print("CO= ");                   //lcd print "CO= "
lcd.print(CO);                   //lcd print CO

analogWrite(LED, CO);            //analog write LED state based on CO value 
delay(100);                   //delay 100 milliseconds 

}
