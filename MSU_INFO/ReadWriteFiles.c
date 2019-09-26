#include <stdio.h>//библиотека для использования функций чтения и записи
#include <stdlib.h>//библиотека для exit

double sumWithElementInFile(double a, FILE *fin);//прототип фукнции

int main(void)
{
    FILE *fin, *fout;//Создаем переменные для файлов
    double a;
    int val;
    
    fin = fopen("input.txt", "r");//в переменную fin открываем и кладем файл input.txt для чтения ("r" - read)
    fout = fopen("output.txt","w");//в переменную fout открываем и кладем файл output.txt для записи ("w" - write)

    //%lf - double, %f - float, %d - int, %c - char (символ), %s - char* (строка)
    //функция fscanf возвращает пример
    val = fscanf(fin, "%lf", &a);//прочитали из файла fin вещественную переменную a и отчет о прочитывании положили в переменную val
    
    if (val == -1)//эквивалентно == EOF, означает что при попытке чтения обнаружилось, что файл закончился
    {
        printf("Empty file\n");
        return -1;
    }
    else if (val == 0)//означает, что считывание прошло некорректно, например вы пытались прочитать число, а оказалось, что считывается буква
    {
        printf("Incorrect first number\n");
        return -2;
    }
    else if (val == 1)//означает, что считывание прошло хорошо
    {
        printf("First number is correct\n");
    }
    
    fprintf(fout, "Sum of numbers is: %f\n", sumWithElementInFile(a, fin));
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}

double sumWithElementInFile(double a, FILE *fin)//функция читает из файла, который приходит ей параметром, число, и прибавлет его к числу, которое тоже приходит ей параметром
{
    double b = 0;
    int val;

    val = fscanf(fin, "%lf", &b);
    
    if (val != 1)//считывание прошло плохо
    {
        printf("Incorrect second number\n");
        exit(-2);//вываливаемся из всей программы с кодом возврата -2
    }

    return a+b;//возвращает сумму a и b
}

