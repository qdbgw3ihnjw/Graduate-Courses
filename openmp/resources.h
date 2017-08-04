#include "common.h"

int set1[110] = { 0 };
int FindSet(int x)
{
    if (x == set1[x])
        return x;
    else
        return set1[x] = FindSet(set1[x]);
}

void UnionSet(int x, int y)
{
    int fx = FindSet(x);
    int fy = FindSet(y);
    set1[fy] = fx;
}


class CEdge{
private:
    int tail, head;
    int weight, capacity;
public:
    CEdge(int a, int b, int c, int d);
    int getHead() { return head; }
    int getTail() { return tail; }
    int getWeight() { return weight; }
    int getCap() { return capacity; }

};


class CGraph{
private:
    int numVertex;
    int numEdge;
    list<CEdge*> IncidentList;
public:
    CGraph(list<CEdge*> listEdge);
    map<int, list<CEdge*> > nelist;
    vector<vector<CEdge*> > adjmatrix;
    int d[N + 10][N + 10];
    set<int> S[N + 10];
    set<int> V[N + 10];

    int getNumVertex() { return numVertex; }
    int getNumEdge() { return numEdge; }
    void initial1() {
        list<CEdge*>::iterator it, iend;
        iend = IncidentList.end();
        CEdge* emptyedge = new CEdge(-1, -1, -1, -1);
        for (int i = 0; i <= numVertex; i++)
        {
            vector<CEdge*> vec;
            for (int j = 0; j <= numVertex; j++)
            {
                vec.push_back(emptyedge);
            }
            adjmatrix.push_back(vec);
        }
        for (it = IncidentList.begin(); it != iend; it++) {
            adjmatrix[(*it)->getTail()][(*it)->getHead()] = *it;
        }
        for (it = IncidentList.begin(); it != iend; it++)
            nelist[(*it)->getTail()].push_back(*it);

        list<CEdge*>::iterator it2, iend2;
        iend2 = nelist[3].end();
    }

    void Update(int k, int i)
    {
        list<CEdge*>::iterator it, iend;
        it = nelist[i].begin();
        iend = nelist[i].end();
        for (; it != iend; it++)
            if ((*it)->getWeight()<d[k][(*it)->getHead()]) {
                d[k][(*it)->getHead()] = (*it)->getWeight();
            }
    }

    int FindMin(int k)
    {
        set<int>::iterator vi, vend;
        vend = V[k].end();
        int mini = 10000000;
        int loc = 0;
        for (vi = V[k].begin(); vi != vend; vi++)
            if (mini >= d[k][*vi])
            {
                mini = d[k][*vi]; loc = *vi;
            }
        return loc;
    }

    void solin() {
        for (int i = 1; i <= N; i++)
            set1[i] = i;
        list<CEdge*> T;
        int e[N + 10];
        int j, k;
        for (k = 1; k <= N; k++)
            for (j = 1; j <= N; j++) {
                V[k].insert(j);
                d[k][j] = INF;
            }

        for (k = 1; k <= N; k++) {
            S[k].insert(k);
            V[k].erase(k);
            d[k][k] = 0;
            Update(k, k);
        }

        while (T.size()<(N - 1))
        {
            for (int i = 1; i <= N; i++)
            {
                if (i != FindSet(i)) continue;
                e[i] = FindMin(i);
            }

            for (int i = 1; i <= N; i++)
            {
                if (i != FindSet(i)) continue;
                if (FindSet(e[i]) != FindSet(i))
                {
                    UnionSet(e[i], i);
                    int gen, gen_other;
                    gen = FindSet(i);
                    if (gen == i) gen_other = e[i];
                    else gen_other = i;
                    set<int>::iterator it, iend;
                    iend = S[gen_other].end();
                    for (it = S[gen_other].begin(); it != iend; it++) {
                        V[gen].erase(*it);
                        S[gen].insert(*it);
                    }
                    iend = V[gen].end();
                    for (it = V[gen].begin(); it != iend; it++)
                        if (d[gen][*it]>d[gen_other][*it])
                            d[gen][*it] = d[gen_other][*it];
                    T.push_back(adjmatrix[e[i]][i]);
                    // printf("%d---%d\n", e[i], i);
                }
            }
        }
    }

    void initial2() {
        list<CEdge*>::iterator it, iend;
        iend = IncidentList.end();
        CEdge* emptyedge = new CEdge(-1, -1, -1, -1);

#pragma omp  for  
        for (int i = 0; i <= numVertex; i++)
        {
            vector<CEdge*> vec;
            for (int j = 0; j <= numVertex; j++)
            {
                vec.push_back(emptyedge);
            }
            adjmatrix.push_back(vec);
        }

        for (it = IncidentList.begin(); it != iend; it++) {
            adjmatrix[(*it)->getTail()][(*it)->getHead()] = *it;
        }
        for (it = IncidentList.begin(); it != iend; it++)
            nelist[(*it)->getTail()].push_back(*it);

        list<CEdge*>::iterator it2, iend2;
        iend2 = nelist[3].end();
    }

    void solin2()
    {
        for (int i = 1; i <= N; i++)
            set1[i] = i;
        list<CEdge*> T;
        int e[N + 10];

#pragma omp parallel
        {

#pragma omp  for 
            for (int k = 1; k <= N; k++)
            {
                for ( int j = 1; j <= N; j++)
                {
                    V[k].insert(j);
                    d[k][j] = INF;
                }
            }
        }

        omp_set_num_threads(2);
#pragma omp parallel
        {
#pragma omp  for
            for (int k = 1; k <= N; k++)
            {
                S[k].insert(k);
                V[k].erase(k);
                d[k][k] = 0;
                Update(k, k);
            }
        }
        for (;T.size() < (N - 1);)
        {
#pragma omp parallel 
        {
#pragma omp  for
            for (int i = 1; i <= N; i++)
            {
                if (i != FindSet(i)) continue;
                e[i] = FindMin(i);
            }
        }
        
#pragma omp  for
            for (int i = 1; i <= N; i++)
            {
                if (i != FindSet(i)) continue;
                if (FindSet(e[i]) != FindSet(i))
                {
                    UnionSet(e[i], i);
                    int gen, gen_other;
                    gen = FindSet(i);
                    if (gen == i) gen_other = e[i];
                    else gen_other = i;
                    set<int>::iterator it, iend;
                    iend = S[gen_other].end();
                    for (it = S[gen_other].begin(); it != iend; it++) {
                        V[gen].erase(*it);
                        S[gen].insert(*it);
                    }
                    iend = V[gen].end();
                    for (it = V[gen].begin(); it != iend; it++)
                        if (d[gen][*it]>d[gen_other][*it])
                            d[gen][*it] = d[gen_other][*it];
                    T.push_back(adjmatrix[e[i]][i]);
                    // printf("%d---%d\n", e[i], i);
                }
            }
        }
    }
};
