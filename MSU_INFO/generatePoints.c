//#include <stdio.h>
//#include <math.h>
//#include <time.h>
//
//double f (double x)
//{
//    return cos(M_PI*x) + 2*cos(2*M_PI*x);
//}
//
//void generatePoints(FILE *fout, int n)
//{
//    double h = 1.0/n;
//
//    for (double x = 0; x <= 1; x+=h)
//    {
//        fprintf(fout, "%f ", f(x));
//    }
//}
//
//int main(void)
//{
//    FILE *fin, *fout;
//    int n;
//
//    fin = fopen("initial_data.txt", "r");
//    fout = fopen("input.txt", "w");
//
//    fscanf(fin, "%d", &n);
//
//    generatePoints(fout, n);
//
//    fclose(fin);
//    fclose(fout);
//}
//
//
