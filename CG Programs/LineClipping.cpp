#include <graphics.h>
#include <iostream>
#include <windows.h>
using namespace std;

// Region Codes
const int INSIDE = 0; // 0000
const int LEFT   = 1; // 0001
const int RIGHT  = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP    = 8; // 1000

// Clipping Window
int xmin = 100, ymin = 100;
int xmax = 300, ymax = 300;

// Compute Region Code
int computeCode(double x, double y)
{
    int code = INSIDE;

    if(x < xmin)
        code |= LEFT;
    else if(x > xmax)
        code |= RIGHT;

    if(y < ymin)
        code |= TOP;
    else if(y > ymax)
        code |= BOTTOM;

    return code;
}

// Cohen-Sutherland Algorithm
bool cohenSutherlandClip(
    double &x1, double &y1,
    double &x2, double &y2)
{
    int code1 = computeCode(x1,y1);
    int code2 = computeCode(x2,y2);

    bool accept = false;

    while(true)
    {
        if((code1 | code2) == 0)
        {
            accept = true;
            break;
        }

        else if(code1 & code2)
        {
            break;
        }

        else
        {
            double x,y;

            int codeOut =
                code1 ? code1 : code2;

            if(codeOut & TOP)
            {
                x = x1 + (x2-x1) *
                    (ymin-y1)/(y2-y1);
                y = ymin;
            }

            else if(codeOut & BOTTOM)
            {
                x = x1 + (x2-x1) *
                    (ymax-y1)/(y2-y1);
                y = ymax;
            }

            else if(codeOut & RIGHT)
            {
                y = y1 + (y2-y1) *
                    (xmax-x1)/(x2-x1);
                x = xmax;
            }

            else
            {
                y = y1 + (y2-y1) *
                    (xmin-x1)/(x2-x1);
                x = xmin;
            }

            if(codeOut == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1,y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2,y2);
            }
        }
    }

    return accept;
}

// Draw 9-cell clipping structure
void drawWindowWithRegions(
        int shiftX,
        int shiftY)
{
    setcolor(WHITE);

    rectangle(
        xmin+shiftX,
        ymin+shiftY,
        xmax+shiftX,
        ymax+shiftY
    );

    // Vertical extensions
    line(xmin+shiftX,0+shiftY,
         xmin+shiftX,400+shiftY);

    line(xmax+shiftX,0+shiftY,
         xmax+shiftX,400+shiftY);

    // Horizontal extensions
    line(0+shiftX,ymin+shiftY,
         400+shiftX,ymin+shiftY);

    line(0+shiftX,ymax+shiftY,
         400+shiftX,ymax+shiftY);

    // Region Labels
    outtextxy(40+shiftX,40+shiftY,
             (char*)"1001");

    outtextxy(170+shiftX,40+shiftY,
             (char*)"1000");

    outtextxy(330+shiftX,40+shiftY,
             (char*)"1010");

    outtextxy(40+shiftX,180+shiftY,
             (char*)"0001");

    outtextxy(170+shiftX,180+shiftY,
             (char*)"0000");

    outtextxy(330+shiftX,180+shiftY,
             (char*)"0010");

    outtextxy(40+shiftX,340+shiftY,
             (char*)"0101");

    outtextxy(170+shiftX,340+shiftY,
             (char*)"0100");

    outtextxy(330+shiftX,340+shiftY,
             (char*)"0110");
}

int main()
{
    int n;

    cout<<"Enter number of lines: ";
    cin>>n;

    double x1[20],y1[20],x2[20],y2[20];

    for(int i=0;i<n;i++)
    {
        cout<<"\nLine "<<i+1<<"\n";

        cout<<"x1 y1 : ";
        cin>>x1[i]>>y1[i];

        cout<<"x2 y2 : ";
        cin>>x2[i]>>y2[i];
    }
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Graphics Window");
    
    // LEFT SIDE
    drawWindowWithRegions(0,0);

    setcolor(YELLOW);

    for(int i=0;i<n;i++)
    {
        line(
            x1[i],y1[i],
            x2[i],y2[i]
        );
    }

    outtextxy(120,420,
        (char*)"Original Lines");

    // RIGHT SIDE
    int offset = 500;

    drawWindowWithRegions(offset,0);

    setcolor(WHITE);

    for(int i=0;i<n;i++)
    {
        double xa=x1[i];
        double ya=y1[i];
        double xb=x2[i];
        double yb=y2[i];

        if(
            cohenSutherlandClip(
                xa,ya,xb,yb))
        {
            line(
                xa+offset,
                ya,
                xb+offset,
                yb
            );
        }
    }

    outtextxy(
        offset+120,
        420,
        (char*)"Clipped Lines"
    );

    getch();
    closegraph();

    return 0;
}