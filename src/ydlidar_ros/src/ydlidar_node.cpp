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
//#include <iostream>
using namespace ydlidar;

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

char scanData[30];

const int	printSize						  =	170;
//SSH print size 170 for laptop 100 for tablet
int			pinMap[printSize][printSize]	=	{0};//SSH print map
int			printScale						  =	1;	//scale
float		unitScale						    =	5.0;//1-unit cm
const int	allMapSize						=	2000;
unsigned int	allMap[allMapSize][allMapSize]      = {0};			//All map wall, sensing, robot
unsigned int	allPointMap[allMapSize][allMapSize] = {0};		//score, departure point
	
//ROBOT data initial setting
int		robotX = 0, robotY = 0;	//center
float	robotAngle = 90;

void SerialPrint(char* strBuffer);
void SerialRead();
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
    /////////////////////////////////////////////////////////////////
   
    ros::init(argc, argv, "ydlidar_node"); 
    printf("__   ______  _     ___ ____    _    ____  \n");
    printf("\\ \\ / /  _ \\| |   |_ _|  _ \\  / \\  |  _ \\ \n");
    printf(" \\ V /| | | | |    | || | | |/ _ \\ | |_) | \n");
    printf("  | | | |_| | |___ | || |_| / ___ \\|  _ <  \n");
    printf("  |_| |____/|_____|___|____/_/   \\_\\_| \\_\\ \n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	printf("\n");
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
	printf("\n");
	printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    fflush(stdout);
  
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
	int count = 0;
	system("clear");
    while (ret&&ros::ok()) {
        bool hardError;
        //and loop here 
    	
		//////////////////////////////////////////////////////////////////////////
		//mapping
		//////////////////////////////////////////////////////////////////////////
		//while(scanChar != EOF){
			
		while(1){
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
			for(int i=0;i<500;i++){
				float difference = fabs(old_distance[i] - YD_distance[i]);
				int Xvalue = round(cos((YD_angle[i]+robotAngle)*M_PI/180.0)*YD_distance[i]*100.0/unitScale);
				int Yvalue = round(-sin((YD_angle[i]+robotAngle)*M_PI/180.0)*YD_distance[i]*100.0/unitScale);
				if(allMap[allMapSize/2+robotY+Yvalue][allMapSize/2+robotX+Xvalue] < 2)
					allMap[allMapSize/2+robotY+Yvalue][allMapSize/2+robotX+Xvalue] = 1; //sense
				if( (difference < 0.015) &&	(difference != 0) && (YD_distance[i] > 0.15) && (YD_distance[i] < 8))
					data_count[i]++;
				else
					data_count[i] = 0;
				if(data_count[i] > 2){//wall sensitivity
					allMap[allMapSize/2+robotY+Yvalue][allMapSize/2+robotX+Xvalue] = 2; //hold
					data_count[i] = 0;
				}
			}
			
			//reset point map
			for(int i=0;i<allMapSize;i++)
				for(int j=0;j<allMapSize;j++){
					allPointMap[i][j] = 0;
					if (allMap[i][j] == 3) //departure 
						allMap[i][j] = 0;
				}
		
			int pointRange = 50;
			unsigned int pointMax=0,pointX=0,pointY=0;
			for(int i=0;i<allMapSize;i++)
				for(int j=0;j<allMapSize;j++)
					if(allMap[i][j]==2){ //find wall place
					  //add point at the around the wall place
						for(int k=-pointRange;k<pointRange;k++)
							for(int p=-pointRange;p<pointRange;p++)
								allPointMap[k+i][p+j]++;
						//print empty space
						Line(allMapSize/2,allMapSize/2,i,j);
					}
				
			//find score and record
			for(int i=0;i<allMapSize;i++)
				for(int j=0;j<allMapSize;j++)
					if(allPointMap[i][j] > pointMax){
						pointMax = allPointMap[i][j];
						pointY=i;
						pointX=j;
					}
			/////////////////////////////////////////////
			//print monitor
			/////////////////////////////////////////////
			printf("\033[%d;%dH",1,1);//set cursor 0,0
			printf("pointMax:%d / X:%d / Y:%d ",pointMax,pointX,pointY);
			allMap[pointY][pointX] = 3; //add departure
			//SSH print
			printSSHmonitor(allMapSize/2+robotY,allMapSize/2+robotX);
			printf("count:%d  /  1-unit : %f cm  / print scale : %d \033[92m []Robot \033[33m Sensing \033[31m Wall\n\033[0m",count,unitScale,printScale);
			printf("\t\t[[ ROS-SLAM SSH monitor ]]\n");
			//return sensing text to empty text 
			for(int i=0;i<printSize;i++)
				for(int j=0;j<printSize;j++){
				  int a = allMap[(i-printSize/2)*printScale+allMapSize/2+robotY][(j-printSize/2)*printScale+allMapSize/2+robotX];
					if(a == 1 || a == 5) //sensing point or robot center
						allMap[(i-printSize/2)*printScale+allMapSize/2+robotY][(j-printSize/2)*printScale+allMapSize/2+robotX] = 0;
				}
    
			//printf("angle-distance[%f - %f]253\n",YD_angle[253],YD_distance[253]);
			/*
			if(active == true){
				time_t now;
				time(&now);
				printf("---------------------------------------------\n");
				printf("Corrent Time :%s", asctime(localtime(&now)));
				printf("%d\tScan! Angle:%f\n",printCount,YD_angle[angleNum]);
				printCount++;
			}
			if(data_average[252] < 0.4){	//trans MS
				SerialPrint("10 0 90"); //X Y angle
			}
			*/
			count++;
			for(int i=0;i<500;i++)
				old_distance[i] = YD_distance[i];
			///////////////////////////////////////////////////////////////////////////read
			//SerialRead();
  			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////END
			rate.sleep();
			ros::spinOnce();
			//scanf("%s",scanData);
			if(strcmp(scanData,"stop")==0){
				printf("\033[45m\033[36m");
				printf("--------------------------------stop--------------------------------");
				printf("\033[40m\033[97m");
				break;
			}
			if(strcmp(scanData,"goto")==0){
				printf("input the X Y :");
				scanf("%d %d",&robotX,&robotY);
				printf("go to robot X:%d / Y:%d",robotX,robotY);
				///////////
				fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);	//detect USB for arduino
				serial1 = write(fd,"10 10 0",7);
				if(serial1 < 0)
				perror("write failed - ");
				close(fd);
				///////////
			}
		}
		break;
    }
    laser.turnOff();
    ROS_INFO("[YDLIDAR INFO] Now YDLIDAR is stopping .......");
    laser.disconnecting();
    return 0;
}

