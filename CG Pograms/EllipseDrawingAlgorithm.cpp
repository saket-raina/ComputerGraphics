#include <graphics.h>
#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

// Function to plot all four symmetric points
void plotEllipsePoints(int xc, int yc, int x, int y)
{
    putpixel(xc + x, yc + y, BLACK);
    putpixel(xc - x, yc + y, BLACK);
    putpixel(xc + x, yc - y, BLACK);
    putpixel(xc - x, yc - y, BLACK);
}

// Midpoint Ellipse Drawing Algorithm
void midpointEllipse(int xc, int yc, int rx, int ry)
{
    float dx, dy, d1, d2, x, y;

    x = 0;
    y = ry;

    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry)
         + (0.25 * rx * rx);

    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // Region 1
    while (dx < dy)
    {
        plotEllipsePoints(xc, yc, x, y);

        if (d1 < 0)
        {
            x++;
            dx += (2 * ry * ry);
            d1 += dx + (ry * ry);
        }
        else
        {
            x++;
            y--;

            dx += (2 * ry * ry);
            dy -= (2 * rx * rx);

            d1 += dx - dy + (ry * ry);
        }
    }

    // Initial decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5)))
         + ((rx * rx) * ((y - 1) * (y - 1)))
         - (rx * rx * ry * ry);

    // Region 2
    while (y >= 0)
    {
        plotEllipsePoints(xc, yc, x, y);

        if (d2 > 0)
        {
            y--;
            dy -= (2 * rx * rx);
            d2 += (rx * rx) - dy;
        }
        else
        {
            y--;
            x++;

            dx += (2 * ry * ry);
            dy -= (2 * rx * rx);

            d2 += dx - dy + (rx * rx);
        }
    }
}

int main()
{
    int xc, yc, rx, ry;

    cout << "Enter center coordinates (xc yc): ";
    cin >> xc >> yc;

    cout << "Enter semi-major axis (rx): ";
    cin >> rx;

    cout << "Enter semi-minor axis (ry): ";
    cin >> ry;

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Graphics Window");
    setbkcolor(WHITE);
    cleardevice();

    midpointEllipse(xc, yc, rx, ry);

    getch();
    closegraph();

    return 0;
}