/*
 * calculate.h
 *
 * Created: 2022-03-16 ���� 9:26:56
 *  Author: cube_
 */ 
void positionCalculate(double nowPosL, double nowPosR, double nowAngle){
	//�̵����� ���
	double c = ((nowPosL-oldPosL)-(nowPosR-oldPosR))/2;
	double angle = 2*asin(c/robot_wheel_pitch);
	//x, y ���
	double distanceL = diameter*PI/pulse*(nowPosL-oldPosL);
	double distanceR = diameter*PI/pulse*(nowPosR-oldPosR);
	robotX += cos(angle/2+robot_angle)*(distanceL+distanceR)/2;
	robotY += -sin(angle/2+robot_angle)*(distanceL+distanceR)/2;
	
	robot_angle += angle;
	if(robot_angle > 180)
		robot_angle = robot_angle - 360;
	else if(robot_angle < -180)
		robot_angle = robot_angle + 360;
	oldPosL = nowPosL;
	oldPosR = nowPosR;
}