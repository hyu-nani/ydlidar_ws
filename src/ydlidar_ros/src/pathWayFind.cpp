/************************************************************************/
/*  �� ã�� �ڵ�     path finding algorithm                             */
/************************************************************************/
/*
	allmap ���� ���� ��ǥ�� ��ǥ ��ǥ ������ �ִ� �Ÿ��� ���������� 
	ǥ���ϴ� �ڵ带 ���� �� ����
	[ BPS ]
	���� ����Ʈ
	https://blog.naver.com/therich21/222665726554
	
	ȸ���ؾ��� ��Ʈ avoid dot
	1. wall
	2. sensing
	3. none space
	��, �ƹ��͵� �ƴ� ������ �ƴ� �νĵ� ����� �̿��� �ϸ�.
	�ﰢ���� ���� ȸ�Ǹ� ���� ���������� ���̵Ǵ� �� ���� ������ �����Ѵ�.
*/
unsigned int	mazeMap[allMapSize][allMapSize]	=	{0};
unsigned int	countMaze[allMapSize][allMapSize]	=	{0};
int		startX, StartY;
int		endX, endY;
int		moveX = 0, moveY = 0;
/*
	Convert allmap to mazeMap
	and
	setting start position , departure position
	1 : path
	0 : wall
*/
void initMap(){
	startX	=	robotX;
	StartY	=	robotY;
	endX	=	departureX;
	endY	=	departureY;
	for(int y = 0; y < allMapSize; y++)
	for(int x = 0; x < allMapSize; x++){
		int dot = allMap[y][x];
		if(	dot == 0 ||	//none
			dot == 1 ||	//sensing
			dot == 2)	//wall
			mazeMap[y][x] = 0;	//wall
		else
			mazeMap[y][x] = 1;	//path
		countMaze[y][x] = 0;
	}
}

/*
	Find path way
	sx = start X
	sy = start Y
	ex = departure X
	ey = departure Y
*/
void findWay(int sx, int sy, int ex, int ey){
	int count = 1;
	countMaze[sy][sx] = 1;
	//counting maze
	printf("%d/%d/%d/%d :\n",sx,sy,ex,ey);
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
					countMaze[y][y + 1] = count + 1;
				if (mazeMap[y][x - 1] == 1 && countMaze[y][x - 1] == 0){
					countMaze[y][x - 1] = count + 1;
					printf("%d\n",count);
				}
			}
		}
		count++;
		
	}
	//find way inversion counting
	int nowX = ex, nowY = ey;
	for (int i = count; i > 0; i--) {
		if (countMaze[nowX][nowY] = i)
		countMaze[nowX][nowY] = -1;
		if (i - 1 == countMaze[nowX - 1][nowY]) {
			countMaze[nowX - 1][nowY] = -1;
			nowX--;
		}
		else if (i - 1 == countMaze[nowX + 1][nowY]) {
			countMaze[nowX + 1][nowY] = -1;
			nowX++;
		}
		else if (i - 1 == countMaze[nowX][nowY - 1]) {
			countMaze[nowX][nowY - 1] = -1;
			nowY--;
		}
		else if (i - 1 == countMaze[nowX][nowY + 1]) {
			countMaze[nowX][nowY + 1] = -1;
			nowY++;
		}
	}
	printf("%d\n", count);
	//next move point
	moveX = 0;
	moveY = 0;
	//���� ���⿡ ���� �� ���� �ʿ�
	if( -10 < robotAngle && robotAngle < 10)//��
		if(countMaze[sy - 1][sx] == -1)
			moveY = -1;
		else if(countMaze[sy + 1][sx] == -1)
			moveY = 1;
		else if(countMaze[sy][sx - 1] == -1)
			moveX = -1;
		else if(countMaze[sy][sx + 1] == -1)
			moveX = 1;
	else if( 80 < robotAngle && robotAngle < 100)//��
		if(countMaze[sy - 1][sx] == -1)
			moveX = -1;
		else if(countMaze[sy + 1][sx] == -1)
			moveX = 1;
		else if(countMaze[sy][sx - 1] == -1)
			moveY = 1;
		else if(countMaze[sy][sx + 1] == -1)
			moveY = -1;
	else if( -100 < robotAngle && robotAngle < -80)//��
		if(countMaze[sy - 1][sx] == -1)
			moveX = 1;
		else if(countMaze[sy + 1][sx] == -1)
			moveX = -1;
		else if(countMaze[sy][sx - 1] == -1)
			moveY = -1;
		else if(countMaze[sy][sx + 1] == -1)
			moveY = 1;
	else if( 170 < robotAngle && robotAngle < -170)//�Ʒ�
		if(countMaze[sy - 1][sx] == -1)
			moveY = 1;
		else if(countMaze[sy + 1][sx] == -1)
			moveY = -1;
		else if(countMaze[sy][sx - 1] == -1)
			moveX = 1;
		else if(countMaze[sy][sx + 1] == -1)
			moveX = -1;
}