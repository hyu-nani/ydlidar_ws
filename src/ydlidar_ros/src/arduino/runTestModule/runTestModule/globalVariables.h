
// encoder position R, L
float encoderPosLeft, encoderPosRight;
double oldPosL, oldPosR;
double oldAngle;

//time
long	nowTime		=	millis(); 
long	preTime		=	nowTime;

//Serial
char	SerialData[256] =	"";
int		unitScale		=	5;//cm

//wheel
bool	calActive	=	false;
float	speedLeft	=	108;
float	SpeedRight	=	120;
float	errorGap	=	0;//¾ç¼ö¸é ¿ÞÂÊÀÌ »¡¶óÁü

//robot
double robotX		=	0;
double robotY		=	0;
double robot_angle	=	0;