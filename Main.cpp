#include <iostream>
#include <conio.h>
#include <Windows.h>

#define l 100

using namespace std;

bool GameOver = false;
const int width = 40, height = 20;
int x, y, i, j, fruitX, fruitY, score = 0, tailX[l], tailY[l], nTail = 0;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection direct;

void Setup()
{
	GameOver = false;
	direct = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
}

void Draw()
{
	system("cls");
	for (i = 0; i <= width; i++)
		cout << "#";
	cout << endl;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	for (i = 0; i <= width; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit())
		switch (_getch())
		{
		case 72:
			direct = UP;
			break;
		case 75:
			direct = LEFT;
			break;
		case 77:
			direct = RIGHT;
			break;
		case 80:
			direct = DOWN;
			break;
		case 27:
			GameOver = true;
			break;
		}
}

void Logic()
{
	int PrevX = tailX[0], PrevY = tailY[0], buffX, buffY;

	tailX[0] = x;
	tailY[0] = y;

	for (i = 1; i < nTail; i++)
	{
		buffX = tailX[i];
		buffY = tailY[i];
		tailX[i] = PrevX;
		tailY[i] = PrevY;
		PrevX = buffX;
		PrevY = buffY;
	}

	for (i = 1; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			GameOver = true;

	switch (direct)
	{
	case UP:
		y--;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	}

	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 1;
	if (y > height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	if (x == fruitX && y == fruitY)
	{
		score++;
		nTail++;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}

int main()
{
	Setup();

	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
	}

	return 0;
}