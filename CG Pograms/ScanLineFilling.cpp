#include <graphics.h>
#include <iostream>
#include <algorithm>
#include <windows.h>
using namespace std;

int main()
{
    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    int x[20], y[20];

    cout << "Enter vertices:\n";

    for(int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Graphics Window");
    setbkcolor(WHITE);
    cleardevice();
    setcolor(RED);
    // Draw polygon
    for(int i = 0; i < n; i++)
    {
        line(x[i], y[i],
             x[(i+1)%n], y[(i+1)%n]);
    }

    int ymin = y[0];
    int ymax = y[0];

    for(int i = 1; i < n; i++)
    {
        ymin = min(ymin, y[i]);
        ymax = max(ymax, y[i]);
    }

    // Scan line filling
    for(int scanY = ymin; scanY <= ymax; scanY++)
    {
        float interX[20];
        int count = 0;

        for(int i = 0; i < n; i++)
        {
            int x1 = x[i];
            int y1 = y[i];

            int x2 = x[(i+1)%n];
            int y2 = y[(i+1)%n];

            if(y1 > y2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }

            if(scanY >= y1 && scanY < y2)
            {
                float xi = x1 +
                    (float)(scanY - y1) *
                    (x2 - x1) /
                    (y2 - y1);

                interX[count++] = xi;
            }
        }

        sort(interX, interX + count);

        for(int i = 0; i < count-1; i += 2)
        {
            line((int)interX[i],
                 scanY,
                 (int)interX[i+1],
                 scanY);
        }
    }

    getch();
    closegraph();

    return 0;
}