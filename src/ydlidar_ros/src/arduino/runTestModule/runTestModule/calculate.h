/*
 * calculate.h
 *
 * Created: 2022-03-16 ���� 9:26:56
 *  Author: cube_
 */ 
void positionCalculate(double nowPosL, double nowPosR, double nowAngle){
	double distanceL = diameter*PI/pulse*(nowPosL-oldPosL);
	double distanceR = diameter*PI/pulse*(nowPosR-oldPosR);
	//�̵����� ���
	double c = -(distanceL-distanceR)/2;
	double angle = asin(2*sin(c/robot_wheel_pitch)*cos(c/robot_wheel_pitch))*PI;
	//x, y ���
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