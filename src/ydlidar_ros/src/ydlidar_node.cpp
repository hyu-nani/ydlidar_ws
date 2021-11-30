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
bool	active = true;
int		lidarReadCount;

const int	printSize						=	50;
int			pinMap[printSize][printSize]	=	{0};

const int	allMapSize = 10000;
int		allMap[allMapSize][allMapSize] = {0};			//All map
int		robotX = allMapSize/2, robotY = allMapSize/2;	//center

void SerialPrint(char* strBuffer);
void SerialRead();
void printSSHmonitor(int currentY,int currentX);

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
        float val = scan->ranges[i];
        if(val != 0)
        	YD_distance[i] = val;
		if(YD_angle[i]> -5 && YD_angle[i]< 5){
        	//printf("angle-distance[%f - %f]%d\n",YD_angle[i],YD_distance[i],i);
   		}
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
    printf("ydlidar_node file\n");
    printf(" NANI version");
    printf("\n");
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
    while (ret&&ros::ok()) {
        bool hardError;
        LaserScan scan;
        //and loop here 
    	
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
		//////////////////////////////////////////////////////////////////////////
		for(int i=0;i<500;i++){
			float difference = fabs(old_distance[i] - YD_distance[i]);
			int Xvalue = cos(YD_angle[i]+90)*YD_distance[i]*5;
			int Yvalue = sin(YD_angle[i]+90)*YD_distance[i]*5;
			if( (difference < 0.005) &&	(difference != 0) && (YD_distance[i] > 0.15)){
				data_count[i]++;
				if(allMap[robotY+Yvalue][robotX+Xvalue]==0){
				allMap[robotY+Yvalue][robotX+Xvalue] = 1;
				}
			}
			else{
				data_count[i] = 0;
			}
			active = true;
			if(data_count[i] > 30){
				allMap[robotY+Yvalue][robotX+Xvalue] = 2;
				data_count[i] = 0;
				//active = true;
			}
		}
		
		/*
		if (old_distance[0] != 0){
			for(int i=0;i<500;i++){
				float difference = abs(data_average[i] - old_distance[i]);
				if (difference > 0.2){
					angleNum = i;
				}
			}
		}
		*/
		if(active == true){
			printSSHmonitor(robotY,robotX);
			printf("angle-distance[%f - %f]253 %d\n",YD_angle[253],YD_distance[253],count);
			active = false;
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
		rate.sleep();
		ros::spinOnce();
		//////////////////////////////////////////////////////////////////////////END
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
	for(int i = 0 ; i<printSize;i++){
		for(int j = 0; j<printSize;j++){
			pinMap[i][j] = allMap[i+currentY-printSize/2][j+currentX-printSize/2];
		}
	}
	pinMap[printSize/2][printSize/2] = 3;
	system("clear");
	printf("\n");
	for(int i=0;i<printSize+1;i++)
	printf("--");
	printf("\n");
	for(int i=0;i<printSize;i++){
		printf("|");
		for(int j=0;j<printSize;j++){
			if(pinMap[i][j] == 1){
				printf("--");
				allMap[i+currentY-printSize/2][j+currentX-printSize/2] = 0;
			}
			else if(pinMap[i][j] == 2)
			printf("OO");
			else if(pinMap[i][j] == 3)
			printf("<>");
			else 
			printf("  ");
		}
		printf("|\n");
	}
	for(int i=0;i<printSize+1;i++)
	printf("--");
	printf("\n");
}