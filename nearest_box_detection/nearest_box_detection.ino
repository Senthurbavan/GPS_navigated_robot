#include <Wire.h>
#include <HMC5883L.h>
#include <NewPing.h>
#include"header.h"

//compass object
HMC5883L compass;

//Ultrasonic Object
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonarL(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE);
NewPing sonarR(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE);



void setup() {
  pinMode(INR1,OUTPUT);
  pinMode(INR2,OUTPUT);
  pinMode(INL1,OUTPUT);
  pinMode(INL2,OUTPUT);
  pinMode(Line_SL,INPUT);
  pinMode(Line_SM,INPUT);
  pinMode(Line_SR,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);

  //Check Magnetometer
  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }

  // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_75HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(-136, 44);
  
    
}



void loop(){
  fowardRobot(200);
  if(check_Line()){
    if(senseline()){
      brakeRobot();
      delay(1000);
      int i = findshortdis();
      delay(600);
      gotodestination(120); 
      delay(500); 
      while(sonar.convert_cm(sonar.ping_median(2)) < 30){
        reverseRobot(120); 
        delay(40); 
      }
      brakeRobot();
      delay(400);
      if(i<= 0){
        turnRobot(100);  
      }else{
        turnRobot(-100);
      }
      fowardRobot(150);
      delay(400);
      brakeRobot();
      delay(400);
      i = findshortdis();
      delay(600);
      gotodestination(120); 
      delay(5000);
    }  
  }
}







  
