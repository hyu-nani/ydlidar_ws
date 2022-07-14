/************************************************************************/
/*  길 찾는 코드     path finding algorithm                             */
/************************************************************************/
/*
	allmap 에서 현재 좌표와 목표 좌표 사이의 최단 거리를 순차적으로 
	표시하는 코드를 구현 할 생각
	[ BPS ]
	참고 사이트
	https://blog.naver.com/therich21/222665726554
	
	회피해야할 도트 avoid dot
	1. wall
	2. sensing
	3. none space
	즉, 아무것도 아닌 공간이 아닌 인식된 빈공간 이여야 하며.
	즉각적인 전방 회피를 위해 순간적으로 센싱되는 곳 또한 벽으로 간주한다.
*/
unsigned int	mazeMap[allMapSize][allMapSize]	=	{0};
unsigned int	countMaze[allMapSize][allMapSize]	=	{0};
int		startX, startY;
int		endX, endY;
int		moveX = 0, moveY = 0;
/*
	Convert allmap to mazeMap
	and
	setting start position , arrival position
	1 : path
	0 : wall
*/
void initMap(){
	startX	=	robotX;
	startY	=	robotY;
	endX	=	arrivalX;
	endY	=	arrivalY;
	int	guide	=	1;
	for(int y = 0; y < allMapSize; y++)
	for(int x = 0; x < allMapSize; x++){
		int dot = allMap[y][x];
		if(	dot == 0 ||	//none
			dot == 2){	//wall
			mazeMap[y][x] = 0;	//wall
		}
		else{
			mazeMap[y][x] = 1;	//path
		}
		countMaze[y][x] = 0;
	}
	for(int i=0;i<5;i++)
	for(int j=0;j<5;j++)
	mazeMap[allMapSize/2+robotY+i-2][allMapSize/2+robotX+j-2] = 1;	//path
	for(int y = 1; y < allMapSize-1; y++)
	for(int x = 1; x < allMapSize-1; x++)
	if( mazeMap[y][x] == 0 )
	if( mazeMap[y+1][x] == 1 ||
		mazeMap[y][x+1] == 1 ||
		mazeMap[y-1][x] == 1 ||
		mazeMap[y][x-1] == 1)
		mazeMap[y][x] = 2;
	for(int y = 1; y < allMapSize-1; y++)
	for(int x = 1; x < allMapSize-1; x++)
	if( mazeMap[y][x] == 2 )
	for(int i=0;i<5;i++)
	for(int j=0;j<5;j++)
	if(mazeMap[y+i-2][x+j-2] != 2)
	mazeMap[y+i-2][x+j-2] = 0;
}
bool findWay(int sx, int sy, int ex, int ey){
	int count = 1;
	countMaze[sy][sx] = 1;
	//counting maze
	printf("%d/%d/%d/%d counting:\n",sx,sy,ex,ey);
	while(countMaze[ey][ex] != count){
		for (int y = -count + sy; y < count + sy; y++)
		for (int x = -count + sx; x < count + sx; x++) {
			if (x < 0 || y < 0 || x > allMapSize || y > allMapSize)//range over
				continue;
			if (countMaze[y][x] == count) {		//check way
				if (mazeMap[y + 1][x] == 1 && countMaze[y + 1][x] == 0)
					countMaze[y + 1][x] = count + 1;
				if (mazeMap[y - 1][x] == 1 && countMaze[y - 1][x] == 0)
					countMaze[y - 1][x] = count + 1;
				if (mazeMap[y][x + 1] == 1 && countMaze[y][x + 1] == 0)
					countMaze[y][x + 1] = count + 1;
				if (mazeMap[y][x - 1] == 1 && countMaze[y][x - 1] == 0)
					countMaze[y][x - 1] = count + 1;
			}
		}
		if(count > 5000){
			return false;
		}
		else
			count++;
	}
	printf("find way\n");
	//find way inversion counting
	int nowX = ex, nowY = ey;
	countMaze[nowY][nowX] = -1;
	for (int i = count; i > 0; i--) {
		if (i - 1 == countMaze[nowY - 1][nowX]) {
			countMaze[nowY - 1][nowX] = -1;
			allMap[nowY - 1][nowX] = 6;
			nowY--;
		}
		else if (i - 1 == countMaze[nowY + 1][nowX]) {
			countMaze[nowY + 1][nowX] = -1;
			allMap[nowY + 1][nowX] = 6;
			nowY++;
		}
		else if (i - 1 == countMaze[nowY][nowX - 1]) {
			countMaze[nowY][nowX - 1] = -1;
			allMap[nowY][nowX - 1] = 6;
			nowX--;
		}
		else if (i - 1 == countMaze[nowY][nowX + 1]) {
			countMaze[nowY][nowX + 1] = -1;
			allMap[nowY][nowX + 1] = 6;
			nowX++;
		}
		else{
			return false;
		}
	}
	//printf("%d\n", count);
	//next move point
	moveX = 0;
	moveY = 0;
	//현재 방향에 따른 값 수정 필요
	if( -10 < robotAngle && robotAngle < 10){//위
		if(countMaze[sy - 1][sx] == -1)
			moveY = -1;
		else if(countMaze[sy + 1][sx] == -1)
			moveY = 1;
		else if(countMaze[sy][sx - 1] == -1)
			moveX = -1;
		else if(countMaze[sy][sx + 1] == -1)
			moveX = 1;
	}
	else if( 80 < robotAngle && robotAngle < 100){//좌
		if(countMaze[sy - 1][sx] == -1)
			moveX = -1;
		else if(countMaze[sy + 1][sx] == -1)
			moveX = 1;
		else if(countMaze[sy][sx - 1] == -1)
			moveY = 1;
		else if(countMaze[sy][sx + 1] == -1)
			moveY = -1;
	}
	else if( -100 < robotAngle && robotAngle < -80){//우
		if(countMaze[sy - 1][sx] == -1)
			moveX = 1;
		else if(countMaze[sy + 1][sx] == -1)
			moveX = -1;
		else if(countMaze[sy][sx - 1] == -1)
			moveY = -1;
		else if(countMaze[sy][sx + 1] == -1)
			moveY = 1;
	}
	else if( 170 < robotAngle && robotAngle < -170){//아래
		if(countMaze[sy - 1][sx] == -1)
			moveY = 1;
		else if(countMaze[sy + 1][sx] == -1)
			moveY = -1;
		else if(countMaze[sy][sx - 1] == -1)
			moveX = 1;
		else if(countMaze[sy][sx + 1] == -1)
			moveX = -1;
	}
	return true;
}