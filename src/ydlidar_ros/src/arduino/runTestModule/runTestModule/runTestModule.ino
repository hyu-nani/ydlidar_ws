/*
 * runTestModule.ino
 *
 * Created: 3/16/2022 5:51:25 PM
 * Author: ������
 * ROS �Ƶ��̳� �׽�Ʈ �ڵ�
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
}

void loop()
{
	nowTime = millis();
	positionCalculate(encoderPosLeft,encoderPosRight);
	if(testMode){
		if(nowTime - preTime > 100){
			Serial.print("Pos/");
			Serial.print(int(robotX/unitScale));
			Serial.print("/");
			Serial.print(int(robotY/unitScale));
			Serial.print("/");
			Serial.print(robot_angle,10);
			preTime = nowTime;
		}
		
	}
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
		//int datalength = i;
		//Serial.print("[");
		//Serial.print(SerialData);
		//Serial.println("]");
		if(strcmp(SerialData,"stop")==0){
			digitalWrite(led,LOW);
			direction = 0;
			driverSet(speedLeft,0,0,0,0,speedRight);
			driverOUTPUT();
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"front")==0){
			digitalWrite(led,HIGH);
			fixAngle = robot_angle;
			direction = 1;
			driverSet(speedLeft,1,0,1,0,speedRight);
			driverOUTPUT();
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"left")==0){
			direction = 2;
			driverSet(speedLeft,0,1,1,0,speedRight);
			driverOUTPUT();
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"right")==0){
			direction = 3;
			driverSet(speedLeft,1,0,0,1,speedRight);
			driverOUTPUT();
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"back")==0){
			direction = 4;
			fixAngle = robot_angle;
			driverSet(speedLeft,0,1,0,1,speedRight);
			driverOUTPUT();
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"reset")==0){
			direction = 0;
			driverSet(speedLeft,0,0,0,0,speedRight);
			driverOUTPUT();
			robot_angle = 0;
			robotX = 0;
			robotY = 0;
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"test")==0){
			digitalWrite(led,HIGH);
			fixAngle = robot_angle;
			direction = 1;
			driverSet(speedLeft,1,0,1,0,speedRight);
			driverOUTPUT();
			while(robot_distance < 100){
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
			driverOUTPUT();
			Serial.print("OK");
		}
		else if(SerialData[0]=='U' && SerialData[1]=='n' && SerialData[2]=='i' && SerialData[3]=='t'){
			sscanf(SerialData,"Unit%f",&unitScale);
			Serial.print("OK");
		}
		else if(strcmp(SerialData,"Pos")==0){
			Serial.print("Pos/");
			Serial.print(int(robotX/unitScale));
			Serial.print("/");
			Serial.print(int(robotY/unitScale));
			Serial.print("/");
			Serial.print(robot_angle,10);
			Serial.print("/");
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
