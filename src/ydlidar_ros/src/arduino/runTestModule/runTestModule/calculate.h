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
	robot_angle += angle;
	//�ӵ�
	//float vel_robot = (wheel_radius * (vel_motorL+vel_motorR)) / 2;
	//���ӵ�
	//float d_robot	= (wheel_radius * (vel_motorL-vel_motorR)) / robot_wheel_pitch;
 	
	oldPosL = nowPosL;
	oldPosR = nowPosR;
}