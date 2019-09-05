//#include <stdio.h>
//
//double sum1(double a, double b);
//void sum2(double a, double b, double *c);
//
//void badAddOneToNumbers(double a, double b);
//void goodAddOneToNumbers(double *a, double *b);
//
//int main(void)
//{
//    FILE *fin, *fout;
//    int val;
//    double a, b;
//    double res;
//
//    fin = fopen("input.txt", "r");
//    fout = fopen("output.txt","w");
//
//    val = fscanf(fin, "%lf", &a);
//
//    if (val == -1)
//    {
//        printf("Empty file\n");
//        return -1;
//    }
//    else if (val == 0)
//    {
//        printf("Incorrect data\n");
//        return -2;
//    }
//
//    val = fscanf(fin, "%lf", &b);
//
//    if (val != 1)
//    {
//        printf("Incorrect data\n");
//        return -2;
//    }
//
//    printf("Current numbers: %lf, %lf\n", a, b);
//
//    badAddOneToNumbers(a, b);
//    printf("Current numbers after bad adding one: %lf, %lf\n", a, b);
//    
//    goodAddOneToNumbers(&a, &b);
//    printf("Current numbers after good adding one: %lf, %lf\n", a, b);
//
//    res = sum1(a, b);
//    printf("Sum of numbers %lf and %lf is: %lf\n", a, b, res);
//
//    sum2(a, b, &res);
//    printf("Sum of numbers %lf and %lf is: %lf\n", a, b, res);
//
//    fclose(fin);
//    fclose(fout);
//
//    return 0;
//}
//
//void badAddOneToNumbers(double a, double b)
//{
//    a++;
//    b++;
//}
//
//void goodAddOneToNumbers(double *a, double *b)
//{
//    ++*a;
//    ++*b;
//}
//
//double sum1(double a, double b)
//{
//    double res;
//
//    res = a + b;
//
//    return res;
//}
//
//void sum2(double a, double b, double *res)
//{
//    *res = a+b;
//}
//
