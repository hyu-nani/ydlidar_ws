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
	attachInterrupt(0, doEncoderA, CHANGE);
	attachInterrupt(1, doEncoderB, CHANGE);
	attachInterrupt(4, doEncoderC, CHANGE);
	attachInterrupt(5, doEncoderD, CHANGE);
}