/************************************************************************/
/*  �� ã�� �ڵ�                                                        */
/************************************************************************/
/*
	allmap ���� ���� ��ǥ�� ��ǥ ��ǥ ������ �ִ� �Ÿ��� ���������� 
	ǥ���ϴ� �ڵ带 ���� �� ����
	
	ȸ���ؾ��� ��Ʈ
	1. wall
	2. sensing
	3. none space
	��, �ƹ��͵� �ƴ� ������ �ƴ� �νĵ� ����� �̿��� �ϸ�.
	�ﰢ���� ���� ȸ�Ǹ� ���� ���������� ���̵Ǵ� �� ���� ������ �����Ѵ�.
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