#include <HMC5883L_Simple.h>
//#include <Arduino.h>
#include <TinyGPS++.h>
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
unsigned long last = 0UL;

HMC5883L_Simple Compass;


int in1=6;
int in2=7;
int in3=8;
int in4=9;
int in5=10;
int in6=11;
int in7=12;
int in8=13;

int en1=2;
int en2=3;
int en3=4;
int en4=5;

//int mtrig=49;
//int mecho=48;
//int rtrig=51;
//int recho=50;
//int ltrig=47;
//int lecho=46;

int led=38;

int sonar();
int dir=0;

#include <Wire.h> //I2C Arduino Library
//#define Magnetometer_mX0 0x03  
//#define Magnetometer_mX1 0x04  
//#define Magnetometer_mZ0 0x05  
//#define Magnetometer_mZ1 0x06  
//#define Magnetometer_mY0 0x07  
//#define Magnetometer_mY1 0x08  
//int mX0, mX1, mX_out;
//int mY0, mY1, mY_out;
//int mZ0, mZ1, mZ_out;
//float heading, headingDegrees, headingFiltered, declination;
//float Xm,Ym,Zm;
//#define Magnetometer 0x1E //I2C 7bit address of HMC5883

void setup() {
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(in5,OUTPUT);
pinMode(in6,OUTPUT);
pinMode(in7,OUTPUT);
pinMode(in8,OUTPUT);
pinMode(en1,OUTPUT);
pinMode(en2,OUTPUT);
pinMode(en3,OUTPUT);
pinMode(en4,OUTPUT);

pinMode(led,OUTPUT);

// pinMode(mtrig,OUTPUT);
// pinMode(mecho,INPUT);
//  pinMode(rtrig,OUTPUT);
// pinMode(recho,INPUT);
//  pinMode(ltrig,OUTPUT);
// pinMode(lecho,INPUT);
 Serial.begin(115200);
  Wire.begin();
  
  
  Compass.SetDeclination(-2, 10, 'W'); 
  
 Compass.SetOrientation(COMPASS_HORIZONTAL_X_NORTH);
  
  Serial1.begin(GPSBaud);
  


}

void loop() {

  int heading = Compass.GetHeadingDegrees();
//dir=80;
  dir=gps1();
  Serial.print(dir);
  Serial.print("Heading: \t");
  Serial.println( heading ); 
     
 if((abs(dir-heading))<1){
  Serial.print("Farward");
  motor(1, 'F', 250);
  motor(2, 'F', 250);
  motor(3, 'F', 250);
  motor(4, 'F', 250);
  delay(500);
 }
else{
      if (dir<180){
        if((heading<(dir+180)) && (heading>dir)){
        Serial.print("acw");
        motor(1, 'B', 250);
        motor(2, 'B', 250);
        motor(3, 'F', 250);
        motor(4, 'F', 250);
    
        }
          else{
            Serial.print("cw");
            
            motor(1, 'F', 250);
            motor(2, 'F', 250);
            motor(3, 'B', 250);
            motor(4, 'B', 250);
            
          }
        
      }
      else{
              if((heading>(dir-180)) && (heading<dir)){

                Serial.print("cw");
          motor(1, 'F', 250);
          motor(2, 'F', 250);
          motor(3, 'B', 250);
          motor(4, 'B', 250);
        }
        else{
          Serial.print("acw");
          motor(1, 'B', 250);
          motor(2, 'B', 250);
          motor(3, 'F', 250);
          motor(4, 'F', 250);
        }
        
}

}

}
 


void motor(int X,char x,int y){
 switch(x){
case 'F':
Forward(X,y);
break;
case 'B':
Backward(X,y);
break;
case 'S':
Break(X,y);
break;
   }
  
}
void Forward(int X,int x){
  if(X==1){
  digitalWrite(in1,HIGH);
   digitalWrite(in2,LOW);
   analogWrite(en1,x);
  }
  else if(X==2){
    digitalWrite(in3,HIGH);
   digitalWrite(in4,LOW);
   analogWrite(en2,x);
  }
  else if(X==3){
  digitalWrite(in5,HIGH);
   digitalWrite(in6,LOW);
   analogWrite(en3,x);
  }
  else if(X==4){
    digitalWrite(in7,HIGH);
   digitalWrite(in8,LOW);
   analogWrite(en4,x);
  }
   
}
void Backward(int X,int x){
  if(X==1){
  digitalWrite(in1,LOW);
   digitalWrite(in2,HIGH);
   analogWrite(en1,x);
  }
  else if(X==2){
    digitalWrite(in3,LOW);
   digitalWrite(in4,HIGH);
   analogWrite(en2,x);
  }
   else if(X==3){
  digitalWrite(in5,LOW);
   digitalWrite(in6,HIGH);
   analogWrite(en3,x);
  }
  else if(X==4){
    digitalWrite(in7,LOW);
   digitalWrite(in8,HIGH);
   analogWrite(en4,x);
  }
}
void Break(int X,int x){
    if(X==1){
  digitalWrite(in1,LOW);
   digitalWrite(in2,LOW);
   analogWrite(en1,0);
  }
  else if(X==2){
    digitalWrite(in3,LOW);
   digitalWrite(in4,LOW);
   analogWrite(en2,0);
  }
    else if(X==3){
  digitalWrite(in5,LOW);
   digitalWrite(in6,LOW);
   analogWrite(en3,0);
  }
  else if(X==4){
    digitalWrite(in7,LOW);
   digitalWrite(in8,LOW);
   analogWrite(en4,0);
  }
}

int sonar(int tp,int ep) {
 digitalWrite(tp,LOW);
 delayMicroseconds(2);
  digitalWrite(tp,HIGH);
delayMicroseconds(10); 
 digitalWrite(tp,LOW);
int due=pulseIn(ep,HIGH);
int  dis1=.033*due;
 int distance=dis1/2;

if (distance<0){
distance=100;
}
return distance;
 
}




float gps1() {
  // put your main code here, to run repeatedly:
   // Dispatch incoming characters
  while (Serial1.available() > 0)
    gps.encode(Serial1.read());
//  Serial.print("LAT=");  Serial.print(gps.location.lat(), 6);
//  Serial.print("  LONG="); Serial.print(gps.location.lng(), 6);
//  Serial.print("  ALT=");  Serial.print(gps.altitude.meters());
//  Serial.println();
  //delay(500);

  if (gps.location.isValid())
    {
      static const double TAR_LAT = 6.796688, TAR_LON = 79.901222;
      double distanceToTarget =
        TinyGPSPlus::distanceBetween(
          gps.location.lat(),
          gps.location.lng(),
          TAR_LAT, 
          TAR_LON);
      double courseToTarget =
        TinyGPSPlus::courseTo(
          gps.location.lat(),
          gps.location.lng(),
          TAR_LAT, 
          TAR_LON);
//0
//      Serial.print(F("  Target Distance="));
//      Serial.print(distanceToTarget, 6);
//      Serial.print(F(" m Course-to="));
//      Serial.print(courseToTarget, 6);
//      Serial+.print(F(" degrees ["));
//      Serial.print(TinyGPSPlus::cardinal(courseToTarget));
//      Serial.println(F("]"));
       smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
    return courseToTarget;
    }

}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}
