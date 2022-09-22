/*
 *  YDLIDAR SYSTEM
 *  YDLIDAR ROS Node Client 
 *
 *  Copyright 2015 - 2018 EAI TEAM
 *  http://www.ydlidar.com
 * 
 */

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "CYdLidar.h"
#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>
#include <csignal>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

using namespace ydlidar;
using namespace std;

#define RAD2DEG(x) ((x)*180./M_PI)
#define ROSVerision "1.4.6"
float	YD_distance[500]; // ���̴� �Ÿ� 
float	YD_angle[500]; // ���̴� ����
float	old_distance[500]; // ���� ���̴� �Ÿ�
int		fd;
int		serial1;
bool	init1 = true;
float	data_average[500]	=	{0}; // ���̴� ���� ���ġ ���� ����
int		data_count[500]		=	{0}; // ���̴� ���� ���� �Է� ����ġ
int		printCount = 0; // SSH ����Ʈ�� Ƚ��
int		lidarReadCount; 
int 	ignoreTime = 0;	// ���� ��ȯ �� �������� ���� ���̴��� ������ ���ֱ� ���� �Է¹��� Ƚ��
float	gapAngle = 0.0; // ȸ���� �������� ���� ����

char	scanData[30];

float	val	=	0;

int		systemMode	=	1;	// 0 = default, 1 = control robot mode

const int	printSize								=	150;		//4K - 185
//SSH print size 170 for laptop 100 for tablet

int			pinMap[printSize][printSize]			=	{0};		//SSH print map
float		unitScale								=	5;			//1-unit cm
const int	allMapSize								=	2000;		//maximum 65535
unsigned int	allMap[allMapSize][allMapSize]      =	{0};		//All map wall, sensing, robot
unsigned int	allPointMap[allMapSize][allMapSize] =	{0};		//score, arrival point
unsigned int	oldMap[allMapSize][allMapSize]		=	{0};		//short-term map
	
//ROBOT data initial setting
int		robotX = 0, robotY = 0;	//center
double	robotAngle = 0;//initial angle

//delay
void	delay_ms(int time){usleep(time*1000);} 

/** arduino now. true: process , false:done */
bool	OKsign	=	false; 

//arrival point
int		arrivalX = 0, arrivalY = 0;//arrival coordinate

//screen cursor
int		cursorX = 0, cursorY = 0;
bool	integration		= true; //cursor and robot
bool	screenActive	= true;
bool	mappingActive	= false;
//test
float distanceTest = 0;

//include file
#include "pathWayFind.cpp"
#include "KBhit.cpp"

void SerialPrint(const char* format);
bool SerialRead();
void printSSHmonitor(int currentY,int currentX);
void Line(int x0, int y0,int x1, int y1);


std::vector<float> split(const std::string &s, char delim) {
    std::vector<float> elems;
    std::stringstream ss(s);
    std::string number;
    while(std::getline(ss, number, delim)) {
        elems.push_back(atof(number.c_str()));
    }
    return elems;
}
void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int lidarReadCount = scan->scan_time / scan->time_increment;
    //printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), lidarReadCount);
    //printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
    
	for(int i = 0; i < lidarReadCount; i++) 
	{
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
        YD_angle[i] = degree;
        YD_distance[i] = scan->ranges[i];
		//float val = scan->ranges[i];
        //if(val != 0)
        //	YD_distance[i] = val;
		//if(YD_angle[i]> -5 && YD_angle[i]< 5){
        	//printf("angle-distance[%f - %f]%d\n",YD_angle[i],YD_distance[i],i);
   		//}
    }
//    for(int i = 0; i < count; i++) {
//        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
//	if(degree > -5 && degree< 5)
//        printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %d]\n", degree, scan->ranges[i], i);
//    }
}
/*
CSV ���������� �� ���� �ڵ�
*/
void saveMapCSV()
{
	delay_ms(1000);
	ofstream mapFile;
	printf("CSV file save.............\n");
	mapFile.open("map.csv");
	mapFile << "[ ALL MAP ] 0:none 1:sense 2:wall 3:arrive 4:empty 5:center 6:path\n";
	for(int i=0;i<allMapSize;i++)
	{
		for(int j=0;j<allMapSize;j++)
		{
			mapFile << (char)(allMap[i][j]+48);
			if(j!=allMapSize-1)
				mapFile << ",";
		}
		mapFile << "\n";
	}
	mapFile.close();
}

