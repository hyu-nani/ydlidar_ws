/*
 *  Return KB hit ASCII code system
 *	auther : hyu-nani
 */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
const char* linux_kbhit()
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
	
	switch(ch){ //ASCII Table code
		case 0:// Ctrl-@
			return "NUL";
		case 1:// Ctrl-A
			return "SOH";
		case 2:// Ctrl-B
			return "STX";
		case 3:// Ctrl-C
			return "ETX";
		case 4:// Ctrl-D
			return "EOT";
		case 5:// Ctrl-E
			return "ENQ";
		case 6:// Ctrl-F
			return "ACK";
		case 7:// Ctrl-G
			return "BEL";
		case 8:// Ctrl-H
			return "BS";
		case 9:// Ctrl-I
			return "HT";
		case 10://Ctrl-J
			return "LF";
		case 11://Ctrl-K
			return "VT";
		case 12://Ctrl-L
			return "FF";
		case 13://Ctrl-M
			return "CR";
		case 14://Ctrl-N
			return "SO";
		case 15://Ctrl-O
			return "SI";
		case 16://Ctrl-P
			return "DLE";
		case 17://Ctrl-Q
			return "DC1";
		case 18://Ctrl-R
			return "DC2";
		case 19://Ctrl-S
			return "DC3";
		case 20://Ctrl-T
			return "DC4";
		case 21://Ctrl-U
			return "NAK";
		case 22://Ctrl-V
			return "SYN";
		case 23://Ctrl-W
			return "ETB";
		case 24://Ctrl-X
			return "CAN";
		case 25://Ctrl-Y
			return "EM";
		case 26://Ctrl-Z
			return "SUB";
		case 32://space key
			return "Space";
		case 65://up arrow
			return "Up";
		case 68://left arrow
			return "Left";
		case 67://right arrow
			return "Right";
		case 66://down arrow
			return "Down";
		case 47:// / key
			return "/";
		case 77:// M key
			return "Map";
		case 71:// G key
			return "Move";
		default:
			return "nothing";
	}
}