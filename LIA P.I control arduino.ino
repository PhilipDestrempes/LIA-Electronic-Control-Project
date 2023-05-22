/* The following program is designed to create a controller using proportional and integral gain (PI). The 
controller will output a signal to an LED, which will then be read by an LDR. The state of the LDR will be read 
as an analog input. The setpoint (Sp) will be what the light intensity of the LED should be and the LDR will output
the process value (PV). Based on the results, the out put to the LED will be controlled using an analog output. The goal
of the PI control will be to minimize error as much as possible and have it so that the PV follows the SP as closely as 
possible with very minimal to no error. The results and values will be displayed on the serial monitor, lcd and serial
plotter. It will utlize several lcd screens, which will be switched between each other between left right pushbuttons. 
Some variables on the screen will also be able to increase and decrease with up down pushbuttons. */

#include <LiquidCrystal.h>   //include liquid crystal library 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);         

int LED= 6;     //set integer LED to 6 
int button1= 10;   //set integer button1 to 10
int button2= 9;   //set integer button2 to 9
int button3= 8;    //set integer button3 to 8
int button4= 7;     //set integer button4 to 7
int SetP=0.0;       //set integer SetP (setpoint) to 0.0
int SCREEN= 0;      //set integer SCREEN to 0
int CO= 0;         //set integer CO (controller output) to 0
int Error= 0;       //set integer Error to 0  
float Pgain= 0.010;      //set float Pgain (proportional gain) to 0.010
float Igain= 0.010;      //set float Igain (integral gain) to 0.010
int integral_action;      //set integer integral_action
unsigned long previousMillis = 0;       //set unsigned long previousMillis to 0
const long interval= 100;           //set constant long interval to 100
unsigned long currentMillis;        //set unsigned long currentMillis

void setup() {

pinMode(LED,OUTPUT);   //set LED as an output 
pinMode(A0, INPUT);    //set pin A0 (analoginput 0) as an INPUT
pinMode(button1, INPUT_PULLUP);  //set button1 as an input pull-up
pinMode(button2, INPUT_PULLUP);  //set button2 as an input pull-up
pinMode(button3, INPUT_PULLUP);  //set button3 as an input pull-up
pinMode(button4, INPUT_PULLUP);  //set button4 as an input pull-up
Serial.begin(9600);  //serial begin at 9600 bps 
lcd.begin(16, 2);    //lcd begin at 16 columns 2 rows 

}

