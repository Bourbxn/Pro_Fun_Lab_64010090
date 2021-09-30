#include "stdio.h"
#include "time.h"
#include "windows.h"
#include "conio.h"
#include "iostream"
#include "thread"

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(0xA, 4);
	printf(" <-0-> ");
}

void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("       ");
}

void draw_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(5, 0);
	printf("o");
}

void erase_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

void draw_enemy(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 0);
	printf("*");
}

void erase_enemy(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

void setScoreBoard(int score)
{
	gotoxy(75, 0);
	setcolor(7, 0);
	printf("Points : %d", score);
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}

int main() {
	//Init variables
	char ch = ' ';
	int x = 38, y = 20;
	int x_bullet[5], y_bullet[5];
	int direction = 0;
	//Bullet variables
	int bulletArrayPos = 0;
	int bulletState[5] = { 0,0,0,0,0 };
	int bulletShow = 0;
	//Enemy variables
	int enemyAmout = 0;
	int enemyAmoutMax = 20;
	//GUI Variables
	int gameScore = 0;
	//srand seed setting
	srand(time(NULL));

	//Game render
	setcursor(0);
	setScoreBoard(gameScore);
	draw_ship(x, y);
	do {
		//Keyboard update input
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0)
			{
				direction = -1;
			}
			if (ch == 'd' && x < 80)
			{
				direction = 1;
			}
			if (ch == 's')
			{
				direction = 0;
			}
			if (ch == ' ' && bulletShow < 5)
			{
				std::thread q(Beep, 1000, 200);
				q.detach();
				bulletState[bulletArrayPos] = 1;
				x_bullet[bulletArrayPos] = x+3;
				y_bullet[bulletArrayPos] = y;
				bulletArrayPos++;
				if (bulletArrayPos == 5) bulletArrayPos = 0;
				bulletShow++;
			}
			fflush(stdin);
		}

		//Check direction for auto move
		if (direction == 1 && x <= 80)
		{
			erase_ship(x, y);
			if (x == 80) draw_ship(x, y);
			else draw_ship(++x, y);

		}
		else if (direction == -1 && x >= 0)
		{
			erase_ship(x, y);
			if (x == 0) draw_ship(x, y);
			else draw_ship(--x, y);
		}
		else if (direction == 0)
		{
			draw_ship(x, y);
		}
		Sleep(100);

		//Spawn enemy
		for (int e = 0; e < 20; e++)
		{
			if (enemyAmout < enemyAmoutMax) {
				draw_enemy((rand() % 61) + 10, (rand() % 4) + 2);
				enemyAmout++;
			}
			else
				break;
		}

		//Bullet Fire on
		for (int i = 0; i < 5; i++) {
			if (bulletState[i] == 1)
			{
				erase_bullet(x_bullet[i], y_bullet[i]);
				if (y_bullet[i] > 0)
				{
					//Check bullet bet bound enemy
					if (cursor(x_bullet[i],y_bullet[i] - 1) == '*')
					{
						erase_enemy(x_bullet[i], y_bullet[i] - 1);
						setScoreBoard(++gameScore);
						std::thread q(Beep, 500, 200);
						q.detach();
						bulletState[i] = 0;
						bulletShow--;
						enemyAmout--;
					}
					else
					{
						draw_bullet(x_bullet[i], --(y_bullet[i]));
					}

				}
				else
				{
					erase_bullet(x_bullet[i], y_bullet[i]);
					bulletState[i] = 0;
					bulletShow--;
				}

			}
		}
	} while (ch != 'x');

	//End game
	return 0;
}
