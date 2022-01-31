#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

FILE *in=fopen("mass.txt","rt");
FILE *out=fopen("S1max.txt","w");


//Создание массива
void create_mass(int mass[], int N)
{
    int i=0,err=0;
    for (i=0; i<N; i++)
    {
        fscanf(in,"%d",&mass[i]);
        if (mass[i]<-1000000||mass[i]>1000000)
        {
            printf("\n----Элементы массива лежат не в диапазоне!----\n");
            err=1;
        }
        if (err==1) exit(1);
    }
}

//Нахождение R1
void compute_max(int mass[], int N)
{
    int S1=0,S1max=-1000000;
    for(int A = 0; A<N; A++)
    {
        for(int B = 0; B<N; B++)
        {
            if(A<=B)
            {
                for(int k = A; k <= B; k++)
                    S1 += mass[k];
                if(S1 > S1max)
                {
                    S1max = S1;
                    fprintf(out,"%d\n",S1max);
                }
                S1=0;
            }
            else
            {
                continue;
            }
        }
    }
    printf("\n----Файл S1max успешно создан!----\n");
}

int compute_R2(int mass[], int N)
{
    int massR2[N];
    fprintf(out,"\nСумма разбиения R2\n");
    for(int C = 0; C<N; C++)
    {
        for(int D = 0; D<N; D++)
        {
            for(int f = 0; f < C; f++)
                massR2[f] = mass[f];
            for(int g = D; g < N - 1; g++)
                massR2[g] = mass[g];
        }
    }
    for (int i=0;i<N;i++)
        fprintf(out,"%d\n",massR2[i]);
    return massR2[N];
}

void swap_func(int mass[],int N)
{
    int i=0, j=0;
    printf("\n----Перестановка элемента массива----\n");
    printf("Введите i и j через пробел\n");
    scanf("%d %d", &i,&j);
    if (i!=j&&mass[i]!=mass[j])
    {
        if (0<=i&&i<=j&&j<N)
        {
            swap(mass[i],mass[j]);
            printf("После перестановки \n%d  %d\n", mass[i], mass[j]);
        }
        else printf("Перестановка не требуется!\n");
    }
}

int main()
{
    int N=0;
    setlocale(LC_ALL,"RUS");

    if (!in) cout<<"----Входной файл не найден!----\n";
    else
    {
        cout<<"----Файл успешно открыт!----\n";
        fscanf(in,"%d",&N);
        if (N>100000||N<1)
        {
            printf("\nN выходит за границу диапазона!\n");
            return 0;
        }

        int arr[N], arrR2[N];
        create_mass(arr,N);
        fprintf(out,"Сумма разбиения R1 до перестановки\n");
        compute_max(arr,N);
        swap_func(arr,N);
        fprintf(out,"\nСумма разбиения R1 после перестановки\n");
        compute_max(arr,N);
        arrR2[N]=compute_R2(arr,N);

      //  for (int i=0;i<N;i++)
       //  printf("%d ", arrR2[i]); //Вывод массива
    }
    fclose(in);
    system("pause");
    return 0;
}
