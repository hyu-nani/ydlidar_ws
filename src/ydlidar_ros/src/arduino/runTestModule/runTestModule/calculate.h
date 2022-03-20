/*
 * calculate.h
 *
 * Created: 2022-03-16 오후 9:26:56
 *  Author: cube_
 */ 
void positionCalculate(double nowPosL, double nowPosR, double nowAngle){
	double distanceL = diameter*PI/pulse*(nowPosL-oldPosL);
	double distanceR = diameter*PI/pulse*(nowPosR-oldPosR);
	//이동각도 계산
	double c = -(distanceL-distanceR)/2;
	//double angle = asin(2*sin(c/robot_wheel_pitch)*cos(c/robot_wheel_pitch))*(180/PI);
	double angle = -2*asin((distanceL-distanceR)/(2*robot_wheel_pitch)*(180/PI));
	
	//x, y 계산
	robotX += cos(((angle-nowAngle)/2)*(PI/180.0))*(distanceL+distanceR)/2;
	robotY += -sin(((angle-nowAngle)/2)*(PI/180.0))*(distanceL+distanceR)/2;
	nowAngle += angle;
	if(nowAngle > 180)
		nowAngle = nowAngle - 360;
	else if(nowAngle < -180)
		nowAngle = nowAngle + 360;
	oldPosL = nowPosL;
	oldPosR = nowPosR;
	robot_angle = nowAngle;
}