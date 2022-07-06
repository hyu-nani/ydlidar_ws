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