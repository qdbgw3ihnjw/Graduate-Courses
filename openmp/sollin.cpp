#include "resources.h"

#define MAX_DISTANCE 100000

bool** G;
int **D;
int v = 0;

CEdge::CEdge(int a, int b, int c, int d){
    tail = a;
    head = b;
    weight = c;
    capacity = d;
}

CGraph::CGraph(list<CEdge*> listEdge){
    IncidentList = listEdge;
    numVertex = N;
    numEdge = listEdge.size();
}

using namespace std;

void floyd()
{
    //initialize
    for (int i = 0; i<N; i++)
    {
        for (int j = 0; j<N; j++)
        {
            if (G[i][j] == 1)
            {
                D[i][j] = 1;
                int weight;
                weight = rand() % 10 + 4;
                D[j][i] = weight;
                D[i][j] = weight;
            }
            else
            {
                D[i][j] = MAX_DISTANCE;
            }
        }
    }
    //floyd
    for (int k = 0; k<N; k++)
    {
        for (int i = 0; i<N; i++)
        {
            for (int j = 0; j<N; j++)
            {
                if (D[i][j]>D[i][k] + D[k][j] && D[i][j]<MAX_DISTANCE)
                {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

void print()
{
    v = 0;
    for (int i = 0; i<N; i++)
    {
        for (int j = 0; j<N; j++)
        {
            if (D[i][j] != MAX_DISTANCE&&i != j)
            {
                // cout << i + 1 << " " << j + 1 << " " << D[i][j] << endl;
                v++;
            }
        }
    }
    cout << v << " " << N << endl;
}


void cinin()
{
    srand((unsigned int)time(NULL));
    //N = rand() % 10 + 5;
    G = new bool *[N];
    D = new int *[N];
    for (int i = 0; i<N; i++)
    {
        G[i] = new bool[N];
        D[i] = new int[N];
        for (int j = 0; j<N; j++)
        {
            G[i][j] = 0;
            D[i][j] = 0;
        }
    }
    for (int i = 0; i<N; i++)
    {
        int n = rand() % N;
        for (int k = 0; k<n; k++)
        {
            int j = rand() % N;
            G[i][j] = true;
            G[j][i] = true;
        }
    }
    floyd();
    print();
}

int main()
{
    double cost = 1;
    list<CEdge*> listEdge;
    cinin();
    for (int k = 0; k < v; k++)
    {
        for (int i = 0; i<N; i++)
        {
            for (int j = 0; j<N; j++)
            {
                if (D[i][j] != MAX_DISTANCE&&i != j)
                {
                    CEdge* e1 = new CEdge(i + 1, j + 1, D[i][j], 10);
                    CEdge* e2 = new CEdge(j + 1, i + 1, D[i][j], 10);
                    listEdge.push_back(e1);
                    listEdge.push_back(e2);
                }
            }
        }
    }
    double starttime, endtime, time;
    
    starttime = omp_get_wtime();
    CGraph g(listEdge);
    g.initial1();
    g.solin();
    endtime = omp_get_wtime();
    time = endtime - starttime;
    cout << "the running time of collin with omp: " << time << endl;

    //****************
    starttime = omp_get_wtime();
    CGraph q(listEdge);
    q.initial2();
    q.solin2();
    endtime = omp_get_wtime();
    time = endtime - starttime;
    cout << "the running time of collin without omp: " << time << endl;
    return 0;
}
