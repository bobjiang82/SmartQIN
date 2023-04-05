#include<FastLED.h>
#define NUM_LEDS 60 //定义 led 数量
#define DATA_PIN 3 //定义 开发板的IO 3 为数据引脚
#define DATA_PIN_1 5
CRGB leds[NUM_LEDS];//定义CRGB的led等数据
CRGB leds_1[NUM_LEDS];
CRGB ledcolor = CRGB::Green;
int songid = 0;
int a[][200]={{20,45,48,388,42,45,24,39,41,20,46},
             {23,23,27,27,28,28,27,20,26,26,25,25,24,24,23,20,27,27,26,26,25,25,24,27,27,26,26,25,25,24,20,23,23,27,27,28,28,27,20,26,26,25,25,24,24,23},
             {24,22,23,21,24,22,23,21,24,22,23,21,45,30,10,13,14,13,45,20,10,13,14,13,14,15,51,13,51,13,51,13,24,23,62,45,20,10,13,14,13,14,15,45,20,10,13,14,13,14,15,51,13,51,13,51,13,25,24,62,11,13,58,18,18,17,28,18,17,18,17,18,17,15,75,30,20,11,13,58,18,18,17,18,17,59,19,29,18,29,28,15,45,10,15,17,15,54,15,54,15,54,15,17,15,17,15}
  };
int b[]={3,1,1,2,1,1,3,5,1,3,1};
//定义灯亮的状态，1：右手白键亮绿灯；2：左手白键亮蓝灯；3：右手黑键亮绿灯；4：左手黑键亮蓝灯；5：同时亮灯

volatile int rhythm = 0;
#define SPEED_MIN (1)
#define SPEED_MAX (2)
int buzzerPin = 6;
int delayspernote[8] = {0, 115, 231, 462, 923, 346, 1846, 1615};
float speedup = 1.0;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds,NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,DATA_PIN_1>(leds_1,NUM_LEDS);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A5, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void resetled(CRGB ledcolor) {
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = ledcolor;
    leds_1[i] = ledcolor;
    FastLED.show();
  }
  delay(1000);
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    leds_1[i] = CRGB::Black;
    FastLED.show();
  }
  delay(500);
}

void testryhthm(int rhythm)
{
  leds[30] = ledcolor;
  leds_1[30] = ledcolor;
  //FastLED.setBrightness(10);
  FastLED.show();
  delay(rhythm);
  leds[30]=CRGB::Black;
  leds_1[30]=CRGB::Black;
  FastLED.show();
  delay(rhythm);
}

void beep(unsigned char delayms) { //creating function
  analogWrite(buzzerPin, 10); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
}

void testtone(unsigned char delayms) {
  tone(buzzerPin, 1000);
  delay(delayms);
  tone(buzzerPin, 2000);
  delay(delayms);
}

void testbuzzer(int rhythm) {
//  beep(rhythm);
  testtone(rhythm);
}

