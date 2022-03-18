/*
 * runTestModule.ino
 *
 * Created: 3/16/2022 5:51:25 PM
 * Author: 배현한
 * ROS 아두이노 테스트 코드
 */ 
bool testMode = true;

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
	if(testMode){
		if(nowTime - preTime > 1000){
			Serial.print("Left position:");
			Serial.print(encoderPosLeft);
			Serial.print("\t Right position:");
			Serial.println(encoderPosRight);
			preTime = nowTime;
		}
	}
	if(Serial.available()){
		int i = 0;
		while(Serial.available()){
			SerialData[i] = Serial.read();
			i++;
		}
		//int datalength = i;
		Serial.print(SerialData);
		if(strcmp(SerialData,"stop")==0){
			digitalWrite(led,LOW);
			driverSet(speedLeft,0,0,0,0,SpeedRight);
			Serial.println("OK");
		}
		else if(strcmp(SerialData,"front")==0){
			digitalWrite(led,HIGH);
			driverSet(speedLeft,1,0,1,0,SpeedRight);
			Serial.println("OK");
		}
		else if(strcmp(SerialData,"left")==0){
			driverSet(speedLeft,0,0,0,0,SpeedRight);
			Serial.println("OK");
		}
		else if(strcmp(SerialData,"right")==0){
			driverSet(speedLeft,0,0,0,0,SpeedRight);
			Serial.println("OK");
		}
		else if(strcmp(SerialData,"back")==0){
			driverSet(speedLeft,0,1,0,1,SpeedRight);
			Serial.println("OK");
		}else{
			if(testMode){
				//Serial.println("OK");
			}
		}
		for(int j=0;j<256;j++)
			SerialData[j] = '\0';
	}
	
}
