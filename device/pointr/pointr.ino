/**
 * Project Pointr
 * (c) 2014 Mikhail Yurasov <me@yurasov.me>
 */

#include <SoftwareSerial.h>

const int YELLOW = 0;

const int displayTx = 8;
const int displayRx = 7;

const int impTx = 9;
const int impRx = 10;

const int reedPin = 2;

int reedState = 0;
int reedLastState = LOW;
long reedLastDebounceTime = 0;
long reedDebounceDelay = 10;

unsigned int pointsYellow = 9;
unsigned int pointsBlue = 4;

//

SoftwareSerial s7s(displayRx, displayTx);
SoftwareSerial imps(impRx, impTx);

//

void setup()
{
  delay(5000);
  imps.begin(9600);
  initDisplay();
}

void loop()
{
  loopReedSwitch();
}

void onContact()
{
  int blinkDelay = 100;

  static char t[10];

  int points = YELLOW ? pointsYellow : pointsBlue;

  sprintf(t, "%04d", points);
  s7s.print(t);

  imps.write(200 + pointsYellow);
  imps.write(100 + pointsBlue);

  // blink
  for (int i = 0; i < 7; ++i)
  {
    setBrightness(0);
    delay(blinkDelay);
    setBrightness(255);
    delay(blinkDelay);
  }
}

void loopReedSwitch()
{

  int reedReading = digitalRead(reedPin);

  if (reedReading != reedLastState) {
    reedLastDebounceTime = millis();
  }

  if ((millis() - reedLastDebounceTime) > reedDebounceDelay) {

    if (reedReading != reedState) {
      reedState = reedReading;

      if (reedState == HIGH) {

        int pyo = pointsYellow;

        if (pointsBlue > 5) {
          pointsYellow += 2;
        } else {
          pointsYellow++;
        }

        if (pyo > 5) {
          pointsBlue += 2;
        } else {
          pointsBlue++;
        }

        onContact();
      }
    }
  }

  reedLastState = reedReading;
}

void initReedSwitch()
{
  pinMode(reedPin, INPUT);
}

void initDisplay()
{
  s7s.begin(9600);
  clearDisplay();
  setBrightness(255);
  setDecimals(0b00001000);

  s7s.print("   -");
  delay(333);
  s7s.print("  --");
  delay(333);
  s7s.print(" ---");
  delay(333);
  s7s.print("----");
  delay(333);
  s7s.print("    ");
  delay(333);
  s7s.print("0000");
  delay(333);
  onContact();
}

void clearDisplay()
{
  s7s.write(0x76);
}

void setBrightness(byte value)
{
  s7s.write(0x7A);
  s7s.write(value);
}

void setDecimals(byte decimals)
{
  s7s.write(0x77);
  s7s.write(decimals);
}