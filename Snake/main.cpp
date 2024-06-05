#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}
void Board()
{
    for(int i =0;i < HEIGHT; i++){
        cout << "\t\t#";
        for(int j = 0;j < WIDTH -2;j++){
            if(i==0||i==HEIGHT-1){
                cout<<'#';
            }
            else if(i==y && j==x) cout<<'0';
            else cout << " ";
        }
        cout<<"#\n";
    }
}
struct NODE {
    int x, y;
};

struct SNAKE {
    NODE A[100];
    int Length;
};

void Init(SNAKE& snake) {
    snake.Length = 7;
    for (int i = 0; i < snake.Length; i++) {
        snake.A[i].x = 9 - i;
        snake.A[i].y = 5;
    }
}

void Draw(SNAKE snake, NODE food) {
    system("cls");
    for (int i = 0; i < snake.Length; i++) {
        gotoxy(snake.A[i].x * 2, snake.A[i].y);
        cout << "O";
    }
    gotoxy(food.x * 2, food.y);
    cout << "@";
    gotoxy(0, HEIGHT + 2);
    cout << "Score: " << snake.Length - 7;
}

void Run(SNAKE& snake, int dir) {
    for (int i = snake.Length - 1; i > 0; i--) {
        snake.A[i] = snake.A[i - 1];
    }
    switch (dir) {
    case 0:
        snake.A[0].x++;
        break;
    case 1:
        snake.A[0].y++;
        break;
    case 2:
        snake.A[0].x--;
        break;
    case 3:
        snake.A[0].y--;
        break;
    }
}

bool CheckCollision(SNAKE snake) {
    for (int i = 1; i < snake.Length; i++) {
        if (snake.A[0].x == snake.A[i].x && snake.A[0].y == snake.A[i].y) {
            return true;
        }
    }
    return false;
}

bool EatFood(SNAKE& snake, NODE food) {
    if (snake.A[0].x == food.x && snake.A[0].y == food.y) {
        snake.Length++;
        return true;
    }
    return false;
}

NODE GenerateFood(SNAKE snake) {
    NODE food;
    bool overlap;
    do {
        overlap = false;
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
        for (int i = 0; i < snake.Length; i++) {
            if (snake.A[i].x == food.x && snake.A[i].y == food.y) {
                overlap = true;
                break;
            }
        }
    } while (overlap);
    return food;
}

int main() {
    srand(time(0));
    SNAKE snake;
    int dir = 0;
    char ch;
    Init(snake);
    NODE food = GenerateFood(snake);
    Draw(snake, food);
    while (true) {
        Board();
        if (kbhit()) {
            ch = getch();
            switch (ch) {
            case 'd':
                if (dir != 2)
                    dir = 0;
                break;
            case 's':
                if (dir != 3)
                    dir = 1;
                break;
            case 'a':
                if (dir != 0)
                    dir = 2;
                break;
            case 'w':
                if (dir != 1)
                    dir = 3;
                break;
            }
        }
        Run(snake, dir);
        if (CheckCollision(snake)) {
            gotoxy(0, HEIGHT + 2);
            cout << "Game Over!";
            break;
        }
        if (EatFood(snake, food)) {
            food = GenerateFood(snake);
        }
        Draw(snake, food);
        Sleep(500);
    }
    return 0;
}
