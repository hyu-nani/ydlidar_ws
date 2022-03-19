/*
 * runTestModule.ino
 *
 * Created: 3/16/2022 5:51:25 PM
 * Author: 배현한
 * ROS 아두이노 테스트 코드
 */ 
bool testMode = false;

#include "hardware.h"
#include "globalVariables.h"
#include "interrupt.h"
#include <math.h>
#include "calculate.h"


void setup()
{
	Serial.begin(115200);
	boardInitial();
	interruptInit();
}

void loop()
{
	nowTime = millis();
	positionCalculate(encoderPosLeft,encoderPosRight,robot_angle);
	if(testMode){
		if(nowTime - preTime > 100){
			Serial.print("Pos/");
			Serial.print(int(robotX/unitScale));
			Serial.print("/");
			Serial.print(int(robotY/unitScale));
			Serial.print("/");
			Serial.print(float(robot_angle));
			preTime = nowTime;
		}
	}
	if(Serial.available()){
		int i = 0;
		while(Serial.available()){
			SerialData[i] = Serial.read();
			delay(1);
			i++;
		}
		//int datalength = i;
		//Serial.print("[");
		//Serial.print(SerialData);
		//Serial.println("]");
		if(strcmp(SerialData,"stop")==0){
			digitalWrite(led,LOW);
			driverSet(speedLeft,0,0,0,0,SpeedRight);
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"front")==0){
			digitalWrite(led,HIGH);
			driverSet(speedLeft,1,0,1,0,SpeedRight);
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"left")==0){
			driverSet(speedLeft/2,0,1,1,0,SpeedRight/2);
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"right")==0){
			driverSet(speedLeft/2,1,0,0,1,SpeedRight/2);
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"back")==0){
			driverSet(speedLeft,0,1,0,1,SpeedRight);
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"Pos")==0){
			Serial.print("Pos/");
			Serial.print(int(robotX/unitScale));
			Serial.print("/");
			Serial.print(int(robotY/unitScale));
			Serial.print("/");
			Serial.print(float(robot_angle));
		}
		else{
			if(testMode){
				//Serial.println("OK");
			}
		}
		for(int j=0;j<256;j++)
			SerialData[j] = '\0';
	}
	
}
