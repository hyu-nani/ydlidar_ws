/*
 * interrupt.h
 *
 * Created: 2022-03-16 ¿ÀÈÄ 8:14:17
 *  Author: cube_
 */ 

void doEncoderA(){
	encoderPosLeft	+= (digitalRead(encoderPinA)==digitalRead(encoderPinB)) ? 1 : -1;
}
void doEncoderB(){
	encoderPosLeft	+= (digitalRead(encoderPinA)==digitalRead(encoderPinB)) ? 1 : -1;
}
void doEncoderC(){
	encoderPosRight	+= (digitalRead(encoderPinC)==digitalRead(encoderPinD)) ? 1 : -1;
}
void doEncoderD(){
	encoderPosRight	+= (digitalRead(encoderPinC)==digitalRead(encoderPinD)) ? 1 : -1;
}
void interruptInit(){
	attachInterrupt(0, doEncoderA, CHANGE);		//mega pin 2
	attachInterrupt(1, doEncoderB, CHANGE);		//mega pin 3
	attachInterrupt(4, doEncoderC, CHANGE);		//mega pin 19
	attachInterrupt(5, doEncoderD, CHANGE);		//mega pin 18
}