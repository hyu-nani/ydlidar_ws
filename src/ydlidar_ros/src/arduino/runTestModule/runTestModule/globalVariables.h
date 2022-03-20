
// encoder position R, L
float encoderPosLeft, encoderPosRight;
double oldPosL, oldPosR;

//time
long	nowTime	=	millis(); 
long	preTime	=	nowTime;

//Serial
char	SerialData[256] = "";

int		unitScale	=	5;//cm

//wheel
int speedLeft	=	116;
int SpeedRight	=	120;

//robot
double robotX		=	0;
double robotY		=	0;
double robot_angle	=	0;