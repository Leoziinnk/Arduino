#include <ShiftRegister74HC595.h>
#define DATA 2
#define CLOCK 4
#define LATCH 3
#define DATA1 5
#define CLOCK1 7
#define LATCH1 6
#define BUZZER 13
ShiftRegister74HC595 leds(1, DATA, CLOCK, LATCH);
int vDisplay[50] = {B01111111, B10111111, B11011111};
int vEscreveOn[50] = {B11111100, B00101010, B00000000};
int vEscreveOff[50] = {B11111100, B10001110, B10001110};

void setup() {
 pinMode(BUZZER, OUTPUT);
pinMode(DATA1, OUTPUT);
 pinMode(CLOCK1, OUTPUT);
 pinMode(LATCH1, OUTPUT);

 digitalWrite(CLOCK1, LOW);
 digitalWrite(LATCH1, LOW);
}
void loop() {

   for(int pos=0; pos<=3;pos++){
  shiftOut(DATA1, CLOCK1, LSBFIRST, vDisplay[pos]); 
  shiftOut( DATA1, CLOCK1, LSBFIRST, vEscreveOn[pos]);
  enviaPulso(LATCH1);
   }
  
}
void enviaPulso(int pino) {
 digitalWrite(pino, HIGH);
 digitalWrite(pino, LOW);
}