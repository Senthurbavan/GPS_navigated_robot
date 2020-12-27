

int obstacle(){
  unsigned int dL = sL.ping_cm();
  unsigned int dM = sM.ping_cm();
  unsigned int dR = sR.ping_cm();
  
  if( ((dL>10)||(dL==0)) && ((dM>10)||(dM==0)) && ((dR>10)||(dR==0))){
    return 0;  
  }else{
    return 1;  
  }  
}

void avoidObstacle(){
  unsigned int dl;
  unsigned int dm;
  unsigned int dr;

  brakeRobot();

  Serial.println("brake");
  delay(200);
  
  dl = sL.ping_cm();
  dm = sM.ping_cm();
  dr = sR.ping_cm();
  Serial.println("read");

  if(dm<=10){
    if(dl>dr){
      turnRobot(-pi/3);
      delay(100);
      Serial.println("turn-pi/3");  
    }else{
      turnRobot(pi/3);
      delay(100);
      Serial.println("turn pi/3");  
    }
  }else{
    while(sR.ping_cm()<=10){
      turnRobot(-pi/6);
      Serial.println("turn-pi/6");  
      delay(100);  
    }

    while(sL.ping_cm()<=10){
      turnRobot(pi/6); 
      Serial.println("turnpi/6");  
      delay(100);
    }
  }

  if(obstacle()){
    avoidObstacle();  
  }else{
    // can put fowardRobot() here
    return;  
  }

  
}