void loop() {

int UP= digitalRead(button1);   //set integer up as reading the state of button1
int DOWN= digitalRead(button2);  //set integer down as reading the state of button2
int RIGHT= digitalRead(button3);  //set integer right as reading the state of button3
int LEFT= digitalRead(button4);  //set integer left as reading the state of button4

int PV= analogRead(A0);    //set integer PV (process value) equal the analog reading of analog input pin A0
currentMillis = millis();  //make the currentMillis equal to the millis of the arduino 

if (currentMillis - previousMillis >= interval){  //if the currentMillis minus the previousMillis is greater or equal to the interval then

int Ierror= (Igain * integral_action);           //integer Ierror (integral error) is equal to Igain times integral_action
previousMillis= currentMillis;                 //previousMillis is equal to currentMillis
Error= (SetP - PV);                            //Error is equal to the Setp minus the PV
integral_action= (integral_action + Error);      //integral_action is equal to the intergral_action plus the error
CO= (((Pgain * Error) + Ierror)/10);             //CO is equal to Pgain times Error plus Ierror all divided by 10 

if (Ierror >= 255){                           //if the Ierror is gretaer than or equal to 255 then 
Ierror= 255;                                 //Ierror is equal to 255 
}
  
if (CO > 255){                           //if CO is greater then 255 (value cap for CO)
CO= 255;                                //CO is equal to 255 
}

if (CO < 0){                             //if CO is less then 255 (value cap for CO)                             
CO= 0;                                  //CO is equal to 0 
}
}

analogWrite(LED, CO);          //analog write the value of the LED based on CO 


if (RIGHT== LOW){             //if right button is pressed then
SCREEN= SCREEN+1;             //screen counter adds +1 

if (SCREEN>4){             //if screen counter is greater than 4 then

SCREEN=4;              //screen counter is equal to 4 
}
}

if (LEFT== LOW){             //if left button is pressed then
SCREEN= SCREEN-1;             //screen counter subtracts 1 

if(SCREEN<0){                 //if screen counter is equal to 0 then

SCREEN=1;                    //screen counter is equal to 1 
}
}


Serial.print("SP= ");          //serial print "SP= "
Serial.print(SetP);            //serial print SetP
Serial.print("  PV= ");          //serial print "  PV= "
Serial.print(PV);               //serial print PV
Serial.print("   CO= ");          //serial print "   CO= "
Serial.print(CO);                //serial print CO
Serial.print("  Error= ");           //serial print "  Error= "
Serial.print(Error);               //serial print Error
Serial.print("  PGAIN= ");          //serial print "  PGAIN= "
Serial.print(Pgain);                //serial print Pgain
Serial.print("  IGAIN= ");         //serial print "  IGAIN= "
Serial.println(Igain);           //serial print Igain
delay(100);                   //delay 100 milliseconds 

if (SCREEN==1){              //if screen counter equals 1 then

lcd.clear();                 //clear lcd
lcd.setCursor(0,0);          //set the lcd cursor to column 0 row 0 
lcd.print("SP= ");          //lcd print "SP= "
lcd.print(SetP);          //lcd print SetP
lcd.setCursor(0,1);          //lcd set cursor to column 0 row 1 
lcd.print("PV= ");          //lcd print "PV= "
lcd.print(PV);            //lcd print  print PV


delay(100);              //delay 100 milliseconds 

if (UP == LOW) {            //if pushbutton up is pressed then
    SetP = SetP + 10.0;          //SetP counter adds +10 
    if (SetP >= 1023.0) {        //if SetP is greater than or equal to bitvalue 1023.0 then
      SetP = 1023.0; }           //SetP is equal to bitvalue 1023.0 
    
  }  if (DOWN == LOW) {          //if pushbutton down is pressed then
    SetP = SetP - 10.0;          //Setp counter subtracts 10 
    if (SetP <= 0.0) {          //if Setp counter is less than or equal to 0.0 then 
      SetP = 0.0; }          //Setp counter is equal to zero 
    
  }

}

if (SCREEN==2){              //if screen counter equals 2 then

lcd.clear();                 //clear lcd
lcd.setCursor(0,0);          //set the lcd cursor to column 0 row 0 
lcd.print("CO=");           //lcd print "CO= "        
lcd.print(CO);              //lcd print CO
lcd.setCursor(0,1);          //lcd set cursor to column 0 row 1 
lcd.print("Error= ");         //lcd print "Error= "
lcd.print(Error);             //lcd print Error 

delay(100);               //delay 100 milliseconds 
  
}

if (SCREEN==3){          //if screen counter equals 3 then

lcd.clear();              //clear lcd 
lcd.setCursor(0,0);         //lcd set cursor to column 0 row 0 
lcd.print("PGAIN= ");        //lcd print "PGAIN= "
lcd.println(Pgain);         //lcd print PGAIN

delay(100);          //delay 100 miliseconds 

 if (UP == LOW) {                //if pushbutton up is pressed then               
    Pgain = Pgain + 0.010;         //Pgain counter adds +0.010 

  } if (DOWN == LOW) {           //if pushbutton down is pressed then
    Pgain = Pgain - 0.010;           //Pgain counter subtracts by 0.010
    if (Pgain <= 0.0) {          //if Pgain is less than or equal to 0.0 then
      Pgain = 0.0;               //Pgain equals 0.0
    } 
  }

}

if (SCREEN==4){          //if screen counter equals 3 then

lcd.clear();                //clear lcd 
lcd.setCursor(0,0);         //lcd set cursor to column 0 row 0 
lcd.print("IGAIN= ");        //lcd print "IGAIN= "
lcd.println(Igain);        //lcd print IGAIN


delay(100);               //delay 100 miliseconds 

 if (UP == LOW) {               //if pushbutton up is pressed then  
    Igain = Igain + 0.010;         //Igain counter adds +0.010 

  } if (DOWN == LOW) {           //if pushbutton down is pressed then
    Igain = Igain - 0.010;         //Igain counter subtarcts 0.010 
    if (Igain <= 0.0) {          //if Igain is less than or equal to 0.0 then
      Igain = 0.0;               //Igain equals 0.0
    } 
  }

}

}

