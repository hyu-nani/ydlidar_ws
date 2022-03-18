
// encoder position R, L
int encoderPosLeft, encoderPosRight;
float oldPosL, oldPosR;

//time
long	nowTime	=	millis(); 
long	preTime	=	nowTime;

//Serial
char	SerialData[256] = "";

//wheel
int speedLeft = 100;
int SpeedRight= 100;

//robot
int robotX	=	0;
int robotY	=	0;