
// encoder position R, L
float encoderPosLeft, encoderPosRight;
float oldPosL, oldPosR;

//time
long	nowTime	=	millis(); 
long	preTime	=	nowTime;

//Serial
char	SerialData[256] = "";

//wheel
int speedLeft	=	80;
int SpeedRight	=	80;

//robot
double robotX		=	0;
double robotY		=	0;
double robot_angle	=	0;