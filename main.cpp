#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <list>


using namespace std;

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

//ledzi judeti teminate naudojant kordinates
void gotoxy(int x, int y)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPOS;
	dwPOS.X = x; //pradeda nuo 0;
	dwPOS.Y = y; //pradeda nuo 0;

	SetConsoleCursorPosition(hCon, dwPOS);
}

void HideCursor()
{//paslepia cursoriu
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = false;
}

void DrawWhiteSpace(int a_x, int a_y, int b_x, int b_y)
{//padaryti specialia vieta terminate, baltos spalvos, kad galima butu matyti kur vykst visas zaidimas
	for(int i = a_x; i < b_x; i++)
	{
		for(int j = a_y; j < b_y; j++)
		{
			gotoxy(i,j); printf(" ");
		}
	}
}

void DrawWindowFrame(int a_x, int a_y, int b_x, int b_y)
{
	DrawWhiteSpace(a_x, a_y, b_x, b_y);
	for(int i = a_x; i < b_x; i++)
	{
		gotoxy(i, a_y); printf("%c",205);
		gotoxy(i, b_y); printf("%c",205);
	}
	for(int i = a_y; i < b_y; i++)
	{
		gotoxy(a_x, i); printf("%c",186);
		gotoxy(b_x, i); printf("%c",186);
	}
	gotoxy(a_x, a_y); printf("%c", 201);
	gotoxy(b_x, a_y); printf("%c", 187);
	gotoxy(a_x, b_y); printf("%c", 200);
	gotoxy(b_x, b_y); printf("%c", 188);
}

void DrawGameLimits()
{//nupesia zaidimo limitus, ten kur reikia, o ko nereikia nepiesia
	DrawWindowFrame(1,2,79,23);
	gotoxy(2,1); printf("Gyvybes: ");
	gotoxy(25,1); printf("Energija: ");
	gotoxy(56,1); printf("Taskai: ");
}

void WelcomeMessage()
{ // The main title, I tried to center it as best as I could
int x = 13;
int y = 6;
gotoxy(x, y  ); printf(" _____                    _____ _           _           ");
gotoxy(x, y+1); printf("|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ");
gotoxy(x, y+2); printf("|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|");
gotoxy(x, y+3); printf("|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ");
gotoxy(x, y+4); printf("      |_|");
gotoxy(x, y+6); printf("        Spauskite space norint pradeti zaisti           ");
gotoxy(x, y+7); printf("                                                        ");
}


int main()
{
	DrawGameLimits();
	WelcomeMessage();
	while(true)
	{

	}
	return 0;
}