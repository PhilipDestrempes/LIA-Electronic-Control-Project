/* The following program is designed to create a controller using on/off control and a hysterisis. The controller will 
output a signal to an LED, which will then be read by an LDR. The state of the LDR will be read as an analog input. The 
setpoint (Sp) will be what the light intensity of the LED should be and the LDR will output the process value (PV). Based 
on the results, the out put to the LED will be controlled using an analog output. The goalof the PI control will be to 
minimize error as much as possible and have it so that the PV follows the SP as closely as possible with very minimal to 
no error. The results and values will be displayed on the serial monitor, lcd and serialplotter. It will utlize several 
lcd screens, which will be switched between each other between left right pushbuttons. Some variables on the screen will 
also be able to increase and decrease with up down pushbuttons. */


#include <LiquidCrystal.h>    //include liquid crystal library 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int LED= 6;           //set integer LED to 6 
int button1= 10;   //set integer button1 to 10
int button2= 9;    //set integer button2 to 9
int button3= 8;     //set integer button3 to 8
int button4= 7;     //set integer button4 to 7
int SetP=0;        //set integer SetP (setpoint) to 0 
int HYS=20;        //set integer HYS (hysterisis) to 20 
int SCREEN= 0;     //set integer screen to 0 
int CO= 0;         //set integer CO (controller output) to 0        

void setup() {

pinMode(LED,OUTPUT);   //set LED as an output 
pinMode(A0, INPUT);     //set pin A0 (analoginput 0) as an INPUT 
pinMode(button1, INPUT_PULLUP);   //set button1 as an input pull-up
pinMode(button2, INPUT_PULLUP);   //set button2 as an input pull-up
pinMode(button3, INPUT_PULLUP);   //set button3 as an input pull-up
pinMode(button4, INPUT_PULLUP);   //set button4 as an input pull-up
Serial.begin(9600);      //serial begin at 9600 bps 
lcd.begin(16, 2);        //lcd begin at 16 columns 2 rows 

}

void loop() {

int UP= digitalRead(button1);   //set integer up as reading the state of button1
int DOWN= digitalRead(button2);  //set integer down as reading the state of button2
int RIGHT= digitalRead(button3);  //set integer right as reading the state of button3
int LEFT= digitalRead(button4);  //set integer left as reading the state of button4

int PV= analogRead(A0);    //set integer PV (process value) equal the analog reading of analog input pin A0
analogWrite(LED, CO);          //analog write the value of the LED based on CO 

if (PV <= SetP- HYS){      //if PV is less than or equal to SetP minus hysterisis then 
CO= 255;                   // CO is equal to 255 
}

else if (PV >= SetP+ HYS){     //if PV is greater than or equal to SetP minus hysterisis then
CO= 0;                         // CO is equal to 0
}

Serial.print("SP= ");          //serial print "SP= "
Serial.print(SetP);            //serial print SetP
Serial.print("   PV= ");       //serial print "  PV= "
Serial.print(PV);              //serial print PV
Serial.print("    CO= ");       //serial print "  CO= "
Serial.print(CO);              //serial print CO 
Serial.print("HYS= ");        //serial print "  HYS= "
Serial.println(HYS);          //serial print HYS

delay(100);                  //delay 100 milliseconds

if (RIGHT== LOW){             //if right button is pressed then
SCREEN= SCREEN+1;             //screen counter adds +1 

if (SCREEN>3){            //if screen counter is greater than 3 then

SCREEN=3;              //screen counter is equal to 3 
}
}

if (LEFT== LOW){            //if left button is pressed then
SCREEN= SCREEN-1;            //screen counter subtracts 1

if(SCREEN<0){                //if screen counter is equal to 0 then

SCREEN=1;                     //screen counter is equal to 1
}
}

if (SCREEN==1){             //if screen counter equals 1 then

lcd.clear();                 //clear lcd
lcd.setCursor(0,0);          //set the lcd cursor to column 0 row 0 
lcd.print("SP= ");          //lcd print "SP= "
lcd.print(SetP);          //lcd print SetP

delay(100);              //delay 100 milliseconds 

if (UP == LOW) {            //if pushbutton up is pressed then
    SetP = SetP + 10;          //SetP counter adds +10 
    if (SetP >= 1023) {        //if SetP is greater than or equal to bitvalue 1023.0 then
      SetP = 1023; }           //SetP is equal to bitvalue 1023.0 
    
  }  if (DOWN == LOW) {          //if pushbutton down is pressed then
    SetP = SetP - 10;          //Setp counter subtracts 10 
    if (SetP <= 0) {          //if Setp counter is less than or equal to 0.0 then 
      SetP = 0; }          //Setp counter is equal to zero 
    
  }

}

if (SCREEN==2){              //if screen counter equals 2 then

  lcd.clear();                //clear lcd
  lcd.setCursor(0,0);         //set the lcd cursor to column 0 row 0 
  lcd.print("PV= ");           //lcd print "PV= "  
  lcd.print(PV);               //lcd print PV  
  lcd.print("  CO=");          //lcd print "   CO= "  
  lcd.print(CO);               //lcd print CO  
  
  delay(100);                //delay 100 milliseconds 
 
}

if (SCREEN==3){          //if screen counter equals 3 then

  lcd.clear();                //clear lcd 
  lcd.setCursor(0,0);        //lcd set cursor to column 0 row 0 
  lcd.print("HYS= ");        //lcd print "HYS= "
  lcd.println(HYS);        //lcd print hysterisis 
 
  delay(100);          //delay 100 miliseconds 

 if (UP == LOW) {          //if pushbutton up is pressed then 
    HYS = HYS + 1;         //HYS counter adds +1 

  } if (DOWN == LOW) {         //if pushbutton down is pressed then
    HYS = HYS - 1;           //HYS counter subtracts 1 
    if (HYS <= 0) {         //if HYS is less than or equal to 0 
      HYS = 0;             //HYS is equal to 0 
    } 
  }

}
}