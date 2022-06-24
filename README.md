# C语言实现小游戏2048

### About

2048是什么游戏我也不多做介绍了，确实没玩过的话也可以先去玩一下。

虽说自己写一个2048工程量不大，但对于一名c语言初学者来说，里面的一些算法以及游戏的一些逻辑关系还是有点复杂并且值得推敲的。



### 头文件 

目前考虑先写出基于命令行的游戏界面（纯文本），后续可使用c语言自带的图形库EGE进行图形界面开发，使整个游戏界面更接近于平时说玩到的2048。

预定义以及头文件包含：

```c
#include <stdio.h>
#define SIZE 4  //网格大小
```

- 2048一般是4*4规格的，适配其他规格意义不大，但本程序仍会预留对规格的拓展性，以SIZE作为网格的大小，核心算法也将具有对不同规格的适配。

  

### 核心结构

2048这个游戏的核心结构很简单，就是一个4x4的网格（我将称其为2048网格），每个格子都会存放一个数字或者为空（本程序用0表示空格子），存放的数字只能为2的n次方

在c语言中，使用一个4x4的整型二维数组`table`来表示这个2048网格，`table`将作为整个程序全局变量。

除此之外，游戏的一些参数也会作为程序的全局变量，目前只有一个表示游戏分数的参数`score`，没错，2048也是有分数滴，不过关于这个分数怎么计算的问题，在稍后我会讲到。

```c
int table[SIZE][SIZE];   //4x4的网格
int score; //游戏分数
```



### 输出模块

若考虑后续的升级，在游戏的开发过程中，主页面以及游戏界面的输出与游戏内部的核心算法将进行分离，这里相当于将定义的函数分成*输出模块*与*操作模块*

在本阶段的2048程序开发将直接在命令行中展示2048界面以及主界面，即单纯使用`printf`函数、使用`system("cls")`来清除屏幕、使用`system("pause")`来等待用户输入任意键。

在整个程序中，将使用一个`init`函数，来展示游戏的主界面以及接受用户对主界面操作的指令，并使用一个`show_table`函数来展示4x4方格，使用`over`函数来展示游戏结束界面。

- 函数声明

```c
void show_table(); //展示4x4方格
int init(); 展示游戏的主界面,接受用户对主界面操作并返回操作值
void over();
```

- show_table函数  ->  输出2048网格以及分数值

``` c
void show_table()
{
	system("cls");   //每一次输出前，先清除屏幕
    //输出当前的2048网格
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			printf("%4d",table[i][j]);
		}
		printf("\n\n");
	}
	printf("Score: %d\n",score);  //输出当前分数值
}
```

- init函数  -> 输出主界面，接收用户输入并返回输入值

``` c
int init()
{
	char choose_num;
	system("cls"); //清屏
	printf("2048\n");
	printf("Please use \'w\',\'a\',\'s\',\'d\' to control\n");
	printf("What will you want to do?\n");
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
```



- over函数

``` c
void over()
{
	printf("Game over!\n");
	printf("Your score is %d\n",score);
	system("pause");
}
```



### 核心模块

- 函数声明

```c
void new_game();  //初始化游戏，游戏开始时执行此函数
void game(); //游戏的运行函数，游戏开始后执行的函数

int get_direction(); //获取用户的键盘操作，并返回操作值（方向）
int upward(); //向上操作
int downward(); //向下操作
int leftward(); //向左操作
int rightward(); //向右操作
void control_in_each_unit(int *unit); //稍后细说
int isover(); //判断是否已经游戏结束
void next_step(); //下一步，操作完成后进入下一步时执行
```



- 运行流程

每一轮游戏开始时，将运行`new_game`函数，即初始化函数，进行初始化工作，之后将进入`game()`函数，此函数为游戏的核心运行函数，游戏运行时的任何操作都在这个函数里面进行，因此将此称为运行函数。



- 初始化函数new_game()

