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
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <math.h>
#include <stdlib.h>

using namespace ydlidar;
using namespace std;

#define RAD2DEG(x) ((x)*180./M_PI)
#define ROSVerision "1.4.6"
float	YD_distance[500];
float	YD_angle[500];
float	old_distance[500];
int		fd;
int		serial1;
bool	init1 = true;
float	data_average[500]	=	{0};
int		data_count[500]		=	{0};
int		printCount = 0;
int		lidarReadCount;

bool mappingActive = false;

char scanData[30];

int	systemMode	=	1;	// 0 = default, 1 = control robot mode

const int	printSize								=	150;//185
//SSH print size 170 for laptop 100 for tablet

int			pinMap[printSize][printSize]			=	{0};	//SSH print map
int			printScale								=	1;		//scale
float		unitScale								=	10;		//1-unit cm
const int	allMapSize								=	2000;		//maximum 65535
unsigned int	allMap[allMapSize][allMapSize]      =	{0};		//All map wall, sensing, robot
unsigned int	allPointMap[allMapSize][allMapSize] =	{0};		//score, departure point
unsigned int	oldMap[allMapSize][allMapSize]		=	{0};		//short-term map
	
//ROBOT data initial setting
int		robotX = 0, robotY = 0;	//center
double	robotAngle = 0;//initial angle

//cursor
int		cursorX = 0, cursorY = 0;
bool	integration		= true;

void SerialPrint(const char* format);
int	 SerialRead();
void printSSHmonitor(int currentY,int currentX);
void Line(int x0, int y0,int x1, int y1);

