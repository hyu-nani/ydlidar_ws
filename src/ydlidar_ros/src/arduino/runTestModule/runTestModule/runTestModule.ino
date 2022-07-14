/*
 * runTestModule.ino
 *
 * Created: 3/16/2022 5:51:25 PM
 * Author: 
 * ROS
 */ 
bool testMode = false;

#include "globalVariables.h"
#include "hardware.h"
#include "interrupt.h"
#include <math.h>
#include "calculate.h"


void setup()
{
	Serial.begin(115200);
	boardInitial();
	interruptInit();
	driverSet(0,0,0,0,0,0);
}

void loop()
{
	nowTime = millis();
	positionCalculate(encoderPosLeft,encoderPosRight);
	errorGapCal(encoderPosLeft,encoderPosRight,direction);
	analogWrite(driverPwmL,lefePWMoutput+errorGap);
	analogWrite(driverPwmR,rightPWMoutput-errorGap);
	if(Serial.available()){
		int i = 0;
		while(Serial.available()){
			SerialData[i] = Serial.read();
			delay(1);
			i++;
		}
		if(strcmp(SerialData,"stop")==0){
			direction = 0;
			driverSet(speedLeft,0,0,0,0,speedRight);
			Serial.print("OK");//notify completion of transfer
		}else if(strcmp(SerialData,"front")==0){
			direction = 1;
			driverSet(speedLeft,1,0,1,0,speedRight);
			fixAngle = robot_angle;
			Serial.print("OK");//notify completion of transfer
		}
		else if(strcmp(SerialData,"left")==0){
			direction = 2;
			driverSet(speedLeft,0,1,1,0,speedRight);
			Serial.print("OK");//notify completion of transfer
		}else if(strcmp(SerialData,"right")==0){
			direction = 3;
			driverSet(speedLeft,1,0,0,1,speedRight);
			Serial.print("OK");//notify completion of transfer
		}else if(strcmp(SerialData,"back")==0){
			direction = 4;
			driverSet(speedLeft,0,1,0,1,speedRight);
			fixAngle = robot_angle;
			Serial.print("OK");//notify completion of transfer
		}else if(strcmp(SerialData,"reset")==0){
			direction = 0;
			driverSet(speedLeft,0,0,0,0,speedRight);
			robot_angle = 0;
			robotX = 0;
			robotY = 0;
			Serial.print("OK");//notify completion of transfer
		}else if(strcmp(SerialData,"test")==0){
			fixAngle = robot_angle;
			direction = 4;
			driverSet(speedLeft,0,1,0,1,speedRight);
			int a = robot_distance;
			while(a - robot_distance < 100){
				nowTime = millis();
				positionCalculate(encoderPosLeft,encoderPosRight);
				errorGapCal(encoderPosLeft,encoderPosRight,direction);
				analogWrite(driverPwmL,lefePWMoutput+errorGap);
				analogWrite(driverPwmR,rightPWMoutput-errorGap);
				if (nowTime > preTime+100)
				{
					Serial.print(robot_distance);
					preTime=nowTime;
				}
			}
			robot_distance = 0;
			direction = 0;
			driverSet(speedLeft,0,0,0,0,speedRight);
			Serial.print("OK");//notify completion of transfer
		}else if(strcmp(SerialData,"10cm")==0){
			digitalWrite(led,HIGH);
			fixAngle = robot_angle;
			direction = 1;
			driverSet(speedLeft,1,0,1,0,speedRight);
			int a = robot_distance;
			while( robot_distance - a < 100){ //check distance
				nowTime = millis();
				positionCalculate(encoderPosLeft,encoderPosRight);
				errorGapCal(encoderPosLeft,encoderPosRight,direction);
				analogWrite(driverPwmL,lefePWMoutput+errorGap);
				analogWrite(driverPwmR,rightPWMoutput-errorGap);
				if (nowTime > preTime+100)
				{
					Serial.print(robot_distance);
					preTime=nowTime;
				}
			}
			robot_distance = 0;
			direction = 0;
			driverSet(speedLeft,0,0,0,0,speedRight);
			Serial.print("OK");	//notify completion of transfer
		}else if(strcmp(SerialData,"up")==0){//this code for setting of value
			robot_wheel_pitch += 0.01;
			Serial.print("OK");	//notify completion of transfer
		}else if(strcmp(SerialData,"down")==0){
			robot_wheel_pitch -= 0.01;
			Serial.print("OK");	//notify completion of transfer
		}else if(SerialData[0]=='U' && SerialData[1]=='n'){
			sscanf(SerialData,"Unit%fD",&unitScale);
			Serial.print("OK");	//notify completion of transfer
		}else if(strcmp(SerialData,"Pos")==0){
			positionPrint();
		}else if(SerialData[0]=='g' && SerialData[1]=='o'){	//targetting mode
			arrivalX = 0;
			arrivalY = 0;
			sscanf(SerialData,"go/%d/%dE", &arrivalX, &arrivalY);
			if(arrivalX == 1){
				rotateRight();
				goOnePoint();
				Serial.print("OK");
			}
			else if(arrivalX == -1){
				rotateLeft();
				goOnePoint();
				Serial.print("OK");
			}
			else if(arrivalY == 1){
				goOnePoint();
				Serial.print("OK");
			}
			else if(arrivalY == -1){
				backOnePoint();
				Serial.print("OK");
			}
		}else{
			if(testMode){
				//Serial.println("OK");
			}
		}
		//reset the SerialData
		for(int j=0;j<256;j++)
		SerialData[j] = '\0';
	}
	
}
