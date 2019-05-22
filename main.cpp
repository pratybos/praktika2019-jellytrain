#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <list>
#include <iostream>
#include <fstream>


using namespace std;

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

string vardas;
int a;
int b;
string line;
int pasirinkimas;
int store;
int hp = 3;
int energy = 5;
int score;



bool levels[5] = {false,false,false,false,false};

//ledzi judeti teminate naudojant kordinates
void gotoxy(int x, int y)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x; //pradeda nuo 0;
	dwPos.Y = y; //pradeda nuo 0;

	SetConsoleCursorPosition(hCon, dwPos);
}

void HideCursor()
{//paslepia cursoriu
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = false;
	SetConsoleCursorInfo(hCon,&cci);
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
	gotoxy(2,1); printf("HP:");
	gotoxy(16,1); printf("Energy:");
	gotoxy(50,1); printf("SCORE:");
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

void GameOverDefeatMessage()
{
	int a_x = 30;
	int a_y = 11;
	int b_x = a_x + 23;
	int b_y = a_y + 4;
	DrawWindowFrame(a_x,a_y,b_x,b_y);
	gotoxy(a_x+1,a_y+2); printf("      You lost...");
}

void GameOverVictoryMessage()
{
	int a_x = 30;
	int a_y = 11;
	int b_x = a_x + 23;
	int b_y = a_y + 4;
	DrawWindowFrame(a_x,a_y,b_x,b_y);
	gotoxy(a_x+1,a_y+2); printf("       LEVEL DONE");
}

class SpaceShip
{
private:
	int x; // x kordinates
	int y; // y kordinates
	bool imDead; // ar laivas yra mires?
public:
	int X() {return x;}
	int Y() {return y;}
	int HP() {return hp;}

bool isDead()
{
	DrawSpaceShipInfo();
	return imDead;
}


SpaceShip(int _x, int _y)
{
	x = _x;
	y = _y;
	imDead = false; //pradzioje neesame mire, o gyvi
}

void DrawSpaceShipInfo()
{
	gotoxy(5, 1); printf("   ");
	gotoxy(5, 1); cout << hp << endl;
	gotoxy(23,1); printf("     ");
	gotoxy(23,1); cout << energy << endl;
}


void Draw()
{//musu laivas
	if(a == 1)
	{
		gotoxy(x,y);		printf( "  %c  ", 178);
		gotoxy(x,y + 1);	printf( "  %c  ", 178);
		gotoxy(x,y + 2);    printf("%c%c%c%c%c",178, 178, 178, 178, 178);
	}
	else if(a==2)
	{
	gotoxy(x,y);		printf( "  %c  ", 176);
	gotoxy(x,y + 1);	printf( "  %c  ", 176);
	gotoxy(x,y + 2);    printf("%c%c%c%c%c",176, 176, 176, 176, 176);
	}
	else
	{
	gotoxy(x,y);		printf( "  %c  ", 223);
	gotoxy(x,y + 1);	printf( "  %c  ", 223);
	gotoxy(x,y + 2);    printf("%c%c%c%c%c",223, 223, 223, 223, 223);
	}
}

void Erase()
{
	gotoxy(x,y); 		printf("     ");
	gotoxy(x,y + 1);	printf("     ");
	gotoxy(x,y + 2); 	printf("     ");
}

void Damage()
{
	energy--;
	if(energy == 0)
	{
		Explosion();
	}
	else
	{
		Erase();
		gotoxy(x,y); 		printf("  *  ");
		gotoxy(x,y + 1);	printf("  *  ");
		gotoxy(x,y + 2);	printf("*****");
		Sleep(100);
	}
}
void Explosion()
{
	hp--;
	Erase();
	gotoxy(x,y); 			printf("  *  ");
	gotoxy(x,y + 1); 		printf("  *  ");
	gotoxy(x,y + 2);		printf("*****");
	Sleep(100);
	Erase();
	gotoxy(x,y);			printf(" * * ");
	gotoxy(x,y + 1);		printf("* * *");
	gotoxy(x,y + 2); 		printf(" * * ");
	Sleep(100);
	Erase();
	gotoxy(x,y);			printf("*   *");
	gotoxy(x,y + 1);		printf(" * * ");
	gotoxy(x,y + 2);		printf("* * *");
	Sleep(100);
	if(hp > 0)
	{
		energy = 1;
	}
	else
	{
		imDead = true;
	}
}
void Move()
{
	if(kbhit())
	{
		Erase();
		char key = getch(); //nematomas
		switch(key)
		{//ziuri ar laivas neiseis is zaidimo liniju
			case LEFT: 	if(x > 2)	   	x -= 1; break;
			case RIGHT: if(x + 4 < 77) 	x += 1; break;
			case UP: 	if(y > 3)		y -= 1; break;
			case DOWN: 	if(y + 2 < 22)	y += 1; break;
			default:
				break;
		}
	}
	Draw();//Nupesia laiva nepaisant ar jis pajudejo ar ne
}
};

class Asteroid
{
private:
	int x;
	int y;
public:
	int X() { return x; }
	int Y() { return y; }


Asteroid(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Draw()
{
	gotoxy(x,y); printf("*");
}
void Collision(SpaceShip &ss)
{
	if(((x > ss.X()) && (x <= ss.X() + 5)) && ((y >= ss.Y()) && (y <= ss.Y() + 2)))
	{
		ss.Damage(); //asteroidas pataiko
		gotoxy(x,y); printf(" ");
		x = rand()%74 + 3;
		y = 4;
	}
	else
	{
		gotoxy(x,y); printf(" ");
		y++;
		if(y > 22)
		{
			x = rand()%74 + 3;
			y = 4;
		}
		Draw();
	}
}
};


class Bullet
{
private:
	int x;
	int y;
public:
	int X() {return x;}
	int Y() {return y;}
Bullet(int _x, int _y)
{
	x = _x;
	y = _y;
}
bool isOut()
{
	if(y <= 3)
	{
		gotoxy(x,y); printf(" ");
		return true;
	}
	else
	{
		return false;
	}
}
void Move()
{
	gotoxy(x,y); printf(" ");
	y--;
	gotoxy(x,y); printf("."); //kulka
}
};

void story(string vardas)
{
	cout << "Welcome!!!!" << endl;
	cout << "You must be..." << endl;
	cin >> vardas;

	system("cls");

	cout << vardas << " we need your help saving the earth and other planets!!!" << endl;
	cout << "We've been under atack from outer space with asteroid!!" << endl;
	cout << "That why we need your help with defending the planets!!!!" << endl;
	cout << "You have to travel from Neptune, to Saturn,to Jupiter, to Mars and las to Earth" << endl;
	cout << "I wish you good luck on this jorney for the sake of planets!!!!" << endl;
	Sleep(2000);
}

void menu()
{
	cout << "You have: health points " << hp << " score: " << score << " energy: " << energy << " " << endl; 
	cout << "1. Start the game." << endl;
	cout << "2. Store." << endl;
	cout << "3. Score Board." << endl;
	cout << "4. Exit." << endl;
	cin >> pasirinkimas; 
}

void storylevel1()
{
	printf("The joyrney begins to save the earth!\n");
	printf("This is Neptune, this is were you begin the joyrney\n");
	printf("You have to get to the earth as fast as posible.\n");
	printf("If you woun't make it, the earth will be gone,\n");
	printf("We count on you, don't let us down\n");
	Sleep(5000);
}

void storylevel2()
{
	printf("You made it to Saturn!!\n");
	printf("Your next stop is Jupiter\n");
	printf("DON'T LET US DOWN\n");
	printf("WE TRUST YOU\n");
	printf("We will give you some strenght\n");
	printf("Accept our offers of help\n");
	Sleep(2000);
}

void storylevel3()
{
	printf("You are half way there\n");
	printf("You are now on Jupiter\n");
	printf("The next planet is Mars\n");
	printf("There is said, that there will be a lot of gifts for you\n");
	printf("Don't waste your chance and go there\n");
	Sleep(5000);
}

void storylevel4()
{
	printf("You are almost there!!!\n");
	printf("You are on Mars\n");
	printf("The next stop is final\n");
	printf("Don't let us down!!!\n");
	Sleep(5000);
}



void storylevel5()
{
	printf("This is the end, we need you to save everyone, that you can\n");
	printf("We will need your help, this woun't be easy to beat, but..\n");
	printf("But we count on you that you will save us all from asteroids\n");
	printf("Good luck soldier, don't let us all down.\n");
	Sleep(5000);

}



void GameLevel1(bool levels[])
{
	levels[1] = true;
	cout << (" _____                    _____ _           _           ") << endl;
	cout << ("|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ") << endl;
	cout << ("|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|") << endl;
	cout << ("|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ") << endl;
	cout << ("      |_|") << endl;
	cout << ("                       LEVEL 1                          ") << endl;
	cout << ("                                                        ") << endl;
 	Sleep(2000);

 	system("CLS");

 	storylevel1();

 	system("CLS");



	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 5; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);



	while(!ss.isDead() && score != 5)
	{

		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();//asteroido X kordinate
				int astY = (*asteroid)->Y();//asteroido Y kordinate
				int bulX = (*bullet)->X();//asteroido X kordinate
				int bulY = (*bullet)->Y();//asteroido Y kordinate

				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3)); 
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(56,1); printf("%d", score);
		Sleep(100);
		system("CLS");
	}
	if(!ss.isDead())
	{
		GameOverVictoryMessage();
		Sleep(5000);
		system("CLS");
		menu();
	}
	else
	{
		GameOverDefeatMessage();
		Sleep(5000);
		system("CLS");
		exit(0);
	}
}

