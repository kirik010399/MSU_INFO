#include <stdio.h>
#include <math.h>
#define PI 3.1415926535
#define eps 0.000001

int reading(double *a, double *b, FILE*fin);
double angle(double *a, double *b, int count, double x0, double y0);
int lines(double *a, double *b, double *tangents, double *freeCoef, int count, int x0, int y0, int *parallelOY);
int ifIntoPolygon(double *a, double *b, double *tangents, double *freeCoef, int count, int *parallelOY);

int main(void)
{
    char nameOfFile[120];
    FILE*fin;
    double a[100], b[100];
    double tangents[100], freeCoef[100]; /* arrays with tangets and free coef-ts of lines*/
    int parallelOY[100];
    int count; /* count of points */
    int flag;
    double x0, y0; /* the main point, relative to which we find angle*/
    double angleValue; /* the value of angle*/
    printf("Enter the name of file with cooridinates ");
    scanf("%s", nameOfFile);
    fin = fopen(nameOfFile, "r");
    
    if (!fin)
    {
        printf("can't open file %s\n", nameOfFile);
        return -1;
    }
    
    count = reading(a, b, fin);
    
    if (count == 0)
    {
        printf("Uncorrect data\n");
        return -1;
    }
    printf("Enter Coordinates: /n");
    printf("x coordinate: ");
    scanf("%lf", &x0);
    printf("y coordinate: ");
    scanf("%lf", &y0);
    
    flag = lines(a, b, tangents, freeCoef, count, x0, y0, parallelOY);
    
    if (flag==-1)
    {
        printf("The point into polygon\n");
        return 0;
    }
    
    flag = ifIntoPolygon(a, b, tangents, freeCoef, count,parallelOY);
    if (flag==0)
    {
        printf("The point into polygon\n");
        return 0;
    }
    
    angleValue = angle(a, b, count, x0, y0);
    if (fabs(angleValue-180)<eps)
    {
        printf("The point into polygon\n");
        return 0;
    } /* if point on side of polygon*/
    
    printf("Еhe angle at which the polygon is visible from a given point %lf\n", angleValue);
    fclose(fin);
    return 0;
}

int lines(double *a, double *b, double *tangents, double *freeCoef, int count, int x0, int y0, int *parallelOY) //function of buiding lines of sides of polygon
{
    int i;
    double dx, dy;
    for (i = 0; i < count; ++i)
    {
        dy = (y0 - b[i]);
        dx = (x0 - a[i]);
        
        if (fabs(dy)<eps && fabs(dx)<eps)
            return -1;
        
        if (fabs(dx) < eps)
        {
            freeCoef[i] = a[i];
            parallelOY[i] = 1;
        } /* if line parallel to oy*/
        else
        {
            if (fabs(dy) < eps)
                tangents[i] = 0; /* if line parallel to ox (tagents is equal to 0)*/
            else
                tangents[i] = dy/dx; /* calculate tangents*/
            
            freeCoef[i] = b[i] - tangents[i] * a[i];
            parallelOY[i]=0;
        }
    }
    return 1;
}

int ifIntoPolygon(double *a, double *b, double *tangents, double *freeCoef, int count, int *parallelOY)
{
    int i, j, upCount, downCount, countFlag;
    double dif;
    for (i = 0; i < count; i++)
    {
        upCount = 0;
        downCount = 0;
        countFlag=0;
        
        for (j = 0; j < count; j++) /* the sign of point relative to line */
        {
            if (i == j)
                continue;
            
            if (parallelOY[i] == 1) /*if line parallel OY */
            {
                if (fabs(a[j]-a[i])<eps)
                    countFlag++;
                else
                {
                    if (a[j]<a[i]) upCount++;
                    else downCount++;
                }
            }
            else
            {
                dif = b[j] - tangents[i]*a[j] - freeCoef[i];
                
                if (fabs(dif)<eps)
                    countFlag++;
                else
                {
                    if (dif<0)
                        upCount++; //count points on one side of line and other
                    else
                        downCount++;
                }
            }
        }
        if (upCount==0 || downCount == 0)
            return 1; /* if all point on one side of line*/
    }
    return 0;
}

double angle(double *a, double *b, int count, double x0, double y0) /* the function of determine the biggest angle*/
{
    double angle = 0, vX1, vX2, vY1, vY2, scalarProduct, firstLength, secondLength, cos, tempAngle=0;
    int i, p;
    for (i = 0; i < count - 1; i++)
    {
        if (fabs(b[i + 1] - b[i]) < eps && fabs(a[i + 1] - a[i]) < eps)
            continue;

        for (p = i + 1; p < count; p++)
        {
            vX1 = (a[i] - x0);
            vY1 = (b[i] - y0);
            vX2 = (a[p] - x0);
            vY2 = (b[p] - y0);
            
            if ((fabs(vX1)<eps && fabs(vY1)<eps) || (fabs(vX2)<eps && fabs(vY2)<eps))
                continue;
            
            scalarProduct = (vX1*vX2 + vY1*vY2);
            
            firstLength = sqrt(vX1*vX1 + vY1*vY1);
            secondLength = sqrt(vX2*vX2 + vY2*vY2);
            
            cos = scalarProduct / (firstLength*secondLength);
            tempAngle = acos(cos)*180/PI;
            
            if (tempAngle>angle) angle = tempAngle;
        }
    }
    return angle;
}

int reading(double *a, double *b, FILE*fin)
{
    int k = 0, i = 0, c = 0;
    double x;
    while (fscanf(fin, "%lf", &x) == 1)
    {
        if (c % 2 == 0)
        {
            a[i] = x;
            i++;
        }
        else
        {
            b[k] = x;
            k++;
        }
        c++;
    }
    if (k != i || i<2) return 0;
    return i;
}

