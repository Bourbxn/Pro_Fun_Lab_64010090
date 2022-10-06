#include <stdio.h>
#include <windows.h>
#include <time.h>

//Variables
#define scount 80
#define screen_x 80
#define screen_y 25
HANDLE wHnd;
HANDLE rHnd;
DWORD fdwMode;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0,0 };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
COORD star[scount];
int ship_color = 7;

//Functions
int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}

int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}

void clear_buffer() {
	for (int y = 0; y < screen_y; ++y) {
		for (int x = 0; x < screen_x; ++x) {
			if (consoleBuffer[x + screen_x * y].Char.AsciiChar != ' ' &&
				consoleBuffer[x + screen_x * y].Char.AsciiChar != '<' &&
				consoleBuffer[x + screen_x * y].Char.AsciiChar != '-' &&
				consoleBuffer[x + screen_x * y].Char.AsciiChar != '0' &&
				consoleBuffer[x + screen_x * y].Char.AsciiChar != '>') {
				consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
				consoleBuffer[x + screen_x * y].Attributes = 7;
			}
		}
	}
}

void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
}

void init_star()
{
	srand(time(NULL));
	for (int i = 0; i < scount; i++)
	{
		star[i].X = rand() % screen_x;
		star[i].Y = rand() % screen_y;
	}
}

void star_fall()
{
	int i;
	for (i = 0; i < scount; i++) {
		if (star[i].Y >= screen_y - 1) {
			star[i].X = rand() % screen_x;
			star[i].Y = 1;
		}
		else {
			star[i].Y += 1;
		}
	}
}

void fill_ship_to_buffer(int x,int y)
{
	//ship
	consoleBuffer[x - 2+ screen_x * y].Char.AsciiChar = '<';
	consoleBuffer[x - 1  + screen_x * y].Char.AsciiChar = '-';
	consoleBuffer[x + screen_x * y].Char.AsciiChar = '0';
	consoleBuffer[x + 1 + screen_x * y].Char.AsciiChar = '-';
	consoleBuffer[x + 2 + screen_x * y].Char.AsciiChar = '>';
	//color
	consoleBuffer[x - 2 + screen_x * y].Attributes = ship_color;
	consoleBuffer[x - 1 + screen_x * y].Attributes = ship_color;
	consoleBuffer[x + screen_x * y].Attributes = ship_color;
	consoleBuffer[x + 1 + screen_x * y].Attributes = ship_color;
	consoleBuffer[x + 2 + screen_x * y].Attributes = ship_color;
}

void clear_ship_from_buffer(int x, int y)
{
	//ship
	consoleBuffer[x - 2 + screen_x * y].Char.AsciiChar = ' ';
	consoleBuffer[x - 1 + screen_x * y].Char.AsciiChar = ' ';
	consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
	consoleBuffer[x + 1 + screen_x * y].Char.AsciiChar = ' ';
	consoleBuffer[x + 2 + screen_x * y].Char.AsciiChar = ' ';
	//color
	consoleBuffer[x - 2 + screen_x * y].Attributes = 7;
	consoleBuffer[x - 1 + screen_x * y].Attributes = 7;
	consoleBuffer[x + screen_x * y].Attributes = 7;
	consoleBuffer[x + 1 + screen_x * y].Attributes = 7;
	consoleBuffer[x + 2 + screen_x * y].Attributes = 7;
}

//Game
int main()
{
	//Init variables
	bool play = true;
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	int hp = 10;
	int lastposx = screen_x / 2;
	int lastposy = screen_y / 2;
	init_star();
	srand(time(NULL));
	setConsole(screen_x, screen_y);
	setMode();
	//Game render
	while (play)
	{
		star_fall();
		clear_buffer();
		//Check collision and fill star
		for (int i = 0; i < scount; i++)
		{
			//Check collision
			if (consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar == '<' ||
				consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar == '-' ||
				consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar == '0' ||
				consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar == '>')
			{
				hp--;
				if (hp == 0)
				{
					play = false;
				}
				star[i].X = rand() % screen_x;
				star[i].Y = rand() % screen_y;
			}
			//Fill star
			consoleBuffer[star[i].X + screen_x * star[i].Y].Char.AsciiChar = '*';
		}
		fill_buffer_to_console();
		//Update input
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);  for (DWORD i = 0; i < numEventsRead; ++i) {
				//Keyboard input
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true)
				{
					//ESC
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
					{
						play = false;
					}
					//C
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c')
					{
						ship_color = rand() % 15 + 1;
					}
				}

				//Mouse input
				else if (eventBuffer[i].EventType == MOUSE_EVENT)
				{
					int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					//Left click
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						ship_color = rand() % 15 + 1;
					}
					//Mouse Position tracking (Ship movement)
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED && posx > 2 && posx < screen_x - 2)
					{
						if (posx != lastposx || posy != lastposy)
						{
							clear_ship_from_buffer(lastposx, lastposy);
						}
						fill_ship_to_buffer(posx, posy);
						lastposx = posx;
						lastposy = posy;
					}
				}
			}
			delete[] eventBuffer;
		}
		Sleep(100);
	}
	//Game end
	return 0;
}
