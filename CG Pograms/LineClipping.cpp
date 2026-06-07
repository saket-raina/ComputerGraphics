#include <graphics.h>
#include <iostream>
#include <windows.h>

using namespace std;

// Region Codes
const int INSIDE = 0;   // 0000
const int LEFT   = 1;   // 0001
const int RIGHT  = 2;   // 0010
const int BOTTOM = 4;   // 0100
const int TOP    = 8;   // 1000

// Logical clipping window
int xmin = 100, ymin = 100;
int xmax = 300, ymax = 300;

// Display shifts
const int LEFT_SHIFT_X  = 150;
const int LEFT_SHIFT_Y  = 150;

const int RIGHT_SHIFT_X = 750;
const int RIGHT_SHIFT_Y = 150;

// Compute Region Code
int computeCode(double x, double y)
{
    int code = INSIDE;

    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;

    // BGI coordinate system:
    // Smaller Y = Above
    // Larger Y  = Below
    if (y < ymin)
        code |= TOP;
    else if (y > ymax)
        code |= BOTTOM;

    return code;
}

// Cohen-Sutherland Line Clipping
bool cohenSutherlandClip(
        double &x1, double &y1,
        double &x2, double &y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    bool accept = false;

    while (true)
    {
        // Completely inside
        if ((code1 | code2) == 0)
        {
            accept = true;
            break;
        }

        // Completely outside
        else if (code1 & code2)
        {
            break;
        }

        // Partially inside
        else
        {
            double x, y;

            int codeOut = code1 ? code1 : code2;

            // Top boundary
            if (codeOut & TOP)
            {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }

            // Bottom boundary
            else if (codeOut & BOTTOM)
            {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }

            // Right boundary
            else if (codeOut & RIGHT)
            {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }

            // Left boundary
            else
            {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    return accept;
}

// Draw 9-region structure
void drawWindowWithRegions(int shiftX, int shiftY)
{
    setcolor(BLACK);

    rectangle(
        xmin + shiftX,
        ymin + shiftY,
        xmax + shiftX,
        ymax + shiftY
    );

    // Vertical extensions
    line(xmin + shiftX, shiftY,
         xmin + shiftX, 400 + shiftY);

    line(xmax + shiftX, shiftY,
         xmax + shiftX, 400 + shiftY);

    // Horizontal extensions
    line(shiftX, ymin + shiftY,
         400 + shiftX, ymin + shiftY);

    line(shiftX, ymax + shiftY,
         400 + shiftX, ymax + shiftY);

    // Region Labels
    outtextxy(40  + shiftX, 40  + shiftY, (char*)"1001");
    outtextxy(170 + shiftX, 40  + shiftY, (char*)"1000");
    outtextxy(330 + shiftX, 40  + shiftY, (char*)"1010");

    outtextxy(40  + shiftX, 180 + shiftY, (char*)"0001");
    outtextxy(170 + shiftX, 180 + shiftY, (char*)"0000");
    outtextxy(330 + shiftX, 180 + shiftY, (char*)"0010");

    outtextxy(40  + shiftX, 340 + shiftY, (char*)"0101");
    outtextxy(170 + shiftX, 340 + shiftY, (char*)"0100");
    outtextxy(330 + shiftX, 340 + shiftY, (char*)"0110");
}

int main()
{
    int n;

    cout << "Enter number of lines: ";
    cin >> n;

    double x1[20], y1[20], x2[20], y2[20];

    for (int i = 0; i < n; i++)
    {
        cout << "\nLine " << i + 1 << endl;

        cout << "Enter x1 y1 : ";
        cin >> x1[i] >> y1[i];

        cout << "Enter x2 y2 : ";
        cin >> x2[i] >> y2[i];
    }

    int width  = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    initwindow(width, height, "Cohen-Sutherland Line Clipping");
    setbkcolor(WHITE);
    cleardevice();

    // LEFT SIDE (Original)
    drawWindowWithRegions(
        LEFT_SHIFT_X,
        LEFT_SHIFT_Y
    );

    setcolor(BLUE);

    for (int i = 0; i < n; i++)
    {
        line(
            x1[i] + LEFT_SHIFT_X,
            y1[i] + LEFT_SHIFT_Y,
            x2[i] + LEFT_SHIFT_X,
            y2[i] + LEFT_SHIFT_Y
        );
    }

    outtextxy(
        LEFT_SHIFT_X + 150,
        100,
        (char*)"Original Lines"
    );

    // RIGHT SIDE (Clipped)
    drawWindowWithRegions(
        RIGHT_SHIFT_X,
        RIGHT_SHIFT_Y
    );

    setcolor(RED);

    for (int i = 0; i < n; i++)
    {
        double xa = x1[i];
        double ya = y1[i];
        double xb = x2[i];
        double yb = y2[i];

        if (cohenSutherlandClip(
                xa, ya,
                xb, yb))
        {
            line(
                xa + RIGHT_SHIFT_X,
                ya + RIGHT_SHIFT_Y,
                xb + RIGHT_SHIFT_X,
                yb + RIGHT_SHIFT_Y
            );
        }
    }

    outtextxy(
        RIGHT_SHIFT_X + 150,
        100,
        (char*)"Clipped Lines"
    );

    getch();
    closegraph();

    return 0;
}