
// encoder position R, L
float encoderPosLeft, encoderPosRight;
double oldPosL, oldPosR;
double oldPosL1, oldPosR1;
double fixAngle;

//time
long	nowTime		=	millis(); 
long	preTime		=	nowTime;

//Serial
char	SerialData[256] =	"";
float	unitScale		=	20;//cm

//mode
int		direction		=	0; //0:stop, 1:front, 2:left, 3:right, 4:back

//wheel
const int	speedLeft		= 60;	//108
const int	speedRight		= 65;	//120
int			lefePWMoutput	= 0;
int			rightPWMoutput	= 0;
float		errorGap		= 0;	//speed gap each wheel
int			in1=0,in2=0,in3=0,in4=0;

//robot
double robotX		=	0;
double robotY		=	0;
double robot_angle	=	0;
double robot_distance =	0;