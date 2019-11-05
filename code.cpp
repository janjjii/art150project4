#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        8
#define NUMPIXELS 11 // interchangeable, for convinience
#define DELAYVAL 500

const int trigPin = 12; // interchangeable, for convinience
const int echoPin = 13; // interchangeable, for convinience
int brightlvl = 0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  
  // initialize serial communication:
  Serial.begin(9600);
  pixels.begin();
}

void loop()
{
  long duration, inches, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, "); 
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // OFF
  if(inches > 20){pixels.clear();}
  
  // WHITE 
  else if(inches > 3 && inches <= 20)
  {
    for(int i=0; i<NUMPIXELS; i++) 
    { 
      brightlvl = (((21 - inches) - 5)*10);
      pixels.setBrightness(brightlvl);
      Serial.print("Brightness :");
      Serial.print(brightlvl);
      Serial.println();
      pixels.setPixelColor(i, pixels.Color(255, 255, 250)); // BRIGHT WHITE
      pixels.show();
    }
  }

  // RED
  else if(inches <= 3)
  {
    for(int i=0; i<NUMPIXELS; i++) 
    {
      pixels.setBrightness(250);
      pixels.setPixelColor(i, pixels.Color(245, 0, 0));
      pixels.show();
    }
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
