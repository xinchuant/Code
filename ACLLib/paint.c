#include "acllib.h"
#include <stdio.h>
#include <math.h>
double f(int n, double a[], double x)
{
    int i;
    double y = 0.0;
    for (i = 0; i < n; i++)
    {
        y += a[i] * pow(x, n - i - 1);
    }
    return y;
}
double fmax(double a, double b)
{
    if (a >= b)
        return a;
    else
        return b;
}
double fmin(double a, double b)
{
    if (a <= b)
        return a;
    else
        return b;
}
int Setup()
{
    initConsole();
    int n, i;
    int X, Y;
    scanf("%d", &n);
    double k[n];
    for (i = 0; i < n; i++)
    {
        scanf("%lf", &k[i]);
    }
    double a, b, maxx, maxy, x, y, dx, dy;
    scanf("%lf %lf", &a, &b);
    X = 600;
    Y = 350;
    maxx = fmax(fabs(a), fabs(b));
    int j;
    maxy = 0;
    for (x = a; x <= b; x += 0.00001)
    {
        y = f(n, k, x);
        maxy = (maxy, fabs(y));
    }
    dx = X / maxx;
    dy = Y / maxy;
    initWindow("paint", DEFAULT, DEFAULT, 2 * X + 20, 2 * Y + 20);
    beginPaint();
    putPixel(540, 280, RED);
    char p;
    p = '0';
    paintText(X, Y, &p);
    line(0, Y + 10, 2 * X + 20, Y + 10);
    line(X + 10, 0, X + 10, 2 * Y);
    setPenColor(RED);
    moveTo(X + 10 + ((int)a) * dx, Y + 10 - ((int)f(n, k, a)) * dy);
    double xx = (b - a) / 5000;
    for (x = a; x <= b; x += xx)
    {
        y = f(n, k, x);
        lineTo(X + 10 + (int)(x * dx), Y + 10 - (int)(dy * y));
    }
    endPaint();
    return 0;
}
// gcc ..\acllib\acllib.c paint.c -I..\acllib -lgdi32 -lole32 -loleaut32 -luuid -lwinmm -lmsimg32 -DWINVER=0x0501 -o paint