void saveMapBMP()
{
	const int w = allMapSize;
	const int h = allMapSize;
	unsigned int size = w*h; // width * Height
	FILE *f;
	unsigned char *img = NULL;
	int filesize = 54 + 3*size;  //w is your image width, h is image height, both int

	unsigned int red[w][h] = {0};
	unsigned int green[w][h] = {0};
	unsigned int blue[w][h] = {0};
	//convert allMap -> red, green, blue
	for(int i=0; i<w; i++)
	for(int j=0; j<h; j++)
	{
		switch(allMap[j][i])
		{
			case 0: // none : black
				red[i][j]	= 0;
				green[i][j]	= 0;
				blue[i][j]	= 0;
			break;
			case 1: // sense : yellow
				red[i][j]	= 0;
				green[i][j]	= 1;
				blue[i][j]	= 1;
			break;
			case 2: // wall : red
				red[i][j]	= 1;
				green[i][j]	= 0;
				blue[i][j]	= 0;
			break;
			case 3: // arrive point : blue
				red[i][j]	= 0;
				green[i][j]	= 0;
				blue[i][j]	= 1;
			break; 
			case 4: // empty place : white
				red[i][j]	= 1;
				green[i][j]	= 1;
				blue[i][j]	= 1;
			break;
			case 5: // center point : green
				red[i][j]	= 0;
				green[i][j]	= 1;
				blue[i][j]	= 0;
			break;
			case 6: // path way : gray
				red[i][j]	= 0.2;
				green[i][j]	= 0.2;
				blue[i][j]	= 0.2;
			break;
			default:
			break;
		}
	}
	img = (unsigned char *)malloc(3*size);
	memset(img,0,3*size);

	int x, y, r, g, b;
	for(int i=0; i<w; i++)
	for(int j=0; j<h; j++)
	{
		x=i; y=(h-1)-j;
		r = red[i][j]*255;
		g = green[i][j]*255;
		b = blue[i][j]*255;
		if (r > 255) r=255;
		if (g > 255) g=255;
		if (b > 255) b=255;
		img[(x+y*w)*3+2] = (unsigned char)(r);
		img[(x+y*w)*3+1] = (unsigned char)(g);
		img[(x+y*w)*3+0] = (unsigned char)(b);
	}


	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	f = fopen("map.bmp","wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(int i=0; i<h; i++)
	{
		fwrite(img+(w*(h-i-1)*3),3,w,f);
		fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	free(img);
	fclose(f);
}

int main(int argc, char * argv[]) 
{
  printf("serial connecting,.....\n");
    //////////////////////////////////////////////////////////////// usb arduino
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) 
	{
    	printf("doesn't connected arduino");
  		perror("open_port: Unable to open /dev/ttyACM0 - ");
    	return(-1);
	}
	struct termios options;
	tcgetattr(fd, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;         //<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);
	//Turn off blocking for reads, use (fd, F_SETFL, FNDELAY) if you want that
	fcntl(fd, F_SETFL, 0);
    /////////////////////////////////////////////////////////////////
   
    ros::init(argc, argv, "ydlidar_node"); 
    printf("__   ______  _     ___ ____    _    ____  \n");
    printf("\\ \\ / /  _ \\| |   |_ _|  _ \\  / \\  |  _ \\ \n");
    printf(" \\ V /| | | | |    | || | | |/ _ \\ | |_) | \n");
    printf("  | | | |_| | |___ | || |_| / ___ \\|  _ <  \n");
    printf("  |_| |____/|_____|___|____/_/   \\_\\_| \\_\\ \n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	printf("\n");
	printf("                 -/oo    .oo+ \n");
	printf("               `dMMNd    -MMN \n");
	printf("              .+MMm..    -MMN         -:::.     \n");
	printf("             `MMMMMMN    -MMN      :hMMMMMMmo`  \n");
	printf("              `+MMd``    -MMN     oMMh:.`.+NMm. \n");
	printf("               /MMd      -MMN    `MMd      -MMy \n");
	printf("               /MMd      -MMN    `NMm.     +MMo \n");
	printf("               /MMd      -MMN     :mMms//+hNMy` \n");
	printf("               :hhs      .hhy      .+hmmmmdy:        ``` \n");
	printf("                                      `...`          ooo \n");
	printf("                                                     ::: \n");
	printf("               `-------------  .++/   /++:   +++`    ---     `+++-+syy+-   \n");
	printf("               .sssssssssssss  `NMM. `NMMm  /MMm     yyy`    .MMMNhsyNMMs  \n");
	printf("               `-------------   oMMs oMMMM: dMM:     yyy`    .MMN.   .NMM. \n");
	printf("                                `mMN`mMshMh-MMh      yyy`    .MMm     dMM- \n");
	printf("                                 /MMdMM.:MMdMM-      yyy`    .MMm     dMM- \n");
	printf("                                  dMMMy  dMMMs       yyy`    .MMm     dMM- \n");
	printf("                                  .+++.  -+++`       ---     `++/     /++` \n");
	printf("\n");
	printf("                                                             `+++++++++++.\n");
	printf("                                                             `ooooooooooo.\n");
	printf("                                                              ``````````` \n");
	printf("                                                              :::     -::`     `-/oo/-`  \n");
	printf("                                                             `MMN     hMM:    `hNNddMNh` \n");
	printf("                                                             `MMN     hMM:    :MMm-.///. \n");
	printf("                                                             `MMN     hMM:     :ymNmhs:  \n");
	printf("                                                             `MMM.   `dMM:    .--..:hMM+ \n");
	printf("                                                              sMMms+sdMMM:    :NMmoomMM/ \n");
	printf("                                                               -shdhs/oss-     .+yddho.  \n");
    printf("\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    fflush(stdout);
	//print of mode name
	if(systemMode==1)
		printf("Run mode 1! test.");
	else if(systemMode==2)
		printf("Run mode 2! basic");
    std::string port;
    int baudrate=230400;
    std::string frame_id;
    bool reversion, resolution_fixed;
    bool auto_reconnect;
    double angle_max,angle_min;
    result_t op_result;
    std::string list;
    std::vector<float> ignore_array;  
    double max_range, min_range;
    double frequency;
    int samp_rate = 5;
    bool inverted = true;
    bool isSingleChannel = false;
    bool isTOFLidar = false;
	
    ros::NodeHandle nh;
    ros::Publisher scan_pub = nh.advertise<sensor_msgs::LaserScan>("scan", 1000);
    ros::NodeHandle nh_private("~");
    nh_private.param<std::string>("port", port, "/dev/ydlidar"); 
    nh_private.param<int>("baudrate", baudrate, 230400); 
    nh_private.param<std::string>("frame_id", frame_id, "laser_frame");
    nh_private.param<bool>("resolution_fixed", resolution_fixed, "true");
    nh_private.param<bool>("auto_reconnect", auto_reconnect, "true");
    nh_private.param<bool>("reversion", reversion, "true");
    nh_private.param<double>("angle_max", angle_max , 180);
    nh_private.param<double>("angle_min", angle_min , -180);
    nh_private.param<double>("range_max", max_range , 64.0);
    nh_private.param<double>("range_min", min_range , 0.01);
    nh_private.param<double>("frequency", frequency , 10.0);
    nh_private.param<std::string>("ignore_array",list,"");
    nh_private.param<int>("samp_rate", samp_rate, samp_rate);
    nh_private.param<bool>("isSingleChannel", isSingleChannel, isSingleChannel);
    nh_private.param<bool>("isTOFLidar", isTOFLidar, isTOFLidar);

    ignore_array = split(list ,',');
    if(ignore_array.size()%2)
        ROS_ERROR_STREAM("ignore array is odd need be even");
    for(uint16_t i =0 ; i < ignore_array.size();i++)
	{
        if(ignore_array[i] < -180 && ignore_array[i] > 180)
        ROS_ERROR_STREAM("ignore array should be between 0 and 360");
    }

    CYdLidar laser;
    if(frequency<3)
		frequency = 7.0; 
    if(frequency>15.7)
		frequency = 15.7;
    if(angle_max < angle_min)
	{
        double temp = angle_max;
        angle_max = angle_min;
        angle_min = temp;
    }
    ROS_INFO("[YDLIDAR INFO] Now YDLIDAR ROS SDK VERSION:%s .......", ROSVerision);
    laser.setSerialPort(port);
    laser.setSerialBaudrate(baudrate);
    laser.setMaxRange(max_range);
    laser.setMinRange(min_range);
    laser.setMaxAngle(angle_max);
    laser.setMinAngle(angle_min);
    laser.setReversion(reversion);
    laser.setFixedResolution(resolution_fixed);
    laser.setAutoReconnect(auto_reconnect);
    laser.setScanFrequency(frequency);
    laser.setIgnoreArray(ignore_array);
    laser.setSampleRate(samp_rate);
    laser.setInverted(inverted);
    laser.setSingleChannel(isSingleChannel);
    laser.setLidarType(isTOFLidar ? TYPE_TOF : TYPE_TRIANGLE);
    bool ret = laser.initialize();
    if (ret) 
	{
        ret = laser.turnOn();
        if (!ret) 
			ROS_ERROR("Failed to start scan mode!!!");
    } 
	else
	{
        ROS_ERROR("Error initializing YDLIDAR Comms and Status!!!");
    }
    ros::Rate rate(20);
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
	
	printf("unit");
	int count=0;
	OKsign = false;
	char buffer[20] = "";
	sprintf(buffer, "Unit%fD\n",unitScale);
	SerialPrint(buffer);
	while(!OKsign)
	{
		delay_ms(200);
		SerialRead();
	}
	system("clear");

	
	delay_ms(1000);
    while (ret&&ros::ok()) 
	{
        bool hardError;
        //and loop start here 
		OKsign = true;
		/************************************************************************/
		/*    Mapping code                                                      */
		/************************************************************************/
		while(true)
		{
			LaserScan scan;
			if(laser.doProcessSimple(scan, hardError ))
			{
				printf("scanning\n");
				sensor_msgs::LaserScan scan_msg;
				ros::Time start_scan_time;
				start_scan_time.sec = scan.stamp/1000000000ul;
				start_scan_time.nsec = scan.stamp%1000000000ul;
				scan_msg.header.stamp = start_scan_time;
				scan_msg.header.frame_id = frame_id;
				scan_msg.angle_min =(scan.config.min_angle);
				scan_msg.angle_max = (scan.config.max_angle);
				scan_msg.angle_increment = (scan.config.angle_increment);
				scan_msg.scan_time = scan.config.scan_time;
				scan_msg.time_increment = scan.config.time_increment;
				scan_msg.range_min = (scan.config.min_range);
				scan_msg.range_max = (scan.config.max_range);
				int size = (scan.config.max_angle - scan.config.min_angle)/ scan.config.angle_increment + 1;
				scan_msg.ranges.resize(size);
				scan_msg.intensities.resize(size);
				
				for(int i=0; i < scan.points.size(); i++) 
				{
					int index = std::ceil((scan.points[i].angle - scan.config.min_angle)/scan.config.angle_increment);
					if(index >=0 && index < size) 
					{
						scan_msg.ranges[index] = scan.points[i].range;
						scan_msg.intensities[index] = scan.points[i].intensity;
					}
				}
				scan_pub.publish(scan_msg);
			}
			/************************************************************************/
			/* Writing sensing, wall                                                */
			/************************************************************************/
			for(int i=0;i<500;i++)
			{
				float difference = fabs(old_distance[i] - YD_distance[i]);
				int Xvalue = round(cos((YD_angle[i]+90+robotAngle+gapAngle)*M_PI/180.0)*YD_distance[i]*100.0/unitScale);
				int Yvalue = round(-sin((YD_angle[i]+90+robotAngle+gapAngle)*M_PI/180.0)*YD_distance[i]*100.0/unitScale);
				if( (allMapSize/2-printSize/2)<(allMapSize/2+robotX+Xvalue) && 
				    (allMapSize/2+printSize/2)>(allMapSize/2+robotX+Xvalue) && 
				    (allMapSize/2-printSize/2)<(allMapSize/2-robotY+Yvalue) && 
				    (allMapSize/2+printSize/2)>(allMapSize/2-robotY+Yvalue) &&
				    (allMap[allMapSize/2-robotY+Yvalue][allMapSize/2+robotX+Xvalue]) == 0)
					{
						allMap[allMapSize/2-robotY+Yvalue][allMapSize/2+robotX+Xvalue] = 1; //sense
					}
				if( (difference < 0.02) &&	(difference != 0) && (YD_distance[i] > 0.2) && (YD_distance[i] < 4))//[M]
					data_count[i]++;
				else
					data_count[i] = 0;
				if(data_count[i] > 4 && mappingActive == true && ignoreTime == 0)//wall sensitivity
				{
					if((allMapSize/2-robotY+Yvalue)>0&&(allMapSize/2-robotY+Yvalue)<allMapSize)
					if((allMapSize/2+robotX+Xvalue)>0&&(allMapSize/2+robotX+Xvalue)<allMapSize)
					{
						Line(allMapSize/2-robotY, allMapSize/2+robotX, allMapSize/2-robotY+Yvalue, allMapSize/2+robotX+Xvalue);
						allMap[allMapSize/2-robotY+Yvalue][allMapSize/2+robotX+Xvalue] = 2; //hold
					}
					data_count[i] = 0;
				} 
				if(ignoreTime > 0)// ignore lidar value
					ignoreTime--;
			}
			/************************************************************************/
			/*    System Mode						                                */
			/************************************************************************/
			printf("SYSTEM MODE : ");
			switch(systemMode)
			{
				case 0:
				printf("0");
				break;
				case 1:
				printf("1");
				break;
				case 2:
				printf("2");
				break;
				case 3:
				printf("3");
				break;
			}
			printf("\n");
			int filterPoint1=0;
			switch(systemMode)
			{
				case 0:
				/*		System Mode 0 : make point map and finding center point           */
					
				break;
				case 1:
				/*     System Mode 1 : Default mode remote control   (edit)    
				*/
			 	OKsign = false;
				SerialPrint("Pos");//require to position data
				delay_ms(20);
				SerialRead();
				//filtering
				for(int i=allMapSize/2-printSize;i<allMapSize/2+printSize;i++)
				{
					for(int j=allMapSize/2-printSize;j<allMapSize/2+printSize;j++)
					{
						filterPoint1=0;
						if(allMap[i][j] == 0)
						{
							for(int k=0;k<3;k++)
							for(int p=0;p<3;p++)
							if(allMap[i-1+k][j-1+p]==4)
								filterPoint1++;
							if(filterPoint1>5)
								allMap[i][j] = 4;
							filterPoint1 = 0;
							for(int k=0;k<3;k++)
							for(int p=0;p<3;p++)
							if(allMap[i-1+k][j-1+p]==2)
								filterPoint1++;
							if(filterPoint1>5)
								allMap[i][j] = 2;
							filterPoint1 = 0;
						}
					}
				}
				break;
				case 2:
				/*		System Mode 2 : adjust to error gap used the lidar (edit)           
				
				*/
				if(count == 10)
					distanceTest = YD_distance[2];
				else if(count == 11)
				{// 10cm 
					SerialPrint("10cm");
				}
				else if(count > 12)
				{
					OKsign = true;
					SerialPrint("Pos");
					if(YD_distance[2] > distanceTest)
					{
						
					}
					else
					{
						
					}
				}
				break;
				case 3:
				/*		System Mode 3 : setting arrival and move (edit)                  
				
				*/
				if(OKsign)
				{
					printf("initMap\n");
					initMap();//convert allMap to mazeMap
					if(!findWay(allMapSize/2+robotX, allMapSize/2-robotY, arrivalX, arrivalY))
					{
						printf("i can't Find way!!!!!!!!!!!!!!!!\n");
						SerialPrint("stop");
						delay_ms(2000);
					}
					else//success
					{
						if(goNextPosition(allMapSize/2+robotX, allMapSize/2-robotY, arrivalX, arrivalY))
						{
							OKsign = false;
							char buffer[20] = "";
							sprintf(buffer, "go/%d/%dE", moveX, moveY);
							printf("send> %s",buffer);
							printf("\n");
							SerialPrint(buffer);
							//delay_ms(5000);
							//reset val
							moveX = 0;
							moveY = 0;
						}
						else
						{
							SerialPrint("stop");
							delay_ms(1000);
						}
					}
				}
				else
				{
					SerialPrint("Pos");//require to position data
					delay_ms(50);
				}
				if(arrivalX==robotX && arrivalY==robotY)
				{	
					systemMode = 1;
					break;
				}
				SerialRead();
				delay_ms(50);
				break;
				default:
				break;
			}
			/************************************************************************/
			/* Printing SSH Monitor                                                 */
			/************************************************************************/
			printf("\033[%d;%dH",1,3);//set cursor 0,2
			//SSH print
			if(screenActive)
			{
				allMap[allMapSize/2-robotY][allMapSize/2+robotX] = 5;//robot
				printSSHmonitor(cursorY,cursorX);
				printf("count:%d  /  1-unit : %f cm \033[92m []Robot \033[33m Sensing \033[31m Wall\n\033[0m",count,unitScale);
				printf("\t\t[[ ROS-SLAM SSH monitor ]]\n");
				//return sensing text to empty text 
				for(int i= -printSize/2-10;i<printSize/2+10;i++)
				for(int j= -printSize/2-10;j<printSize/2+10;j++)
				{
					int a = allMap[i+allMapSize/2-robotY][j+allMapSize/2+robotX];
					if(a == 1 || a == 5) //sensing point or robot center
						allMap[i+allMapSize/2-robotY][j+allMapSize/2+robotX] = 0;
					//else if(a == 6)
					//s	allMap[i+allMapSize/2-robotY][j+allMapSize/2+robotX] = 4;
				}
				count++;
			}
			for(int i=0;i<500;i++)
			old_distance[i] = YD_distance[i];
			//ydlidar one time loop end code
			delay_ms(1);
			rate.sleep();
			ros::spinOnce();
			/************************************************************************/
			/* end system            SSH 출력 후 실행 부                            */
			/************************************************************************/
			switch(systemMode)
			{
				case 0:
				break;
				case 1:
				break;
				case 2:
				break;
				case 3:
				break;
				default:
				break;
			}
			/************************************************************************/
			/* Command list                                                         */
			/**************************r**********************************************/
			string kb = linux_kbhit();
			if(kb.compare("nothing")!=0)
			{
				//printf("%s", kb);
				delay_ms(10);
			}
			// command word list
			if(kb.compare("Space")==0)
			{
				printf("\033[45m\033[36m");
				for(int i=0; i<printSize/2-1; i++)
				printf("--");
				printf("PAUSE");
				for(int i=0; i<printSize/2-1; i++)
				printf("--");
				printf("-\n");
				printf("\033[40m\033[97m");
				printf("\nCommand Please...\n input:");
				scanf(" %s",scanData);
				// all stop
				if(strcmp(scanData,"stop") == 0)
				{		
					SerialPrint("stop");
					ignoreTime = 10;		//Delay to eliminate Lidar value error due to inertia
					gapAngle = 0.0;			//It's when the robot spins Error value of interference by rotation
					system("clear");
					printf("\033[45m\033[36m");
					printf("STOP....\n");
					printf("\033[40m\033[97m");
					break;
				}
				// Serial print "up"
				else if(strcmp(scanData,"up") == 0)
				{
					SerialPrint("up");
					system("clear");
					delay_ms(10);
				}
				// Serial print "down"
				else if(strcmp(scanData,"down") == 0)
				{
					SerialPrint("down");
					system("clear");
					delay_ms(10);
				}
				// Serial print "10cm"
				else if(strcmp(scanData,"10cm") == 0)
				{
					SerialPrint("10cm");
					system("clear");
					delay_ms(10);
				}
				// Serial print "test"
				else if(strcmp(scanData,"test") == 0)
				{
					SerialPrint("test");
					system("clear");
					delay_ms(10);
				}
				// map filtering - remove empty place 
				else if(strcmp(scanData,"filter") == 0)
				{
					printf("Filtering.............................\n");
					int filterPoint=0;
					for(int m=0;m<10;m++)	//10 times
					for(int i=1;i<allMapSize;i++)
					for(int j=1;j<allMapSize;j++)
					if(allMap[i][j] == 0)
					{
						for(int k=0;k<3;k++)
						for(int p=0;p<3;p++)
						if(allMap[i-1+k][j-1+p]==4)
							filterPoint++;
						if(filterPoint>4)
							allMap[i][j] = 4;
						filterPoint = 0;
						for(int k=0;k<3;k++)
						for(int p=0;p<3;p++)
						if(allMap[i-1+k][j-1+p]==2)
							filterPoint++;
						if(filterPoint>4)
							allMap[i][j] = 2;
						filterPoint = 0;
					}
				}
				// save file
				else if(strcmp(scanData,"save")==0)
				{
					ofstream savefile;
					savefile.open("map.txt");
					for(int k = 0; k< allMapSize ; k++)
					{
						for(int j=0;j<allMapSize;j++)
							savefile << (char)allMap[k][j];
						savefile << endl;
					}
					savefile.close();
				}
				// forcibly mode setting 
				else if(strcmp(scanData,"mode")==0)
				{
					printf("Setting mode!");
					scanf("%d", &systemMode);
				}
				// scale change
				else if(strcmp(scanData,"scale")==0)
				{
					char buffer[20];
					scanf("%f",&unitScale);
					sprintf(buffer, "Unit%f",unitScale);
					SerialPrint(buffer);
					system("clear");
					delay_ms(50);
				}
				else
				{
					printf("nothing...");
				}
				system("clear");
				delay_ms(50);
			/************************************************************************/
			/*   Kbhit keyboard command list										*/
			/************************************************************************/
			}
			else if(kb.compare("Up")==0)
			{
				if(integration && OKsign)
				{
					SerialPrint("front");
					ignoreTime = 20;	//Delay to eliminate Lidar value error due to inertia
					gapAngle = 0.0;		//It's when the robot spins Error value of interference by rotation
					system("clear");
					delay_ms(50);
				}
				else
				{
					cursorY+=int(50/unitScale);	//cursor move
				}
			}
			else if(kb.compare("Left")==0)
			{
				if(integration && OKsign)
				{
					SerialPrint("left");
					ignoreTime = 20;	//Delay to eliminate Lidar value error due to inertia
					gapAngle = 1.0;		//It's when the robot spins Error value of interference by rotation 
					system("clear");
					delay_ms(50);
				}
				else
					cursorX-=int(50/unitScale);	//cursor move
			}
			else if(kb.compare("Right")==0)
			{
				if(integration && OKsign)
				{
					SerialPrint("right");
					ignoreTime = 20;	//Delay to eliminate Lidar value error due to inertia
					gapAngle = -1;		//It's when the robot spins Error value of interference by rotation
					system("clear");
					delay_ms(50);
				}
				else
					cursorX+=int(50/unitScale);	//cursor move
			}
			else if(kb.compare("Down")==0)
			{
				if(integration && OKsign)
				{
					SerialPrint("back");
					ignoreTime = 20;	//Delay to eliminate Lidar value error due to inertia
					gapAngle = 0.0;		//It's when the robot spins Error value of interference by rotation
					system("clear");
					delay_ms(50);
				}
				else
					cursorY-=int(50/unitScale);	//cursor move
			}
			else if(kb.compare("/")==0)
			{
				SerialPrint("stop");
				ignoreTime = 10;		//Delay to eliminate Lidar value error due to inertia
				gapAngle = 0.0;			//It's when the robot spins Error value of interference by rotation
				system("clear");
				delay_ms(50);
			}
			else if(kb.compare("Map")==0)//map calculate active
			{	
				mappingActive = !mappingActive;
				delay_ms(50);
			}
			else if(kb.compare("Move")==0)
			{
				integration = false;
				bool decide = false;
				while(decide==false)
				{
					kb = linux_kbhit();
					delay_ms(10);//protect process
					if(kb.compare("Up")==0)//up arrow
						cursorY+=int(30/unitScale);	//cursor move
					else if(kb.compare("Down")==0)//down arrow
						cursorY-=int(30/unitScale);	//cursor move
					else if(kb.compare("Right")==0)//right arrow
						cursorX+=int(30/unitScale);	//cursor move
					else if(kb.compare("Left")==0)//left arrow
						cursorX-=int(30/unitScale);	//cursor move
					else if(kb.compare("/")==0)//stop '/' key
						decide = true;
					allMap[allMapSize/2-robotY][allMapSize/2+robotX] = 5;//robot
					printf("################### move point and press '/' ###################\n");
					printf("\033[%d;%dH",1,3);//set cursor 0,2
					printSSHmonitor(cursorY,cursorX);
					printf("count:%d  /  1-unit : %f cm \033[92m []Robot \033[33m Sensing \033[31m Wall\n\033[0m",count,unitScale);
					printf("\t\t[[ ROS-SLAM SSH monitor ]]\n");
				}
				allMap[allMapSize/2-cursorY][allMapSize/2+cursorX] = 3;//setup arrival point
				arrivalX = allMapSize/2+cursorX;
				arrivalY = allMapSize/2-cursorY;
				integration = true; //integrate cursor and robot pos
				//while(!OKsign){delay_ms(100);}
				cursorX = robotX;
				cursorY = robotY;
				system("clear");
				systemMode = 3; //move to arrival find way mode
				delay_ms(50);
			}
			else if(kb.compare("S")==0 || kb.compare("s")==0)//Save
			{
				printf("TXT file save..............\n");
				ofstream savefile;
				savefile.open("map.txt");
				for(int k = 0; k< allMapSize ; k++)
				{
					for(int j=0;j<allMapSize;j++)
						savefile << (char)allMap[k][j];
					savefile << endl;
				}
				savefile.close();
				saveMapCSV(); // save file map.csv
				saveMapBMP(); // save file map.bmp
				system("clear");
			}
			else if(kb.compare("R")==0 || kb.compare("r")==0)//reset
			{
				for(int i=0;i<allMapSize;i++)
				for(int j=0;j<allMapSize;j++)
					allMap[i][j] = 0;
				OKsign = true;
				SerialPrint("reset");
				systemMode = 1; 
				system("clear");
				delay_ms(50);
			}
			else if(kb.compare("c")==0 || kb.compare("C")==0)//stop
			{
				SerialPrint("stop");
				ignoreTime = 10;		//Delay to eliminate Lidar value error due to inertia
				gapAngle = 0.0;			//It's when the robot spins Error value of interference by rotation
				system("clear");
				printf("\033[45m\033[36m");
				printf("STOP....\n");
				printf("\033[40m\033[97m");
				break;
			}
			else if(kb.compare("f")==0 || kb.compare("F")==0)//filter one cycle
			{
				int filterPoint=0;
				for(int i=allMapSize/2-printSize;i<allMapSize/2+printSize;i++)
				for(int j=allMapSize/2-printSize;j<allMapSize/2+printSize;j++)
				if(allMap[i][j] == 0)
				{
					for(int k=0;k<3;k++)
					for(int p=0;p<3;p++)
					if(allMap[i-1+k][j-1+p]==4)
						filterPoint++;
					if(filterPoint>4)
						allMap[i][j] = 4;
					filterPoint = 0;
					for(int k=0;k<3;k++)
					for(int p=0;p<3;p++)
					if(allMap[i-1+k][j-1+p]==2)
						filterPoint++;
					if(filterPoint>4)
						allMap[i][j] = 2;
					filterPoint = 0;
				}
			}
		}
		break;
    }
	OKsign = true;
	SerialPrint("stop");
	close(fd);
    laser.turnOff();
    ROS_INFO("[YDLIDAR INFO] Now YDLIDAR is stopping .......");
    laser.disconnecting();
    return 0;
}

/**
 * brief : transport serial data
 * note  :
 * param : string data
 * return:
 */
void SerialPrint(const char* format)
{
	if(OKsign)
	{
		serial1 = write(fd,format,int(strlen(format)));
		if(serial1 < 0)
			perror("write failed - ");
		else
			OKsign = false;
		
	}
	
}

/**
 * brief : 	read Serial code
 * note  : 	OK : change OKsign
 * 			Pos : read position and angle
 * param : 
 * return:
 */
bool SerialRead()
{
	char buf[256] = "";
	serial1 = read(fd, (void*)buf, 255);
	if (serial1 < 0) 
	{
		printf("\033[%d;%dH",printSize+10,3);
		printf("Read failed - ");
	}
	else if (serial1 == 0)
	{
		printf("\033[%d;%dH",printSize+10,3);
		printf("No data on port\n");
		for(int i=0;i<10;i++)
			printf("                                                                                        \n");
	}
	else
	{
		buf[serial1] = '\0';//remove the endline
		printf("\033[%d;%dH",printSize+10,3);
		printf("%d bytes read :\n   [ %s ]   ", serial1, buf);
	}
	if(strcmp(buf,"OK")==0)//success transform message
	{
		//printf("ddddddddddddddddddddddddddddddddd");
		delay_ms(1);
		OKsign = true;
		return true;
	}
	if( buf[0]=='P' && buf[1]=='o' && buf[2]=='s' )
	{
		sscanf(buf,"Pos/%d/%d/%lf/%fE",&robotX,&robotY,&robotAngle,&val);
		if(integration == true)
		{
			cursorX = robotX;
			cursorY = robotY;
		}
		printf("reading....");
		OKsign = true;
		delay_ms(1);
		return true;
	}
	return false;
}

/**
 * brief : SSH 모니터 출력 코드
 * note  :
 * param : 현재 X, Y 좌표
 * return:
 */
void printSSHmonitor(int currentY,int currentX)
{
	for(int i = 0 ; i<printSize;i++)
	for(int j = 0; j<printSize;j++)
		pinMap[i][j] = allMap[(allMapSize/2+i-printSize/2)-currentY][(allMapSize/2+j-printSize/2)+currentX];
	if(pinMap[printSize/2][printSize/2] != 3)
		pinMap[ printSize/2 ][ printSize/2 ] = 5;//setup of print center
	printf("\n ");
	printf("\033[97m");//white
	for(int i=0;i<printSize/2-1;i++)
		printf("--");
	printf("FRONT");
	for(int i=0;i<printSize/2-1;i++)
		printf("--");
	printf("-\n");
	int prePixel = 0;
	for(int i=0;i<printSize;i++)
	{
		printf(" |");
		prePixel = 0;
		for(int j=0;j<printSize;j++)
		{
			switch(pinMap[i][j])
			{
				case 1://sensing
				if(prePixel != 1)
					printf("\033[43m\033[33m");//orange background color
				printf("  ");
				prePixel = 1;
				break;
				case 2://wall
				if(prePixel != 2)
					printf("\033[41m");		//red background color
				printf("  ");
				prePixel = 2;
				break;
				case 3://arrival point
				if(prePixel != 3)
					printf("\033[44m");		//blue background color
				printf("  ");
				prePixel = 3;
				break;
				case 4://empty
				if(prePixel != 4)
					printf("\033[47m");		//white background color
				printf("  ");
				prePixel = 4;
				break;
				case 5://center
				if(prePixel != 5)
					printf("\033[45m\033[36m");	//magenta BG & cyan
				printf("<>");
				prePixel = 5;
				break;
				case 6://path
				if(prePixel != 6)
					printf("\033[45m\033[37m");
				printf("  ");
				prePixel = 6;
				break;
				default:
				if(prePixel != 0)
					printf("\033[40m\033[97m");	//black BG & white
				printf("  ");
				prePixel = 0;
				break;
			}
		}
		printf("\033[40m\033[97m");	//black BG & white
		printf("|\n");
	}
	printf(" ");
	for(int i=0;i<printSize/2;i++)
		printf("--");
	printf("BACK");
	for(int i=0;i<printSize/2-1;i++)
		printf("--");
	printf("\n");
	printf("\033[0m");//white
}

/**
 * brief : Drawing line in the map
 * note  :
 * param : start X, Y end X, Y
 * return:
 */
void Line(int x0, int y0,int x1, int y1) //printing line
{ 
	int steep = abs(y1 - y0) > abs(x1 - x0);
	int t;
	if(steep)
	{
		t=x0;
		x0=y0;
		y0=t;
		t=x1;
		x1=y1;
		y1=t;
	}
	if(x0 > x1) 
	{
		t=x0;
		x0=x1;
		x1=t;
		t=y0;
		y0=y1;
		y1=t;
	}
	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);
	int16_t err = dx / 2;
	int16_t ystep;
	if(y0 < y1)
		ystep = 1;
	else
		ystep = -1;
	for (; x0<=x1; x0++) 
	{
		if (steep) 
		{
			if(allMap[y0][x0]!=2 && allMap[y0][x0]!=6)
				allMap[y0][x0]=4;
		} 
		else 
		{
			if(allMap[x0][y0]!=2 && allMap[x0][y0]!=6)
				allMap[x0][y0]=4;
		}
		err -= dy;
		if (err < 0) 
		{
			y0 += ystep;
			err += dx;
		}
	}
}
