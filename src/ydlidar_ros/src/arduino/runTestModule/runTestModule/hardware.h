/*
 * board.h
 * 
 * Created: 2022-03-16 8:02:20
 *  Author: 
 */ 

//encoder sensor pin
#define encoderPinA	2
#define encoderPinB	3
#define encoderPinC	18
#define encoderPinD	19

#define led	13

//information of robo
//#define wheel_radius		6//
float	robot_wheel_pitch	=	39.54;//distance
//#define gear_ratio	100
//#define gear		0.2
//#define volume		0.25
float	diameter	=	12.25;
#define pulse	7228 //
//#define radius		6
//#define encoderPPR	28
//#define quardature	2

//motor driver pin
#define driverPwmL	6
#define driverIn1	7
#define driverIn2	8
#define driverIn3	9
#define driverIn4	10
#define driverPwmR	11

void boardInitial(){
	pinMode(driverPwmL,OUTPUT);
	pinMode(driverPwmR,OUTPUT);
	pinMode(driverIn1,OUTPUT);
	pinMode(driverIn2,OUTPUT);
	pinMode(driverIn3,OUTPUT);
	pinMode(driverIn4,OUTPUT);
	pinMode(led,OUTPUT);
	pinMode(encoderPinA,INPUT_PULLUP);
	pinMode(encoderPinB,INPUT_PULLUP);
	pinMode(encoderPinC,INPUT_PULLUP);
	pinMode(encoderPinD,INPUT_PULLUP);
	
	digitalWrite(driverIn1,LOW);
	digitalWrite(driverIn2,LOW);
	digitalWrite(driverIn3,LOW);
	digitalWrite(driverIn4,LOW);
	analogWrite(driverPwmL,0);
	analogWrite(driverPwmR,0);
}

void driverSet(int Lpwm, int drivein1, int drivein2, int drivein3, int drivein4, int Rpwm){
	in1 = drivein1;	
	in2 = drivein2;
	in3 = drivein3;
	in4 = drivein4;
	lefePWMoutput = Lpwm;
	rightPWMoutput= Rpwm;
	lefePWMoutput = (Lpwm>255) ? 255 : Lpwm;
	rightPWMoutput= (Rpwm>255) ? 255 : Rpwm;
	lefePWMoutput = (Lpwm<0) ? 0 : Lpwm;
	rightPWMoutput= (Rpwm<0) ? 0 : Rpwm;
	
	//all low protect motor driver
	digitalWrite(driverIn1,LOW);
	digitalWrite(driverIn2,LOW);
	digitalWrite(driverIn3,LOW);
	digitalWrite(driverIn4,LOW);
	delay(200);	//essential code protect for motor driver
	digitalWrite(driverIn1,in1);
	digitalWrite(driverIn2,in2);
	digitalWrite(driverIn3,in3);
	digitalWrite(driverIn4,in4);
}


void positionPrint(){
	Serial.print("Pos/");
	Serial.print(int(robotX/unitScale));
	Serial.print("/");
	Serial.print(int(robotY/unitScale));
	Serial.print("/");
	Serial.print(robot_angle,10);
	Serial.print("/");
	Serial.print(robot_wheel_pitch);
	Serial.print("E");
}//

