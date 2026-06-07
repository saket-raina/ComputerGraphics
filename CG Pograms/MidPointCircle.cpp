#include <graphics.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void plotpoints(int, int, int, int);

void CMP(int xcenter, int ycenter, int radius)
{
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    plotpoints(xcenter, ycenter, x, y);

    while(x < y)
    {
        x++;

        if(p < 0)
        {
            p = p + 2 * x + 1;
        }
        else
        {
            y--;
            p = p + 2 * (x - y) + 1;
        }

        plotpoints(xcenter, ycenter, x, y);
    }
}

void plotpoints(int xcenter, int ycenter, int x, int y)
{
    putpixel(xcenter + x, ycenter + y, BLACK);
    putpixel(xcenter - x, ycenter + y, BLACK);
    putpixel(xcenter + x, ycenter - y, BLACK);
    putpixel(xcenter - x, ycenter - y, BLACK);
    putpixel(xcenter + y, ycenter + x, BLACK);
    putpixel(xcenter - y, ycenter + x, BLACK);
    putpixel(xcenter + y, ycenter - x, BLACK);
    putpixel(xcenter - y, ycenter - x, BLACK);
}

int main()
{
    int xc, yc, r;

    cout << "Enter center coordinates (xc yc): ";
    cin >> xc >> yc;

    cout << "Enter radius: ";
    cin >> r;

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Graphics Window");
    setbkcolor(WHITE);
    cleardevice();
    // Draw circle
    CMP(xc, yc, r);

    getch();
    closegraph();

    return 0;
}