/*
 * calculate.h
 *
 * Created: 2022-03-16 오후 9:26:56
 *  Author: cube_
 */ 
void positionCalculate(double nowPosL, double nowPosR){
	double distanceL = diameter*M_PI/pulse*(nowPosL-oldPosL);
	double distanceR = diameter*M_PI/pulse*(nowPosR-oldPosR);
	oldPosL = nowPosL;
	oldPosR = nowPosR;
	
	//이동각도 계산
	double c = (distanceL-distanceR)/2;
	//double angle = asin(2*sin(c/robot_wheel_pitch)*cos(c/robot_wheel_pitch))*(PI/180);
	double angle = -2*asin(c/robot_wheel_pitch)*(180.0/M_PI);

	//x, y 계산
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

//0:stop, 1:front, 2:left, 3:right, 4:back
void errorGapCal(double nowAngle, double nowPosL, double nowPosR, int direct){
	double distanceL1 = diameter*M_PI/pulse*(nowPosL-oldPosL1);
	double distanceR1 = diameter*M_PI/pulse*(nowPosR-oldPosR1);
	oldPosL1 = nowPosL;
	oldPosR1 = nowPosR;
	
	//개별 방향 속도 제어
	if(direct==0){//stop
		errorGap = 0;
	}
	else if(direct==1){//front
		if(fixAngle < nowAngle)//rising
			errorGap = +10;
		else if(fixAngle > nowAngle)
			errorGap = -10;
		else
			errorGap = 0;
	}
	else if(direct==2){//left
		if(-distanceL1>distanceR1)
			errorGap = -10;
		else if(-distanceL1<distanceR1)
			errorGap = +10;
		else
			errorGap = 0;
	}
	else if(direct==3){//right
		if(distanceL1>-distanceR1)
			errorGap = -10;
		else if(distanceL1<-distanceR1)
			errorGap = +10;
		else
			errorGap = 0;
	}
	else if(direct==4){//back
		if(fixAngle < nowAngle)//rising
			errorGap = -10;
		else if(fixAngle > nowAngle)
			errorGap = +10;
		else
			errorGap = 0;
	}
	
}