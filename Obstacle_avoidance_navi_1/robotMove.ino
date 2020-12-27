

void turnRobot(float angle){
  long int yR = encodercount_R;
  Serial.println(yR);
  long int yL = encodercount_L;
  Serial.println(yL);
  long int y = (encoderCPR*chassisR*angle)/(2.0*pi*wheelR);
  Serial.println(y);
  yR = yR - y;
  yL = yL + y;
  Serial.println("y set");


  if(y>=0){
    digitalWrite(INR1,LOW);
    digitalWrite(INR2,HIGH);
    digitalWrite(INL1,HIGH);
    digitalWrite(INL2,LOW);
    Serial.println("dir set y>=0"); 
  }else{
    digitalWrite(INR1,HIGH);
    digitalWrite(INR2,LOW);
    digitalWrite(INL1,LOW);
    digitalWrite(INL2,HIGH);
    Serial.println("dir set y<0");  
  }

  while((encodercount_R != yR) && (encodercount_L != yL)){
    analogWrite(ENR,200);
    analogWrite(ENL,200);  
  }
//    analogWrite(ENR,0);
//    analogWrite(ENL,0); //dont use this driver give wierd result
    Serial.println("going to brake");
    digitalWrite(INR1,HIGH);
    digitalWrite(INR2,HIGH);
    digitalWrite(INL1,HIGH);
    digitalWrite(INL2,HIGH); 

    return;
  
}


void fowardRobot(int spd){
  
    digitalWrite(INR1,HIGH);
    digitalWrite(INR2,LOW);
    digitalWrite(INL1,HIGH);
    digitalWrite(INL2,LOW);

    analogWrite(ENR,spd);
    analogWrite(ENL,spd); 
  }
  
void brakeRobot(void){
    analogWrite(ENR,255);
    analogWrite(ENL,255);

    digitalWrite(INR1,HIGH);
    digitalWrite(INR2,HIGH);
    digitalWrite(INL1,HIGH);
    digitalWrite(INL2,HIGH);
}

void reverseRobot(int spd){
     digitalWrite(INR2,HIGH);
    digitalWrite(INR1,LOW);
    digitalWrite(INL2,HIGH);
    digitalWrite(INL1,LOW);

    analogWrite(ENR,spd);
    analogWrite(ENL,spd); 
}
  
