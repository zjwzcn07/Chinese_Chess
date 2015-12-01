#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>
#include <conio.h>
#include<time.h>
/***
棋子结构体，Belong为红黑双方，Name_Digit为棋子名称量化
Name_Chi为中文，X_Background、Y_Background为背景坐标，X_Mat、
Y_Mat为棋盘矩阵坐标，ID为32棋身份识别
***/
struct Chess
{
	int Belong;
	int Name_Digit;
	char Name_Chi[1];
	int Alive;
	int X_Background;
	int Y_Background;
	int X_Mat;
	int Y_Mat;
	int ID;
	// int color;

}Pieces[32];
/***
一副棋，悔棋存录
***/
struct Stones
{
	Chess Ch[32];
	int Turn;
	Chess *Add[12][10];
};
/***
棋局读取记录
***/
struct Log
{
	int Pre_X;
	int Pre_Y;
	int Next_X;
	int Next_Y;
};


struct Chess *Address[12][10];
/***
车的走法，先判断是否直线，再判断是否线上有障碍
***/
int Rook(int x0, int y0, int x, int y)
{
	int i, a, b, k = 1;
	if (x - x0 != 0 && y - y0 != 0)
		return k = 0;
	a = x<x0 ? x : x0;
	b = x>x0 ? x : x0;
	for (i = a + 10; i<b; i += 10)
	if (Address[y / 4][i / 10] != NULL)
		return k = 0;
	a = y<y0 ? y : y0;
	b = y>y0 ? y : y0;
	for (i = 4 + a; i<b; i += 4)
	if (Address[i / 4][x / 10] != NULL)
		return k = 0;
	return k;
}
/***
炮的走法，先判断是否直线，再判断线上是否有棋子，
有则判断棋子数是否为一，且目的是否为敌人，无则判断
目的是否为空
***/
int Cannon(int x0, int y0, int x, int y, int be)
{
	int i, a, b, k = 1, n = 0;
	if (x - x0 == 0 && y - y0 == 0)
		return k = 1;
	if (x - x0 != 0 && y - y0 != 0)
		return k = 0;
	//  if(address[y/4][x/10]==NULL)
	{
		a = x<x0 ? x : x0;
		b = x>x0 ? x : x0;
		for (i = a + 10; i<b; i += 10)
		if (Address[y / 4][i / 10] != NULL)
			n++;
		a = y<y0 ? y : y0;
		b = y>y0 ? y : y0;
		for (i = 4 + a; i<b; i += 4)
		if (Address[i / 4][x / 10] != NULL)
			n++;
	}
	if (n != 0)
	{
		if (Address[y / 4][x / 10] == NULL)
			return k = 0;
		else
		if (n>1) return k = 0;
		else
		if ((*Address[y / 4][x / 10]).Belong == be)
			return k = 0;

	}
	if (n == 0)
	{
		if (Address[y / 4][x / 10] != NULL)
			return k = 0;
	}
	return k;
}
/***
兵的走法，先判断是否直线，然后判断红黑属性，在判断所在地域（敌我），
不同地域走法稍有差别。
***/
int Pawn(int x0, int y0, int x, int y, int be)
{
	int k = 1;
	if (x - x0 == 0 && y - y0 == 0)
		return k = 1;
	if (x - x0 != 0 && y - y0 != 0)
		return k = 0;
	if (be)
	{
		if (y0<24)
		{
			if (x - x0 != 0)
				return k = 0;
			else if (y - y0 != 4) return k = 0;
			else return k = 1;
		}
		else
		{
			if (abs(x - x0) == 10)
			{
				if (y - y0 != 0) return  k = 0;
				return 1;
			}
			if (abs(x - x0) == 0)
			{
				if (y - y0 != 4) return  k = 0;
				return 1;
			}
			return k = 0;
		}
	}
	else
	{
		if (y0>20)
		{
			if (x - x0 != 0)
				return k = 0;
			else if (y0 - y != 4) return k = 0;
			else return k = 1;
		}
		else
		{
			if (abs(x - x0) == 10)
			{
				if (y0 - y != 0) return  k = 0;
				return 1;
			}
			if (abs(x - x0) == 0)
			{
				if (y0 - y != 4) return  k = 0;
				return 1;
			}
			return k = 0;
		}
	}
}
/***
士的走法，先判断是否移动，移动是否为对角线，再判断红黑，
是否位于九宫格内
***/
int Bishop(int x0, int y0, int x, int y, int be)
{
	int k = 1;
	if (x - x0 == 0 && y - y0 == 0)
		return k = 1;
	if (!(abs(x - x0) == 10 && abs(y - y0) == 4))
		return k = 0;
	if (be)
	{
		if (y0<24)
		{
			if (x <= 30 || x >= 70 || y >= 16)
				return k = 0;
			else return k = 1;
		}
	}
	else
	{
		if (y0>20)
		{
			if (x <= 30 || x >= 70 || y <= 28)
				return k = 0;
			else return k = 1;
		}

	}
	return k = 1;
}
/***
帅的走法，判断是否直线，判断是否落子处是否为敌将，判断
是否走一步，且在九宫格内。
***/
int King(int x0, int y0, int x, int y, int be)
{
	int i, a, b, k = 1, n = 0;
	{
		a = x<x0 ? x : x0;
		b = x>x0 ? x : x0;
		for (i = a + 10; i<b; i += 10)
		if (Address[y / 4][i / 10] != NULL)
			n++;
		a = y<y0 ? y : y0;
		b = y>y0 ? y : y0;
		for (i = 4 + a; i<b; i += 4)
		if (Address[i / 4][x / 10] != NULL)
			n++;
	}
	if (x - x0 == 0 && y - y0 == 0)
		return k = 1;
	if (x - x0 != 0 && y - y0 != 0)
		return k = 0;
	if (be)
	{
		if (y0<24)
		{
			if ((Address[y / 4][x / 10] != NULL) && ((*Address[y / 4][x / 10]).ID == 16 && n == 0))
				return 1;
			if (abs(x - x0)>10 || abs(y - y0)>4)
				return k = 0;
			if (x <= 30 || x >= 70 || y >= 16)
				return k = 0;
		}
	}
	else
	{
		if (y0>20)
		{
			if ((Address[y / 4][x / 10] != NULL) && ((*Address[y / 4][x / 10]).ID == 0 && n == 0))
				return 1;
			if (abs(x - x0)>10 || abs(y - y0)>4)
				return k = 0;
			if (x <= 30 || x >= 70 || y <= 28)
				return k = 0;
		}

	}
	return k = 1;
}
/***
象的走法，是否走田字格，是否越界，是否有堵象眼
***/
int Minister(int x0, int y0, int x, int y, int be)
{
	int k = 1;
	if (x - x0 == 0 && y - y0 == 0)
		return k = 1;
	if (!(abs(x - x0) == 20 && abs(y - y0) == 8))
		return k = 0;
	if (be)
	{
		if (y0<24)
		{
			if (y>20)
				return k = 0;
		}
	}
	else
	{
		if (y0>20)
		{
			if (y < 24)
				return k = 0;
		}

	}
	if (Address[(y + y0) / 8][(x + x0) / 20] != NULL)
		return 0;
	return k = 1;
}
/***
马的走法，无脑的判断马脚，醉了%>_<%
***/
int Knight(int x0, int y0, int x, int y)
{
	int k = 1;
	if (x - x0 == 0 && y - y0 == 0)
		return k = 1;
	if (!((abs(x - x0) == 20 && abs(y - y0) == 4) || (abs(x - x0) == 10 && abs(y - y0) == 8)))
		return k = 0;
	if ((x - x0) == 20 && (y - y0) == 4)
	if (Address[(y0) / 4][(10 + x0) / 10] != NULL)
		return 0;
	else return 1;
	else if ((x - x0) == -20 && (y - y0) == -4)
	if (Address[(y0) / 4][(x0 - 10) / 10] != NULL)
		return 0;
	else
		return 1;
	else if ((x - x0) == -20 && (y - y0) == 4)
	if (Address[(y0) / 4][(x0 - 10) / 10] != NULL)
		return 0;
	else
		return 1;
	else if ((x - x0) == 20 && (y - y0) == -4)
	if (Address[(y0) / 4][(10 + x0) / 10] != NULL)
		return 0;
	else
		return 1;
	else if ((x - x0) == 10 && (y - y0) == 8)
	if (Address[(y0 + 4) / 4][(x0) / 10] != NULL)
		return 0;
	else
		return 1;
	else if ((x - x0) == -10 && (y - y0) == 8)
	if (Address[(y0 + 4) / 4][(x0) / 10] != NULL)
		return 0;
	else
		return 1;
	else if ((x - x0) == 10 && (y - y0) == -8)
	if (Address[(y0 - 4) / 4][(x0) / 10] != NULL)
		return 0;
	else
		return 1;
	else if ((x - x0) == -10 && (y - y0) == -8)
	if (Address[(y0 - 4) / 4][(x0) / 10] != NULL)
		return 0;
	else
		return 1;
	
}
