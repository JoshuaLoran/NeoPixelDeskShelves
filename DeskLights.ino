#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 180
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
String val = "";
String off = "o";
String blueOne = "b";
String rainbow = "R";
String greenOne = "g";
String white = "w";
String redOne = "r";
String plus = "+";
String minus = "-";
String teal = "t";
String lime = "l";
String pink = "p";
String yellow = "y";
String violet = "v";
String purple = "z";
String orange = "q";
String stripOne = "1";
String stripTwo = "2";
String stripAll = "3";
String hannukah = "h";
String christmas = "c";
int lengthNum = 180;
int brightness = 100;
int pixStart = 0;

void setup() {
Serial.begin(57600);
mySerial.begin(57600);
strip.setBrightness(brightness);
strip.begin();
strip.show(); //Initialize pixels "off"

}

void loop() {
//check serial is connected
if(mySerial.available()) {
  //gather input data from serial port
  while(mySerial.available())
    {val += (char)mySerial.read();
    if(val.equals(stripOne)){
        lengthNum = 60;
        pixStart = 0;}
    if(val.equals(stripTwo)){
        lengthNum = 180;
        pixStart = 60;}
    if(val.equals(stripAll)){
        lengthNum = 180;
        pixStart = 0;}  
    if(val.equals(plus) && brightness < 101){
      brightness += 2;
      strip.setBrightness(brightness);
      strip.show();}
    if(val.equals(minus) && brightness > 5){
      brightness -= 2;
      strip.setBrightness(brightness);
      strip.show();}
    if(val.equals(off)){
        colorWipe(strip.Color(0, 0, 0, 0), lengthNum, pixStart);}
    if(val.equals(blueOne)){
    colorWipe(strip.Color(0, 0, 255), lengthNum, pixStart);
    }
    if(val.equals(greenOne)){
    colorWipe(strip.Color(0, 255, 0), lengthNum, pixStart);
    }
    if(val.equals(white)){
    colorWipe(strip.Color(0, 0, 0, 255), lengthNum, pixStart);
    }
    if(val.equals(redOne)){
    colorWipe(strip.Color(255, 0, 0), lengthNum, pixStart);
    }
    if(val.equals(teal)){
    colorWipe(strip.Color(9, 234, 219), lengthNum, pixStart);
    }
    if(val.equals(lime)){
    colorWipe(strip.Color(174, 234, 9), lengthNum, pixStart);
    }
    if(val.equals(pink)){
    colorWipe(strip.Color(255, 11, 100), lengthNum, pixStart);
    }
    if(val.equals(violet)){
    colorWipe(strip.Color(150, 11, 255), lengthNum, pixStart);
    }
    if(val.equals(yellow)){
    colorWipe(strip.Color(237, 110, 0), lengthNum, pixStart);
    }
    if(val.equals(purple)){
    colorWipe(strip.Color(80, 0, 255), lengthNum, pixStart);
    }
    if(val.equals(orange)){
    colorWipe(strip.Color(255, 55, 0), lengthNum, pixStart);
    strip.setBrightness(70);
    }
    if(val.equals(rainbow)){
    rainbowFade2White(1000);
    val = "";
    }
    if(val.equals(hannukah)){
    festiveWipe(strip.Color(0, 0, 0, 255), strip.Color(0, 0, 255), lengthNum, pixStart);
    }
    if(val.equals(christmas)){
    festiveWipe(strip.Color(0, 255, 0), strip.Color(255, 0, 0), lengthNum, pixStart);
    }    
    val= "";
  }
}
}


void colorWipe(uint32_t c, uint8_t pixNum, int pixStart) {
  for(uint16_t i=pixStart; i<pixNum; i++) {
    strip.setPixelColor(i, c);
    delay(0);
  }
  strip.show();
}


void festiveWipe(uint32_t c, uint32_t d, uint8_t pixNum, int pixStart){ //color 1, color 2, length of strip, where strip starts
int animate = 2; //counter for color switch
while(val.equals(hannukah) || val.equals(christmas)){ //loop for as long as val equals h or c
    
  if(animate%2 !=0){ //every odd cycle of animate
    for(uint16_t i=pixStart; i<pixNum; i++){ //for each pixel with start pixStart, to length pixNum
      if(i%2 !=0){ //set every odd pixel to color c in buffer
        strip.setPixelColor(i,c);
      }
      if(i%2 ==0){ //set every even pixel to color d in buffer
        strip.setPixelColor(i,d);
      }
      if(mySerial.available()) {   //check if controller buffer has changed and set value to val
      while(mySerial.available()){val += (char)mySerial.read();}
      }
      if(!val.equals(hannukah) && !val.equals(christmas)){return;} //if val is not h, and it's not c, exit loop
    }
     strip.show();
     delay(500);
  }

      
  if(animate%2 ==0){ //every even cycle of animate
    for(uint16_t i=pixStart; i<pixNum; i++){ 
        if(i%2==0){ //set every even pixel to color c in buffer
          strip.setPixelColor(i, c);
        }
        if(i%2!=0) { //set every odd pixel to color d in buffer
          strip.setPixelColor(i,d);
        }
        if(mySerial.available()) {
          while(mySerial.available()){val += (char)mySerial.read();}
          }
        if(!val.equals(hannukah) && !val.equals(christmas)){return;}
      }
      strip.show();
      delay(500);
    }
    animate = animate + 1;
  }
}


void rainbowFade2White(int rainbowLoops) {
  
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;
  while(val.equals(rainbow)){
    for(int k = 0 ; k < rainbowLoops ; k ++){
          for(int j=0; j<256; j++) {
            for(int i=0; i< strip.numPixels(); i++) {
              if(mySerial.available()) {
                while(mySerial.available())
                  {val += (char)mySerial.read();}
              }
              if(!val.equals(rainbow)){return;}
              wheelVal = Wheel(((i * 256 / strip.numPixels()) + j) & 255);
              redVal = red(wheelVal) * float(fadeVal/fadeMax);
              greenVal = green(wheelVal) * float(fadeVal/fadeMax);
              blueVal = blue(wheelVal) * float(fadeVal/fadeMax);
              strip.setPixelColor( i, strip.Color( redVal, greenVal, blueVal ) );
            }
            if(k == 0 && fadeVal < fadeMax-1) {
            fadeVal++;
            }
            else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
              fadeVal--;
            }
            strip.show();
          }
      }
   }
}


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 8);
}
uint8_t green(uint32_t c) {
  return (c >> 16);
}
uint8_t blue(uint32_t c) {
  return (c);
}
