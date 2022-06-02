/*
 * calculate.h
 *
 * Created: 2022-03-16 9:26:56
 *  Author: cube_
 */ 
void positionCalculate(double nowPosL, double nowPosR){
	double distanceL = diameter*M_PI/pulse*(nowPosL-oldPosL);
	double distanceR = diameter*M_PI/pulse*(nowPosR-oldPosR);
	oldPosL = nowPosL;
	oldPosR = nowPosR;
	
	//calculating the angle
	double c = (distanceL-distanceR)/2;
	double angle = -2*asin(c/robot_wheel_pitch)*(180.0/M_PI);

	//calculating the distance
	double distance = (distanceL+distanceR)/2;
	robotX += -sin(((angle/2+robot_angle))*(M_PI/180.0))*distance;
	robotY += cos(((angle/2+robot_angle))*(M_PI/180.0))*distance;
	robot_distance += distance;
	robot_angle = robot_angle+angle;
	if(robot_angle > 180)
		robot_angle = robot_angle - 360;
	else if(robot_angle < -180)
		robot_angle = robot_angle + 360;
}

int oldDirect=0;
//0:stop, 1:front, 2:left, 3:right, 4:back
void errorGapCal(double nowPosL, double nowPosR, int direct){
	//if the direction changed, save the wheel position 
	if(direct != oldDirect){
		oldPosL1	= nowPosL;
		oldPosR1	= nowPosR;
		oldDirect	= direct;
	}
	//calculating for distance each wheel
	double distanceL1 = diameter*M_PI/pulse*(nowPosL-oldPosL1);
	double distanceR1 = diameter*M_PI/pulse*(nowPosR-oldPosR1);
	
	int val = 5;//this error gap for wheel speed each wheel
	
	if(direct==0){//stop
		errorGap = 0;
	}else if(direct==1){//front
		if(distanceL1<distanceR1)//rising
			errorGap = +val;
		else if(distanceL1>distanceR1)
			errorGap = -val;
		else
			errorGap = 0;
	}else if(direct==2){//left
		if(-distanceL1>distanceR1)
			errorGap = -val;
		else if(-distanceL1<distanceR1)
			errorGap = +val;
		else
			errorGap = 0;
	}else if(direct==3){//right
		if(distanceL1>-distanceR1)
			errorGap = -val;
		else if(distanceL1<-distanceR1)
			errorGap = +val;
		else
			errorGap = 0;
	}else if(direct==4){//back
		if(distanceL1<distanceR1)//rising
			errorGap = -val*2;
		else if(distanceL1>distanceR1)
			errorGap = +val*2;
		else
			errorGap = 0;
	}
}

void rotateLeft(){
	driverSet(speedLeft,0,1,1,0,speedRight);
	fixAngle = robot_angle;
	while(robot_angle < fixAngle+90){
		positionCalculate(encoderPosLeft,encoderPosRight);
		errorGapCal(encoderPosLeft,encoderPosRight,direction);
		analogWrite(driverPwmL,lefePWMoutput+errorGap);
		analogWrite(driverPwmR,rightPWMoutput-errorGap);
	}
}
void rotateRight(){
	driverSet(speedLeft,1,0,0,1,speedRight);
	fixAngle = robot_angle;
	while(robot_angle > fixAngle-90){
		positionCalculate(encoderPosLeft,encoderPosRight);
		errorGapCal(encoderPosLeft,encoderPosRight,direction);
		analogWrite(driverPwmL,lefePWMoutput+errorGap);
		analogWrite(driverPwmR,rightPWMoutput-errorGap);
	}
}
void goOnePoint(){
	driverSet(speedLeft,1,0,1,0,speedRight);
	int fixDistance = robot_distance;
	while(robot_distance - fixDistance < unitScale){
		positionCalculate(encoderPosLeft,encoderPosRight);
		errorGapCal(encoderPosLeft,encoderPosRight,direction);
		analogWrite(driverPwmL,lefePWMoutput+errorGap);
		analogWrite(driverPwmR,rightPWMoutput-errorGap);
	}
}
void backOnePoint(){
	driverSet(speedLeft,0,1,0,1,speedRight);
	int fixDistance = robot_distance;
	while(fixDistance - robot_distance < unitScale){
		positionCalculate(encoderPosLeft,encoderPosRight);
		errorGapCal(encoderPosLeft,encoderPosRight,direction);
		analogWrite(driverPwmL,lefePWMoutput+errorGap);
		analogWrite(driverPwmR,rightPWMoutput-errorGap);
	}
}