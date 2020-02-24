#ifndef __DOUBLEDRAGON_H__
#define __DOUBLEDRAGON_H__

#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;


#define Max 99		//节数max

#define	up 72      
#define	down 80
#define left 75
#define	right 77
#define	w 119    
#define	s 115
#define a 97
#define	d 100          //宏定义运动ASCII码

/******************以下结构体声明******************/
typedef struct pointxy
{
	int x;
	int y;
}pointxy; //定义坐标数据类型pointxy

struct Player
{
	int lenth;			//节数
	pointxy xy[Max];	//最大长度
	char position;		//标记方向
	int speed;			//速度
	int grade;			//分数
}snake,dragon;        //龙与蛇


struct Beads
{
	pointxy Beadsxy;		//珠宝坐标
	int symbol;		//珠宝存在标志
}Beads;//珠宝

enum positon { sright, sleft, sup, sdown, pause }; //方向判断枚举

/******************以下部分函数声明******************/

void Cover()
{
	setbkcolor(RGB(25, 20, 20));
	int i = 0;
	char name[] = "双龙 戏猪";
	char choice[2][30] = { "按任意键开始游戏", "Bilibili@工科狗Niko" };


	Sleep(800);  //800ms后显现
	settextstyle(100, 0, "华文行楷");
	settextcolor(COLORREF RGB(250, 5, 60));
	outtextxy(280, 125, name);    //标题-双龙戏珠-新年红
	settextcolor(COLORREF RGB(50, 150, 100));
	settextstyle(19, 0, "楷体");
	outtextxy(640, 250, choice[1]);    //作者-工科狗Niko-原谅色
	setlinecolor(COLORREF RGB(255, 0, 50));
	rectangle(70, 90, 900, 500);   //线框
	settextstyle(25, 0, "楷体");
	do {
		settextcolor(COLORREF RGB(144, 236, 194));
		outtextxy(380, 325, choice[0]);
		Sleep(800);
		settextcolor(COLORREF RGB(i, 0, 0));
		outtextxy(380, 325, choice[0]);
		Sleep(800);
		i += 30;
	} while (!_kbhit());       //按任意键开始游戏-只有按键才会跳出循环
	_getch();

}
//OKOKOKOKOKOK  显示封面及设置字体

void KeyCommunity()
{
	char key = _getch();

	switch (key)
	{
	case up:
		//实现蛇的移动逻辑判断,不能往相反的方向移动
		if (snake.position != sdown)
			snake.position = sup;
		break;
	case down:
		if (snake.position != sup)
			snake.position = sdown;
		break;
	case left:
		if (snake.position != sright)
			snake.position = sleft;
		break;
	case right:
		if (snake.position != sleft)
			snake.position = sright;
		break;

	case w:
		//实现龙的移动逻辑判断,不能往相反的方向移动
		if (dragon.position != sdown)
			dragon.position = sup;
		break;
	case s:
		if (dragon.position != sup)
			dragon.position = sdown;
		break;
	case a:
		if (dragon.position != sright)
			dragon.position = sleft;
		break;
	case d:
		if (dragon.position != sleft)
			dragon.position = sright;
		break;

	case 'p':
		snake.position = pause;
		dragon.position = pause;
		break;
	}
}
//OKOKOKOKOKOK  龙蛇按键交互功能

void Createplayers()
{
	dragon.xy[2].x = 50;
	dragon.xy[2].y = 100;

	dragon.xy[1].x = 60;
	dragon.xy[1].y = 100;

	dragon.xy[0].x = 70;
	dragon.xy[0].y = 100;    //dragon初始位在左上角

	dragon.lenth = 3;
	dragon.position = sright;

	snake.xy[2].x = 590;
	snake.xy[2].y = 540;

	snake.xy[1].x = 580;
	snake.xy[1].y = 540;

	snake.xy[0].x = 570;
	snake.xy[0].y = 540;    //蛇初始在右下角

	snake.lenth = 3;
	snake.position = sleft;


	Beads.symbol = 0;

}
//初始化龙与蛇

void Explanation()
{
	char snake_grade[] = "蛇得到猪数：";
	char dragon_grade[] = "龙得到猪数：";
	char grade1[100];  char grade2[100];
	char exp[7][25] = { "玩法说明:", "1.分别用wasd与上下左右", "键改变方向", "2.按p键暂停,按其他键继续","3.龙蛇互撞会有惊喜","4.随着时间推移，节奏会","越来越快，祝你好运" };
	settextstyle(22, 0, "楷体");
	setlinecolor(COLORREF RGB(150, 3, 125));
	rectangle(620, 90, 900, 560);
	settextcolor(COLORREF RGB(255, 215, 15));  //金黄色

	sprintf(grade1, "%d", snake.grade);
	sprintf(grade2, "%d", dragon.grade);

	outtextxy(630, 100, snake_grade);
	outtextxy(750, 100, grade1);    //显示蛇的得分
	outtextxy(630, 120, dragon_grade);
	outtextxy(750, 120, grade2);   //显示龙的得分
	outtextxy(630, 300, exp[0]);
	outtextxy(630, 325, exp[1]);
	outtextxy(630, 350, exp[2]);
	outtextxy(630, 375, exp[3]);
	outtextxy(630, 400, exp[4]);
	outtextxy(630, 425, exp[5]);
	outtextxy(630, 450, exp[6]);
}
//右侧信息栏,字会闪烁？

void CreateBeads()
{
	int i, j, x, y;
	srand((unsigned int)time(NULL));  //产生随机值
	x = rand() % 54 + 6;	//初始化珠宝坐标,要为10的倍数,否则无法对齐
	y = rand() % 45 + 10;
	Beads.Beadsxy.x = x * 10;
	Beads.Beadsxy.y = y * 10;
	Beads.symbol = 1;

	for (i = 0; i < snake.lenth; i++)
	{
		if (Beads.Beadsxy.x == snake.xy[i].x && Beads.Beadsxy.y == snake.xy[i].y)
		{
			x = rand() % 40 + 10;
			y = rand() % 50 + 10;
			Beads.Beadsxy.x = x * 10;
			Beads.Beadsxy.y = y * 10;
		}
	}
	for (j = 0; j < dragon.lenth; j++)
	{
		if ((Beads.Beadsxy.x == dragon.xy[j].x && Beads.Beadsxy.y == dragon.xy[j].y))
		{
			x = rand() % 40 + 10;
			y = rand() % 50 + 10;
			Beads.Beadsxy.x = x * 10;
			Beads.Beadsxy.y = y * 10;
		}
	}
	//珠宝不与龙蛇身重叠，如果有就重新生成一次珠宝
}
//初始化并产生珠宝

void DrawBeads()
{
	setfillcolor(COLORREF RGB(255, 192, 203));
	solidrectangle(Beads.Beadsxy.x, Beads.Beadsxy.y, Beads.Beadsxy.x + 10, Beads.Beadsxy.y + 10);
}
//OKOKOKOKOKOK  绘制珠宝

void Eatbeads()
{
	if (snake.xy[0].x == Beads.Beadsxy.x && snake.xy[0].y == Beads.Beadsxy.y)
	{
		snake.lenth++;
		snake.grade++;
		Beads.symbol = 0;
		snake.speed -= 3;
	}
	if (dragon.xy[0].x == Beads.Beadsxy.x && dragon.xy[0].y == Beads.Beadsxy.y)
	{
		dragon.lenth++;
		dragon.grade++;
		Beads.symbol = 0;
		dragon.speed -= 3;
	}

}
//吃猪功能

#endif 