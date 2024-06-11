
//Barometer Mechanical  gauge , This works , It displays In/Hg  and Millibars
// 
// To correct the barometer for  altitude above sea level use the 10 turn potentiometer to adjust the meter to read what your local barormeter setting. That can be obtained from your local airport or cell phone 
// //
//This BMP180 board/chip uses I2C 7-bit address 0x77.
// The MCP4725 default address is 0x62
//This is now setup for the AT Nano 
//Rev 2 added a gain correction term to compensate for 5% resistors in the voltage scaling op amp circuit
// Rev 4 - Added Led trend lights. Timer set for 1 Hr update.

#include <Adafruit_MCP4725.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
int  Timer=0;
int Timermax= 3600; //How many seconds for LED update - 3600 = 1 hr

//Variables
double  History[11]; //Declare history array
double old=29.92 ; 
double newx=29.92;

// these are a required variables for the graphing functions
 Adafruit_BMP085 bmp; // Start BMP,  This also works for the BMP180
Adafruit_MCP4725 dac; //open the DAC   



void setup() {

  Serial.begin(9600);
#define potmeterPin A0;  //Potentiometer is now on A0 , this is the offset voltage to compensate for altitude above sealevel  
 
// Set up BMP085
  
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}}
 //setup the DAC
//Adafruit_MCP4725 dac; //open the DAC   
#define DAC_RESOLUTION    (9) //  This can't be more than 9. The DAC is 12 bits but the statement requires 9 to work
 dac.begin(0x62);
 if (!dac.begin()) {
  Serial.println("Could not find a valid DAC sensor, check wiring!");
  while (1) {}}
}



  
  
  

void loop(void) { 
 
   Serial.begin(9600);
   delay (20);
 
int Gled = 4 ; //green led on pin D2
int Rled = 5; //Red led on pin D3 
int Yled = 2; //yellow led on D4
int Bled = 3; //blue led on D5

/* These LEDs were used in a previous sketch to indicate pressure rising and falling over the previous hour. I left them in in casu you want to use them 
 You will need to hook up a LED in series with a 220 resistor .
 Green = pressure rising 
 Red = pressure falling 
 Yellow means the pressure change is less than 0.02 " of Hg
 Blue = pressure change was > 0.06 in of HG
 */ 
pinMode(Gled,OUTPUT);
pinMode(Rled,OUTPUT);  
pinMode(Yled,OUTPUT);
pinMode(Bled,OUTPUT);

digitalWrite (Yled ,HIGH);  //To show led work
double p = analogRead(A0); //Potientiometer input for altitude offset
 double Offset = ((p/1024)*5)-1; //map pot to in of Hg ofset              
double Q=(bmp.readPressure()); //read the pressure from the barometer in pascals 
 double  PS = Q*0.0002953;  //convert pressue pascals to in"
double PSNEW = PS;
 Serial.print("Pressure = ");
 delay (10);
 Serial.print(PS);
  delay (10);
 Serial.println ("in/Hg");
  delay (10);
 PS = PS + Offset;  //Correct the pressure reading for your altitude

  Serial.print ("corrected pressure =");
 Serial.println(PS);
 delay (500);
  //Convert the scale to 0-4" of mercury 
 PS=PS-28.00;
 // Correct the op amp gain/slope for the crummy 5% resistors I used for the op amp scaling circuit. My correction factor is 1.6%
 // To figure your gain factor correcton you will need to set the DAC to ~ 1V then ~ 5V and look at the difference in the slope of the meter readings. 
 // To avoid this hassle use 1% resistors for R5 and R4 and set the correction factor below to 1.000 
 PS=PS *1.016 ; 
   //Convert the pressure to an integer to scale it to the meter multiply by 100 This is so we can use the map function which only handles integers
 int psi = PS*100;
 //Map the barometric pressure to the meter movement. 0in/Hg = 0v ,4 in/Hg = 6 V  
 int m = map(psi,0,400,0,4095);  // m is the needle position it needs to be an integer     
// char prs [6]; //declare buffer ps
//write the pressure to the DAC 
 Serial.print("DAC Voltage =");
  delay (10);
Serial.println(m);
 delay (10);
 dac.setVoltage(m,false); //This writes the dac voltage value 0= 0 0V, 4095 =6V
 delay(250);
 
// Below is the LED control if we want to set LEDs for pressure change over the last hour
 
 
 Timer=Timer+1 ;
 Serial.print("Timer="); 
  Serial.println (Timer);
  delay (20);
 if (Timer>Timermax) {
   
    // timer check at 36 sec for now
 // below code is to set LEDS based on recent pressure changes 
 // Really need some hystersis and timer should be 3600 
  old=newx; // Shift the pressure 
  Timer=0;// reset the timer 
  newx=PSNEW; //write the pressure to the new value  
  //digitalWrite (Gled ,LOW);
   if (old==newx ) {
  digitalWrite (Gled ,LOW);
  digitalWrite  (Rled, LOW);
 digitalWrite (Yled,HIGH);
 digitalWrite (Bled,LOW);
   }  //end of old==new if
   if (old < newx){
 digitalWrite (Gled ,HIGH);
 digitalWrite  (Rled, LOW);
 digitalWrite (Yled,LOW);
 digitalWrite (Bled,LOW);
 } //end of old< new if
 if (old > newx){
  digitalWrite (Gled ,LOW);
  digitalWrite  (Rled, HIGH);
 digitalWrite (Yled,LOW);
 digitalWrite (Bled,LOW);  
 } //end of old> new if 
 float delta= (old-newx);
 if (abs( delta) > .06) {    // If the change in the last hour is big turn on blue led
 digitalWrite (Bled, HIGH);
 }  // end of change > .06 InHg
  //Write the LED values 
  //Serial.print ("G,R,Y,B" );
  //delay(10);
  //Serial.println (Gled);
  //delay (10);
  
  
  }  //end of timer loop 
  }  // end of picture loop

 

 
 
 
