#include<iostream>
#include<graphics.h>
#include<windows.h>
#include<cmath>
using namespace std;

void drawline(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int x = x0;
    int y = y0;

    int sx = (x1 > x0) ? 1 : -1;
    int sy = (y1 > y0) ? 1 : -1;

    // Case 1: m < 1
    if(dx >= dy)
    {
        int p = 2 * dy - dx;
        for(int i = 0; i <= dx; i++)
        {
            putpixel(x, y, BLACK);
            if(p >= 0)
            {
                y += sy;
                p += 2 * dy - 2 * dx;
            }
            else
            {
                p += 2 * dy;
            }
            x += sx;
        }
    }

    // Case 2: m > 1
    else
    {
        int p = 2 * dx - dy;
        for(int i = 0; i <= dy; i++)
        {
            putpixel(x, y, BLACK);
            if(p >= 0)
            {
                x += sx;
                p += 2 * dx - 2 * dy;
            }
            else
            {
                p += 2 * dx;
            }
            y += sy;
        }
    }
}

int main()
{
    int x0, y0, x1, y1;
    cout << "Enter coordinates of first point: ";
    cin >> x0 >> y0;
    cout << "Enter coordinates of second point: ";
    cin >> x1 >> y1;

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Bresenham Line Drawing");
    setbkcolor(WHITE);
    cleardevice();

    drawline(x0, y0, x1, y1);
    getch();
    closegraph();
    return 0;
}
