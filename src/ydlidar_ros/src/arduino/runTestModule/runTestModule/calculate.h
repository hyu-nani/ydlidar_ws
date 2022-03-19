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
	//x, y 계산
	double distanceL = diameter*PI/pulse*(abs(nowPosL-oldPosL));
	double distanceR = diameter*PI/pulse*(abs(nowPosR-oldPosR));
	robotX += cos(angle/2+nowAngle)*(distanceL+distanceR)/2;
	robotY += -sin(angle/2+nowAngle)*(distanceL+distanceR)/2;
	
	nowAngle += angle;
	if(nowAngle > 180)
		nowAngle = nowAngle - 360;
	else if(nowAngle < -180)
		nowAngle = nowAngle + 360;
	oldPosL = nowPosL;
	oldPosR = nowPosR;
	robot_angle = nowAngle;
}