#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#define tSize 100

using namespace std;

class Snake {
	public:
		Snake() {
			srand(time(NULL));

			isGameOver = false;
			direct = STOP;
			x = width / 2 - 1;
			y = height / 2 - 1;
			iFruitX = rand() % (width - 2) + 1;
			iFruitY = rand() % (height - 2) + 1;
			dFruitX = rand() % (width - 2) + 1;
			dFruitY = rand() % (height - 2) + 1;
			while (iFruitX == dFruitX)
				dFruitX = rand() % (width - 2) + 1;
			while (iFruitY == dFruitY)
				dFruitY = rand() % (height - 2) + 1;
		}

		bool GetGameOver() {
			return this->isGameOver;
		}

		void Draw() {
			COORD cursPos;
			cursPos.X = 0;
			cursPos.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursPos);

			for (int i = 0; i <= width; i++)
				cout << "#";
			cout << endl;
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (j == 0 || j == width - 1)
						cout << "#";
					if (i == y && j == x)
						cout << "Z";
					else if (i == iFruitY && j == iFruitX)
						cout << "I";
					else if (i == dFruitY && j == dFruitX)
						cout << "D";
					else {
						bool isSpace = true;
						for (int k = 0; k < tailSize; k++)
							if (tailX[k] == j && tailY[k] == i) {
								isSpace = false;
								cout << "z";
							}
						if (isSpace)
							cout << " ";
					}
				}
				cout << endl;
			}
			for (int i = 0; i <= width; i++)
				cout << "#";
			cout << endl;
			cout << "Score: " << score << endl;
		}

		void Input() {
			if (_kbhit())
				switch (_getch()) {
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
						isGameOver = true;
						break;
				}
		}

		void Logic() {
			switch (direct) {
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
			int PrevX = tailX[0], PrevY = tailY[0], buffX, buffY;

			tailX[0] = x;
			tailY[0] = y;

			for (int i = 1; i < tailSize; i++) {
				buffX = tailX[i];
				buffY = tailY[i];
				tailX[i] = PrevX;
				tailY[i] = PrevY;
				PrevX = buffX;
				PrevY = buffY;
			}
			for (int i = 1; i < tailSize; i++)
				if (tailX[i] == x && tailY[i] == y)
					isGameOver = true;

			if (x >= width - 1)
				x = 0;
			else if (x < 0)
				x = width - 1;
			if (y > height)
				y = 0;
			else if (y < 0)
				y = height - 1;

			if (x == iFruitX && y == iFruitY) {
				score++;
				tailSize++;
				iFruitX = rand() % (width - 2) + 1;
				iFruitY = rand() % (height - 2) + 1;
				while (iFruitX == dFruitX)
					iFruitX = rand() % (width - 2) + 1;
				while (iFruitY == dFruitY)
					iFruitY = rand() % (height - 2) + 1;
			}
			else if (x == dFruitX && y == dFruitY) {
				if (score == 0)
					isGameOver = true;
				else {
					score--;
					tailSize--;
					dFruitX = rand() % (width - 2) + 1;
					dFruitY = rand() % (height - 2) + 1;
					while (iFruitX == dFruitX)
						dFruitX = rand() % (width - 2) + 1;
					while (iFruitY == dFruitY)
						dFruitY = rand() % (height - 2) + 1;
				}
			}
		}
	private:
		enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
		eDirection direct;
		bool isGameOver;
		const int width = 40, height = 20;
		int x, y, iFruitX, iFruitY, dFruitX, dFruitY, specFrX, specFrY, tailX[tSize], tailY[tSize], score = 0, tailSize = 1;
};

int main() {
	Snake game;
	while (!game.GetGameOver()) {
		game.Draw();
		game.Input();
		game.Logic();
	}
	return 0;
}