#include "mbed.h"
#include "uLCD_4DGL.h"

const double pi = 3.141592653589793238462;
const double amplitude = 0.5f;
const double offset = 65535 / 2;

DigitalOut myled(LED3);
InterruptIn up(A0);
InterruptIn down(A1);
InterruptIn sel(A4);
AnalogIn Ain(A3);

AnalogOut Aout(PA_4);
AnalogOut Sout(PA_5);
uLCD_4DGL uLCD(D1, D0, D2);
EventQueue queue(32 * EVENTS_EVENT_SIZE);

float period = 1;
int sample = 10000;
float ADCdata[10000];
float F;

Thread t1;
Thread t2;

int arr=2;
float freq=100.0f;


void choice(){
    uLCD.locate(5, 2);
    uLCD.printf("100Hz");
    uLCD.set_font(FONT_7X8);

    uLCD.locate(5, 7);
    uLCD.printf("200Hz");
    uLCD.set_font(FONT_7X8);

    uLCD.locate(5, 12);
    uLCD.printf("300Hz");
    uLCD.set_font(FONT_7X8);

    uLCD.text_string("<<",  11, arr, FONT_7X8,  WHITE);
}

void up_fun(){
   if(up){
          uLCD.cls() ;
          if(arr == 7 or arr == 12){
                arr = arr-5;
          }
          else if(arr == 2){
                arr = 12;
          }
     }
     choice();
}

void up_fun_isr() {
  queue.call(up_fun);
}

void down_fun(){
   if(down){
          uLCD.cls() ;
          if(arr == 2 or arr == 7){
                arr = arr+5;
          }
          else if(arr == 12){
                arr = 2;
          }
     }
     choice();   
}

void down_fun_isr() {
  queue.call(down_fun);
}


void Output(){
  float p = period - 33;
  float i;
  int j = 0;

  while (j < sample)
  {
    for(i=0.0f; i < 0.834f && j < sample; i += 0.1666f) {
      ADCdata[j] = Ain;
      Sout = i;
      wait_us(p);

      j=j+1;

    }
    for(i=1.0f; i  > 0.004f && j < sample; i -= 0.25f) {
      ADCdata[j] = Ain;
      Sout = i;
      wait_us(p);
      j=j+1;
    }
  }
   printf("%f\r\n", F);
  for (int k = 0; k < sample; k++){
      printf("%f\r\n", ADCdata[k]);
      wait_us(100);
  } 
}


void select_freq(){
   //uLCD.background_color(0xFF0000);
   if(sel){
            if(arr == 2) {
                  freq=100;
                  }
            else if (arr== 7) {
                  freq = 200;
                  }
            else if(arr == 12) {
                  freq =  300;
                  }
            F = 10*freq;
            period = 1 / freq *100000;
            t2.start(&Output);
   }
}

void select_freq_isr() {
  queue.call(select_freq);
}



int main() {
    choice();
    Aout = 1;
    Sout = 1;
    t1.start(callback(&queue, &EventQueue::dispatch_forever));
    up.rise(&up_fun_isr);
    down.rise(&down_fun_isr);
    sel.rise(&select_freq_isr);

}