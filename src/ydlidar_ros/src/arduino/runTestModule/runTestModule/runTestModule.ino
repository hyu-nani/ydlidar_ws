/*
 * runTestModule.ino
 *
 * Created: 3/16/2022 5:51:25 PM
 * Author: ������
 * ROS �Ƶ��̳� �׽�Ʈ �ڵ�
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
	driverSet(speedLeft,1,0,1,0,SpeedRight);
	delay(1000);
}

void loop()
{
	nowTime = millis();
	if(testMode){
		digitalWrite(led,HIGH);
		delay(100);
		digitalWrite(led,LOW);
		driverSet(speedLeft,1,0,1,0,SpeedRight);
		delay(100);
		Serial.print("Left position:");
		Serial.print(encoderPosLeft);
		Serial.print("\t Right position:");
		Serial.println(encoderPosRight);
	}
	if(Serial.available()){
		int i = 0;
		while(Serial.available()){
			SerialData[i] = Serial.read();
			i++;
		}
		//int datalength = i;
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
