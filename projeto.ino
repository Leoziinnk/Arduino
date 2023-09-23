//Leonardo Garcia && Gustavo Dieckmann TRO6M

#include <ShiftDisplay.h> 
#include <ShiftRegister74HC595.h> 
#define BOTAO A3
#define VERDE A1
#define VERMELHO A0
#define DATA 2
#define CLOCK 4
#define LATCH 3
#define BUZZER 13
#define SENSOR 12

ShiftDisplay display7s (COMMON_CATHODE, 4);
ShiftRegister74HC595 leds(1, DATA, CLOCK, LATCH);
static int disp = 10;
int condicao1 = -1, condicao2 =-1, desativaled=-1, leituraSensor;
int liga=1, sensor=-1;
long tempoleds = 0 ,tempoBuzzer = 0, tempoDisparo= 0, tempoDisplay = 0;

void setup() {

pinMode(VERDE, OUTPUT);
pinMode(VERMELHO, OUTPUT);
pinMode(BOTAO,INPUT);
pinMode(DATA,OUTPUT);
pinMode(CLOCK,OUTPUT);
pinMode(LATCH, OUTPUT);

leds.setAllLow();

}

void loop() {
        int sensor;
        int leBotao= analogRead(BOTAO);

    if(condicao1 != 1 && condicao1 != 3 && condicao1 != 0){
       if(leBotao>= 664 && leBotao<= 684 ){
         condicao1 = 1;
        acionaBuzzer(2825);
       }
    }
    if (condicao1 != 2){
        if(leBotao >= 736 && leBotao <= 756){
         condicao1 = 2;
        acionaBuzzer(4000);
       }
    }
    if(condicao1 == 1){
        digitalWrite(VERDE,0);
        digitalWrite(VERMELHO,1);
        displaycont();
        giraLeds();
    }
    else if(condicao1 == 2){
       digitalWrite(VERMELHO,0);
       digitalWrite(VERDE, 1);
       display7s.set("0ff");
       disp=11;
       leds.setAllLow();
    }
    if(condicao1 == 3){
     giraLeds();
       if(digitalRead(SENSOR)== 0){
          condicao1 = 0;
      }
    }
    if(condicao1==0){
      disparo(0);
    }
    display7s.show();
}

void giraLeds(){
static int pos = 0;
      if(millis() - tempoleds >= 300){
         if (pos==8){
            pos=0;
          }
       leds.set(pos,1);
       leds.set(pos-1,0);
          if(pos-1== -1){
             leds.set(7,0);
             leds.set(0,1);
           }
       pos++;
       tempoleds = millis();
       }
}
void acionaBuzzer(int freq){
    tone(BUZZER,freq);
    delay(300);
    noTone(BUZZER);
}
void displaycont(){
      if(disp == 0){
        disp=0;
        display7s.set("0N");
        condicao1=3;
      }
   if(disp != 0){
       digitalWrite(VERMELHO,liga);
        if(millis() - tempoDisplay >= 1000) {
         disp--;
         liga=!liga;
          tempoDisplay= millis();
       }
        display7s.set(disp);
        display7s.show();
      }
}

void disparo(int leSensor){
  static int led = 1;
      if(leSensor == 0){
      condicao2=1;
      }
      if(condicao2 == 1){
        tone(BUZZER,2000);
         if(millis()-tempoDisparo>=300){
          led = !led;
            if(led==0){
              leds.setAllHigh();
            }
            else if (led==1){
              leds.setAllLow();
            }
        tempoDisparo = millis();
        }
      }
 }