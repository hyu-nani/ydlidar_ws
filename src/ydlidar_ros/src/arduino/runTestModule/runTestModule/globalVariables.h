
// encoder position R, L
float encoderPosLeft, encoderPosRight;
float oldPosL, oldPosR;

//time
long	nowTime	=	millis(); 
long	preTime	=	nowTime;

//Serial
char	SerialData[256] = "";

//wheel
int speedLeft = 50;
int SpeedRight= 50;

//robot
int robotX	=	0;
int robotY	=	0;