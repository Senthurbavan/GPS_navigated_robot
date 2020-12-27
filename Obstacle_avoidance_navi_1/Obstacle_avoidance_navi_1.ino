#include <NewPing.h>
#include "header.h"

NewPing sL(TL,EL,MAX_DIS);
NewPing sR(TR,ER,MAX_DIS);
NewPing sM(TM,EM,MAX_DIS);

void setup() {
  Serial.begin(115200);
  pinMode(INR1,OUTPUT);
  pinMode(INR2,OUTPUT);
  pinMode(INL1,OUTPUT);
  pinMode(INL2,OUTPUT);

  pinMode(leftEncoderA,INPUT);
  pinMode(leftEncoderB,INPUT);
  pinMode(rightEncoderA,INPUT);
  pinMode(rightEncoderB,INPUT);
  
  attachInterrupt(digitalPinToInterrupt(leftEncoderA),en_ISR_L,RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncoderA),en_ISR_R,RISING);

}

void loop() {
 fowardRobot(200);
 if(obstacle()){
    avoidObstacle();
 }
  delay(200);
}

void en_ISR_R(){
    if(digitalRead(rightEncoderA)==digitalRead(rightEncoderB)){
        encodercount_R++;
    }else{
        encodercount_R--;  
    }
}

void en_ISR_L(){
    if(digitalRead(leftEncoderA)==digitalRead(leftEncoderB)){
        encodercount_L--;
    }else{
        encodercount_L++;  
    }
}

