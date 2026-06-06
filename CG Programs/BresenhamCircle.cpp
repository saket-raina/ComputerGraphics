#include <direct.h>
#include <graphics.h>
#include <iostream>
#include <windows.h>
using namespace std;

void drawCircle(int xc, int yc, int x, int y){
    putpixel(xc+x, yc+y, WHITE);
    putpixel(xc-x, yc+y, WHITE);
    putpixel(xc+x, yc-y, WHITE);
    putpixel(xc-x, yc-y, WHITE);
    putpixel(xc+y, yc+x, WHITE);
    putpixel(xc-y, yc+x, WHITE);
    putpixel(xc+y, yc-x, WHITE);
    putpixel(xc-y, yc-x, WHITE);
}

// Function for circle-generation
// using Bresenham's algorithm
void circleBres(int xc, int yc, int r){
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y);
    while (y >= x){
      
        if (d > 0) {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;

        // Increment x after updating decision parameter
        x++;
        
        // Draw the circle using the new coordinates
        drawCircle(xc, yc, x, y);
    }
}

int main()
{   
    int xc, yc, r;
    cout<<"Circle Generation using Bresenham's Algorithm"<<endl;
    cout<<"Enter the center coordinates (xc, yc) and radius r: "<<endl;
    cin>>xc>>yc>>r;

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Graphics Window");

    circleBres(xc, yc, r);    // function call
    getch();
    return 0;
}