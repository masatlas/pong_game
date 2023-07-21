#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 60;
const int HEIGHT = 20;
int ballX, ballY;
int paddleLeftY, paddleRightY;
int ballSpeedX, ballSpeedY;
bool gameOver;

enum Direction { STOP = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 };
Direction ballDir;

void Setup()
{
    gameOver = false;
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
    ballSpeedX = 1;
    ballSpeedY = 1;
    ballDir = Direction::STOP;
    paddleLeftY = HEIGHT / 2 - 2;
    paddleRightY = HEIGHT / 2 - 2;
}

void Draw()
{
    system("cls");

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0 || j == WIDTH - 1)
                cout << "#";
            if (i == ballY && j == ballX)
                cout << "O";
            else if (i >= paddleLeftY && i < paddleLeftY + 4 && j == 1)
                cout << "#";
            else if (i >= paddleRightY && i < paddleRightY + 4 && j == WIDTH - 2)
                cout << "#";
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
}

void Input()
{
    if (_kbhit())
    {
        char key = _getch();
        switch (key)
        {
        case 'w':
            ballDir = UP;
            break;
        case 's':
            ballDir = DOWN;
            break;
        case 'a':
            ballDir = LEFT;
            break;
        case 'd':
            ballDir = RIGHT;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    switch (ballDir)
    {
    case UP:
        ballY--;
        break;
    case DOWN:
        ballY++;
        break;
    case LEFT:
        ballX--;
        break;
    case RIGHT:
        ballX++;
        break;
    }

    // Ball collision with walls
    if (ballY <= 0 || ballY >= HEIGHT - 1)
        ballDir = (ballDir == UP) ? DOWN : UP;
    if (ballX <= 0)
        ballDir = RIGHT;
    if (ballX >= WIDTH - 1)
        ballDir = LEFT;

    // Ball collision with paddles
    if (ballX == 1 && ballY >= paddleLeftY && ballY < paddleLeftY + 4)
        ballDir = RIGHT;
    if (ballX == WIDTH - 2 && ballY >= paddleRightY && ballY < paddleRightY + 4)
        ballDir = LEFT;

    // Move paddles
    if (paddleLeftY > 0 && ballDir == UP)
        paddleLeftY--;
    if (paddleLeftY < HEIGHT - 4 && ballDir == DOWN)
        paddleLeftY++;
    if (paddleRightY > 0 && ballDir == UP)
        paddleRightY--;
    if (paddleRightY < HEIGHT - 4 && ballDir == DOWN)
        paddleRightY++;
}

int main()
{
    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50); // To slow down the game
    }

    return 0;
}
