#include <graphics.h>
#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

// DDA Line Drawing Algorithm
void DDA(int X0, int Y0, int X1, int Y1)
{
    float dx, dy, steps, x_inc, y_inc, x, y;

    // Calculate differences
    dx = X1 - X0;
    dy = Y1 - Y0;

    // Determine number of steps
    steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    // Calculate increments
    x_inc = dx / steps;
    y_inc = dy / steps;

    // Initialize starting point
    x = X0;
    y = Y0;

    // Plot the first point
    putpixel(round(x), round(y), BLACK);

    // Generate and plot remaining points
    for (int i = 0; i < steps; i++)
    {
        x += x_inc;
        y += y_inc;
        putpixel(round(x), round(y), BLACK);
    }
}

int main()
{
    int X0, Y0, X1, Y1;

    // Take input from the user
    cout << "Enter the starting point (X0 Y0): ";
    cin >> X0 >> Y0;

    cout << "Enter the ending point (X1 Y1): ";
    cin >> X1 >> Y1;

    
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Graphics Window");
    setbkcolor(WHITE);
    cleardevice();

    DDA(X0, Y0, X1, Y1);
    
    getch();
    closegraph();

    return 0;
}