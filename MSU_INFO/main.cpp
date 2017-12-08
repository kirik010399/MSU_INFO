#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <locale>
#include "RealStack.h"
#include <iostream>
#include <math.h>
using namespace std;
FILE *in, *out;

static void onNOD();
static void onAdd();
static void onSub();
static void onMul();
static void onDiv();
static void onPush(const char* line);
static void onPop();
static void onInit();
static void display();
static void onShow();
int nod(int,int);
static void onPower();
static void onPow();
static void onExp();
static void onSin();
static void onCos();
static void onTg();
double sin (double a);
double cos (double a);
static void onArcsin();
static void onArccos();
static void onArctg();
double arcsin (double a);
double arccos (double a);
double arctg (double a);


static RealStack *stack = 0;

int main() {
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    char line[256];
    stack = new RealStack();
    
    // gets(line);
    int res = fscanf(in, "%s", line);
    while (res != EOF && *line != 0) {
        int linelen = strlen(line);
        try {
            if (strcmp(line, "+") == 0)
                onAdd();
            else if (strcmp(line, "-") == 0)
                onSub();
            else if (strcmp(line, "%") == 0)
                onNOD();
            
            
            else if (strcmp(line, "*") == 0)
                onMul();
            else if (strcmp(line, "/") == 0)
                onDiv();
            else if (strcmp(line, "=") == 0)
                display();
            else if (
                     (linelen > 0 && isdigit(line[0])) ||
                     (linelen > 1 && (line[0] == '-' || line[0] == '+') &&
                      isdigit(line[1]))
                     )
                onPush(line);
            else if (strcmp(line, "pop") == 0)
                onPop();
            else if (strcmp(line, "init") == 0)
                onInit();
            else if (strcmp(line, "show") == 0)
                onShow();
            else if (strcmp(line, "power") == 0)
                onPower();
            else if (strcmp(line, "pow") == 0)
                onPow();
            else if (strcmp(line, "exp") == 0)
                onExp();
            else if (strcmp(line, "sin") == 0)
                onSin();
            else if (strcmp(line, "cos") == 0)
                onCos();
            else if (strcmp(line, "tg") == 0)
                onTg();
            else if (strcmp(line, "arcsin") == 0)
                onArcsin();
            else if (strcmp(line, "arccos") == 0)
                onArccos();
            else if (strcmp(line, "arctg") == 0)
                onArctg();
            else if (
                     strcmp(line, "") == 0 ||
                     (linelen > 0 && (line[0] == 'q' || line[0] == 'Q'))
                     )
                break;
        } catch (StackException& e) {
            fprintf(out, "Stack Exception: %s\n", e.reason);
        }
        // gets(line);
        res = fscanf(in, "%s", line);
    }
    
    delete stack;
    fclose(in);
    fclose(out);
    return 0;
}

static void onAdd() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push(x + y);
    display();
}


static void onNOD() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push((double)nod((int)x , (int)y));
    display();
}

static void onSub() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push(x - y);
    display();
}

static void onMul() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push(x * y);
    display();
}

static void onDiv() {
    double y = stack->pop();
    double x = stack->pop();
    stack->push(x / y);
    display();
}

static void onPush(const char* line) {
    double x = atof(line);
    stack->push(x);
}

static void onPop() {
    stack->pop();
}

static void onInit() {
    stack->init();
}

static void display() {
    if (!stack->empty()) {
        double a = stack->top();
        if (isnan(a))
            fprintf(out, "nan\n");
        else
           fprintf(out, "%lf\n", a);
    } else {
        fprintf(out, "stack empty\n");
    }
}

static void onShow() {
    int d = stack->depth();
    int i;
    fprintf(out, "[");
    for (i = 0; i < d; ++i) {
        fprintf(out, "%lf%s", stack->elementAt(i), (i < d - 1) ? ", " : "");
    }
    fprintf(out, "]\n");
}

int nod(int x, int y)
{
    if (y == 0)
        return abs(x);
    else
        return nod(y, x % y);
}

static void onPow()
{
    if (stack->depth()<2)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    
    int d = (int)stack->pop();
    double x = stack->pop();
    
    if (x<0 || d<0)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    
    double res = 1;
    
    while (d > 0)
    {
        if (d%2 == 1)
            res*=x;
        
        x*=x;
        d/=2;
    }
    
    stack->push(res);
    display();
}

