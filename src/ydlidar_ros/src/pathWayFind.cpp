/************************************************************************/
/*  길 찾는 코드                                                        */
/************************************************************************/
/*
	allmap 에서 현재 좌표와 목표 좌표 사이의 최단 거리를 순차적으로 
	표시하는 코드를 구현 할 생각
	
	회피해야할 도트
	1. wall
	2. sensing
	3. none space
	즉, 아무것도 아닌 공간이 아닌 인식된 빈공간 이여야 하며.
	즉각적인 전방 회피를 위해 순간적으로 센싱되는 곳 또한 벽으로 간주한다.
*/
unsigned int	mazeMap[allMapSize][allMapSize]	=	{0};
	
void convertMap(){
	for(int y=0;y<allMapSize;y++)
	for(int x=0;x<allMapSize;x++){
		int dot = allMap[y][x];
		if(	dot == 0 ||	//none
			dot == 1 ||	//sensing
			dot == 2)	//wall
			mazeMap[y][x] = 1;//wall
		else
			mazeMap[y][x] = 0;//way
	}
}
void path(){
	
}