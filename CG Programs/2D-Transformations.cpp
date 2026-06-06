#include <graphics.h>
#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

const int XC = 640;  // Origin X
const int YC = 360;  // Origin Y

// Convert Cartesian coordinates to screen coordinates
int sx(int x)
{
    return XC + x;
}

int sy(int y)
{
    return YC - y;
}

// Draw coordinate axes
void drawAxes()
{
    setcolor(WHITE);

    // X-axis
    line(0, YC, getmaxx(), YC);

    // Y-axis
    line(XC, 0, XC, getmaxy());

    outtextxy(getmaxx()-20, YC+5, (char*)"X");
    outtextxy(XC+5, 10, (char*)"Y");
}

// Draw polygon
void drawPolygon(int x[], int y[], int n, int color)
{
    setcolor(color);

    for(int i = 0; i < n; i++)
    {
        line(
            sx(x[i]), sy(y[i]),
            sx(x[(i+1)%n]), sy(y[(i+1)%n])
        );
    }
}

int main()
{
    int n;

    cout<<"Enter number of vertices: ";
    cin>>n;

    int x[20], y[20];
    int tx[20], ty[20];

    cout<<"\nEnter vertices (x y):\n";

    for(int i=0;i<n;i++)
    {
        cin>>x[i]>>y[i];
        tx[i]=x[i];
        ty[i]=y[i];
    }

    int choice;

    cout<<"\n----- 2D Transformations -----\n";
    cout<<"1. Translation\n";
    cout<<"2. Scaling\n";
    cout<<"3. Rotation\n";
    cout<<"4. Reflection\n";
    cout<<"5. Shearing\n";
    cout<<"Enter choice: ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            int dx,dy;

            cout<<"Enter tx and ty: ";
            cin>>dx>>dy;

            for(int i=0;i<n;i++)
            {
                tx[i]=x[i]+dx;
                ty[i]=y[i]+dy;
            }

            break;
        }

        case 2:
        {
            float sxf, syf;

            cout<<"Enter scaling factors Sx and Sy: ";
            cin>>sxf>>syf;

            for(int i=0;i<n;i++)
            {
                tx[i]=round(x[i]*sxf);
                ty[i]=round(y[i]*syf);
            }

            break;
        }

        case 3:
        {
            float angle;

            cout<<"Enter angle (degrees): ";
            cin>>angle;

            float rad = angle * M_PI / 180.0;

            for(int i=0;i<n;i++)
            {
                tx[i]=round(
                    x[i]*cos(rad) - y[i]*sin(rad)
                );

                ty[i]=round(
                    x[i]*sin(rad) + y[i]*cos(rad)
                );
            }

            break;
        }

        case 4:
        {
            int ref;

            cout<<"\n1. About X-axis";
            cout<<"\n2. About Y-axis";
            cout<<"\n3. About Origin";
            cout<<"\nEnter choice: ";
            cin>>ref;

            for(int i=0;i<n;i++)
            {
                switch(ref)
                {
                    case 1:
                        tx[i]=x[i];
                        ty[i]=-y[i];
                        break;

                    case 2:
                        tx[i]=-x[i];
                        ty[i]=y[i];
                        break;

                    case 3:
                        tx[i]=-x[i];
                        ty[i]=-y[i];
                        break;
                }
            }

            break;
        }

        case 5:
        {
            float shx, shy;

            cout<<"Enter Shx and Shy: ";
            cin>>shx>>shy;

            for(int i=0;i<n;i++)
            {
                tx[i]=round(x[i] + shx*y[i]);
                ty[i]=round(y[i] + shy*x[i]);
            }

            break;
        }

        default:
            cout<<"Invalid Choice!";
    }

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Graphics Window");

    drawAxes();

    // Draw original polygon
    drawPolygon(x,y,n,YELLOW);

    // Draw transformed polygon
    drawPolygon(tx,ty,n,RED);

    setcolor(YELLOW);
    outtextxy(20,20,(char*)"Original Object");

    setcolor(RED);
    outtextxy(20,40,(char*)"Transformed Object");

    getch();
    closegraph();

    return 0;
}