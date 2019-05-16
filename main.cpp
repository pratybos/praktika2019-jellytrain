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
		for(int j = a_y; i < b_y; j++)
		{
			gotoxy(i,j); printf(" ");
		}
	}
}




int main()
{
	cout << "Hello" << endl;

	return 0;
}