char linux_kbhit(void)
{
	int ch;
	struct termios oldt, newt;
	int oldf;
	tcgetattr(STDIN_FILENO, &oldt);//read current setting
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);//CANONICAL and ECHO off
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);//input setting on terminal
	newt.c_cc[VMIN] = 1;//min input char num = 1
	newt.c_cc[VTIME] = 0;//read wait time = 0
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();//read keyboard
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);//reset setting
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	//if(ch != -1)
	//for(int i=0 ;i<10000;i++)
	//	printf("%d\n",ch);
	if(ch == 32)//space key
		return 'M';
	else if(ch == 65)//up arrow
		return 'U';
	else if(ch == 68)//left arrow
		return 'L';
	else if(ch == 67)//right arrow
		return 'R';
	else if(ch == 66)//down arrow
		return 'D';
	else if(ch == 47)// / key
		return 'S';
	else
		return 'N';
}
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
    
	for(int i = 0; i < lidarReadCount; i++) {
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

int main(int argc, char * argv[]) {
    printf("serial connecting,.....\n");
    //////////////////////////////////////////////////////////////// usb arduino
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
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
	while(SerialRead()!=1){
		SerialPrint("reset");
		usleep(50000);
		count++;
		if(count>100)
		  break;
	}
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
	if(systemMode==1){
		printf("Run mode 1! test.");
	}
	else if(systemMode==2){
		printf("Run mode 2! basic");
	}
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
    if(ignore_array.size()%2){
        ROS_ERROR_STREAM("ignore array is odd need be even");
    }

    for(uint16_t i =0 ; i < ignore_array.size();i++){
        if(ignore_array[i] < -180 && ignore_array[i] > 180){
            ROS_ERROR_STREAM("ignore array should be between 0 and 360");
        }
    }

    CYdLidar laser;
    if(frequency<3){
       frequency = 7.0; 
    }
    if(frequency>15.7){
        frequency = 15.7;
    }
    if(angle_max < angle_min){
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
    if (ret) {
        ret = laser.turnOn();
        if (!ret) {
            ROS_ERROR("Failed to start scan mode!!!");
        }
    } else {
        ROS_ERROR("Error initializing YDLIDAR Comms and Status!!!");
    }
    ros::Rate rate(20);
    
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
	
	printf("....");
    	//test ms
	int count=0;
	char buffer[20];
	sprintf(buffer, "Unit%f",unitScale);
	while(SerialRead()!=1){
		SerialPrint(buffer);
		usleep(50000);
		count++;
		if(count>100)
		break;
	}
	system("clear");
	usleep(50000);
    while (ret&&ros::ok()) {
        bool hardError;
        //and loop here 
    	
		//////////////////////////////////////////////////////////////////////////
		//mapping
		//////////////////////////////////////////////////////////////////////////
		//while(scanChar != EOF){
			
		while(true){
			LaserScan scan;
			if(laser.doProcessSimple(scan, hardError )){
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
				
				for(int i=0; i < scan.points.size(); i++) {
					int index = std::ceil((scan.points[i].angle - scan.config.min_angle)/scan.config.angle_increment);
					if(index >=0 && index < size) {
						scan_msg.ranges[index] = scan.points[i].range;
						scan_msg.intensities[index] = scan.points[i].intensity;
					}
				}
				scan_pub.publish(scan_msg);
			}
			/************************************************************************/
			/* Writing sensing, wall                                                */
			/************************************************************************/
			for(int i=0;i<500;i++){
				float difference = fabs(old_distance[i] - YD_distance[i]);
				int Xvalue = round(cos((YD_angle[i]+90+robotAngle)*M_PI/180.0)*YD_distance[i]*100.0/unitScale);
				int Yvalue = round(-sin((YD_angle[i]+90+robotAngle)*M_PI/180.0)*YD_distance[i]*100.0/unitScale);
				if(allMap[allMapSize/2-robotY+Yvalue][allMapSize/2+robotX+Xvalue] == 0)
					allMap[allMapSize/2-robotY+Yvalue][allMapSize/2+robotX+Xvalue] = 1; //sense
				if( (difference < 0.02) &&	(difference != 0) && (YD_distance[i] > 0.2) && (YD_distance[i] < 4))//[M]
					data_count[i]++;
				else
					data_count[i] = 0;
				if(data_count[i] > 12 && mappingActive == true){//wall sensitivity
					if((allMapSize/2-robotY+Yvalue)>0&&(allMapSize/2+robotY+Yvalue)<allMapSize)
						if((allMapSize/2+robotX+Xvalue)>0&&(allMapSize/2+robotX+Xvalue)<allMapSize){
							allMap[allMapSize/2-robotY+Yvalue][allMapSize/2+robotX+Xvalue] = 2; //hold
							Line(allMapSize/2-robotY,allMapSize/2+robotX,allMapSize/2-robotY+Yvalue,allMapSize/2+robotX+Xvalue);
						}
					data_count[i] = 0;
				} 
			}
			/************************************************************************/
			/* system  0                                                            */
			/************************************************************************/
			if(systemMode == 0){//default(point map)
				//reset point map
				for(int i=0;i<allMapSize;i++)
				for(int j=0;j<allMapSize;j++){
					allPointMap[i][j] = 0;
					if (allMap[i][j] == 3) //departure
					allMap[i][j] = 0;
				}
				//add point
				int pointRange = 50;
				unsigned int pointMax=0,pointX=0,pointY=0;
				for(int i=0;i<allMapSize;i++)
				for(int j=0;j<allMapSize;j++)
				if(allMap[i][j]==2){ //find wall place
					for(int k=-pointRange;k<pointRange;k++)
					for(int p=-pointRange;p<pointRange;p++)
					if(k+i>0&&p+j>0&&k+i<allMapSize&&p+j<allMapSize)
					allPointMap[k+i][p+j]++;
				}
				else if(allMap[i][j]==4) //find empty place
				allPointMap[i][j]+=5;
				//find score and record
				for(int i=0;i<allMapSize;i++)
				for(int j=0;j<allMapSize;j++)
				if(allPointMap[i][j] > pointMax){
					pointMax = allPointMap[i][j];
					pointY=i;
					pointX=j;
				}
				printf("\033[%d;%dH",1,1);//set cursor 0,0
				printf("pointMax:%d / X:%d / Y:%d ", pointMax, pointX, pointY);
				allMap[pointY][pointX] = 3; //add departure
			}
			/////////////////////////////////////////////////////////////////////////
			else if(systemMode == 1){// 
				SerialPrint("Pos");
				usleep(1000);
				SerialRead();
			}
			
			/************************************************************************/
			/* print monitor                                                        */
			/************************************************************************/
			printf("\033[%d;%dH",1,3);//set cursor 0,2
			//SSH print
			printSSHmonitor(cursorY,cursorX);
			printf("count:%d  /  1-unit : %f cm  / print scale : %d \033[92m []Robot \033[33m Sensing \033[31m Wall\n\033[0m",count,unitScale,printScale);
			printf("\t\t[[ ROS-SLAM SSH monitor ]]\n");
			//return sensing text to empty text 
			for(int i= -printSize/2-5;i<printSize/2+5;i++)
				for(int j= -printSize/2-5;j<printSize/2+5;j++){
				  int a = allMap[i*printScale+allMapSize/2-robotY][j*printScale+allMapSize/2+robotX];
					if(a == 1 || a == 5) //sensing point or robot center
						allMap[i*printScale+allMapSize/2-robotY][j*printScale+allMapSize/2+robotX] = 0;
				}
			count++;
			for(int i=0;i<500;i++)
				old_distance[i] = YD_distance[i];
			usleep(1000);
			rate.sleep();
			ros::spinOnce();
			/************************************************************************/
			/* end system                                                           */
			/************************************************************************/
			if(systemMode == 2){// Tracking map point
				for(int i=0;i<allMapSize;i++){//save short term storage
					for(int j=0;j<allMapSize;j++){
						oldMap[i][j]=allMap[i][j];
					}
				}
			}
			/************************************************************************/
			/* Command Line                                                         */
			/************************************************************************/
			char kb = linux_kbhit();
			if(kb=='M'){
				printf("\033[45m\033[36m");
				for(int i=0;i<printSize/2-1;i++)
					printf("--");
				printf("PAUSE");
				for(int i=0;i<printSize/2-1;i++)
					printf("--");
				printf("-\n");
				printf("\033[40m\033[97m");
				printf("\nCommand Please...\n input:");
				scanf(" %s",scanData);
				if(strcmp(scanData,"stop")==0){//all stop
					printf("\033[45m\033[36m");
					printf("STOP....\n");
					printf("\033[40m\033[97m");
					break;
				}
				else if(strcmp(scanData,"goto")==0){//goto robot command
					printf("input the X Y :");			
					int moveX=0, moveY=0;				
					scanf("%d %d", &moveX, &moveY);		
					robotX += moveX;				    
					robotY += moveY;				    
					printf("go to robot X:%d / Y:%d\n", robotX, robotY);
					char buffer[20];
					sprintf(buffer, "%d %d\n", moveX, moveY);
					printf("ARDUINO SENDING : %s\n", buffer);
					SerialPrint(buffer);
					printf("Serial waiting\n");
					//while(SerialRead()==0)
					usleep(100000);
					printf("read!\n");
					usleep(100000);
				}
				else if(strcmp(scanData,"test")==0){//
					int count=0;
					while(SerialRead()!=1){
						SerialPrint("test");
						usleep(50000);
						count++;
						if(count>100)
						break;
					}
					system("clear");
					usleep(50000);
				}
				else if(strcmp(scanData,"reset")==0){//
					for(int i=0;i<allMapSize;i++)
						for(int j=0;j<allMapSize;j++)
							allMap[i][j] = 0;
					int count=0;
					while(SerialRead()!=1){
						SerialPrint("reset");
						usleep(50000);
						count++;
						if(count>100)
						break;
					}
					system("clear");
					usleep(50000);
				}
		//		else if(strcmp(scanData,"test")==0){
		//			int count=0;
		//			while(SerialRead()!=1){
		//				SerialPrint("test");
		//				usleep(50000);
		//				count++;
		//				if(count>100)
		//				break;
		//			}
		//			system("clear");
		//			usleep(50000);
		//		}
				else if(strcmp(scanData,"mapping")==0){
					mappingActive = !mappingActive;
				}
				else if(strcmp(scanData,"cursor")==0){
					integration = !integration;
				}
				else if(strcmp(scanData,"filter")==0){
					printf("Filtering.............................\n");
					int filterPoint=0;
					for(int m=0;m<10;m++)	//10 times
						for(int i=1;i<allMapSize;i++)
							for(int j=1;j<allMapSize;j++)
								if(allMap[i][j]==0){
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
				else if(strcmp(scanData,"save")==0){
					ofstream savefile;
					savefile.open("map.c");
					for(int k = 0; k< allMapSize ; k++){
						for(int j=0;j<allMapSize;j++){
							savefile << (char)allMap[k][j];
						}
						savefile << endl; 
					}
					savefile.close();
				}
				else if(strcmp(scanData,"load")==0){
					ifstream loadfile("map.c");
					string ch;
					printf("\033[%d;%dH",1,1);//set cursor 0,0
					if(loadfile.good()){
						for(int i=0;i<allMapSize;i++){
							getline(loadfile,ch);
							for(int j=0;j<allMapSize;j++){
								allMap[i][j] = (int)ch[j];
							}
						}
					}
					loadfile.close();  
					printf("loading......");
				}
				else if(strcmp(scanData,"mode")==0){
					printf("Setting mode!");
					scanf("%d", &systemMode);
				}
				else if(strcmp(scanData,"scale")==0){
					char buffer[20];
					printf("input(cm):");
					scanf("%f",&unitScale);
					sprintf(buffer, "Unit%f",unitScale);
					SerialPrint(buffer);
					system("clear");
					usleep(50000);
				}
				else{
					printf("nothing...");
				}
				system("clear");
				usleep(50000);
			}
			else if(kb == 'U'){
				if(integration){
					int count=0;
					while(SerialRead()!=1){
						SerialPrint("front");
						usleep(50000);
						count++;
						if(count>100)
						break;
					}
					system("clear");
					usleep(50000);
				}
				else{
					cursorY+=3;
				}
			}
			else if(kb == 'L'){
				if(integration){
					int count=0;
					while(SerialRead()!=1){
						SerialPrint("left");
						usleep(50000);
						count++;
						if(count>100)
						break;
					}
					system("clear");
					usleep(50000);
				}
				else{
					cursorX-=3;
				}
			}
			else if(kb == 'R'){
				if(integration){
					int count=0;
					while(SerialRead()!=1){
						SerialPrint("right");
						usleep(50000);
						count++;
						if(count>100)
						break;
					}
					system("clear");
					usleep(50000);
				}
				else{
					cursorX+=3;
				}
			}
			else if(kb == 'D'){
				if(integration){
					int count=0;
					while(SerialRead()!=1){
						SerialPrint("back");
						usleep(50000);
						count++;
						if(count>100)
						break;
					}
					system("clear");
					usleep(50000);
				}
				else{
					cursorY-=3;
				}
			}
			else if(kb == 'S'){
				int count=0;
				while(SerialRead()!=1){
					SerialPrint("stop");
					usleep(50000);
					count++;
					if(count>100)
					break;
				}
				system("clear");
				usleep(50000);
			}
		}
		
		break;
    }
	SerialPrint("stop");
	close(fd);
    laser.turnOff();
    ROS_INFO("[YDLIDAR INFO] Now YDLIDAR is stopping .......");
    laser.disconnecting();
    return 0;
}

void SerialPrint(const char* format)
{
	serial1 = write(fd,format,int(strlen(format)));
	//printf("\n %s %d\n",format,int(strlen(format)));
	//serial1 = write(fd,"front",5);
	if(serial1 < 0)
		perror("write failed - ");
}
int SerialRead()
{
	char buf[256] ="";
	serial1 = read(fd, (void*)buf, 255);
	if (serial1 < 0) {
		printf("\033[%d;%dH",printSize+10,3);
		printf("Read failed - ");
	}
	else if (serial1 == 0){
		printf("\033[%d;%dH",printSize+10,3);
		printf("No data on port\n");
		for(int i=0;i<10;i++)
		printf("                                                                                                    \n");
	}
	else{
		buf[serial1] = '\0';
		//for(int i=0;i<=25;i++)
		//	printf("[%c]",buf[i]);
		printf("\033[%d;%dH",printSize+10,3);
		printf("%i bytes read :\n   [ %s ]   ", serial1, buf);
	}
	if(strcmp(buf,"OK")==0){
		return 1;
	}
	else{
		if(buf[0]=='P' && buf[1]=='o' && buf[2]=='s'){
			sscanf(buf,"Pos/%d/%d/%lf/",&robotX,&robotY,&robotAngle);
			if(integration == true){
				cursorX = robotX;
				cursorY = robotY;
			}
			printf("reading....");
			usleep(10000);
		}
		return 0;
	}
}
void printSSHmonitor(int currentY,int currentX){
	for(int i = 0 ; i<printSize;i++)
		for(int j = 0; j<printSize;j++)
			pinMap[i][j] = allMap[(allMapSize/2+i-printSize/2)-currentY][(allMapSize/2+j-printSize/2)+currentX];
	pinMap[printSize/2][printSize/2] = 5;
	printf("\n ");
	printf("\033[97m");//white
	for(int i=0;i<printSize/2-1;i++)
	printf("--");
	printf("FRONT");
	for(int i=0;i<printSize/2-1;i++)
	printf("--");
	printf("-\n");
	int prePixel = 0;
	for(int i=0;i<printSize;i++){
		//printf("\033[40m\033[97m");//black BG & white
		printf(" |");
		prePixel = 0;
		for(int j=0;j<printSize;j++){
			if(pinMap[i][j] == 1){        //sensing
				if(prePixel != 1)
					printf("\033[43m\033[33m");//orange
				printf("  ");
				//printf("\033[40m\033[97m");//black BG & white
				prePixel = 1;
			}
			else if(pinMap[i][j] == 2){   //hold , wall
				if(prePixel != 2)
					printf("\033[41m");//red BG
				printf("  ");
				//printf("\033[40m\033[97m"); //black BG & white
				prePixel = 2;
			}
			else if(pinMap[i][j] == 3){   //departure
				if(prePixel != 3)
					printf("\033[44m");//blue BG
				printf("  ");
				//printf("\033[40m\033[97m");//black BG & white
				prePixel = 3;
			}
			else if(pinMap[i][j] == 4){   //empty space
				if(prePixel != 4)
					printf("\033[47m");//blue BG
				printf("  ");
				//printf("\033[40m\033[97m");//black BG & white
				prePixel = 4;
			}
			else if(pinMap[i][j] == 5){   //center
				if(prePixel != 5)
					printf("\033[45m\033[36m");//magenta BG & cyan
				printf("<>");
				//printf("\033[40m\033[97m");//black BG & white
				prePixel = 5;
			}
			else{//nothing
				if(prePixel != 0)
					printf("\033[40m\033[97m");//black BG & white
				printf("  ");
				prePixel = 0;
			}
		}
		printf("\033[40m\033[97m");//black BG & white
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
void Line(int x0, int y0,int x1, int y1) {
	int steep = abs(y1 - y0) > abs(x1 - x0);
	int t;
	if (steep) {
		t=x0;x0=y0;y0=t;
		t=x1;x1=y1;y1=t;
	}

	if (x0 > x1) {
		t=x0;x0=x1;x1=t;
		t=y0;y0=y1;y1=t;
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
		} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			if(allMap[y0][x0]!=2)
				allMap[y0][x0]=4;
			} else {
			if(allMap[x0][y0]!=2)
				allMap[x0][y0]=4;
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}
