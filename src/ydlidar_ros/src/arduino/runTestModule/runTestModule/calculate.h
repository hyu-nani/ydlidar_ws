/*
 * calculate.h
 *
 * Created: 2022-03-16 오후 9:26:56
 *  Author: cube_
 */ 
void positionCalculate(double nowPosL, double nowPosR){
	double distanceL = diameter*PI/pulse*(nowPosL-oldPosL);
	double distanceR = diameter*PI/pulse*(nowPosR-oldPosR);
	oldPosL = nowPosL;
	oldPosR = nowPosR;
	//이동각도 계산
	double c = (distanceL-distanceR)/2;
	//double angle = asin(2*sin(c/robot_wheel_pitch)*cos(c/robot_wheel_pitch))*(180/PI);
	double angle = -2*asin((distanceR-distanceL)/(2*robot_wheel_pitch)*(180/PI));
	
	//x, y 계산
	robotX += cos(((angle/2-robot_angle))*(PI/180.0))*(distanceL+distanceR)/2;
	robotY += sin(((angle/2-robot_angle))*(PI/180.0))*(distanceL+distanceR)/2;
	robot_angle = angle - robot_angle;
	if(robot_angle > 180)
		robot_angle = robot_angle - 360;
	else if(robot_angle < -180)
		robot_angle = robot_angle + 360;
}