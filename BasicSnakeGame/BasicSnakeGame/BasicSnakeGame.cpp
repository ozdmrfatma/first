#include<iostream>
#include<conio.h>
#include<Windows.h>
#include <cstdlib>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int headX, headY;//head position
int fruitX, fruitY;//fruit position
int score;
int tailX[100], tailY[100];
int lengthTail;

enum eDirection
{
	STOP = 0, LEFT, RIGHT, UP, DOWN
};
eDirection dir;//that will hold the direction of the snake

void Setup()
{
	gameOver = false;
	dir = STOP;//the snake will not move until we start moving it
	headX = width / 2;
	headX = height / 2;//the snakehead will be centered of the map
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls");//call the windows commanda CLS that will be clear the screen 
	//top wall
	for (int i = 0; i < width + 2; i++)
		cout << "#";//print this character for the map wall ,top wall
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == headY && j == headX)
				cout << "O";

			else if (i == fruitY && j == fruitX)
			{
				//system("color B");
				cout << "*";

			}

			else
			{
				bool print = false;
				for (int k = 0; k < lengthTail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "SCORE:" << score << endl;

}
void Input()
{
	if (_kbhit())
	{	//this will handle the controls
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case'x':
			gameOver = true;
			system("color B0");


			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = headX;//tailX first eleman to fallow to head
	tailY[0] = headY;
	for (int i = 1; i < lengthTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	case  UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	default:
		break;
	}
	if (headX > width || headX<0 || headY>height || headY < 0)
		gameOver = true;
	cout << "G A M E O V E R " << endl;

	//if we hit ourself or our tail with a head,its similar to the wall
	//just we re going to loop to all tail segments
	for (int i = 0; i < lengthTail; i++)
	{
		if (tailX[i] == headX && tailY[i] == headY)
			gameOver = true;
	}
	if (headX == fruitX && headY == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		lengthTail++;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		system("color 6");
		Input();
		//system("color 60");
		Logic();
		Sleep(20);
	}




	return 0;
}