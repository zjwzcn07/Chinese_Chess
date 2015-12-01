#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>
#include <conio.h>
#include<time.h>
#include<stack>
#include<iostream>
#include"rule.h"
#include<queue>
#include <mmsystem.h> 
#pragma comment (lib, "winmm.lib")
using namespace std;
DWORD _stdcall ThrProc(LPVOID lpParameter);
HANDLE hThread = NULL;
int X, Y, X1, Y1, G;
//int turn=1;
char Welcome(int time);
void Draw();
void Gotoxy(int x, int y);
void HideCursor();
void DrawChess(struct Chess chess);
void ReadyPieces();
void DrawPieces();
void Cursor(int x, int y);
int ControlCursor(int turn);
void ClsPieces(int x, int y);
void RunGame();
int GameLoad();
int Result(int turn, int step);
void Check(int turn);
void Waring();
void Music();
void ReadMe();
void EmptyAdress();
/***
将悔棋存入栈
***/
stack<Stones>St;
/***
主程序
***/
int main()
{
	char cmd;
	int flag = 1,time=0;
	Music();
	while (flag)
	{
		HideCursor();
		cmd = Welcome(time);
		time = 1;
		system("cls");
		system("mode con cols=100 lines=50");
		//system("color E0");
		Music();

		if (cmd == '1')
		{
			EmptyAdress();
			Draw();
			ReadyPieces();
			RunGame();
		}

		else if (cmd == '2')
		{
			EmptyAdress();
			ReadyPieces();
			GameLoad();
		}
		else if (cmd == '3')
		{
			ReadMe();

		}
		else
			return 0;
		if (cmd != '3')
		Sleep(1000);
	}
	

	return 0;

}

