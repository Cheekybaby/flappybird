#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <ctime>

using namespace std;

void gotoXY(int x, int y)
{
    COORD coordinate = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

const int hurdlecount = 5;

class FLAPPYBIRD
{
private:
    int hurdlepos[hurdlecount][2];
    int screenwidth = 80;
    int screenheight = 24;
    int hurdlegap = 8;
    int betweenHurdleGaps;

    int birdX = 17;
    int birdY = 15;

    int jump = 3;
    int score = 0;

public:
    FLAPPYBIRD()
    {
        srand(time(NULL));

        betweenHurdleGaps = (screenwidth / hurdlecount) + 10;
        // Designing the upper and lower part of the hurdle;
        for (int i = 0; i < hurdlecount; i += 1)
        {
            hurdlepos[i][0] = betweenHurdleGaps * (i + 1);

            int breakpos = rand() % (screenheight / 3) + hurdlegap;
            hurdlepos[i][1] = breakpos;
        }
    }

    // Printing the hurdle
    void printhurdle()
    {
        int count = 0;
        for (int i = 0; i < hurdlecount; i += 1)
        {
            for (int j = 0; j < screenheight; j += 1)
            {
                if (hurdlepos[i][1] == j)
                    count = hurdlegap;

                if (count == 0)
                {
                    if (hurdlepos[i][0] < screenwidth)
                    {
                        gotoXY(hurdlepos[i][0] + 1, j);
                        cout << " ";

                        gotoXY(hurdlepos[i][0], j);
                        cout << "|";
                    }
                }
                else
                {
                    if ((count == 1 || count == hurdlegap) && hurdlepos[i][0] < screenwidth)
                    {
                        if (hurdlepos[i][0] + 1 > 0)
                        {
                            gotoXY(hurdlepos[i][0] + 1, j);
                            cout << "   ";
                        }
                        if (hurdlepos[i][0] - 1 > 0)
                        {
                            gotoXY(hurdlepos[i][0] - 1, j);
                            cout << "===";
                        }
                    }
                    count -= 1;
                }
            }
            hurdlepos[i][0] -= 1;

            if (hurdlepos[i][0] == -1)
            {
                int prev;
                if (i == 0)
                    prev = hurdlecount - 1;
                else
                    prev = i - 1;

                hurdlepos[i][0] = hurdlepos[prev][0] + betweenHurdleGaps;

                int breakpos = rand() % (screenheight / 3) + hurdlegap;
                hurdlepos[i][1] = breakpos;

                for (int i = 0; i < screenheight; i += 1)
                {
                    gotoXY(0, i);
                    cout << " ";
                }
            }
        }
    }

    // Collision Check
    bool collisioncheck()
    {
        if (birdY == 0 || birdY + 3 == screenheight)
            return true; // Collision with ceiling or floor of the game.
        for (int i = 0; i < hurdlecount; i += 1)
        {
            if (hurdlepos[i][0] == birdX && (birdY >= hurdlepos[i][1] || birdY + 3 <= (hurdlepos[i][1] + hurdlegap)))
            {
                score += 1;
            }

            if (hurdlepos[i][0] >= birdX - 5 && hurdlepos[i][0] <= birdX && (birdY <= hurdlepos[i][1] || birdY + 3 >= (hurdlepos[i][1] + hurdlegap)))
            {
                return true;
            }
        }

        return false;
    }

    // Clear bird
    void clearBird()
    {
        gotoXY(birdX - 5, birdY);
        cout << "   ";
        gotoXY(birdX - 5, birdY + 1);
        cout << "     ";
        gotoXY(birdX - 5, birdY + 2);
        cout << "       ";
    }

    // Print Bird
    void printBird()
    {
        gotoXY(birdX - 5, birdY);
        cout << " __";
        gotoXY(birdX - 5, birdY + 1);
        cout << "/-/o\\";
        gotoXY(birdX - 5, birdY + 2);
        cout << "\\_\\-/";
    }

    // Scoring
    void scoring()
    {
        gotoXY(0, screenheight + 4);
        cout << "Score: " << score << '\n';
    }

    void play()
    {
        while (true)
        {
            if (GetAsyncKeyState(VK_SPACE))
            {
                birdY -= jump;
            }

            printhurdle();
            printBird();
            scoring();

            if (collisioncheck())
            {
                break;
            }

            Sleep(100);
            clearBird();
            birdY += 1;
        }
    }
};

int main()
{
    while (true)
    {
        FLAPPYBIRD game;
        game.play();

        gotoXY(30, 30);

        cout << "\nDo you want to play again? (Y/N)";

        char ch;
        cin >> ch;
        if (ch == 'N' || ch == 'n')
        {
            break;
        }
        system("cls");
    }

    return 0;
}