``` c
void new_game()
{
	score=0;  //初始化分数值
	
	//初始化2048网格
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
	//生成两个初始位置(x1,y1)及（x2,y2）
	int init_pos_x1 = rand()%SIZE, init_pos_y1 = rand()%SIZE;
	int init_pos_x2 = rand()%SIZE, init_pos_y2 = rand()%SIZE;
	
	if(init_pos_x1==init_pos_x2&&init_pos_y1==init_pos_y2){
		Sleep(10); //这里暂停10ms是为了让下一次产生的随机位置不一样，不然会爆栈！
		return new_game();  //如果生成的刚好是同一个格子，则重新生成一个
	}
	
	table[init_pos_x1][init_pos_y1] = init_value1;
	table[init_pos_x2][init_pos_y2] = init_value2;
}
```

游戏初始化时，先将分数初始化为0，然后对2048网格进行初始化，即将网格的所有项都初始化为0（空格子），然后生成两个随机的初始格子以及对应的初始数字（2或者4）。



- 运行函数game()

``` c
void game()
{
	int direction; //操作的方向 1上2左3下4右
    int iseffect; //是否为有效操作
	while(1)
	{
		show_table(); //展示2048网格
		if(isover())  //判断是否游戏结束，若结束则输出结束信息并退出循环
		{
			over();
			break;
		}
		direction=get_direction(); //获取键盘输入的操作方向（上下左右）
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
		if(iseffect) next_step(); //若为有效操作，执行下一步函数
	}
}
```

每轮循环的开头，输出上一次操作后的2048网格(`show_table()`)，然后等待用户输入（`get_direction()`），输入的方向将赋给`direction`变量，之后按照对应的方向执行该方向对应的操作函数（`upward()`, `leftward()`, `downward()`, `rightward()`），操作函数将返回本次操作是否为有效操作（1或0），若为有效操作，执行下一步函数`next_step()`。



初始化函数`new_game`和运行函数`game`组成了2048的核心流程，

下面将介绍在`game()`中的各个函数：

- “是否结束”函数isover()

``` c
int isover()
{
	for(int i=0;i<SIZE;i++) //判断有无空格子
	{
		for(int j=0;j<SIZE;j++)
		{
			if(table[i][j]==0) return 0;
		}
	}
	
	for(int i=0;i<SIZE;i++) //判断横向有无连续相同数字格子
	{
		for(int j=1;j<SIZE;j++)
		{
			if(table[i][j]==table[i][j-1]) return 0;
		}
	}
	
	for(int i=0;i<SIZE;i++) //判断纵向有无连续相同格子
	{
		for(int j=1;j<SIZE;j++)
		{
			if(table[j][i]==table[j-1][i]) return 0;
		}
	}
	
	return 1; //以上条件都不满足，游戏结束
}
```

`isover`函数用于判断是否游戏结束，若结束返回1，未结束返回2，游戏结束需包括以下条件：1.无空格子	2.每一个格子的相邻位置无相同数字的格子。



- “获取按键信息”函数get_direction

``` c
int get_direction() //获取键盘输入
{
	int key;
	while(!_kbhit()){} //等待用户输入，如果不输入则死循环
	key = _getch(); //获取输入的字符
	if(key=='w') return 1;
	else if(key=='a') return 2;
	else if(key=='s') return 3;
	else if(key=='d') return 4;
	else return get_direction(); //若输入错误的内容，重新等待用户输入
}
```

为了直接获取用户的键盘按键事件，即按下键盘就触发而不是输入完按回车才触发的事件，这里引入`conio.h`库文件中的`_kbhit`函数以及`_getch`函数

> ``` c
> int _kbhit(void);
> int _getch(void);
> ```
>
> 当`_kbhit()`运行时，判断用户是否正在触发键盘输入事件，若是则返回非零值，否则返回0；
>
> `_getch()`的作用是从控制台中获取输入的字符，在获取输入的字符之后，并不会在控制台中显示该字符。

由于刚按下的按键进入缓冲区，_getch()在执行时会被自动读取。

通过一个循环来等待用户按下按键，按下按键后退出循环，将读取到的字符赋值给`key`变量，并判断是否输入了w,a,s或者d，如果是则返回对应数字，否则重新等待用户输入。



