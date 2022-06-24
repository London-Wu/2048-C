#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define SIZE 4

int table[SIZE][SIZE];   //4x4棋盘格
int score;

int init();
void new_game();
void show_table();
int get_direction();
void game();
int upward();
int downward();
int leftward();
int rightward();
void control_in_each_unit(int *unit);
int isover(); //判断是否结束
void next_step();
void over();


void new_game()
{
	score=0;  //初始化分数值
	
	//初始化棋盘格
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			table[i][j]=0;
		}
	}
	
	//生成两个初始格子以及对应的初始值,初始值的可能值为2或4
	//生成两个初始值value1，value2
	srand((unsigned)(time(NULL)));
	int init_value1 = (rand()%2+1)*2;
	int init_value2 = (rand()%2+1)*2;
	//生成两个初始位置(x1,y1)及(x2,y2)
	int init_pos_x1 = rand()%SIZE, init_pos_y1 = rand()%SIZE;
	int init_pos_x2 = rand()%SIZE, init_pos_y2 = rand()%SIZE;
	
	if(init_pos_x1==init_pos_x2&&init_pos_y1==init_pos_y2){
		Sleep(10);
		return new_game();  //如果生成的刚好是同一个格子，则重新生成一个
	}
	
	table[init_pos_x1][init_pos_y1] = init_value1;
	table[init_pos_x2][init_pos_y2] = init_value2;
}

void show_table()
{
	system("cls");
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			printf("%4d",table[i][j]);
		}
		printf("\n\n");
	}
	printf("Score: %d\n",score);
}

int get_direction() //获取键盘输入
{
	int key;
	while(!_kbhit()){}
	key = _getch();
	if(key=='w') return 1;
	else if(key=='a') return 2;
	else if(key=='s') return 3;
	else if(key=='d') return 4;
	else return get_direction();
}

int isover() //判断是否无路可走
{
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(table[i][j]==0) return 0;
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=1;j<SIZE;j++)
		{
			if(table[i][j]==table[i][j-1]) return 0;
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=1;j<SIZE;j++)
		{
			if(table[j][i]==table[j-1][i]) return 0;
		}
	}
	
	return 1; //游戏结束啦
}

void control_in_each_unit(int *unit)
{
	//加和
	int point=0;
	for(int i=1;i<SIZE;i++)
	{
		if(unit[i]==0) continue; //如果有空格子，比较下一格与指定格
		else if(unit[i]==unit[point]) //否则，只与前一格比较
		{
			unit[point]*=2;
			unit[i]=0;
			//出现正确移动，加分
			score+=unit[point];
		}
		point = i;
	}
	
	//推
	for(int i=SIZE-1;i>=0;i--)
	{
		if(unit[i]==0)
		{
			for(int j=i+1;j<SIZE;j++)
			{
				unit[j-1]=unit[j];
			}
			unit[SIZE-1]=0;
		}
	}
}

int upward()
{
	int unit[SIZE];
	int ori_table[SIZE][SIZE]; //复制一份以便判断是否为有效操作
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			ori_table[i][j]=table[i][j];
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			unit[j]=table[j][i];
		}
		control_in_each_unit(unit);
		//将操作后的单元弄回去
		for(int j=0;j<SIZE;j++)
		{
			table[j][i]=unit[j];
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(ori_table[i][j]!=table[i][j]) return 1;
		}
	}
	
	return 0;
}

int downward()
{
	int unit[SIZE];
	int ori_table[SIZE][SIZE]; //复制一份以便判断是否为有效操作
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			ori_table[i][j]=table[i][j];
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=SIZE-1;j>=0;j--)
		{
			unit[SIZE-j-1]=table[j][i];
		}
		control_in_each_unit(unit);
		//将操作后的单元弄回去
		for(int j=SIZE-1;j>=0;j--)
		{
			table[j][i]=unit[SIZE-j-1];
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(ori_table[i][j]!=table[i][j]) return 1;
		}
	}
	
	return 0;
}

int leftward()
{
	int unit[SIZE];
	int ori_table[SIZE][SIZE]; //复制一份以便判断是否为有效操作
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			ori_table[i][j]=table[i][j];                                                                                                                            //id：********3053  name:LondonWu  （防伪用）
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			unit[j]=table[i][j];
		}
		control_in_each_unit(unit);
		//将操作后的单元弄回去
		for(int j=0;j<SIZE;j++)
		{
			table[i][j]=unit[j];
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(ori_table[i][j]!=table[i][j]) return 1;
		}
	}
	
	return 0;
}

int rightward()
{
	int unit[SIZE];
	int ori_table[SIZE][SIZE]; //复制一份以便判断是否为有效操作
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			ori_table[i][j]=table[i][j];
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=SIZE-1;j>=0;j--)
		{
			unit[SIZE-j-1]=table[i][j];
		}
		control_in_each_unit(unit);
		//将操作后的单元弄回去
		for(int j=SIZE-1;j>=0;j--)
		{
			table[i][j]=unit[SIZE-j-1];
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(ori_table[i][j]!=table[i][j]) return 1;
		}
	}
	
	return 0;
}

void next_step()
{
	int add_able[SIZE][2];  //可以加的格子
	int add_able_num=0;
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(table[i][j]==0)
			{
				add_able[add_able_num][0]=i;
				add_able[add_able_num][1]=j;
				add_able_num++;
			}
		}
	}
	if(add_able_num==0) return;
	else
	{
		int add_num = (rand()%2+1)*2;
		int add_point=rand()%add_able_num;
		table[add_able[add_point][0]][add_able[add_point][1]]=add_num;
	}
}

void over()
{
	printf("Game over!\n");
	printf("Your score is %d\n",score);
	system("pause");
}

void game()
{
	int direction,iseffect;
	while(1)
	{
		show_table();
		if(isover())
		{
			over();
			break;
		}
		direction=get_direction();
		switch(direction) 
		{
		case 1:
			iseffect = upward();
			break;
		case 2:
			iseffect = leftward();
			break;
		case 3:
			iseffect = downward();
			break;
		case 4:
			iseffect = rightward();
			break;
		}
		if(iseffect) next_step();
	}
	
}

int init()
{
	char choose_num;
	system("cls"); //清屏
	printf("2048\n");
	printf("Please use \'w\',\'a\',\'s\',\'d\' to control\n");
	printf("What will you want to do?\n");
	//printf("1. continue game\n");
	//printf("1. Chart\n");	
	printf("1. start a new game\n");
	printf("2. exit\n");
	printf("Please input a number:");
	while(1)
	{
		scanf("%c",&choose_num);
		getchar();
		if(choose_num=='1') return 1;
		else if(choose_num=='2')
		{
			return 2;
		}
		else
		{
			printf("Error input! Please input again:");
		}
	}
}

int main()
{
	int choose_num;
	while(1)
	{
		choose_num=init();
		if(choose_num==1) //开始游戏
		{
			new_game();
			game();
			
		}
		else if(choose_num==2) //退出游戏
		{
			printf("Press any key to end game.\n");
			system("pause");
			return 0;
		}
	}
	
	return 0;
}
