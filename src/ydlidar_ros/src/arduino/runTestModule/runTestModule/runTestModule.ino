/*
 * runTestModule.ino
 *
 * Created: 3/16/2022 5:51:25 PM
 * Author: 배현한
 * ROS 아두이노 테스트 코드
 */ 
#include "hardware.h"
#include "globalVariables.h"
#include "interrupt.h"
#include <math.h>
#include "calculate.h"

bool testMode = true;


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
		Serial.print("Left position:");
		Serial.print(encoderPosLeft);
		Serial.print("\t Right position:");
		Serial.println(encoderPosRight);
	}
	if(Serial.available()){
		while(Serial.available()){
			SerialData += Serial.read();
		}
		if(strcmp(SerialData,"stop")==0){
			driverSet(speedLeft,0,0,0,0,SpeedRight);
		}
		else if(strcmp(SerialData,"front")==0){
			driverSet(speedLeft,0,0,0,0,SpeedRight);
		}
		else if(strcmp(SerialData,"left")==0){
			driverSet(speedLeft,0,0,0,0,SpeedRight);
		}
		else if(strcmp(SerialData,"right")==0){
			driverSet(speedLeft,0,0,0,0,SpeedRight);
		}
		else{
			if(testMode){
				Serial.println("I don't understand");
			}
		}
	}
	preTime = nowTime;
}
