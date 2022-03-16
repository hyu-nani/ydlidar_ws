/*
 * calculate.h
 *
 * Created: 2022-03-16 오후 9:26:56
 *  Author: cube_
 */ 
void positionCalculate(float nowPosL, float nowPosR, float setha){
	//각속도
	float vel_motorL = ((nowPosL-oldPosL) / encoderPPR * TWO_PI) / (quardature * gear_ratio);
	float vel_motorR = ((nowPosR-oldPosR) / encoderPPR * TWO_PI) / (quardature * gear_ratio);
	
	//속도
	float vel_robot = (wheel_radius * (vel_motorL+vel_motorR)) / 2;
	//각속도
	float d_robot	= (wheel_radius * (vel_motorL-vel_motorR)) / robot_wheel_pitch;
 	
	oldPosL = nowPosL;
	oldPosR = nowPosR;
}