void loop() {
  // put your main code here, to run repeatedly:
//  rhythm = analogRead(A5);  //(0~1023) ==> (0.5~2)
//  speedup = (float)(SPEED_MIN + (SPEED_MAX-SPEED_MIN)*(float)(1024-rhythm)/1024.0);
//  testryhthm(rhythm);
//  testbuzzer(rhythm);
//  return;

  //每一个led逐个闪烁绿色
  for(int i=0;i<107;i++){
    if (!digitalRead(A0)) {
    songid = 0;
    ledcolor = CRGB::Green;
    i = 0;
    resetled(ledcolor);
  }
    if (!digitalRead(A1)) {
    songid = 1;
    ledcolor = CRGB::Yellow;
    i = 0;
    resetled(ledcolor);
  }
    if (!digitalRead(A2)) {
    ledcolor = CRGB::Red;
    songid = 2;
    i = 0;
    resetled(ledcolor);
  }

  rhythm = analogRead(A5);  //(0~1023) ==> (0.5~2)
  speedup = (float)(SPEED_MIN + (SPEED_MAX-SPEED_MIN)*(float)(1024-rhythm)/1024.0);

    if(a[songid][i]/10 == 1){
      if(a[songid][i]%10){
        if(songid==0 && (b[i]==2))
        leds[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==4))
        leds_1[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==3))
        leds_1[a[songid][i]%10 + 15] = ledcolor;
        else
        leds[a[songid][i]%10 + 15] = ledcolor;
        //FastLED.setBrightness(10);
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
        if(songid==0 && (b[i]==5)){}
        else
        {leds[a[songid][i]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i]%10 + 15]=CRGB::Black;}
        if(i!=0){
          if(songid==0 && b[i-1]==5)
        leds[a[songid][i-1]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i-1]%10 + 15]=CRGB::Black;
        }
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }else{
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }    
    }
    if(a[songid][i]/10 == 2){
      if(a[songid][i]%10){
        if(songid==0 && (b[i]==2))
        leds[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==4))
        leds_1[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==3))
        leds_1[a[songid][i]%10 + 15] = ledcolor;
        else
        leds[a[songid][i]%10 + 15] = ledcolor;
        //FastLED.setBrightness(10);
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
        if(songid==0 && (b[i]==5)){}
        else
        {leds[a[songid][i]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i]%10 + 15]=CRGB::Black;}
        if(i!=0){
          if(songid==0 && b[i-1]==5)
        leds[a[songid][i-1]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i-1]%10 + 15]=CRGB::Black;
        }
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }else{
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }    
    }
    if(a[songid][i]/10 == 3){
      if(a[songid][i]%10){
        if(songid==0 && (b[i]==2))
        leds[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==4))
        leds_1[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==3))
        leds_1[a[songid][i]%10 + 15] = ledcolor;
        else        
        leds[a[songid][i]%10 + 15] = ledcolor;
        //FastLED.setBrightness(10);
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
        if(songid==0 && (b[i]==5)){}
        else
        {leds[a[songid][i]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i]%10 + 15]=CRGB::Black;}
        if(i!=0){
          if(songid==0 && b[i-1]==5)
        leds[a[songid][i-1]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i-1]%10 + 15]=CRGB::Black;
        }
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }else{
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }    
    }
    if(a[songid][i]/10 == 4){
      if(a[songid][i]%10){
        if(songid==0 && (b[i]==2))
        leds[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==4))
        leds_1[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==3))
        leds_1[a[songid][i]%10 + 15] = ledcolor;
        else        
        leds[a[songid][i]%10 + 15] = ledcolor;
        //FastLED.setBrightness(10);
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
        if(songid==0 && (b[i]==5)){}
        else
        {leds[a[songid][i]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i]%10 + 15]=CRGB::Black;}
        if(i!=0){
          if(songid==0 && b[i-1]==5)
        leds[a[songid][i-1]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i-1]%10 + 15]=CRGB::Black;
        }
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }else{
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }    
    }
    if(a[songid][i]/10 == 5){
        if(songid==0 && (b[i]==2))
        leds[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==4))
        leds_1[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==3))
        leds_1[a[songid][i]%10 + 15] = ledcolor;
        else      
      if(a[songid][i]%10){
        leds[a[songid][i]%10 + 15] = ledcolor;
        //FastLED.setBrightness(10);
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
        if(songid==0 && (b[i]==5)){}
        else
        {leds[a[songid][i]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i]%10 + 15]=CRGB::Black;}
        if(i!=0){
          if(songid==0 && b[i-1]==5)
        leds[a[songid][i-1]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i-1]%10 + 15]=CRGB::Black;
        }
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }else{
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }    
    }
    if(a[songid][i]/10 == 6){
        if(songid==0 && (b[i]==2))
        leds[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==4))
        leds_1[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==3))
        leds_1[a[songid][i]%10 + 15] = ledcolor;
        else      
      if(a[songid][i]%10){
        leds[a[songid][i]%10 + 15] = ledcolor;
        FastLED.setBrightness(10);
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
        if(songid==0 && (b[i]==5)){}
        else
        {leds[a[songid][i]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i]%10 + 15]=CRGB::Black;}
        if(i!=0){
          if(songid==0 && b[i-1]==5)
        leds[a[songid][i-1]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i-1]%10 + 15]=CRGB::Black;
        }
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }else{
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }    
    }
    if(a[songid][i]/10 == 7){
      if(a[songid][i]%10){
        if(songid==0 && (b[i]==2))
        leds[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==4))
        leds_1[a[songid][i]%10 + 15] = CRGB::Blue;
        else if 
        (songid==0 && (b[i]==3))
        leds_1[a[songid][i]%10 + 15] = ledcolor;
        else        
        leds[a[songid][i]%10 + 15] = ledcolor;
        FastLED.setBrightness(10);
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
        if(songid==0 && (b[i]==5)){}
        else
        {leds[a[songid][i]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i]%10 + 15]=CRGB::Black;}
        if(i!=0){
          if(songid==0 && b[i-1]==5)
        leds[a[songid][i-1]%10 + 15]=CRGB::Black;
        leds_1[a[songid][i-1]%10 + 15]=CRGB::Black;
        }
        FastLED.show();
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }else{
        delay(int(speedup*delayspernote[a[songid][i]/10]));
      }    
    }
  }
  

}