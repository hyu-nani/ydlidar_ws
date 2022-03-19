/*
 * calculate.h
 *
 * Created: 2022-03-16 오후 9:26:56
 *  Author: cube_
 */ 
void positionCalculate(double nowPosL, double nowPosR, double nowAngle){
	//이동각도 계산
	double c = ((nowPosL-oldPosL)-(nowPosR-oldPosR))/2;
	double angle = 2*asin(c/robot_wheel_pitch);
	robot_angle += angle;
	if(robot_angle > 180)
		robot_angle = robot_angle - 360;
	else if(robot_angle < -180)
		robot_angle = robot_angle + 360;
	//x, y 계산
	double distanceL = diameter*PI/pulse*(nowPosL-oldPosL);
	double distanceR = diameter*PI/pulse*(nowPosR-oldPosR);
	robotX += sin(angle/2)*(distanceL+distanceR)/2;
	robotY += cos(angle/2)*(distanceL+distanceR)/2;
	
	oldPosL = nowPosL;
	oldPosR = nowPosR;
}