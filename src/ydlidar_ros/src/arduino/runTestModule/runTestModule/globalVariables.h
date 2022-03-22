
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
boolean	calActive	=	false;
float	speedLeft	=	108;
float	speedRight	=	120;
float	errorGap	=	0;//¾ç¼ö¸é ¿ÞÂÊÀÌ »¡¶óÁü
int		in1=0,in2=0,in3=0,in4=0;

//robot
double robotX		=	0;
double robotY		=	0;
double robot_angle	=	0;