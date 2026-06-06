#include <graphics.h>
#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

const int ORGX = 640;
const int ORGY = 360;

// Projection constants
const double PX = 0.5;
const double PY = 0.5;

struct Point3D
{
    double x, y, z;
};

// Convert 3D point to screen coordinates
void project(Point3D p, int &sx, int &sy)
{
    sx = ORGX + p.x + PX * p.z;
    sy = ORGY - p.y - PY * p.z;
}

// Draw 3D axes
void drawAxes3D()
{
    setcolor(WHITE);

    // X-axis
    line(ORGX - 300, ORGY,
         ORGX + 300, ORGY);

    // Y-axis
    line(ORGX, ORGY + 250,
         ORGX, ORGY - 250);

    // Z-axis
    line(ORGX, ORGY,
         ORGX + 180,
         ORGY - 180);

    outtextxy(ORGX + 310, ORGY, (char*)"X");
    outtextxy(ORGX, ORGY - 260, (char*)"Y");
    outtextxy(ORGX + 190, ORGY - 190, (char*)"Z");
}

// Draw cube
void drawCube(Point3D v[], int color)
{
    setcolor(color);

    int sx[8], sy[8];

    for(int i=0;i<8;i++)
        project(v[i], sx[i], sy[i]);

    // Front face
    line(sx[0],sy[0],sx[1],sy[1]);
    line(sx[1],sy[1],sx[2],sy[2]);
    line(sx[2],sy[2],sx[3],sy[3]);
    line(sx[3],sy[3],sx[0],sy[0]);

    // Back face
    line(sx[4],sy[4],sx[5],sy[5]);
    line(sx[5],sy[5],sx[6],sy[6]);
    line(sx[6],sy[6],sx[7],sy[7]);
    line(sx[7],sy[7],sx[4],sy[4]);

    // Connecting edges
    line(sx[0],sy[0],sx[4],sy[4]);
    line(sx[1],sy[1],sx[5],sy[5]);
    line(sx[2],sy[2],sx[6],sy[6]);
    line(sx[3],sy[3],sx[7],sy[7]);
}

int main()
{
    double side;

    cout<<"Enter cube side length: ";
    cin>>side;

    Point3D cube[8];
    Point3D tCube[8];

    // Cube vertices
    cube[0]={0,0,0};
    cube[1]={side,0,0};
    cube[2]={side,side,0};
    cube[3]={0,side,0};

    cube[4]={0,0,side};
    cube[5]={side,0,side};
    cube[6]={side,side,side};
    cube[7]={0,side,side};

    for(int i=0;i<8;i++)
        tCube[i]=cube[i];

    int choice;

    cout<<"\n3D Transformations\n";
    cout<<"1. Translation\n";
    cout<<"2. Scaling\n";
    cout<<"3. Rotation about X-axis\n";
    cout<<"4. Rotation about Y-axis\n";
    cout<<"5. Rotation about Z-axis\n";
    cout<<"6. Reflection about XY-plane\n";
    cout<<"7. Reflection about YZ-plane\n";
    cout<<"8. Reflection about ZX-plane\n";
    cout<<"9. Shearing\n";

    cout<<"\nEnter choice: ";
    cin>>choice;

    switch(choice)
    {
        case 1:
        {
            double tx,ty,tz;

            cout<<"Enter Tx Ty Tz: ";
            cin>>tx>>ty>>tz;

            for(int i=0;i<8;i++)
            {
                tCube[i].x += tx;
                tCube[i].y += ty;
                tCube[i].z += tz;
            }
            break;
        }

        case 2:
        {
            double sx,sy,sz;

            cout<<"Enter Sx Sy Sz: ";
            cin>>sx>>sy>>sz;

            for(int i=0;i<8;i++)
            {
                tCube[i].x *= sx;
                tCube[i].y *= sy;
                tCube[i].z *= sz;
            }
            break;
        }

        case 3:
        {
            double angle;
            cout<<"Angle: ";
            cin>>angle;

            double rad = angle*M_PI/180.0;

            for(int i=0;i<8;i++)
            {
                double y=tCube[i].y;
                double z=tCube[i].z;

                tCube[i].y = y*cos(rad)-z*sin(rad);
                tCube[i].z = y*sin(rad)+z*cos(rad);
            }
            break;
        }

        case 4:
        {
            double angle;
            cout<<"Angle: ";
            cin>>angle;

            double rad = angle*M_PI/180.0;

            for(int i=0;i<8;i++)
            {
                double x=tCube[i].x;
                double z=tCube[i].z;

                tCube[i].x = x*cos(rad)+z*sin(rad);
                tCube[i].z = -x*sin(rad)+z*cos(rad);
            }
            break;
        }

        case 5:
        {
            double angle;
            cout<<"Angle: ";
            cin>>angle;

            double rad = angle*M_PI/180.0;

            for(int i=0;i<8;i++)
            {
                double x=tCube[i].x;
                double y=tCube[i].y;

                tCube[i].x = x*cos(rad)-y*sin(rad);
                tCube[i].y = x*sin(rad)+y*cos(rad);
            }
            break;
        }

        case 6:
        {
            for(int i=0;i<8;i++)
                tCube[i].z = -tCube[i].z;
            break;
        }

        case 7:
        {
            for(int i=0;i<8;i++)
                tCube[i].x = -tCube[i].x;
            break;
        }

        case 8:
        {
            for(int i=0;i<8;i++)
                tCube[i].y = -tCube[i].y;
            break;
        }

        case 9:
        {
            double shx,shy,shz;

            cout<<"Enter Shx Shy Shz: ";
            cin>>shx>>shy>>shz;

            for(int i=0;i<8;i++)
            {
                double x=tCube[i].x;
                double y=tCube[i].y;
                double z=tCube[i].z;

                tCube[i].x = x + shx*y;
                tCube[i].y = y + shy*z;
                tCube[i].z = z + shz*x;
            }
            break;
        }

        default:
            cout<<"Invalid Choice";
    }

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    initwindow(width, height, "Graphics Window");

    drawAxes3D();
    drawCube(cube,YELLOW); //Original cube
    drawCube(tCube, RED);  //Transformed Cube

    setcolor(YELLOW);
    outtextxy(20,20,(char*)"Original Cube");

    setcolor(RED);
    outtextxy(20,40,(char*)"Transformed Cube");

    getch();
    closegraph();

    return 0;
}