- **加和推格算法**

其实从这里开始，才会真正体现出2048程序的核心算法，才是游戏能正常运行的最关键的一步，这个核心的算法，就叫作**加和推格算法**（真编不出什么好听的名字了哈哈哈）

由于操作方向上的每一列数字均独立运用此算法，所以我将根据操作方向对2048网格分成4个单元然后再这4个单元分别运用加和推格算法。

例如我这里有一个2048网格：

> 0 2 4 2
>
> 2 8 2 0
>
> 0 0 0 2
>
> 0 0 0 0

如果操作方向是向上，那组成的四个单元为：

[0,2,0,0], [2,8,0,0], [4,2,0,0], [2,0,2,0]

如果操作方向是向下，那组成的四个单元为：

[0,0,2,0], [0,0,8,2], [0,0,2,4], [0,2,0,2]

如果操作方向是向左，那组成的四个单元为：

[0,2,4,2], [2,8,2,0], [0,0,0,2], [0,0,0,0]

如果操作方向是向右，那组成的四个单元为：

[2,4,2,0], [0,2,8,2], [2,0,0,0], [0,0,0,0]

分好单元后，对每一个单元进行**加和推格操作**：

1. 加和

   若每单元除去空格子后出现两个相邻的相同数字的格子，这将这两个格子进行相加，被加的格子一个赋值为相加之后的数值，另一个赋值为0。

   例如，对单元`[2,4,2,2]`，进行加和操作，其结果为`[2,4,4,0]`；

   对单元`[2,0,2,8]`，进行加和操作，其结果为`[4,0,0,8]`；

   对单元`[2,2,8,8]`，进行加和操作，其结果为`[4,0,16,0]`；

2. 推格

   加和执行完毕后，接下来就是推格了，推格就是将加和后的每一个非零格子向指定方向进行对齐处理，其操作原理类似于"推箱子"，因此叫做"推格"。由于每个单元的操作方向已经在外部确定，所以对每个单元的推格只需要往前推（往左推）即可。例如，单元`[0,4,0,2]`推格后为`[4,2,0,0]`，单元`[2,0,8,2]`推格后为`[2,8,2,0]`。

- control_in_each_unit函数

每个单元的加和推格，用一个control_in_each_unit函数实现

``` c
void control_in_each_unit(int *unit)
{
	//加和
	int point=0; //指定格
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
	
	//推格
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
```

值得一提的是，之前说到的2048的分数，就是在加和这一步产生的，每一次成功的加和，都会触发加分，加的分数即为相加之后的和。

- 操作函数upward(), downward(), leftward(), rightward()

以upward()为例

``` c
int upward()
{
	int unit[SIZE];
	int ori_table[SIZE][SIZE]; //复制一份操作前的2048网格作为备用以便后续判断是否为有效操作
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
		//将操作后的单元重新写回2048网格
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
```

在操作函数中，对2048网格按照方向，生成4个单元，每个单元均执行加和推格操作，每单元操作完后将数据写回2048网格，之后判断网格与操作前是否一致，如果是，函数返回0，否则返回1，代表本次操作为有效操作。

同样道理，写出其他三个操作函数：

``` c
int downward()
{
	int unit[SIZE];
	int ori_table[SIZE][SIZE]; 
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
	int ori_table[SIZE][SIZE]; 
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			ori_table[i][j]=table[i][j];                                                                                                                            //name:LondonWu  （防伪用）
		}
	}
	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			unit[j]=table[i][j];
		}
		control_in_each_unit(unit);
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
	int ori_table[SIZE][SIZE];
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
		for(int j=SIZE-1;j>=0;j--)
		{
			table[i][j]=unit[SIZE-j-1];
		}
	}
```



- 下一步函数next_step()

``` c
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
```

先获取所有空格子的位置，如果没有空格子不进行任意操作，如果有则在这些位置中产生一个随机位置并为这个格子赋一个数值2或4。



### main函数

再写一个main函数，程序就能跑起来啦

``` c
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
		
	return 0;
}
```



