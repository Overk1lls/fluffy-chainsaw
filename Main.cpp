#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

#define tSize 100
#define width 40
#define height 20

using namespace std;

class Snake {
	public:
		Snake() {
			srand(time(NULL));
			
			nowTime = clock();
			specFrTime = (float)nowTime / CLOCKS_PER_SEC + 60;

			score = 0;
			tailSize = 1;
			isGameOver = false;
			specAppears = false;
			step = STOP;

			headX = width / 2 - 1;
			headY = height / 2 - 1;
			iFruitX = rand() % (width - 2) + 1;
			iFruitY = rand() % (height - 2) + 1;
			dFruitX = rand() % (width - 2) + 1;
			dFruitY = rand() % (height - 2) + 1;
			specFrX = rand() % (width - 2) + 1;
			specFrY = rand() % (height - 2) + 1;

			while (iFruitX == dFruitX && iFruitY == dFruitY) {
				dFruitX = rand() % (width - 2) + 1;
				dFruitY = rand() % (height - 2) + 1;
			}
			while ((specFrX == iFruitX && specFrY == iFruitY) || (specFrX == dFruitX && specFrY == dFruitY)) {
				specFrX = rand() % (width - 2) + 1;
				specFrY = rand() % (height - 2) + 1;
			}
		}

		bool GetGameOver() {
			return this->isGameOver;
		}

		void Redrawing() {
			COORD cursPos;
			cursPos.X = 0;
			cursPos.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursPos);

			nowTime = clock();
			if (((float)nowTime) / CLOCKS_PER_SEC > specFrTime)
				specAppears = true;

			for (int i = 0; i <= width; i++)
				cout << "#";
			cout << endl;
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (j == 0 || j == width - 1)
						cout << "#";
					if (i == headY && j == headX)
						cout << "Z";
					else if (i == iFruitY && j == iFruitX)
						cout << "I";
					else if (i == dFruitY && j == dFruitX)
						cout << "D";
					else if (specAppears && i == specFrY && j == specFrX)
						cout << "S";
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

		void Move() {
			if (_kbhit())
				switch (_getch()) {
					case 72:
						step = UP;
						break;
					case 75:
						step = LEFT;
						break;
					case 77:
						step = RIGHT;
						break;
					case 80:
						step = DOWN;
						break;
					case 27:
						isGameOver = true;
						break;
				}
		}

		void Loot() {
			switch (step) {
				case UP:
					headY--;
					break;
				case LEFT:
					headX--;
					break;
				case RIGHT:
					headX++;
					break;
				case DOWN:
					headY++;
					break;
			}
			int PrevX = tailX[0], PrevY = tailY[0], buffX, buffY;

			tailX[0] = headX;
			tailY[0] = headY;

			for (int i = 1; i < tailSize; i++) {
				buffX = tailX[i];
				buffY = tailY[i];
				tailX[i] = PrevX;
				tailY[i] = PrevY;
				PrevX = buffX;
				PrevY = buffY;
			}
			for (int i = 1; i < tailSize; i++)
				if (tailX[i] == headX && tailY[i] == headY)
					isGameOver = true;

			if (headX >= width - 1)
				headX = 0;
			else if (headX < 0)
				headX = width - 1;
			if (headY > height)
				headY = 0;
			else if (headY < 0)
				headY = height - 1;

			if (headX == iFruitX && headY == iFruitY) {
				score++;
				tailSize++;
				iFruitX = rand() % (width - 2) + 1;
				iFruitY = rand() % (height - 2) + 1;
				while (iFruitX == dFruitX)
					iFruitX = rand() % (width - 2) + 1;
				while (iFruitY == dFruitY)
					iFruitY = rand() % (height - 2) + 1;
			}
			else if (headX == dFruitX && headY == dFruitY) {
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
			else if (headX == specFrX && headY == specFrY && specAppears) {
				specFrTime = ((float)nowTime) / CLOCKS_PER_SEC + 60;
				score += 3;
				tailSize += 3;
				specAppears = false;
				specFrX = rand() % (width - 2) + 1;
				specFrY = rand() % (height - 2) + 1;
				while ((specFrX == iFruitX && specFrY == iFruitY) || (specFrX == dFruitX && specFrY == dFruitY)) {
					specFrX = rand() % (width - 2) + 1;
					specFrY = rand() % (height - 2) + 1;
				}
			}
		}

	private:
		enum eStep { STOP = 0, LEFT, RIGHT, UP, DOWN };
		eStep step;
		bool isGameOver, specAppears;
		int headX, headY, iFruitX, iFruitY, dFruitX, dFruitY, specFrX, specFrY, tailX[tSize], tailY[tSize], score, tailSize;
		clock_t nowTime;
		int specFrTime;
};

int main() {
	Snake game;
	while (!game.GetGameOver()) {
		game.Redrawing();
		game.Move();
		game.Loot();
	}
	return 0;
}