static void onPower()
{
    if (stack->depth()<3)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    
    int m = (int)stack->pop();
    int d = (int)stack->pop();
    double x = stack->pop();

    if (x<0 || d<0 || m<0)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
        
    double res = 1;
    
    while (d > 0)
    {
        if (d%2 == 1)
            res*=x;
        
        x*=x;
        d/=2;
    }
    
    while (res>=m)
        res-=m;
    
    stack->push(res);
    display();
}

static void onExp()
{
    if (stack->depth() < 1)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    else
    {
        double x = stack->pop();
        double res = 0, d = 1, fact = 1;
        int i = 1;
        
        while (d/fact>=0.0000000001 || d/fact<=-0.0000000001)
        {
            res+=d/fact;
            d*=x;
            fact*=i;
            i++;
        }
        
        stack->push(res);
        display();
    }
}

static void onSin()
{
    if (stack->depth() < 1)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    else
    {
        double x = stack->pop();
        
        double res = sin (x);
        
        stack->push(res);
        display();
    }
}

static void onCos()
{
    if (stack->depth() < 1)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    else
    {
        double x = stack->pop();
       
        double res = cos(x);
        
        stack->push(res);
        display();
    }
}

double cos (double x)
{
    if (x>0)
        while (x>=2*M_PI)
        {
            x-=2*M_PI;
        }
    else
        while (x<=-2*M_PI)
        {
            x+=2*M_PI;
        }
    
    double res = 0, d = 1, fact = 1;
    int i = 1;
    
    while (d/fact>=0.0000000000001 || d/fact<=-0.0000000000001)
    {
        if (i%2==1)
        {
            if (i%4==1)
                res+=d/fact;
            else if (i%4==3)
                res-=d/fact;
        }
        d*=x;
        fact*=i;
        i++;
    }
    
    return res;
}

double sin (double x)
{
    if (x>0)
        while (x>=2*M_PI)
        {
            x-=2*M_PI;
        }
    else
        while (x<=-2*M_PI)
        {
            x+=2*M_PI;
        }
    
    double res = 0, d = 1, fact = 1;
    int i = 1;
    
    while (d/fact>=0.0000000000001 || d/fact<=-0.0000000000001)
    {
        if (i%2!=1)
        {
            if (i%4==2)
                res+=d/fact;
            else if (i%4==0)
                res-=d/fact;
        }
        d*=x;
        fact*=i;
        i++;
    }
    
    return res;
}

static void onTg()
{
    if (stack->depth() < 1)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    else
    {
        double x = stack->pop();
        
        double res = sin(x)/cos(x);
        
        stack->push(res);
        display();
    }
}


static void onArcsin()
{
    if (stack->depth() < 1)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    else
    {
        double x = stack->pop();
        double res;
        
        if (isnan(x))
            res = NAN;
        else
        {
            res = arcsin(x);
        }
        
        stack->push(res);
        display();
    }
}

double arcsin(double x)
{
    if (x == 1)
        return M_PI_2;
    if (x == -1)
        return -M_PI_2;
    if (fabs(x) > 1)
    {
        return NAN; 
    }
    else
    {
        double res = x;
        double d = x;
        int i=1;
        while (true)
        {
            d*=x*x*i/(i+1);
            i+=2;
            d/=i;
            if (d>=0.000000000001||d<=-0.000000000001)
                res+=d;
            else
                return res;
            d*=i;
        }
    }
}

static void onArccos()
{
    if (stack->depth() < 1)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    else
    {
        double x = stack->pop();
        
        double res;
        
        if (isnan(x))
            res = NAN;
        else
            res = arccos(x);
        
        stack->push(res);
        display();
    }
}

double arccos(double x)
{
    return M_PI_2-arcsin(x);
}

static void onArctg()
{
    if (stack->depth() < 1)
    {
        StackException exception;
        exception.reason = "error";
        throw (exception);
    }
    else
    {
        double x = stack->pop();
        double res;
        if (isnan(x))
            res = NAN;
        else
            res = arctg(x);
        
        stack->push(res);
        display();
    }
}

double arctg(double x)
{
    double res = arcsin(x/(sqrt(1+x*x)));
    return res;
}

