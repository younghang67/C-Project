#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <ncurses.h>
#include <unistd.h>
#endif

#define MAX_LENGTH 100

int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int length = 1;

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;

// Function to generate the fruit within the boundary
void setup()
{
    gameover = 0;
    x = height / 2;
    y = width / 2;

    // Seed the random number generator
    srand(time(NULL));

    // Generate initial fruit position
    fruitx = rand() % (height - 2) + 1;
    fruity = rand() % (width - 2) + 1;

    score = 0;
}

// Function to draw the boundaries
void draw()
{
#ifdef _WIN32
    system("cls");
#else
    clear();
#endif

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printf("#");
            }
            else
            {
                int isSnakeSegment = 0;
                for (int k = 0; k < length; k++)
                {
                    if (i == snakeX[k] && j == snakeY[k])
                    {
                        printf("o"); // Snake's body segment
                        isSnakeSegment = 1;
                        break;
                    }
                }
                if (!isSnakeSegment)
                {
                    if (i == x && j == y)
                        printf("0");
                    else if (i == fruitx && j == fruity)
                        printf("*");
                    else
                        printf(" ");
                }
            }
        }
        printf("\n");
    }

    printf("score = %d\n", score);
    printf("press X to quit the game\n");
}

// Function to take the input
void input()
{
#ifdef _WIN32
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
#else
    int ch = getch();
    switch (ch)
    {
    case 'a':
        flag = 1;
        break;
    case 's':
        flag = 2;
        break;
    case 'd':
        flag = 3;
        break;
    case 'w':
        flag = 4;
        break;
    case 'x':
        gameover = 1;
        break;
    }
#endif
}

// Function for the logic behind each movement
void logic()
{
#ifdef _WIN32
    Sleep(100);
#else
    usleep(10000);
#endif

    switch (flag)
    {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    // If the game is over
    if (x < 0 || x >= height || y < 0 || y >= width)
        gameover = 1;

    // If snake reaches the fruit then update the score
    if (x == fruitx && y == fruity)
    {
        score += 10;
        length++;

        // Generate new fruit position
        fruitx = rand() % (height - 2) + 1;
        fruity = rand() % (width - 2) + 1;
    }

    // Update snake's body segments
    for (int k = length - 1; k > 0; k--)
    {
        snakeX[k] = snakeX[k - 1];
        snakeY[k] = snakeY[k - 1];
    }
    snakeX[0] = x;
    snakeY[0] = y;
}

// Driver Code
int main()
{
#ifdef _WIN32
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
    }
#else
    // Initialize ncurses library
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
    }

    // Clean up ncurses
    endwin();
#endif

    return 0;
}