void GameLevel2(bool levels[])
{
	levels[2] = true;
	cout << (" _____                    _____ _           _           ") << endl;
	cout << ("|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ") << endl;
	cout << ("|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|") << endl;
	cout << ("|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ") << endl;
	cout << ("      |_|") << endl;
	cout << ("                       LEVEL 2                          ") << endl;
	cout << ("                                                        ") << endl;
 	Sleep(2000);
 	system("CLS");

 	storylevel2();

 	system("CLS");


	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 7; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead() && score != 10)
	{

		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();//asteroido kordinates
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3)); 
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(56,1); printf("%d", score);
		Sleep(80);
		system("CLS");
	}
	if(!ss.isDead())
	{
		GameOverVictoryMessage();
		system("CLS");
		if(score == 10)
		{
			cout << "You get double the points!!!" << endl;
			score += 10;
		}
		Sleep(5000);
		system("CLS");
		menu();
	}
	else
	{
		GameOverDefeatMessage();
		Sleep(5000);
		system("CLS");
		exit(0);
	}
}
void GameLevel3(bool levels[])
{
	levels[3] = true;
	cout << (" _____                    _____ _           _           ") << endl;
	cout << ("|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ") << endl;
	cout << ("|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|") << endl;
	cout << ("|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ") << endl;
	cout << ("      |_|") << endl;
	cout << ("                       LEVEL 3                          ") << endl;
	cout << ("                                                        ") << endl;
 	Sleep(2000);
 	system("CLS");

 	storylevel3();

 	system("cls");
	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 9; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead() && score != 15)
	{

		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();//asteroido kordinates
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3)); 
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(56,1); printf("%d", score);
		Sleep(60);
		system("CLS");
	}
	if(!ss.isDead())
	{

		GameOverVictoryMessage();
		Sleep(5000);
		system("CLS");
		menu();
	}
	else
	{
		GameOverDefeatMessage();
		Sleep(5000);
		system("CLS");
		exit(0);
	}
}
void GameLevel4(bool levels[])
{
	levels[4] = true;
	cout << (" _____                    _____ _           _           ") << endl;
	cout << ("|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ") << endl;
	cout << ("|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|") << endl;
	cout << ("|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ") << endl;
	cout << ("      |_|") << endl;
	cout << ("                       LEVEL 4                          ") << endl;
	cout << ("                                                        ") << endl;
 	Sleep(2000);
 	system("CLS");

 	storylevel4();

 	system("cls");
	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 10; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead() && score != 20)
	{

		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();//asteroido kordinates
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3)); 
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(56,1); printf("%d", score);
		Sleep(40);
		system("CLS");
	}
	if(!ss.isDead())
	{
		GameOverVictoryMessage();
		system("CLS");
		if(score == 20)
		{
			cout << "Job well done!" << endl;
			cout << "More points" << endl;
			score += 5;
		}

		Sleep(5000);
		system("CLS");
		menu();
	}
	else
	{
		GameOverDefeatMessage();
		Sleep(5000);
		system("CLS");
		exit(0);
	}
}

