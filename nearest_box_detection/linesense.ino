



int check_Line(){
  Line_SVL = digitalRead(Line_SL);
  Line_SVR = digitalRead(Line_SR);
  Line_SVM = digitalRead(Line_SM);

  Line_RF = !Line_SVR;
  Line_MF = !Line_SVM;
  Line_LF = !Line_SVL;

  timeStart = millis();
  
  if(!(Line_SVL && Line_SVM && Line_SVR)){
    Serial.println("IFIN");
      //brakeRobot();
      return 1;
  }else{
    return 0;  
  }

}


int senseline(){
  while(millis()<= timeStart+2000){
        Line_SVL = digitalRead(Line_SL);
        Line_SVR = digitalRead(Line_SR);
        Line_SVM = digitalRead(Line_SM);

        if(Line_RF==1){
          ;  
        }else {
           Line_RF = !Line_SVR; 
        }

         if(Line_LF==1){
          ;  
        }else {
           Line_LF = !Line_SVL; 
        }

         if(Line_MF==1){
          ;  
        }else {
           Line_MF = !Line_SVM; 
        }
        
        if(Line_RF && Line_MF && Line_LF){
        return 1;
        }
      }

  return 0;
  
}
