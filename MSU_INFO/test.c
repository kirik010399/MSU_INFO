#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "plot_x11.h"

static int n;
static double a;
static double b;

static double *x = NULL;
static double *f_x = NULL;
static double *c = NULL;
static double *d = NULL;
static double *a1 = NULL;
static double *b1 = NULL;

/* Вариант рисуемого графика */
static int variant = 0;

double x_left = -5, x_right = 9;

double scale = 1;

double func(double x);
double func(double x)
{
    return sin(x);
}

/* Нарисовать содержимое окна */
static void
DrawWindowContent (void)
{
    int width = nWWidth;        /* Текущая ширина экрана */
    int height = nWHeight;    /* Текущая высота экрана */
    
    WSetColor (DARKGRAY);
    WFillRectangle (0, 0, width, height);
    
    WSetColor (BLACK);
    WDrawLine (0, height / 2, width, height / 2);
    WDrawLine (width * abs(x_left) / (x_right - x_left), 0, width * abs(x_left) / (x_right - x_left), height);
    
    WDrawString ("Press Q to quit, F1...F4 to change function", 10, 20);
    
    switch (variant)
    {
        case 1:
            WSetColor (BLUE);
            WDrawLine (0, height, width, 0);
            break;
        case 2:
            WSetColor (GREEN);
            WDrawLine (0, 0, width, height);
            break;
        case 3:
            WSetColor (BLUE);
        {
            int i;
            double x_start, y_start, x_end, y_end;
            
            for (i = 1; i < width; i++)
            {
                x_start = i - 1;
                y_start = (x_start - width / 2) * (x_start  - width / 2) / (width / 2 * width / 2) * height;
                x_end = i;
                y_end = (x_end  - width / 2) * (x_end  - width / 2) / (width / 2 * width / 2) * height;
                WDrawLine (x_start, y_start, x_end, y_end);
            }
        }
            break;
        case 4:
            WSetColor (GREEN);
        {
            int i;
            double x_start, y_start, x_end, y_end;
            
            for (i = 1; i < width; i++)
            {
                x_start = i - 1;
                y_start = (1. - (x_start - width / 2) * (x_start  - width / 2) / (width / 2 * width / 2)) * height;
                x_end = i;
                y_end = (1. - (x_end    - width / 2) * (x_end  - width / 2) / (width / 2 * width / 2)) * height;
                WDrawLine (x_start, y_start, x_end, y_end);
            }
        }
            break;
        case 5:
            WSetColor (MAGENTA);
        {
            int i;
            double x_start, y_start, x_end, y_end;
            double x_start2, y_start2, x_end2, y_end2;
            
            for (i = 1; i < width; i++) {
                x_start = i - 1;
                x_end = i;
                
                x_start2 = (x_start * (x_right - x_left) / width + x_left) / scale;
                x_end2 = (x_end * (x_right - x_left) / width + x_left) / scale;
                y_start2 = func(x_start2) * scale;
                y_end2 = func(x_end2) * scale;
                
                y_start = height / 2 - y_start2 * width / (x_right - x_left);
                y_end = height / 2 - y_end2 * width / (x_right - x_left);
                
                WDrawLine (x_start, y_start, x_end, y_end);
                
            }
        }
            break;
        case 6:
            WSetColor(RED);
        {
            DrawFunction(width, height, f_14);
        }
            break;
    }
}

static int
KeyPressFunction (int nKeySym)
{
    switch (nKeySym)
    {
        case XK_Q:
        case XK_q:
            return KEY_PRESS_QUIT;
            
        case XK_F1:
        case XK_1:
            variant = 1;
            WSetTitle ("Function 1");
            break;
        case XK_F2:
        case XK_2:
            variant = 2;
            WSetTitle ("Function 2");
            break;
        case XK_F3:
        case XK_3:
            variant = 3;
            WSetTitle ("Function 3");
            break;
        case XK_F4:
        case XK_4:
            variant = 4;
            WSetTitle ("Function 4");
            break;
        case XK_F5:
        case XK_5:
            variant = 5;
            WSetTitle ("Function 5");
            break;
        case XK_F6:
        case XK_6:
            variant = 6;
            WSetTitle ("Function 6");
            Input_14();
            Coeff_14(n, x, f_x, c, d, a1, b1);
            break;
        case XK_KP_Add:
            scale *= 1.1;
            break;
        case XK_KP_Subtract:
            scale /= 1.1;
            break;
        default:
            return KEY_PRESS_NOTHING;
    }
    
    /* Перерисовать окно */
    return KEY_PRESS_EXPOSE;
}

