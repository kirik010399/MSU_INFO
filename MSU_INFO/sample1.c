//Передается последовательность положительных целых чисел a1, a2, ... . Участок последовательности называется подъемом, если на этом участке каждое следующее число больше предыдущего. Высотой подъема называется разность первого и последнего элемента подъема. Необоходимо найти наибольшую высоту среди всех подъемов последовательности и количество элементов в последовательности.

//Во время чтения программа помнит число maxRise — высоту самого высокого из уже закончившихся подъемов, а также высоту текущего подъема curRise (то есть разность между последним и первым числом участка) и последнее прочитанное число a0.
//Прочитав очередное число a, программа сравнивает его с числом a0.
//Если a > a0, то значение curRise увеличивается на a-a0.
//В противном случае фиксируется конец подъема и начало нового участка. То есть, во-первых, значение curRise сравнивается с maxRise и, при необходимости, maxRise полагается равным curRise. Во-вторых, полагаем curRise = 0.
//На случай, если последовательность заканчивается подъемом, отдельно после цикла еще раз сравниваем curRise и maxRise.

#include <stdio.h>

int findMaxRise(FILE *fin, int *elemCount);

int main(void)
{
    FILE *fin, *fout;
    int res;
    int elemCount; 
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    
    res = findMaxRise(fin, &elemCount);
    
    fprintf(fout, "Количество элементов: %d\nМаксимальный подъем: %d", elemCount, res);
    
    fclose(fin);
    fclose(fout);
    return 0;
}

int findMaxRise(FILE *fin, int *elemCount)
{
    int a, a0, curRise, maxRise = 0;
    
    fscanf(fin, "%d", &a);
    
    curRise = 0;
    a0 = a;
    *elemCount = 1;
    
    while(fscanf(fin, "%d", &a) != EOF)
    {
        if (a > a0)
        {
            curRise += a - a0;
        }
        else
        {
            if (curRise > maxRise)
                maxRise = curRise;
           
            curRise = 0;
        }
        
        *elemCount += 1;
        a0 = a;
    }
    
     if (curRise > maxRise)//в случае, если последовательность закончилась подъемом
        maxRise = curRise;
    
    return maxRise;
}

