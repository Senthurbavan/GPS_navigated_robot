


void blinkk(void){
  digitalWrite(LED,HIGH);
  delay(200);
  digitalWrite(LED,LOW);  
}



void gotodestination(int spd){
  analogWrite(ENR,0);
  analogWrite(ENL,0);
  
  int disL = 0;
  int disM = 0;
  int disR = 0;

  while(true){
         
    disL = sonarL.convert_cm(sonarL.ping_median(2));
    delay(10);
    disM = sonar.convert_cm(sonar.ping_median(2));
    delay(10);
    disR = sonarR.convert_cm(sonarR.ping_median(2));
    delay(10);

    if(((disM < 15) && (disL < 15))||((disL < 15) && (disR < 15))||((disM < 15) &&(disR < 15))){
      brakeRobot();
      delay(300);
      return;
    }

    int error = disL - disR;
    error = error*gotodestination_kp;
    int lspeed = spd + error;
    if (lspeed > gotodestination_MAX_SPEED){
      lspeed = gotodestination_MAX_SPEED;  
    }

    int rspeed = spd - error;
    if (rspeed > gotodestination_MAX_SPEED){
      rspeed = gotodestination_MAX_SPEED;  
    }

    digitalWrite(INR1,HIGH);
    digitalWrite(INR2,LOW);
    digitalWrite(INL1,HIGH);
    digitalWrite(INL2,LOW);

   
    analogWrite(ENR,rspeed);
    analogWrite(ENL,lspeed);

  
  }
}




int findshortdis(void){
  int mindis = 600;
  int min_i=0;
  int dis = 0;
  
  int ang = 0;
  float heading = getHeading();
  
  for(int i=-8; i<=8; i++){
      ang = 10*i + heading;

      if(ang >= 360){
      ang -= 360;  
      }
      else if(ang<0){
        ang += 360;
      }

      while(true){
        float err = errorang(ang);
        if (err < 3.0){
          break;  
        }

        turnRobotAngle(ang);
        delay(250);
      }

      delay(300);
      dis = sonar.convert_cm(sonar.ping_median(3));
      if((dis <= mindis) && (dis != 0)){
        mindis = dis;
        min_i = i ;
        blinkk();  
      }

  }

  turnRobot(-((8-min_i)*10));
  return min_i ;
}




























//IGNORE THESE

//void findshortdis1(void){
//  int mindis = 600;
//  int min_i=0;
//  int dis = 0;
//
//  turnRobot(-80);
//  delay(300);
//  dis = sonar.convert_cm(sonar.ping_median(3));
//
//  if((dis <= mindis) && (dis != 0)){
//      mindis = dis;
//      min_i = 0 ;
//      blinkk(); 
//    }
//
//  for(int i=1;i<=16;i++){
//      turnRobot(10);
//      delay(300);
//      dis = sonar.convert_cm(sonar.ping_median(3));
//      if((dis <= mindis) && (dis != 0)){
//        mindis = dis;
//        min_i = i ;
//        blinkk();  
//      } 
//  }
//  int angle = -((16-min_i)*10);
//  turnRobot(angle);
//  
//}



//void loop() {
// String thisString; 
//  float mindis = 600;
//  int min_i=0;
//  int dis = 0;
//  Serial.print("finding -80");
//  turnRobot(-80);
//  delay(300);
//  Serial.print("\t");
//  Serial.println(getHeading());
// // dis = sonar.ping_cm();
//  //dis =sonar.ping_median(3);
//  dis = sonar.convert_cm(sonar.ping_median(3));
//  if((dis <= mindis) && (dis != 0)){
//        mindis = dis;
//        min_i = 0 ;
//        blinkk(); 
//      } 
//  for(int i=1;i<=16;i++){
//        thisString = String(i);
//       Serial.print(thisString);
//       Serial.print("\t");
//      turnRobot(10);
//      delay(300);
//      Serial.println(getHeading());
//      //dis = sonar.ping_cm();
//      dis = sonar.convert_cm(sonar.ping_median(3));
//      if((dis <= mindis) && (dis != 0)){
//        mindis = dis;
//        min_i = i ;
//        blinkk();  
//      } 
//  }
//  int angle = -((16-min_i)*10);
//  turnRobot(angle);
//  Serial.print(mindis);
//  Serial.print("\t");
//  Serial.print(min_i);
//  Serial.print("\t");
//  Serial.println(angle);
//  delay(3000);
//}



//void loop(){
//    
//    disL = sonarL.convert_cm(sonarL.ping_median(2));
//    delay(50);
//    disM = sonar.convert_cm(sonar.ping_median(2));
//    delay(50);
//    disR = sonarR.convert_cm(sonarR.ping_median(2));
//    delay(50);
//
//    if(((disM < 15) && (disL < 15))||((disL < 15) && (disR < 15))||((disM < 15) &&(disR < 15))){
//      brakeRobot();
//      delay(300);
//      reverseRobot(200);
//      delay(800);
//      brakeRobot();
//      delay(300);  
//      turnRobot(10);
//      delay(600);
//    }
////
////    Serial.print(disL);
////    Serial.print("\t");
////    Serial.print(disM);
////    Serial.print("\t");
////    Serial.println(disR);
//
//
//    
//
//    int error = disL - disR;
//    error = error*5;
//    
//    int lspeed = 120 + error;
//    if (lspeed > 180){
//      lspeed = 230;  
//    }
//
//    int rspeed = 120 - error;
//    if (rspeed > 180){
//      rspeed = 230;  
//    }
//
//    
//    
//    
//
//    digitalWrite(INR1,HIGH);
//    digitalWrite(INR2,LOW);
//    digitalWrite(INL1,HIGH);
//    digitalWrite(INL2,LOW);
//
//    
//
//    analogWrite(ENR,rspeed);
//    analogWrite(ENL,lspeed);
//
//    
//}










