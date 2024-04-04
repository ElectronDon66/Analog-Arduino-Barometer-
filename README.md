# Analog-Arduino-Barometer-
Analog Barometer with Voltmeter 
Analog Barometer with Arduino Nano and 0-6V Meter 

This sketch uses an Arduino Nano to read a BMP180 barometric pressure sensor. The sketch converts the pressure to a 0-5V analog voltage but since the meter is 6V max we need to amplify the 0-5V signal to 0-6V. This is done with a small gain amplification through U1 the LM358. The gain is 1+ R5/R4. This equates to a gain of 1.2. So 5V *1.2 = 6V.  Also, because my R4 and R5 resistors were of poor quality I also added a correction factor of 1.016 to compensate for their tolerance error. If you use 1% resistors you could set the gain correction factor to 1.000; however, because I wanted high accuracy I left this correction factor in the code.  Zener U3 is a clamp to prevent turn on transients from driving the meter over 6V. The trim pot resistor R1 is used to adjust the Barometer output to the barometric pressure for your location minus your altitude above sea level.  The weather service always uses barometric pressure relative to sea level for consistency. This is extremely important for the aviation community. Once your barometer is up and working you can obtain the local barometric pressure for your location either from your cell phone (weather tab) or from your local airport (listen to a scanner where the landing pilots are told the local barometric pressure). Just adjust the trim pot to get the correct barometric pressure reading on your meter. 
One of the fun factors on this project was repurposing a 0-6 V meter to have a barometric scale. To do this I chose the Meter program from Tonne software .  https://www.tonnesoftware.com/index.html  . The software allowed me to actually put dual scales on the meter face. It took a few tries to get it right but I was able to print the new calibrated scale on glossy photographic paper, trim it to size and carefully slip it under the meter’s needle. Two of the meter’s screws allowed me to secure the scale in place near the center and the outside trim bezel clamped the scale to the meter such that I didn’t need to glue it. Jim Tonne was of great help in getting the scale factor exactly right and I think the scale looks super professional. The overall accuracy of the Barometer is fantastic. Its way better then the digital meters you buy at Walmart or the mechanical units you find on Ebay. In fact, I am sure it’s even better than the professional Weems & Plath Barometer I used to have on my boat. 
Also this sketch has some remnant code from a previous barometer project where the  sketch controlled 4 LEDs to indicate whether the pressure trend was increasing or decreasing. Originally, I was going to include the LEDs in this meter but ultimately decided not to. However, the code is in there if you whish to use it. It was debugged and working previously but I’m not 100% sure if its still fully functional. Theoretically all you’d need to add is 4 Leds and 4 current limiting resistors. See the code for imbedded notes. 
BAROMETER7.mtr IS THE mETER SOFTWARE WORKING FILE. You'll need "Meter to load this file and see it. 

You will need to include the following library files 
include <Adafruit_MCP4725.h>
include <Adafruit_BMP085.h>
include <Wire.h>

Youtube video - 
