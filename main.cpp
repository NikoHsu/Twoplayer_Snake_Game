#include <stdio.h>
#include "DOUBLEDRAGON.h"

/******************源代码 函数声明******************/
void CreateMap();			//初始化地图******
void Drawplayers();			//绘制*****
void Movement();			//移动*****
void Snakewin();
void Dragonwin();
void Collision();			//撞墙******
void Action();              //运行程序**********

int main()
{
	PlaySound(TEXT("D:\\dragonbgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);   //BGM
	Action();
	return 0;

}   //主函数，刷新每一项，各类设置

void Action()
{
	initgraph(1000, 600);
	Cover();				//生成封面函数
	snake.speed = 100, dragon.speed = 100;
	snake.grade = 0, dragon.grade = 0;
	setbkcolor(RGB(190, 150, 150));   //RBG set blackcolor
	cleardevice();              // 清屏
	Createplayers();             //初始化蛇
	while (1)
	{
		cleardevice();		//刷新蛇的路径
		CreateMap();
		Explanation();
		Drawplayers();
		DrawBeads();
		Movement();
		if (Beads.symbol == 0)
		{
			CreateBeads();
		}
		Sleep((dragon.speed + snake.speed));			//这个值会越来越小,节奏越来越快
		Collision();
		Eatbeads();
	}

	_getch();   //不回显函数，按下某个字符时，自动读取，无需回车
	closegraph();
}
//主函数，从头开始

void Drawplayers()
{
	int i, j;  //形参
	for (i = 0; i < snake.lenth; i++)
	{
		setlinecolor(COLORREF RGB(250, 250, 250));  //color of snakeline
		setfillcolor(COLORREF RGB(250, 5, 170));   //color of snake
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);  //fill in the color of the snake
	}
	/******************龙蛇分割******************/
	for (j = 0; j < dragon.lenth; j++)
	{
		setlinecolor(COLORREF RGB(250, 250, 5));  //color of dragonline
		setfillcolor(COLORREF RGB(250, 5, 10));   //color of dragon
		fillrectangle(dragon.xy[j].x, dragon.xy[j].y, dragon.xy[j].x + 10, dragon.xy[j].y + 10);  //fill in the color of the dragon
	}
}
//OKOKOKOKOKOK  龙蛇的绘制(与Movement函数结合实现移动)

void Movement()
{
	int i, j, m, n;

	for (i = snake.lenth - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	for (j = dragon.lenth - 1; j > 0; j--)
	{
		dragon.xy[j].x = dragon.xy[j - 1].x;
		dragon.xy[j].y = dragon.xy[j - 1].y;
	}
	//除了第一节以外,后一节身体的坐标是前一节的坐标

	switch (snake.position)
	{
	case sup:
		snake.xy[0].y -= 10;
		break;
	case sdown:
		snake.xy[0].y += 10;
		break;
	case sright:
		snake.xy[0].x += 10;
		break;
	case sleft:
		snake.xy[0].x -= 10;
		break;
	case pause:
		_getch();
		break;
	}
	
	switch (dragon.position)
	{
	case sup:
		dragon.xy[0].y -= 10;
		break;
	case sdown:
		dragon.xy[0].y += 10;
		break;
	case sright:
		dragon.xy[0].x += 10;
		break;
	case sleft:
		dragon.xy[0].x -= 10;
		break;
	case pause:
		_getch();
		break;   //?暂停会出错
	}
	//头xy[0]运动方向,根据方向标志来移动

	while (_kbhit())     //kbhit()检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
	{
		KeyCommunity();  //键盘交互函数
	}

	for (m = 2; m < snake.lenth; m++)
	{
		if (snake.xy[0].x == snake.xy[m].x && snake.xy[0].y == snake.xy[m].y)
			Dragonwin();
		else if (snake.xy[0].x == dragon.xy[m].x && snake.xy[0].y == dragon.xy[m].y)
			snake.lenth--, snake.grade --,dragon.lenth++, dragon.grade++;
	}

	for (n = 2; n < dragon.lenth; n++)
	{
		if (dragon.xy[0].x == dragon.xy[n].x && dragon.xy[0].y == dragon.xy[n].y)
			Snakewin();
		else if (dragon.xy[0].x == snake.xy[n].x && dragon.xy[0].y == snake.xy[n].y)
			dragon.lenth--, dragon.grade --,snake.lenth++, snake.grade++;
	}
	//当龙或蛇头坐标等于身体时,撞到自己，游戏结束；当龙或者蛇撞到对方，可以吸取长度和得分

}
//龙蛇的运动

void Gameover()
{
	cleardevice();
	char choose;
	settextstyle(50, 0, "华文行楷");
	settextcolor(COLORREF RGB(230, 35, 40));
	char End[] = "新年快乐！";
	char reburn[] = "按y键重新开始游戏";
	outtextxy(100, 125, End);
	outtextxy(100, 175, reburn);
	_getch();
	choose = _getch();
	switch (choose)
	{
	case 'y': Action();  //导致程序模块化不是很好，高耦合,严禁套娃！
		break;
	}
	_getch();  //按其他键退出游戏
	exit(0);
}

void CreateMap()
{
	char name[] = "双龙戏猪";
	settextstyle(40, 0, "华文行楷");
	settextcolor(COLORREF RGB(230, 5, 10));
	outtextxy(250, 50, name);

	setlinecolor(COLORREF RGB(250, 0, 0));    //地图线条颜色
	rectangle(40, 90, 610, 560);   //out圈，左上角xy，右下角xy
	rectangle(50, 100, 600, 550);  //in圈，同  
}
//OKOKOKOKOKOK  绘画地图，地图数据和Collision撞墙函数耦合，与产生珠宝函数耦合

void Snakewin()
{
	settextstyle(28, 0, "楷体");
	char end[] = "这场争夺中,";
	char end0[] = "蛇取得了胜利。";

	settextstyle(25, 0, "楷体");
	char tips[] = "按任意键继续";
	outtextxy(250, 200, end);
	outtextxy(240, 225, end0);
	outtextxy(250, 300, tips);
	_getch();

	Gameover();
}

void Dragonwin()
{
	settextstyle(28, 0, "楷体");
	char end[] = "这场争夺中,";
	char end0[] = "龙取得了胜利。";

	settextstyle(25, 0, "楷体");
	char tips[] = "按任意键继续";
	outtextxy(250, 200, end);
	outtextxy(240, 225, end0);
	outtextxy(250, 300, tips);
	_getch();

	Gameover();
}

void Collision()
{
	if (snake.xy[0].x > 590 || snake.xy[0].x < 50 || snake.xy[0].y > 540 || snake.xy[0].y < 100)
	{
		Dragonwin();		
	}
	if (dragon.xy[0].x > 590 || dragon.xy[0].x < 50 || dragon.xy[0].y > 540 || dragon.xy[0].y < 100)
	{
		Snakewin();		//撞墙时,游戏结束
	}

}
//OKOKOKOKOKOK  判断龙蛇是否撞墙
