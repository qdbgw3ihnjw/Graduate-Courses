#include <stdio.h>  
#include <iostream>
#include <stdlib.h>  
#include <time.h>  
#include "omp.h"  

using namespace std;

void swap(int &a, int &b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

void quicksort(int *A, int l, int u)
{
    int i, m, k;
    if (l >= u) return;
    m = l;
    for (i = l + 1; i <= u; i++)
        if (A[i] < A[l])
            swap(A[++m], A[i]);
    swap(A[l], A[m]);
    quicksort(A, l, m - 1);
    quicksort(A, m + 1, u);
}

void sub_main(const uint num_thds)
{
    omp_set_num_threads(num_thds);
    int k = 0, i = 0;
    int m = 0, n = 0;
    double cost = 0;
    int len = 10000;
    int short_len = len / 2;
    int B[10000], C[10000], D[5000], E[5000];
#pragma omp parallel default(none) shared(B,C,len) private(i)
    {
        int j = 50000;
#pragma omp for  
        for (i = 0; i<len; i++)
        {
            B[i] = j--;
            C[i] = j--;
        }
    }
    clock_t begin = clock();
#pragma omp parallel default(none) shared(B,D,E,short_len) private(i)
    {
#pragma omp for  
        for (i = 0; i<short_len; i++)
        {
            D[i] = B[i];
            E[i] = B[i + 5000];
        }
    }
#pragma omp parallel default(none) shared(E,D,short_len)
        {
#pragma omp parallel sections  
            {
#pragma omp section  
                quicksort(D, 0, short_len - 1);
#pragma omp section  
                quicksort(E, 0, short_len - 1);
            }
        }
        for (; k<len; k++)
        {
            if (m<short_len && n<short_len)
            {
                if (D[n] <= E[m])
                {
                    B[k] = D[n];
                    n++;
                }
                else
                {
                    B[k] = E[m];
                    m++;
                }
            }
            if (m == short_len || n == short_len)
            {
                if (m == short_len)
                    B[k] = E[m];
                else
                    B[k] = D[n - 1];
                k += 1;
                break;
            }
        }
        if (/*m==short_len &&*/ n<short_len)
        {
            int tem = short_len - n;
            for (int p = 0; p<tem; p++)
            {
                B[k] = D[n];
                n++;
                k++;
            }
        }
        else if (/*n==short_len &&*/ m<short_len)
        {
            int tem = short_len - m;
            for (int q = 0; q<tem; q++)
            {
                B[k] = E[m];
                m++;
                k++;
            }
        }
        clock_t end = clock();
        cost = (double)(end - begin);
        cout << "num_thds: " << omp_get_max_threads() << endl;
        cout << "running time with omp: " << cost << endl;
        begin = clock();
        quicksort(C, 0, len - 1);
        end = clock();
        cost = (double)(end - begin);
        cout << "running time without omp: " << cost << endl;
}

int main(int argc, char **argv)
{
    for (uint i = 1; i <= 8; i++) {
        sub_main(i);
    }
    return 0;
}
