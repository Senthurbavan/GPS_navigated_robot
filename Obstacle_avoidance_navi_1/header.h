
//int BUTTON = 18;
//int bState = 0;

//MOTOR Driver PINS
int ENR = 6;
int ENL = 7;
int INR1 =30;
int INR2 =31;
int INL1 =32;
int INL2 =33;

//Encoder Pins
int leftEncoderA = 3;
int leftEncoderB = 5;
int rightEncoderA = 2;
int rightEncoderB = 4;

//Encoder Count
volatile long int encodercount_R =0;
volatile long int encodercount_L =0;

//Encoder parameters
long int encoderCPR = 275;     //rising
long int chassisR = 95;
long int wheelR = 41;
float pi = 3.141592653;

//Ultrasonic Pins
int TL = 40;
int TM = 42;
int TR = 44;

int EL = 41;
int EM = 43;
int ER = 45;

int MAX_DIS = 200;

//Functions
void turnRobot(float angle);
void fowardRobot(int withspeed);
void brakeRobot(void);
void reverseRobot(int withspeed);
int obstacle();
void avoidObstacle();
