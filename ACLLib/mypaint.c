#include <stdio.h>
#include "acllib.h"
#include <math.h>

#define WIDTH_OF_WINDOW 800
#define HEIGHT_OF_WINDOW 450

double f(int num_of_item, double *k, double x);

int Setup()
{
    initConsole();
    double Domain_min, Domain_max;
    int num_of_items;
    double k[num_of_items];
    printf("Lower limit of Domain:");
    scanf("%lf", &Domain_min);
    printf("Higher limit of Domain:");
    scanf("%lf", &Domain_max);
    if(Domain_max<Domain_min)
    {
        printf("The higher limit of Domain you entered is lower than the lower limit of Domain.\nThey will be exchanged.\n");
        double temp = Domain_min;
        Domain_min = Domain_max;
        Domain_max = temp;
    }
    printf("Number of items:");
    scanf("%d", &num_of_items);
    for (int i = 0; i < num_of_items;i++)
    {
        printf("Coefficient of item \"x^%d\":", i);
        scanf("%lf", &k[i]);
    }
    double number_of_pixels_for_1 = (WIDTH_OF_WINDOW / 2) / max(fabs(Domain_min), fabs(Domain_max));
    double dx = (Domain_max - Domain_min) / 6000;
    printf("dx = %lf", dx);
    initWindow("f(x)", DEFAULT, DEFAULT, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    beginPaint();
    line(0, HEIGHT_OF_WINDOW / 2, WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW / 2);
    line(WIDTH_OF_WINDOW / 2, 0, WIDTH_OF_WINDOW / 2, HEIGHT_OF_WINDOW);
    setPenColor(RED);
    double x, y;
    moveTo(WIDTH_OF_WINDOW / 2 + (int)(Domain_min * number_of_pixels_for_1), HEIGHT_OF_WINDOW / 2 - (int)(f(num_of_items, k, Domain_min) * number_of_pixels_for_1));
    for (x = Domain_min; x <= Domain_max; x += dx)
    {
        y = f(num_of_items, k, x);
        lineTo(WIDTH_OF_WINDOW / 2+(int)(x*number_of_pixels_for_1), HEIGHT_OF_WINDOW / 2-(int)(y*number_of_pixels_for_1));
        printf("%lf %lf\n", x, y);
    }
    endPaint();
    return 0;
}
// gcc ..\acllib\acllib.c mypaint.c -I..\acllib -lgdi32 -lole32 -loleaut32 -luuid -lwinmm -lmsimg32 -DWINVER=0x0501 -o mypaint

double f(int num_of_item, double *k, double x)
{
    double ret = 0;
    for (int i = 0; i < num_of_item;i++)
    {
        ret += k[i]*pow(x,i);
    }
    return ret;
}