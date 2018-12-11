#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 180
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
int lengthNum = 180;
int brightness = 100;
int pixStart = 0;
int wait = 500;
String buttons = "obRgwr+-tlpyvzq123hc";
String val = "";

void setup() {
  Serial.begin(57600);
  mySerial.begin(57600);
  strip.setBrightness(brightness);
  strip.begin();
  strip.show(); //Initialize pixels "off"

}

void loop() {

    getVal();
    if(val.equals(buttons.charAt(16))){
        lengthNum = 60;
        pixStart = 0;}
    if(val.equals(buttons.charAt(17))){
        lengthNum = 180;
        pixStart = 60;}
    if(val.equals(buttons.charAt(18))){
        lengthNum = 180;
        pixStart = 0;}  
    if(val.equals(buttons.charAt(7)) && brightness < 101){
      brightness += 2;
      strip.setBrightness(brightness);
      strip.show();}
    if(val.equals(buttons.charAt(8)) && brightness > 5){
      brightness -= 2;
      strip.setBrightness(brightness);
      strip.show();}
    if(val.equals(buttons.charAt(0))){
        colorWipe(strip.Color(0, 0, 0, 0), lengthNum, pixStart);}
    if(val.equals(buttons.charAt(1))){
    colorWipe(strip.Color(0, 0, 255), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(4))){
    colorWipe(strip.Color(0, 255, 0), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(5))){
    colorWipe(strip.Color(0, 0, 0, 255), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(6))){
    colorWipe(strip.Color(255, 0, 0), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(9))){
    colorWipe(strip.Color(9, 234, 219), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(10))){
    colorWipe(strip.Color(174, 234, 9), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(11))){
    colorWipe(strip.Color(255, 11, 100), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(13))){
    colorWipe(strip.Color(150, 11, 255), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(12))){
    colorWipe(strip.Color(237, 110, 0), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(14))){
    colorWipe(strip.Color(80, 0, 255), lengthNum, pixStart);
    }
    if(val.equals(buttons.charAt(15))){
    colorWipe(strip.Color(255, 55, 0), lengthNum, pixStart);
    strip.setBrightness(70);
    }
    if(val.equals(buttons.charAt(3))){
    rainbows(1000);
    val = "";
    }
    if(val.equals(buttons.charAt(19))){
    festiveWipe(strip.Color(0, 0, 0, 255), strip.Color(0, 0, 255), lengthNum, pixStart, wait);
    }
    if(val.equals(buttons.charAt(20))){
    festiveWipe(strip.Color(0, 255, 0), strip.Color(255, 0, 0), lengthNum, pixStart, wait);
    }    
    val= "";
}

void getVal() {
  if(mySerial.available()) {
    while(mySerial.available())
    {val += (char)mySerial.read();}
  }
}

void colorWipe(uint32_t c, uint8_t pixNum, int pixStart) {
  for(uint16_t i=pixStart; i<pixNum; i++) {
    strip.setPixelColor(i, c);
    delay(0);
  }
  strip.show();
}

void festiveWipe(uint32_t c, uint32_t d, uint8_t pixNum, int pixStart, int wait){ //color 1, color 2, length of strip, where strip starts
int animate = 2; //counter for color switch
while(val.equals(buttons.charAt(19)) || val.equals(buttons.charAt(20))){ //loop for as long as val equals h or c
    
  if(animate%2 !=0){ //every odd cycle of animate
    for(uint16_t i=pixStart; i<pixNum; i++){ //for each pixel with start pixStart, to length pixNum
      if(i%2 !=0){ //set every odd pixel to color c in buffer
        strip.setPixelColor(i,c);
      }
      if(i%2 ==0){ //set every even pixel to color d in buffer
        strip.setPixelColor(i,d);
      }
      getVal();
      }
      if(!val.equals(buttons.charAt(19)) && !val.equals(buttons.charAt(20))){return;} //if val is not h, and it's not c, exit loop
    }
     strip.show();
     delay(wait);
  }

      
  if(animate%2 ==0){ //every even cycle of animate
    for(uint16_t i=pixStart; i<pixNum; i++){ 
        if(i%2==0){ //set every even pixel to color c in buffer
          strip.setPixelColor(i, c);
        }
        if(i%2!=0) { //set every odd pixel to color d in buffer
          strip.setPixelColor(i,d);
        }
        getVal();
        if(!val.equals(buttons.charAt(19)) && !val.equals(buttons.charAt(20))){return;}
      }
      strip.show();
      delay(wait);
    }
    animate = animate + 1;
  }

void rainbows(int rainbowLoops) {
  int pixLength = lengthNum - pixStart;
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;
    for(int k = 0 ; k < rainbowLoops ; k ++){
          for(int j=0; j<256; j++) {
            for(int i=pixStart; i< lengthNum; i++) {
              getVal();
              if(!val.equals(buttons.charAt(3))){return;}
              wheelVal = Wheel(((i * 256 / pixLength) + j) & 255);
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