void Coeff_14(int n, double *x, double *f_x, double *c, double *d, double *a1, double *b1)
{
    int i, j;
    double tmp1, tmp2;
    
    for (i = 2; i < n - 2; i++)
        d[i] = f_first(x[i]);
    
    for (i = 0; i < 16; i++)
        a1[i] = 0.0;
    
    a1[4 * 0 + 0] = 1.0;
    a1[4 * 0 + 1] = (x[0] - x[2]);
    a1[4 * 0 + 2] = (x[0] - x[2]) * (x[0] - x[2]);
    a1[4 * 0 + 3] = (x[0] - x[2]) * (x[0] - x[2]) * (x[0] - x[2]);
    
    a1[4 * 1 + 0] = 1.0;
    a1[4 * 1 + 1] = (x[1] - x[2]);
    a1[4 * 1 + 2] = (x[1] - x[2]) * (x[1] - x[2]);
    a1[4 * 1 + 3] = (x[1] - x[2]) * (x[1] - x[2]) * (x[1] - x[2]);
    
    a1[4 * 2 + 0] = 1.0;
    
    a1[4 * 3 + 1] = 1.0;
    
    b1[0] = f_x[0]; b1[1] = f_x[1]; b1[2] = f_x[2]; b1[3] = d[2];
    
    SolveSystem(4, a1, b1, c);
    
    for (i = 0; i < 16; i++)
        a1[i] = 0.0;
    
    a1[4 * 0 + 0] = 1.0;
    
    a1[4 * 1 + 0] = 1.0;
    a1[4 * 1 + 1] = (x[n - 2] - x[n - 3]);
    a1[4 * 1 + 2] = (x[n - 2] - x[n - 3]) * (x[n - 2] - x[n - 3]);
    a1[4 * 1 + 3] = (x[n - 2] - x[n - 3]) * (x[n - 2] - x[n - 3]) * (x[n - 2] - x[n - 3]);
    
    a1[4 * 2 + 0] = 1.0;
    a1[4 * 2 + 1] = (x[n - 1] - x[n - 3]);
    a1[4 * 2 + 2] = (x[n - 1] - x[n - 3]) * (x[n - 1] - x[n - 3]);
    a1[4 * 2 + 3] = (x[n - 1] - x[n - 3]) * (x[n - 1] - x[n - 3]) * (x[n - 1] - x[n - 3]);
    
    a1[4 * 3 + 1] = 1.0;
    
    b1[0] = f_x[n - 3]; b1[1] = f_x[n - 2]; b1[2] = f_x[n - 1]; b1[3] = d[n - 3];
    
    SolveSystem(4, a1, b1, c + 4 * (n - 4));
    
    j = 4;
    
    for (i = 2; i < n - 3; i++)
    {
        c[j + 0] = f_x[i];
        c[j + 1] = d[i];
        tmp2 = x[i + 1] - x[i];
        tmp1 = (f_x[i + 1] - f_x[i]) / tmp2;
        c[j + 2] = (3 * tmp1 - 2 * d[i] - d[i + 1]) / tmp2;
        tmp2 *= tmp2;
        c[j + 3] = (d[i] + d[i + 1] - 2 * tmp1) / tmp2;
        j += 4;
    }
}

double f_14(double t)
{
    return Value_14(t, n, c, x);
}

