#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>
#include <conio.h>
#include<time.h>
/***
���ӽṹ�壬BelongΪ���˫����Name_DigitΪ������������
Name_ChiΪ���ģ�X_Background��Y_BackgroundΪ�������꣬X_Mat��
Y_MatΪ���̾������꣬IDΪ32�����ʶ��
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
һ���壬�����¼
***/
struct Stones
{
	Chess Ch[32];
	int Turn;
	Chess *Add[12][10];
};
/***
��ֶ�ȡ��¼
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
�����߷������ж��Ƿ�ֱ�ߣ����ж��Ƿ��������ϰ�
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
�ڵ��߷������ж��Ƿ�ֱ�ߣ����ж������Ƿ������ӣ�
�����ж��������Ƿ�Ϊһ����Ŀ���Ƿ�Ϊ���ˣ������ж�
Ŀ���Ƿ�Ϊ��
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
�����߷������ж��Ƿ�ֱ�ߣ�Ȼ���жϺ�����ԣ����ж����ڵ��򣨵��ң���
��ͬ�����߷����в��
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
ʿ���߷������ж��Ƿ��ƶ����ƶ��Ƿ�Ϊ�Խ��ߣ����жϺ�ڣ�
�Ƿ�λ�ھŹ�����
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
˧���߷����ж��Ƿ�ֱ�ߣ��ж��Ƿ����Ӵ��Ƿ�Ϊ�н����ж�
�Ƿ���һ�������ھŹ����ڡ�
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
����߷����Ƿ������ָ��Ƿ�Խ�磬�Ƿ��ж�����
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
����߷������Ե��ж���ţ�����%>_<%
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