void GameLevel5(bool levels[5])
{
	levels[5] = true;
	cout << (" _____                    _____ _           _           ") << endl;
	cout << ("|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ") << endl;
	cout << ("|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|") << endl;
	cout << ("|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ") << endl;
	cout << ("      |_|") << endl;
	cout << ("                       LEVEL 5                          ") << endl;
	cout << ("                                                        ") << endl;
 	Sleep(2000);
 	system("CLS");

 	storylevel5();

 	system("cls");

	list<Bullet*> Bullets;
	list<Bullet*>::iterator bullet;

	list<Asteroid*> Asteroids;
	list<Asteroid*>::iterator asteroid;

	for(int i = 0; i < 15; i++)
	{
		Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3));
	}

	SpaceShip ss = SpaceShip(40,20);


	while(!ss.isDead() && score != 25)
	{

		if(kbhit())
		{
			char key = getch();
			if(key == ' ')
			{
				Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
			}
		}
		for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
		{
			(*bullet)->Move();
			if((*bullet)->isOut())
			{
				delete (*bullet);
				bullet = Bullets.erase(bullet);
			}
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			(*asteroid)->Collision(ss);
		}
		for(asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
		{
			for(bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
			{
				int astX = (*asteroid)->X();//asteroido kordinates
				int astY = (*asteroid)->Y();
				int bulX = (*bullet)->X();
				int bulY = (*bullet)->Y();
				if((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
				{
					gotoxy(bulX,bulY); printf(" ");
					gotoxy(astX,astY); printf("X"); printf(" ");
					delete (*bullet);
					bullet = Bullets.erase(bullet);
					delete (*asteroid);
					asteroid = Asteroids.erase(asteroid);
					Asteroids.push_back(new Asteroid(rand()%78 + 1, rand()%4 + 3)); 
					score++;
				}
			}
		}
		ss.Move();
		gotoxy(56,1); printf("%d", score);
		Sleep(30);
		system("CLS");
	}
	if(!ss.isDead())
	{
		GameOverVictoryMessage();
		Sleep(5000);
		system("CLS");
		menu();
	}
	else
	{
		GameOverDefeatMessage();
		Sleep(5000);
		system("CLS");
		exit(0);
	}
}






int main()
{
	HideCursor();
	WelcomeMessage();
	getch();
	system("CLS");

	story(vardas);

	system("CLS");

	menu();

	system("CLS");

while(true)
{
	if(pasirinkimas == 1 )
	{
		system("CLS");

			if(!levels[1])
			{
				GameLevel1(levels);
			}
			else if(!levels[2])
			{
				cout << "Would you like to upgrade the ship?" << endl;
				cout << "ITS COMPLETELY FREEEEEEEEE!!!!!" << endl;
				cout << "1. yes. 2. no." << endl;
				cin >> b;
				if(b == 1)
				{
					a=1;
					GameLevel2(levels);
				}
				else
				{
					GameLevel2(levels);
				}
			}
			else if(!levels[3])
			{
				GameLevel3(levels);
			}
			else if(!levels[4])
			{
				cout << "Would you like to upgrade the ship?" << endl;
				cout << "That will cost 10 score :(" << endl;
				cout << "1. yes. 2. no." << endl;
				cin >> b;
				if(b==1)
				{
					a = 2;
					score -= 10;
					GameLevel4(levels);
				}
				else
				{
				GameLevel4(levels);
				}
			}
			else if(!levels[5])
			{
				GameLevel5(levels);
			}
	}
	else if(pasirinkimas == 2)
	{
		system("CLS"); 
		cout << "Welcome to the Store " << vardas << endl;
		cout << "What would you like to buy? " << endl;
		cout << "You have: health points " << hp << " score: " << score << " energy: " << energy << " " << endl; 
		cout << "1. More health." << endl;
		cout << "2. More Energy." << endl;
		cout << "0. Return to the Menu" << endl;
		cin >> store;


		if(store == 1)
		{ 
			if(score == 0)
			{
				cout << "You can't buy that, you don't have points for that." << endl;
				Sleep(1000);
				system("CLS");
				menu();
			}
			else
			{
				hp++;
				score--;
				system("CLS");
				menu();
			}
		}
		else if(store == 2)
		{
			if(score == 0)
			{
				cout << "You can't buy that, you don't have points for that." << endl;
				Sleep(1000);
				system("CLS");
				menu();
			}
			else
			{
				energy++;
				score--;
				system("CLS");
				menu(); 
			}
		}
		else if (store == 0)
		{
			system("CLS");
			menu();
		}
	}
	else if(pasirinkimas == 3)
	{

	}
	else if(pasirinkimas == 4)
	{
		return 0;
	}
}
return 0;
}