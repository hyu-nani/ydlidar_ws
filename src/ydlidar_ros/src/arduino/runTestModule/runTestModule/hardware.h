/*
 * board.h
 * 하드웨어 정보 모음
 * Created: 2022-03-16 오후 8:02:20
 *  Author: 배현한
 */ 

//encoder sensor pin
#define encoderPinA		2
#define encoderPinB		3
#define encoderPinC		18
#define encoderPinD		19

#define led			13

//information of robot
#define wheel_radius		6
#define	robot_wheel_pitch	39
#define gear_ratio			100
#define gear		0.2
#define volume		0.25
#define diameter	12.2
#define pulse		6400
#define radius		6
#define encoderPPR	28
#define quardature	2

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

void driverSet(int Lpwm, int in1, int in2, int in3, int in4, int Rpwm){
	in1 = (in1>1) ? 1 : in1;
	in2	= (in2>1) ? 1 : in2;
	in3	= (in3>1) ? 1 : in3;
	in4	= (in4>1) ? 1 : in4;
	in1 = (in1<0) ? 0 : in1;
	in2 = (in2<0) ? 0 : in2;
	in3 = (in3<0) ? 0 : in3;
	in4 = (in4<0) ? 0 : in4;
	Lpwm= (Lpwm>255) ? 255 : Lpwm;
	Rpwm= (Rpwm>255) ? 255 : Rpwm;
	Lpwm= (Lpwm<0) ? 0 : Lpwm;
	Rpwm= (Rpwm<0) ? 0 : Rpwm;
	digitalWrite(driverIn1,in1);
	digitalWrite(driverIn2,in2);
	digitalWrite(driverIn3,in3);
	digitalWrite(driverIn4,in4);
	analogWrite(driverPwmL,Lpwm);
	analogWrite(driverPwmR,Rpwm);
	/*
	if(testMode){
		Serial.println("motor driver Setting..");
		Serial.print("in1:");
		Serial.print(in1);
		Serial.print(" in2:");
		Serial.print(in2);
		Serial.print(" in3:");
		Serial.print(in3);
		Serial.print(" in4:");
		Serial.print(in4);
		Serial.print("\t LeftPWM:");
		Serial.print(Lpwm);
		Serial.print("\t RightPWM:");
		Serial.println(Rpwm);
	}
	*/
}