/***
棋子初始化
***/
void ReadyPieces()
{
	int i;
	for (i = 0; i<16; i++)
	{
		Pieces[i].Belong = 1;
		Pieces[i].Name_Digit = i;
		Pieces[i].ID = i;
		Pieces[i].Alive = 1;
		switch (Pieces[i].Name_Digit)
		{
		case 0:Pieces[i].X_Background = 10 + 40, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "帅"); break;
		case 1:Pieces[i].X_Background = 10 + 30, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "士"); break;
		case 2:Pieces[i].X_Background = 10 + 50, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "士"); break;
		case 3:Pieces[i].X_Background = 10 + 20, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "相"); break;
		case 4:Pieces[i].X_Background = 10 + 60, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "相"); break;
		case 5:Pieces[i].X_Background = 10 + 0, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "车"); break;
		case 6:Pieces[i].X_Background = 10 + 80, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "车"); break;
		case 7:Pieces[i].X_Background = 10 + 10, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "马"); break;
		case 8:Pieces[i].X_Background = 10 + 70, Pieces[i].Y_Background = 4; strcpy(Pieces[i].Name_Chi, "马"); break;
		case 9:Pieces[i].X_Background = 10 + 10, Pieces[i].Y_Background = 12; strcpy(Pieces[i].Name_Chi, "炮"); break;
		case 10:Pieces[i].X_Background = 10 + 70, Pieces[i].Y_Background = 12; strcpy(Pieces[i].Name_Chi, "炮"); break;
		case 11:Pieces[i].X_Background = 10, Pieces[i].Y_Background = 16; strcpy(Pieces[i].Name_Chi, "兵"); break;
		case 12:Pieces[i].X_Background = 30, Pieces[i].Y_Background = 16; strcpy(Pieces[i].Name_Chi, "兵"); break;
		case 13:Pieces[i].X_Background = 50, Pieces[i].Y_Background = 16; strcpy(Pieces[i].Name_Chi, "兵"); break;
		case 14:Pieces[i].X_Background = 70, Pieces[i].Y_Background = 16; strcpy(Pieces[i].Name_Chi, "兵"); break;
		case 15:Pieces[i].X_Background = 90, Pieces[i].Y_Background = 16; strcpy(Pieces[i].Name_Chi, "兵"); break;
		}
		Pieces[i].X_Mat = Pieces[i].X_Background / 10;
		Pieces[i].Y_Mat = Pieces[i].Y_Background / 4;
		Address[Pieces[i].Y_Mat][Pieces[i].X_Mat] = &Pieces[i];
	}
	for (i = 16; i<32; i++)
	{
		Pieces[i].Belong = 0;
		Pieces[i].Name_Digit = i - 16;
		Pieces[i].ID = i;
		Pieces[i].Alive = 1;
		Pieces[i].X_Mat = Pieces[i].X_Background / 10;
		Pieces[i].Y_Mat = Pieces[i].X_Background / 4;
		switch (Pieces[i].Name_Digit)
		{
		case 0:Pieces[i].X_Background = 10 + 40, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "將"); break;
		case 1:Pieces[i].X_Background = 10 + 30, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "仕"); break;
		case 2:Pieces[i].X_Background = 10 + 50, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "仕"); break;
		case 3:Pieces[i].X_Background = 10 + 20, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "象"); break;
		case 4:Pieces[i].X_Background = 10 + 60, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "象"); break;
		case 5:Pieces[i].X_Background = 10 + 0, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "車"); break;
		case 6:Pieces[i].X_Background = 10 + 80, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "車"); break;
		case 7:Pieces[i].X_Background = 10 + 10, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "馬"); break;
		case 8:Pieces[i].X_Background = 10 + 70, Pieces[i].Y_Background = 4 + 36; strcpy(Pieces[i].Name_Chi, "馬"); break;
		case 9:Pieces[i].X_Background = 10 + 10, Pieces[i].Y_Background = 12 + 20; strcpy(Pieces[i].Name_Chi, "砲"); break;
		case 10:Pieces[i].X_Background = 10 + 70, Pieces[i].Y_Background = 12 + 20; strcpy(Pieces[i].Name_Chi, "砲"); break;
		case 11:Pieces[i].X_Background = 10, Pieces[i].Y_Background = 16 + 12; strcpy(Pieces[i].Name_Chi, "卒"); break;
		case 12:Pieces[i].X_Background = 30, Pieces[i].Y_Background = 16 + 12; strcpy(Pieces[i].Name_Chi, "卒"); break;
		case 13:Pieces[i].X_Background = 50, Pieces[i].Y_Background = 16 + 12; strcpy(Pieces[i].Name_Chi, "卒"); break;
		case 14:Pieces[i].X_Background = 70, Pieces[i].Y_Background = 16 + 12; strcpy(Pieces[i].Name_Chi, "卒"); break;
		case 15:Pieces[i].X_Background = 90, Pieces[i].Y_Background = 16 + 12; strcpy(Pieces[i].Name_Chi, "卒"); break;
		}
		Pieces[i].X_Mat = Pieces[i].X_Background / 10;
		Pieces[i].Y_Mat = Pieces[i].Y_Background / 4;
		Address[Pieces[i].Y_Mat][Pieces[i].X_Mat] = &Pieces[i];
	}
}
/***
画棋盘。。。真是个体力活
***/
void Draw()
{
	int i, j = 0, k = 0, h, x = 10 + 0, y = 4;
	Gotoxy(x, y);
	printf("┏");
	for (i = 0; i<38; i++)
	{
		j++;
		if (j == 5)
		{
			printf("┳");
			j = 0;
		}

		else
			printf("━");
	}
	printf("━");
	printf("┓");
	for (j = 0; j<8; j++)
	{
		y++;
		Gotoxy(x, y);
		if (j == 4)
		{
			for (h = 0; h<3; h++)
			{
				printf("┃");
				if (h == 1)
					printf("%25c河%24c界%25c", ' ', ' ', ' ');
				else
					printf("%78c", ' ');//9+1
				printf("┃");
				y++;
				Gotoxy(x, y);
			}
			k = 0;
			printf("┣");
			for (i = 0; i<38; i++)
			{
				k++;
				if (k == 5)
				{
					printf("┳");
					k = 0;
				}

				else
					printf("━");
			}
			printf("━┫");
			y++;
			Gotoxy(x, y);
		}
		for (h = 0; h<3; h++)
		{
			printf("┃");
			for (k = 0; k<8; k++)
				printf("        ┃");//9+1
			y++;
			Gotoxy(x, y);
		}
		printf("┣");
		k = 0;
		for (i = 0; i<38; i++)
		{
			k++;
			if (k == 5)
			{
				printf("╋");
				k = 0;
			}

			else
				printf("━");
		}
		printf("━");
		printf("┫");
	}
	for (x = 10 + 31, y = 4; x<40, y<8; x += 2, y++)
	{
		Gotoxy(x, y); printf("╲");
	}
	for (x = 10 + 41, y = 8; y<13; x += 2, y++)
	{
		Gotoxy(x, y); printf("╲");
	}
	for (x = 10 + 50, y = 4; y<8; x -= 2, y++)
	{
		Gotoxy(x, y); printf("╱");
	}
	for (x = 10 + 39, y = 8; y<13; x -= 2, y++)
	{
		Gotoxy(x, y); printf("╱");
	}
	Gotoxy(50, 8); printf("╳");

	for (x = 10 + 31, y = 32; x<40, y<8 + 28; x += 2, y++)
	{
		Gotoxy(x, y); printf("╲");
	}
	for (x = 10 + 41, y = 36; y<13 + 28; x += 2, y++)
	{
		Gotoxy(x, y); printf("╲");
	}
	for (x = 10 + 50, y = 32; y<8 + 28; x -= 2, y++)
	{
		Gotoxy(x, y); printf("╱");
	}
	for (x = 10 + 39, y = 36; y<13 + 28; x -= 2, y++)
	{
		Gotoxy(x, y); printf("╱");
	}
	Gotoxy(50, 36); printf("╳");
}
/***
画单个棋子
***/
void DrawChess(struct Chess chess)
{
	int x = chess.X_Background;
	int y = chess.Y_Background;
	if (chess.Belong)
	{
		Gotoxy(x - 2, y); printf("┃%s┃", chess.Name_Chi);
		Gotoxy(x - 2, y - 1); printf("┏━");
		Gotoxy(x + 2, y - 1); printf("┓");
		Gotoxy(x - 2, y + 1); printf("┗━");
		Gotoxy(x + 2, y + 1); printf("┛");
	}
	else
	{
		Gotoxy(x - 2, y); printf("┃%s┃", chess.Name_Chi);
		Gotoxy(x - 2, y - 1); printf("  ─");
		// Gotoxy(x+2,y-1);printf("╮");
		Gotoxy(x - 2, y + 1); printf("╰━");
		Gotoxy(x + 2, y + 1); printf("╯");
	}

}
/***
画32粒棋子
***/
void DrawPieces()
{
	int i;
	for (i = 0; i<32; i++)
	if (Pieces[i].Alive)
		DrawChess(Pieces[i]);
}
/***
显示光标
***/
void Cursor(int x, int y)
{
	Gotoxy(x - 3, y - 2); printf("╔");
	Gotoxy(x + 3, y - 2); printf("╗");
	Gotoxy(x - 3, y + 2); printf("╚");
	Gotoxy(x + 3, y + 2); printf("╝");
}
/***
输出坐标
***/
void Gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/***
隐藏光标
***/
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/***
清除棋子
***/
void ClsPieces(int x, int y)
{
	Gotoxy(x, y); printf("●");
	Gotoxy(x - 2, y - 1); printf("  ");
	Gotoxy(x + 2, y - 1); printf("  ");
	Gotoxy(x - 2, y + 1); printf("  ");
	Gotoxy(x + 2, y + 1); printf("  ");
}
/***
游戏流程
***/
int ControlCursor(int turn)
{
	int a, b, c, d, p, q, w;
	static int x1 = 10, x2 = 10, x = 10, y1 = 4, y2 = 4, y = 4;
	int flag, flag1 = 1;
	G = 0;
	Cursor(x, y);
	while (1)
	{
		a = _getch(); Gotoxy(12, 22); printf("%25c河%24c界%25c", ' ', ' ', ' ');//上下左右方向键控制，空格键提放棋子
		switch (a)
		{

		case 224: b = _getch();
			switch (b)
			{
			case 77:if (x == 90) break;
					else
					{
						Gotoxy(x - 3, y - 2); printf("  ");
						Gotoxy(x + 3, y - 2); printf("  ");
						Gotoxy(x - 3, y + 2); printf("  ");
						Gotoxy(x + 3, y + 2); printf("  ");
						x = x + 10;
						Cursor(x, y);
					}break;
			case 75:if (x == 10) break;
					else
					{
						Gotoxy(x - 3, y - 2); printf("  ");
						Gotoxy(x + 3, y - 2); printf("  ");
						Gotoxy(x - 3, y + 2); printf("  ");
						Gotoxy(x + 3, y + 2); printf("  ");
						x = x - 10;
						Cursor(x, y);
					}break;
			case 72:if (y == 4) break;
					else
					{
						Gotoxy(x - 3, y - 2); printf("  ");
						Gotoxy(x + 3, y - 2); printf("  ");
						Gotoxy(x - 3, y + 2); printf("  ");
						Gotoxy(x + 3, y + 2); printf("  ");
						y -= 4;
						Cursor(x, y);
					}break;
			case 80:if (y == 40) break;
					else
					{
						Gotoxy(x - 3, y - 2); printf("  ");
						Gotoxy(x + 3, y - 2); printf("  ");
						Gotoxy(x - 3, y + 2); printf("  ");
						Gotoxy(x + 3, y + 2); printf("  ");
						y += 4;
						Cursor(x, y);
					}
			}break;
		case 32:
			if (Address[y / 4][x / 10] == NULL)
				break;
			p = (*Address[y / 4][x / 10]).Belong;
			if (p != turn) break;

			x2 = x1 = X = x;
			y2 = y1 = Y = y;
			X1 = x;
			Y1 = y;
		lable1:      hThread = CreateThread(NULL, 0, ThrProc, NULL, 0, NULL);//开始另一段线程
			while (1)
			{
				c = _getch();

				if (c == 224)
				{
					d = _getch();//获取下一段位置
					switch (d)
					{
					case 77:if (x == 90) break;
							else
							{
								Gotoxy(x - 3, y - 2); printf("  ");
								Gotoxy(x + 3, y - 2); printf("  ");
								Gotoxy(x - 3, y + 2); printf("  ");
								Gotoxy(x + 3, y + 2); printf("  ");
								x = x + 10;
								Cursor(x, y);
								X = x;
								Y = y;
							}break;
					case 75:if (x == 10) break;
							else
							{
								Gotoxy(x - 3, y - 2); printf("  ");
								Gotoxy(x + 3, y - 2); printf("  ");
								Gotoxy(x - 3, y + 2); printf("  ");
								Gotoxy(x + 3, y + 2); printf("  ");
								x = x - 10;
								Cursor(x, y);
								X = x;
								Y = y;
							}break;
					case 72:if (y == 4) break;
							else
							{
								Gotoxy(x - 3, y - 2); printf("  ");
								Gotoxy(x + 3, y - 2); printf("  ");
								Gotoxy(x - 3, y + 2); printf("  ");
								Gotoxy(x + 3, y + 2); printf("  ");
								y -= 4;
								Cursor(x, y);
								X = x;
								Y = y;
							}break;
					case 80:if (y == 40) break;
							else
							{
								Gotoxy(x - 3, y - 2); printf("  ");
								Gotoxy(x + 3, y - 2); printf("  ");
								Gotoxy(x - 3, y + 2); printf("  ");
								Gotoxy(x + 3, y + 2); printf("  ");
								y += 4;
								Cursor(x, y);
								X = x;
								Y = y;
							}
					}
				}
				if (c == 32)
				{
					TerminateThread(hThread, 0);							//停止线程
					CloseHandle(hThread);
					hThread = NULL;
					Cursor(x, y);
					flag = (*Address[y2 / 4][x2 / 10]).Name_Digit;			//获取棋子类别
					switch (flag)
					{
					case 0:flag1 = King(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 1:flag1 = Bishop(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 2:flag1 = Bishop(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 3:flag1 = Minister(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 4:flag1 = Minister(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 5:flag1 = Rook(x2, y2, x, y); break;
					case 6:flag1 = Rook(x2, y2, x, y); break;
					case 7:flag1 = Knight(x2, y2, x, y); break;
					case 8:flag1 = Knight(x2, y2, x, y); break;
					case 9:flag1 = Cannon(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 10:flag1 = Cannon(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 11:flag1 = Pawn(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 12:flag1 = Pawn(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 13:flag1 = Pawn(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 14:flag1 = Pawn(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					case 15:flag1 = Pawn(x2, y2, x, y, (*Address[y2 / 4][x2 / 10]).Belong); break;
					default:break;
					}
					/*
					若下子失败，则重新下子
					*/
					if (flag1 == 0)
					{
						goto lable1;
					}
					/*
					判断目标是否有子，为敌为友，落子成功，更新信息
					*/
					(*Address[y1 / 4][x1 / 10]).X_Background = x;
					(*Address[y1 / 4][x1 / 10]).Y_Background = y;
					if (Address[y / 4][x / 10] != NULL)
					{
						p = (*Address[y2 / 4][x2 / 10]).ID;
						q = (*Address[y / 4][x / 10]).ID;
						w = (*Address[y / 4][x / 10]).Belong;
						if (p == q)
						{
							(*Address[y / 4][x / 10]).Alive = 1;
							G = 1;
						}
						else if (w == turn)
						{
							(*Address[y1 / 4][x1 / 10]).X_Background = x2;
							(*Address[y1 / 4][x1 / 10]).Y_Background = y2;
							goto lable1;
						}
						else
							(*Address[y / 4][x / 10]).Alive = 0;
					}
					Address[y / 4][x / 10] = Address[y1 / 4][x1 / 10];
					if (G != 1)Address[y1 / 4][x1 / 10] = NULL;
					system("cls");
					Draw();
					DrawPieces();
					Cursor(x, y);
					goto lable;
					break;
				}
			}
			break;

		default:break;

		}
	}
lable:;
	return G;
}
/***
开始游戏,并且附有悔棋功能
***/
void RunGame()
{
	FILE *fout = fopen("棋局.out", "a+");///////棋局记录
	fprintf(fout, "该局结果\n");
	int step = 0;
	int  a = 0;
	int turn = 1;
Undo_label:	DrawPieces();
	while (1)
	{
		if (step <= 0)//将第一步棋存入栈
		{
			Stones Ori;
			Ori.Turn = turn;
			for (int i = 0; i<32; i++)
			{
				Pieces[i].X_Mat = Pieces[i].X_Background / 10;
				Pieces[i].Y_Mat = Pieces[i].Y_Background / 4;
				Ori.Ch[i] = Pieces[i];
			}

			Gotoxy(0, 25);

			for (int i = 0; i<12; i++)
			for (int j = 0; j<10; j++)
				Ori.Add[i][j] = Address[i][j];
			printf("\n");
			St.push(Ori);
		}

		Gotoxy(30, 47);
		printf("悔棋请按0，退到主界面按esc（移动方向键时无效）否则按任意键继续");
		char cmd;
		cmd = _getch();
		if (cmd == 27)
			return ;
		if (cmd == '0')//弹栈，更新棋子信息
		{
			step--;
			system("cls");
			Draw();
			Stones New;
			New = St.top();
			turn = New.Turn;
			for (int i = 0; i<32; i++)
				Pieces[i] = New.Ch[i];
			for (int i = 0; i<12; i++)
			for (int j = 0; j<10; j++)
				Address[i][j] = New.Add[i][j];
			char Party[1];
			if (turn)
				strcpy(Party, "红");
			else
				strcpy(Party, "黑");
			fprintf(fout, "%s悔棋啦\n", Party);
			St.pop();
			goto Undo_label;



			//goto pre_label;
		}
		else
		{
			//	step++;
			Stones Ori;//进栈
			Ori.Turn = turn;
			for (int i = 0; i<32; i++)
			{
				Pieces[i].X_Mat = Pieces[i].X_Background / 10;
				Pieces[i].Y_Mat = Pieces[i].Y_Background / 4;
				Ori.Ch[i] = Pieces[i];
			}
			/***
			找出移动过的棋子，记录走法
			***/
			Stones Pre = St.top();
			for (int i = 0; i<32; i++)
			{
				int x = Pre.Ch[i].X_Mat;
				int y = Pre.Ch[i].Y_Mat;
				int xx = Pieces[i].X_Mat;
				int yy = Pieces[i].Y_Mat;
				if (xx != x || yy != y)
				{
					char Party[1];
					if (Pieces[i].Belong)
						strcpy(Party, "红");
					else
						strcpy(Party, "黑");
					fprintf(fout, "第%d步%s%s X:%d Y:%d —>X:%d Y:%d\n", step, Party, Pieces[i].Name_Chi, x, y, Pieces[i].X_Mat, Pieces[i].Y_Mat);
					break;
				}
			}
			for (int i = 0; i<12; i++)
			for (int j = 0; j<10; j++)
				Ori.Add[i][j] = Address[i][j];
			St.push(Ori);

		}
		a = Result(turn, step);
		if (a == 2 || a == 1)
			break;
		G = ControlCursor(turn);

		step++;
		Check(turn);

		if (G)
		{
			G = 0;
			continue;
		}
		if (turn == 1)turn = 0;
		else turn = 1;




		a = Result(turn, step);
		if (a == 2 || a == 1)
			break;
	}
}
/***
胜负判断，走棋判断
***/
int Result(int turn, int step)
{
	FILE *fout = fopen("棋局.out", "a+");
	//fprintf(fout, "总计%d步", step);
	if (turn)
	{
		Gotoxy(40, 45);
		printf("帅     的     人     走				已走了%d步", step);

	}
	else
	{
		Gotoxy(40, 45);
		printf("为     将     者     走				已走了%d步", step);

	}
	if (Pieces[0].Alive == 0)
	{
		Gotoxy(40, 45);
		printf("方     败     圆     胜!,		 	总计%d步", step);
		fprintf(fout, "将赢啦!!!\n");
		return 2;
	}
	if (Pieces[16].Alive == 0)
	{
		Gotoxy(40, 45);
		printf("圆     败     方     胜!,		 	总计%d步", step);
		fprintf(fout, "帅的人赢啦啦\n");
		return 1;
	}
	return 0;
}
/***
线程控制，实现闪烁
***/
DWORD _stdcall ThrProc(LPVOID lpParameter)
{
	while (1)
	{
		DrawChess(*Address[Y1 / 4][X1 / 10]);
		Cursor(X, Y);
		Sleep(500);
		Gotoxy(X - 3, Y - 2); printf("  ");
		Gotoxy(X + 3, Y - 2); printf("  ");
		Gotoxy(X - 3, Y + 2); printf("  ");
		Gotoxy(X + 3, Y + 2); printf("  ");
		ClsPieces((*Address[Y1 / 4][X1 / 10]).X_Background, (*Address[Y1 / 4][X1 / 10]).Y_Background);
		Sleep(500);
	}

	return 0;
}
/***
介绍界面
***/
char Welcome(int time)//time指是否第一次打开游戏，第一次打开则出现加载页面
{
	if (time == 0)
	{
		Gotoxy(27, 10);
		printf("中国象棋 \n");
		//Gotoxy(20, 11);
		//printf("作者：14010410051 胡智欣、14010520007 游齐恒 \n");
		Gotoxy(25, 12);
		printf("努力加载中，请稍候");
		int second;
		for (second = 0; second<10; second++)
		{
			printf(".");
			Sleep(100);
		}
		printf("\n");
		printf("%16c", ' ');
		int s, ii;
		for (s = 0, ii = 0; s<16; s++, ii++)
		{
			printf("▇");
			switch (ii % 8)
			{
			case 1:system("color 1"); break;
			case 2:system("color 2"); break;
			case 3:system("color 6"); break;
			case 4:system("color C"); break;
			case 5:system("color 1"); break;
			case 6:system("color 2"); break;
			case 7:system("color 6"); break;
			case 8:system("color C"); break;
			}
			Sleep(300);
		}
		Sleep(1000);
		system("color 0F");
		system("cls");
	}
	system("cls");
	Gotoxy(20, 10);
	{
		printf("中国象棋（方向键移动，空格键选取）");
		Gotoxy(26, 14);
		printf("1.双人对战");
		Gotoxy(26, 16);
		printf("2.观看棋局");
		Gotoxy(26, 18);
		printf("3.游戏介绍");
		Gotoxy(26, 20);
		printf("4.退出游戏");
		/***
		设置箭头坐标，通过上下移动增减pos值，而后对8取模，即是定位
		****/
		int cmd = 0;
		int pos = 0;
		Gotoxy(23, 14);
		printf("-->");
		while (cmd!=1&&cmd!=2&&cmd!=3&&cmd!=4)
		{
			int fir;
			fir = _getch();
			switch (fir)
			{
			case 224:
				int sec;
				sec = _getch();
				switch (sec)
				{
				case 72:pos-=2; Gotoxy(23, (pos + 2) % 8 + 14); printf("   "); Gotoxy(23, pos % 8 + 14); printf("-->"); break;
				case 80:pos+=2; Gotoxy(23, (pos - 2) % 8 + 14); printf("   "); Gotoxy(23, pos % 8 + 14); printf("-->"); break;
				default:
					break;
				}break;
			case 32:cmd = pos % 8 / 2 + 1; break;
			default:
				break;
			}
		}
		
		
		char command = cmd + '0';
		
		return command;
	}
}
/***
将军时警告界面
***/
void Check(int turn)
{
	if (turn)
	{
		int X_Mat = Pieces[16].X_Mat, Y_Mat = Pieces[16].Y_Mat;
		int X_Back = Pieces[16].X_Background, Y_Back = Pieces[16].Y_Background;
		int i, flag1 = 0;
		for (i = 0; i<16; i++)
		{
			if (Pieces[i].Alive == 0)
				continue;
			int flag;
			int X0_Mat = Pieces[i].X_Mat, Y0_Mat = Pieces[i].Y_Mat;
			int X0_Back = Pieces[i].X_Background, Y0_Back = Pieces[i].Y_Background;
			flag = (Pieces[i]).Name_Digit;
			switch (flag)
			{
			case 0:flag1 = King(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 1:flag1 = Bishop(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 2:flag1 = Bishop(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 3:flag1 = Minister(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 4:flag1 = Minister(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 5:flag1 = Rook(X0_Back, Y0_Back, X_Back, Y_Back); break;
			case 6:flag1 = Rook(X0_Back, Y0_Back, X_Back, Y_Back); break;
			case 7:flag1 = Knight(X0_Back, Y0_Back, X_Back, Y_Back); break;
			case 8:flag1 = Knight(X0_Back, Y0_Back, X_Back, Y_Back); break;
			case 9:flag1 = Cannon(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 10:flag1 = Cannon(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 11:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 12:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 13:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 14:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			case 15:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 1); break;
			default:break;
			}
			if (flag1)
			{
				Waring();
				Gotoxy(40, 48);
				printf("%s要将军了", Pieces[i].Name_Chi);
				Sleep(1000);
				break;
			}
		}

	}
	else
	{
		int X_Mat = Pieces[0].X_Mat, Y_Mat = Pieces[0].Y_Mat;
		int X_Back = Pieces[16].X_Background, Y_Back = Pieces[0].Y_Background;
		int i, flag1 = 0;
		for (i = 16; i<32; i++)
		{
			int flag;
			int X0_Mat = Pieces[i].X_Mat, Y0_Mat = Pieces[i].Y_Mat;
			int X0_Back = Pieces[i].X_Background, Y0_Back = Pieces[i].Y_Background;
			flag = (Pieces[i]).Name_Digit;
			switch (flag)
			{
			case 0:flag1 = King(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 1:flag1 = Bishop(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 2:flag1 = Bishop(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 3:flag1 = Minister(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 4:flag1 = Minister(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 5:flag1 = Rook(X0_Back, Y0_Back, X_Back, Y_Back); break;
			case 6:flag1 = Rook(X0_Back, Y0_Back, X_Back, Y_Back); break;
			case 7:flag1 = Knight(X0_Back, Y0_Back, X_Back, Y_Back); break;
			case 8:flag1 = Knight(X0_Back, Y0_Back, X_Back, Y_Back); break;
			case 9:flag1 = Cannon(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 10:flag1 = Cannon(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 11:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 12:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 13:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 14:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			case 15:flag1 = Pawn(X0_Back, Y0_Back, X_Back, Y_Back, 0); break;
			default:break;
			}
			if (flag1)
			{
				Waring();
				break;
			}
		}

	}

}
void Waring()
{
	int s;
	for (s = 0; s <= 2; s++)
	{
		{
			system("color 0C");
			Sleep(500);
			system("color 0F");
			Sleep(500);
		}

	}
}
/***
载入内置棋局
***/
int GameLoad()
{
	system("cls");
	Gotoxy(40, 20);
	printf("棋谱选择");
	Gotoxy(40, 22);
	printf("1.胡荣华胜杨官璘（1964年）");
	Gotoxy(40, 24);
	printf("2.雷法耀和黄松轩（仙人指路）");
	FILE *fin;
	while (1)
	{
		char decison;
		decison = _getch();
		if (decison == '1')
		{
			fin = fopen("棋谱.in", "r");
			if (fin == NULL)
			{
				printf("请准确放入棋谱位置\n");
				return 0;
			}break;
		}
		else if (decison == '2')
		{
			fin = fopen("棋谱1.in", "r");
			if (fin == NULL)
			{
				printf("\n请准确放入棋谱位置\n");
				return 0;
			}break;
		}


	}
	Draw();
	DrawPieces();
	/***
	将棋局从文件读入到队列
	***/
	queue<Log>Que;
	char chat[30];
	int step;
	int Sumstep = 0;
	fscanf(fin, "%s", chat);//获取该棋局信息
	Gotoxy(1, 1);
	printf("%s", chat);
	fscanf(fin, "%d", &step);
	int i;
	for (i = 0; i < step; i++)
	{
		fscanf(fin, "\n%s", chat);
		Log StepWork;
		fscanf(fin, "\nX:%d Y:%d —>X:%d Y:%d", &StepWork.Pre_X, &StepWork.Pre_Y, &StepWork.Next_X, &StepWork.Next_Y);
		Que.push(StepWork);
	}
	//puts("\nok4");
	char CharEnd[30];
	fscanf(fin, "\n%s", CharEnd);
	fclose(fin);
	DrawPieces();
	//puts("ok3");
	int cmd;
	
	while (1)
	{
		Gotoxy(40, 43);
		printf("返回主菜单请按esc");
		cmd = _getch();
		if (cmd == 27)
			return 0;
		if (cmd == 224)
		{
			int cmd1;
			cmd1 = _getch();
			switch (cmd1)
			{
			case 77:
			{
					   /***
					   出队，并更新棋盘矩阵位置和棋子信息
					   ***/
					   Log STEP = Que.front();
					   Sumstep = ~Sumstep;
					   Check(1);
					   Check(0);
					   int pre_x = STEP.Pre_X, pre_y = STEP.Pre_Y, next_x = STEP.Next_X, next_y = STEP.Next_Y;
					   if (Address[next_y][next_x] != NULL)
						   (*Address[next_y][next_x]).Alive = 0;
					   (*Address[pre_y][pre_x]).X_Background = (next_x)* 10;
					   (*Address[pre_y][pre_x]).Y_Background = (next_y)* 4;
					   (*Address[pre_y][pre_x]).X_Mat = next_x;
					   (*Address[pre_y][pre_x]).Y_Mat = next_y;
					   Address[next_y][next_x] = (Address[pre_y][pre_x]);
					   Address[pre_y][pre_x] = NULL;
					   system("cls");
					   Draw();
					   DrawPieces();
					   if (Sumstep)
					   {
						   Gotoxy(40, 45);
						   printf("帅     的     人     走!\n");
						   printf("红%s X:%d Y:%d——>X:%d Y:%d", (*Address[next_y][next_x]).Name_Chi, pre_x, pre_y, next_x, next_y);
					   }
					   else
					   {
						   Gotoxy(40, 45);
						   printf("为     将     者     走!\n");
						   printf("黑%s X:%d Y:%d——>X:%d Y:%d", (*Address[next_y][next_x]).Name_Chi, pre_x, pre_y, next_x, next_y);
					   }
					   Que.pop();
					   {
						   if (Pieces[0].Alive == 0)
						   {
							   Gotoxy(40, 45);
							   printf("方     败     圆     胜!");
							   return 1;
						   }
						   if (Pieces[16].Alive == 0)
						   {
							   Gotoxy(40, 45);
							   printf("圆     败     方     胜!");
							   return 1;
						   }
						   if (Que.empty())
						   {
							   Gotoxy(37, 20);
							   printf("%s", CharEnd);
							   return 1;
						   }
					   }
			}
			default:
				break;
			}
		}

	}
}
/****
播放音乐
****/
void Music()
{
	mciSendString(L"open 渔舟唱晚.mp3 alias betabin", NULL, 0, NULL);
	mciSendString(L"play betabin repeat", NULL, 0, NULL);


}
/***
游戏介绍
***/
void ReadMe()
{
	system("cls");
	FILE *read = fopen("Readme.txt", "r");
	if (read == NULL)
	{
		printf("请将Readme.txt放于和exe文件同一路径");
		Sleep(300);
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		char A[50];
		fscanf(read, "%s", A);
		puts(A);
	}
	printf("按任意键返回主菜单\n");
	_getch();
}
/***
置空棋盘信息
***/
void EmptyAdress()
{
	int i, j;
	for (i = 0; i < 12;i++)
	for (j = 0; j < 10; j++)
		Address[i][j] = NULL;
}