void SerialPrint(char* strBuffer)
{
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);	//detect USB for arduino
	serial1 = write(fd,strBuffer,strlen(strBuffer));
	if(serial1 < 0)
		perror("write failed - ");
	close(fd);
}

void SerialRead()
{
	char buf[256];
	serial1 = read(fd, (void*)buf, 255);
	if (serial1 < 0) {
		perror("Read failed - ");
	}
	else if (serial1 == 0) printf("No data on port\n");
	else {
		buf[serial1] = '\0';
		printf("%i bytes read : %s", serial1, buf);
	}
	close(fd);
}
void printSSHmonitor(int currentY,int currentX){
	for(int i = 0 ; i<printSize;i++)
		for(int j = 0; j<printSize;j++)
			pinMap[i][j] = allMap[(i-printSize/2)*printScale+currentY][(j-printSize/2)*printScale+currentX];
	pinMap[printSize/2][printSize/2] = 5;
	printf("\n ");
	printf("\033[97m");//white
	for(int i=0;i<printSize/2-1;i++)
	printf("--");
	printf("FRONT");
	for(int i=0;i<printSize/2-1;i++)
	printf("--");
	printf("-\n");
	for(int i=0;i<printSize;i++){
		printf(" |");
		for(int j=0;j<printSize;j++){
			if(pinMap[i][j] == 1){        //sensing
				printf("\033[33m");//orange
				printf("::");
				printf("\033[97m");//white
			}
			else if(pinMap[i][j] == 2){   //hold , wall
				printf("\033[41m");//red BG
				printf("  ");
				printf("\033[40m\033[97m"); //black BG & white
			}
			else if(pinMap[i][j] == 3){   //departure
				printf("\033[44m");//blue BG
				printf("  ");
				printf("\033[40m\033[97m");//black BG & white
			}
			else if(pinMap[i][j] == 4){   //empty space
				printf("\033[47m");//blue BG
				printf("  ");
				printf("\033[40m\033[97m");//black BG & white
			}
			else if(pinMap[i][j] == 5){   //center
				printf("\033[45m\033[36m");//magenta BG & cyan
				printf("<>");
				printf("\033[40m\033[97m");//black BG & white
			}
			else//nothing
			printf("  ");
		}
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
