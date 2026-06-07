#include <graphics.h>
#include <windows.h>
#include <iostream>

using namespace std;

#define MAX 50

struct Point
{
    float x, y;
};

Point input[MAX];

int xmin = 150;
int ymin = 150;
int xmax = 350;
int ymax = 300;

// Draw Polygon with horizontal shift
void drawPolygon(Point p[], int n, int color, int shiftX)
{
    setcolor(color);

    for(int i = 0; i < n; i++)
    {
        line(
            p[i].x + shiftX,
            p[i].y,
            p[(i + 1) % n].x + shiftX,
            p[(i + 1) % n].y
        );
    }
}

// Draw clipping window with shift
void drawWindow(int shiftX)
{
    rectangle(
        xmin + shiftX,
        ymin,
        xmax + shiftX,
        ymax
    );
}

// Inside Tests
bool insideLeft(Point p)
{
    return p.x >= xmin;
}

bool insideRight(Point p)
{
    return p.x <= xmax;
}

bool insideTop(Point p)
{
    return p.y >= ymin;
}

bool insideBottom(Point p)
{
    return p.y <= ymax;
}

// Intersection Functions
Point intersectLeft(Point s, Point p)
{
    Point i;

    i.x = xmin;

    i.y = s.y +
          (p.y - s.y) *
          (xmin - s.x) /
          (p.x - s.x);

    return i;
}

Point intersectRight(Point s, Point p)
{
    Point i;

    i.x = xmax;

    i.y = s.y +
          (p.y - s.y) *
          (xmax - s.x) /
          (p.x - s.x);

    return i;
}

Point intersectTop(Point s, Point p)
{
    Point i;

    i.y = ymin;

    i.x = s.x +
          (p.x - s.x) *
          (ymin - s.y) /
          (p.y - s.y);

    return i;
}

Point intersectBottom(Point s, Point p)
{
    Point i;

    i.y = ymax;

    i.x = s.x +
          (p.x - s.x) *
          (ymax - s.y) /
          (p.y - s.y);

    return i;
}

// Clip against Left Boundary
int clipLeft(Point in[], int n, Point out[])
{
    int k = 0;

    for(int i = 0; i < n; i++)
    {
        Point S = in[i];
        Point P = in[(i + 1) % n];

        bool Sin = insideLeft(S);
        bool Pin = insideLeft(P);

        if(Sin && Pin)
            out[k++] = P;

        else if(Sin && !Pin)
            out[k++] = intersectLeft(S, P);

        else if(!Sin && Pin)
        {
            out[k++] = intersectLeft(S, P);
            out[k++] = P;
        }
    }

    return k;
}

// Clip against Right Boundary
int clipRight(Point in[], int n, Point out[])
{
    int k = 0;

    for(int i = 0; i < n; i++)
    {
        Point S = in[i];
        Point P = in[(i + 1) % n];

        bool Sin = insideRight(S);
        bool Pin = insideRight(P);

        if(Sin && Pin)
            out[k++] = P;

        else if(Sin && !Pin)
            out[k++] = intersectRight(S, P);

        else if(!Sin && Pin)
        {
            out[k++] = intersectRight(S, P);
            out[k++] = P;
        }
    }

    return k;
}

// Clip against Top Boundary
int clipTop(Point in[], int n, Point out[])
{
    int k = 0;

    for(int i = 0; i < n; i++)
    {
        Point S = in[i];
        Point P = in[(i + 1) % n];

        bool Sin = insideTop(S);
        bool Pin = insideTop(P);

        if(Sin && Pin)
            out[k++] = P;

        else if(Sin && !Pin)
            out[k++] = intersectTop(S, P);

        else if(!Sin && Pin)
        {
            out[k++] = intersectTop(S, P);
            out[k++] = P;
        }
    }

    return k;
}

// Clip against Bottom Boundary
int clipBottom(Point in[], int n, Point out[])
{
    int k = 0;

    for(int i = 0; i < n; i++)
    {
        Point S = in[i];
        Point P = in[(i + 1) % n];

        bool Sin = insideBottom(S);
        bool Pin = insideBottom(P);

        if(Sin && Pin)
            out[k++] = P;

        else if(Sin && !Pin)
            out[k++] = intersectBottom(S, P);

        else if(!Sin && Pin)
        {
            out[k++] = intersectBottom(S, P);
            out[k++] = P;
        }
    }

    return k;
}

int main()
{
    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cout << "Vertex " << i + 1 << " : ";
        cin >> input[i].x >> input[i].y;
    }

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    initwindow(width, height, "Sutherland-Hodgman Polygon Clipping");
    setbkcolor(WHITE);
    cleardevice();

    // Right side offset
    int offset = width / 2;

    setcolor(BLACK);
    drawWindow(0);

    drawPolygon(input, n, BLUE, 0);

    Point temp1[MAX];
    Point temp2[MAX];

    int count;

    count = clipLeft(input, n, temp1);
    count = clipRight(temp1, count, temp2);
    count = clipTop(temp2, count, temp1);
    count = clipBottom(temp1, count, temp2);

    setcolor(BLACK);
    drawWindow(offset);

    drawPolygon(temp2, count, RED, offset);

    setcolor(BLUE);
    outtextxy(200,420,
        (char*)"Original Polygon");

    setcolor(RED);
    outtextxy(
        offset+200,420,
        (char*)"Clipped Polygon"
    );

    getch();
    closegraph();

    return 0;
}