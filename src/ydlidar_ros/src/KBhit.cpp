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
		case 27://Ctrl-[
		return "ESC";
		case 28://Ctrl--	
		return "FS";
		case 29://Ctrl-]
		return "GS";
		case 30://Ctrl-^
		return "RS";
		case 31://Ctrl-_
		return "US";
		case 32://Space
		return "Space";
		case 33:// !
		return "!";
		case 34:// "
		return "\"";
		case 35:// #
		return "#";
		case 36:// $
		return "$";
		case 37:// %
		return "%";
		case 38:// &
		return "&";
		case 39:// '
		return "'";
		case 40:// (
		return "(";
		case 41:// )
		return ")";
		case 42:// *
		return "*";
		case 43:// +
		return "+";
		case 44:// ,
		return ",";
		case 45:// -
		return "-";
		case 46:// .
		return ".";
		case 47:// /
		return "/";
		case 48:// 0
		return "0";
		case 49:// 1
		return "1";
		case 50:// 2
		return "2";
		case 51:// 3
		return "3";
		case 52:// 4
		return "4";
		case 53:// 5
		return "5";
		case 54:// 6
		return "6";
		case 55:// 7
		return "7";
		case 56:// 8
		return "8";
		case 57:// 9
		return "9";
		case 58:// :
		return ":";
		case 59:// ;
		return ";";
		case 60:// <
		return "<";
		case 61:// =
		return "=";
		case 62:// >	
		return ">";
		case 63:// ?
		return "?";
		case 64:// @
		return "";
		case 65:// A, up arrow
		return "Up";
		case 66:// B, down arrow
		return "Down";
		case 67:// C, right arrow
		return "Right";
		case 68:// D, left arrow
		return "Left";
		case 69:// E
		return "E";
		case 70:// F
		return "F";
		case 71:// G
		return "Move";
		case 72:// H
		return "H";
		case 73:// I
		return "I";
		case 74:// J
		return "J";
		case 75:// K
		return "K";
		case 76:// L
		return "L";
		case 77:// M
		return "Map";
		case 78:// N
		return "N";
		case 79:// O
		return "O";
		case 80:// P
		return "P";
		case 81:// Q 
		return "Q";
		case 82:// R
		return "R";
		case 83:// S
		return "S";
		case 84:// T
		return "T";
		case 85:// U
			return "U";
		case 86:// V
		return "V";
		case 87:// W
		return "W";
		case 88:// X
		return "X";
		case 89:// Y
		return "Y";
		case 90:// Z
		return "Z";
		case 91:// [
		return "[";
		case 92:// |
		return "|";
		case 93:// ]
		return "]";
		case 94:// ^
		return "^";
		case 95:// _
		return "_";
		case 96:// '
		return "'";
		case 97:// a
		return "a";
		case 98:// b
		return "b";
		case 99:// c
		return "c";
		case 100:// d
		return "d";
		case 101:// e
		return "e";
		case 102:// f
		return "f";
		case 103:// g
		return "g";
		case 104:// h
		return "h";
		case 105:// i
		return "i";
		case 106:// j
		return "j";
		case 107:// k
		return "k";
		case 108:// l
		return "l";
		case 109:// m
		return "m";
		case 110:// n
		return "n";
		case 111:// o
		return "o";
		case 112:// p
		return "p";
		case 113:// q
		return "q";
		case 114:// r
		return "r";
		case 115:// s
		return "s";
		case 116:// t
		return "t";
		case 117:// u
		return "u";
		case 118:// v
		return "v"; 
		case 119:// w 
		return "w";
		case 120:// x
		return "x";
		case 121:// y 
		return "y";
		case 122:// z
		return "z";
		case 123:// {
		return "{";
		case 124:// |
		return "|"; 
		case 125:// }
		return "}";
		case 126:// ~
		return "~";
		case 127:// DEL
		return "DEL";
		default:
		return "nothing";
	}
}