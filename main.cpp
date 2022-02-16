//Nail Guseynov

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <utility>

using namespace std;

FILE *in=fopen("mass.txt","rt");
FILE *out=fopen("S1max.txt","w");

//������ ������� �� �����
void create_mass(int mass[], int N)
{
    int i=0,err=0;
    printf("�������� ������: ");
    for (i=0; i<N; i++)
    {
        fscanf(in,"%d",&mass[i]);
        printf("%d ", mass[i]);
        if (mass[i]<-1000000||mass[i]>1000000)
        {
            printf("\n----�������� ������� ����� �� � ���������!----\n");
            err=1;
        }
        if (err==1) exit(1);
    }
}

//���������� ������������ ����� R1
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
}

//��������� ��������
bool compute_R2(int mass[], int mass2[], int NC, int ND)
{
    bool  ch1=true, ch2=true;
    for(int i = 0; i < NC; i++){
        ch1 = false;
        for(int j = 0; j < ND; j++)
            if(mass[i] == mass2[j]){
                ch1 = true;
                break;
            }
        if(ch1 == false)
            break;
    }

    for(int j = 0; j < ND; j++){
        ch2 = false;
        for(int i = 0; i < NC; i++)
            if(mass2[j] == mass[i]){
                ch2 = true;
                break;
            }
        if(ch2 == false)
            break;
    }


   /* if(ch1&ch2){
        printf("Yes\n");
    }
    else
        printf("No\n");
*/
    return ch1&ch2;

}

//�������� ������������� �������
int new_array(int mass[], int N)
{
    int NC = 0;
    int ND = 0;
    int D = 0;
    int k = 0;
    for(int C = 0; C < N; C++){
        for(int D_i = 0; D_i < N; D_i++){
            NC = C+1;
            ND = N-D_i;
            int *dmassC, *dmassD;

            dmassC = (int*)malloc(NC * sizeof(int)); //��������� ������
            dmassD = (int*)malloc(ND * sizeof(int));

            //printf("\n\nC: %d D: %d\n", C,D_i);
            for(int i = 0; i<NC; i++) {
                dmassC[i]=mass[i];
            }
            D = D_i;

            for(int j = 0; j<ND; j++)
            {
                dmassD[j]=mass[D];
                D++;
            }

            /*printf("MassC ");
                for (int i=0; i<NC; i++)
            {
                printf("%d ", dmassC[i]);
            }
            printf("\nMassD ");
                for (int j=0; j<ND; j++)
            {
                printf("%d ", dmassD[j]);
            }*/

            if(compute_R2(dmassC, dmassD, NC, ND))
                k++;
            free(dmassC); //������������ ������
            free(dmassD);
        }
   }
    printf("\n���������� R2: %d \n",k);
    fprintf(out,"%d\n",k); //���������� ��������� R2

    return k;
}

//������������ �������� �������
void swap_func(int mass[],int N)
{
    int i=0, j=0;
    printf("\n----������������ �������� �������----\n");
    printf("������� i � j ����� ������\n");
    scanf("%d %d", &i,&j);
    if (i!=j&&mass[i]!=mass[j])
    {
        if (0<=i&&i<=j&&j<N)
        {
            swap(mass[i],mass[j]);
            printf("����� ������������ \n%d  %d\n", mass[i], mass[j]);
        }
        else printf("������������ �� ���������!\n");
    }
}

int main()
{
    int N=0;
    setlocale(LC_ALL,"RUS");

    if (!in) printf("----������� ���� �� ������!----\n");
    else
    {
        printf("----���� ������� ������!----\n");
        fscanf(in,"%d",&N);
        if (N>100000||N<1)
        {
            printf("\nN ������� �� ������� ���������!\n");
            return 0;
        }

        int arr[N];
        create_mass(arr,N);
        fprintf(out,"����� ��������� R1 �� ������������\n");
        compute_max(arr,N);

        fprintf(out,"\n���������� ��������� R2\n");
        new_array(arr, N);

        swap_func(arr,N);
        fprintf(out,"\n����� ��������� R1 ����� ������������\n");
        compute_max(arr,N);
    }
    fclose(in);
	fclose(out);
    system("pause");
    return 0;
}
