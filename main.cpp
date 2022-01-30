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
                if(S1 > S1max){
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
    char tmp[30];
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

        int arr[N];
        create_mass(arr,N);
        fprintf(out,"Максимальные суммы до перестановки\n");
        compute_max(arr,N);
        swap_func(arr,N);
        fprintf(out,"\nМаксимальные суммы после перестановки\n");
        compute_max(arr,N);
        // for (int i=0;i<N;i++)
        // printf("%d ", arr[i]); //Вывод массива
    }
    fclose(in);
    system("pause");
    return 0;
}