double Value_14(double t, int n, double *c, double *x)
{
    int i;
    
    if (t <= x[2]) return c[0] + c[1] * (t - x[2]) + c[2] * (t - x[2]) * (t - x[2]) +
        c[3] * (t - x[2]) * (t - x[2]) * (t - x[2]);
    
    for (i = 2; i < n - 3; i++)
    {
        if (t <= x[i + 1]) return c[4 * (i - 1)] + c[4 * (i - 1) + 1] * (t - x[i]) +
            c[4 * (i - 1) + 2] * (t - x[i]) * (t - x[i]) +
            c[4 * (i - 1) + 3] * (t - x[i]) * (t - x[i]) * (t - x[i]);
    }
    
    return c[4 * (n - 4)] + c[4 * (n - 4) + 1] * (t - x[n - 3]) +
    c[4 * (n - 4) + 2] * (t - x[n - 3]) * (t - x[n - 3]) +
    c[4 * (n - 4) + 3] * (t - x[n - 3]) * (t - x[n - 3]) * (t - x[n - 3]);
}

int Init_14(int n_, double a_, double b_)
{
    n = n_;
    a = a_;
    b = b_;
    
    x = (double*)malloc(n * sizeof(double));
    f_x = (double*)malloc(n * sizeof(double));
    c = (double*)malloc(4 * (n - 3) * sizeof(double));
    d = (double*)malloc(n * sizeof(double));
    a1 = (double*)malloc(16 * sizeof(double));
    b1 = (double*)malloc(4 * sizeof(double));
    
    if (!(x && f_x && c && d && a1 && b1)) return 0;
    
    return 1;
}

void Finalize_14(void)
{
    if (x) free(x); x = NULL;
    if (f_x) free(f_x); f_x = NULL;
    if (c) free(c); c = NULL;
    if (d) free(d); d = NULL;
    if (a1) free(a1); a1 = NULL;
    if (b1) free(b1); b1 = NULL;
}

void Input_14(void)
{
    int i;
    double h;
    
    h = (b - a)/(n - 1);
    for (i = 0; i < n; i++)
    {
        x[i] = a + i * h;
        f_x[i] = f(x[i]);
    }
}

void DrawFunction(int width, int height, double (*func)(double x))
{
    int i;
    double hx, hy;
    double x, y_start, y_end;
    
    hx = (x_right - x_left)/(width - 1);
    hy = height/(y_up - y_down);
    
    y_start = height - (func(x_left) - y_down) * hy;
    
    for (i = 1; i < width; i++)
    {
        x = x_left + i * hx;
        y_end = height - (func(x) - y_down) * hy;
        xlibDrawLine(i - 1, y_start, i, y_end);
        y_start = y_end;
    }
}

int main (void)
{
    int ret_code;
    
    /* Вывод на экран X11. */
    ret_code = DrawWindow (DrawWindowContent, KeyPressFunction);
    if (ret_code)
    {
        switch (ret_code)
        {
            case PLOT_X11_ERR_1:
                printf ("%s\n", PLOT_X11_ERR_MSG_1);
                break;
            case PLOT_X11_ERR_2:
                printf ("%s\n", PLOT_X11_ERR_MSG_2);
                break;
            case PLOT_X11_ERR_3:
                printf ("%s\n", PLOT_X11_ERR_MSG_3);
                break;
            case PLOT_X11_ERR_4:
                printf ("%s\n", PLOT_X11_ERR_MSG_4);
                break;
            case PLOT_X11_ERR_5:
                printf ("%s\n", PLOT_X11_ERR_MSG_5);
                break;
            default:
                printf ("%s\n", PLOT_X11_ERR_MSG_DEF);
                break;
        }
        return ret_code;
    }
    
#ifdef CONSOLE_INPUT
    printf("Enter a and b: ");
    scanf("%lg %lg", &a, &b);
    printf("Enter n: ");
    scanf("%d", &n);
#endif
    
    if (b <= a || n < 3)
    {
        printf("Input error.\n");
        return 0;
    }
    
    x_left = a;
    x_right = b;
    Init_14(n, a, b);
    
    return 0;
}

