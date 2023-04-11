#include <bits/stdc++.h>
using namespace std;
#define INF 1e7
#define ll int
#define ld double 
const ll dimension = 4000;
const ll V = 50;
int main()
{
    ifstream inputgrid("../Data/grid.txt");
    ld** graph = (ld**)malloc(sizeof(ld*) * V);
    for (ll i = 0; i < V; i++)
    {
        for (ll k = 0; k < dimension/V - 1; k++) inputgrid.ignore(100000000L,'\n');
        graph[i] = (ld*)malloc(sizeof(ld) * V);
        for (ll j = 0; j < V; j++)
        {
            ld a;
            for (ll k = 0; k < dimension/V - 1; k++) inputgrid >> a;
            inputgrid >> graph[i][j];
        }
    }
    inputgrid.close();
    ifstream inputslope("../Data/slope.csv");
    ld** slopes = (ld**)malloc(sizeof(ld*) * V);
    for (ll i = 0; i < V; i++)
    {
        for (ll k = 0; k < dimension/V - 1; k++) inputslope.ignore(100000000L,'\n');
        slopes[i] = (ld*)malloc(sizeof(ld) * V);
        for (ll j = 0; j < V; j++)
        {
            ld a;
            for (ll k = 0; k < dimension/V - 1; k++) inputslope >> a;
            inputslope >> slopes[i][j];
        }
    }
    inputslope.close();
    ll** Next = (ll**)malloc(sizeof(ll*) * V * V);
    for (ll i = 0; i < V * V; i++) Next[i] = (ll*)malloc(sizeof(ll) * V * V);
    ld** elevation = (ld**)malloc(sizeof(ld*) * V * V);
    for (ll i = 0; i < V * V; i++) elevation[i] = (ld*)malloc(sizeof(ld) * V * V);
    for (ll distanceOptimized = 0; distanceOptimized < 2; distanceOptimized++)
    {
        for (ll i = 0; i < V * V; i++) for (ll j = 0; j < V * V; j++) Next[i][j] = -1;
        for (ll i = 0; i < V * V; i++) for (ll j = 0; j < V * V; j++) elevation[i][j] = INF;
        if (distanceOptimized == false)
        {
            for (ll i = 0; i < V - 1; i++)
            {
                for (ll j = 0; j < V - 1; j++)
                {
                    elevation[V * i + j][V * i + j] = 0;
                    elevation[V * i + j][V * i + j + 1] = elevation[V * i + j + 1][V * i + j] = (slopes[i][j+1] < 20) ? abs(graph[i][j + 1] - graph[i][j]) : INF;
                    elevation[V * (i + 1) + j][V * i + j] = elevation[V * i + j][V * (i + 1) + j] = (slopes[i+1][j] < 20) ? abs(graph[i][j] - graph[i + 1][j]) : INF;
                    elevation[V * i + j][V * (i + 1) + j + 1] = elevation[V * (i + 1) + j + 1][V * i + j] = (slopes[i+1][j+1] < 20) ? abs(graph[i + 1][j + 1] - graph[i][j]) : INF;
                }
            }
            for (ll i = 0; i < V - 1; i++)
            {
                for (ll j = 1; j < V; j++)
                {
                    elevation[V * i + j][V * i + j] = 0;
                    elevation[V * i + j][V * i + j - 1] = elevation[V * i + j - 1][V * i + j] = (slopes[i][j-1] < 20) ? abs(graph[i][j - 1] - graph[i][j]) : INF;
                    elevation[V * (i + 1) + j][V * i + j] = elevation[V * i + j][V * (i + 1) + j] = (slopes[i+1][j] < 20) ? abs(graph[i][j] - graph[i + 1][j]) : INF;
                    elevation[V * i + j][V * (i + 1) + j - 1] = elevation[V * (i + 1) + j - 1][V * i + j] = (slopes[i+1][j-1] < 20) ? abs(graph[i + 1][j - 1] - graph[i][j]) : INF;
                }
            }
        }
        else
        {
            for (ll i = 0; i < V - 1; i++)
            {
                for (ll j = 0; j < V - 1; j++)
                {
                    elevation[V * i + j][V * i + j] = 0;
                    elevation[V * i + j][V * i + j + 1] = elevation[V * i + j + 1][V * i + j] = (slopes[i][j+1] < 20) ? pow(pow(abs(graph[i][j + 1] - graph[i][j]), 2) + 25, 0.5) : INF;
                    elevation[V * (i + 1) + j][V * i + j] = elevation[V * i + j][V * (i + 1) + j] = (slopes[i+1][j] < 20) ? pow(pow(abs(graph[i][j] - graph[i + 1][j]), 2) + 25, 0.5) : INF;
                    elevation[V * i + j][V * (i + 1) + j + 1] = elevation[V * (i + 1) + j + 1][V * i + j] = (slopes[i+1][j+1] < 20) ? pow(pow(abs(graph[i + 1][j + 1] - graph[i][j]), 2) + 50, 0.5) : INF;
                }
            }
            for (ll i = 0; i < V - 1; i++)
            {
                for (ll j = 1; j < V; j++)
                {
                    elevation[V * i + j][V * i + j] = 0;
                    elevation[V * i + j][V * i + j - 1] = elevation[V * i + j - 1][V * i + j] = (slopes[i][j-1] < 20) ? pow(pow(abs(graph[i][j - 1] - graph[i][j]), 2) + 25, 0.5) : INF;
                    elevation[V * (i + 1) + j][V * i + j] = elevation[V * i + j][V * (i + 1) + j] = (slopes[i+1][j] < 20) ? pow(pow(abs(graph[i][j] - graph[i + 1][j]), 2) + 25, 0.5) : INF;
                    elevation[V * i + j][V * (i + 1) + j - 1] = elevation[V * (i + 1) + j - 1][V * i + j] = (slopes[i+1][j-1] < 20) ? pow(pow(abs(graph[i + 1][j - 1] - graph[i][j]), 2) + 50, 0.5) : INF;
                }
            }
        }
        for (ll i = 0; i < V * V; i++) for (ll j = 0; j < V * V; j++) if (elevation[i][j] != INF) Next[i][j] = j;
        for (ll k = 0; k < V * V; k++)
        {
            for (ll i = 0; i < V * V; i++)
            {
                for (ll j = 0; j < V * V; j++)
                {
                    if (elevation[i][k] == INF || elevation[k][j] == INF) continue;
                    if (elevation[i][j] > elevation[i][k] + elevation[k][j])
                    {
                        elevation[i][j] = elevation[i][k] + elevation[k][j];
                        Next[i][j] = Next[i][k];
                    }
                }
            }
        }
        if (distanceOptimized)
        {
            ofstream output("../Data/distance20grid.txt");
            for (ll i = 0; i < V * V; i++)
            {
                for (ll j = 0; j < V * V; j++) output << Next[i][j] << " ";
                output << endl;
            }
            output.close();
        }
        else
        {
            ofstream output("../Data/elevation20grid.txt");
            for (ll i = 0; i < V * V; i++)
            {
                for (ll j = 0; j < V * V; j++) output << Next[i][j] << " ";
                output << endl;
            }
            output.close();
        }
    }
    return 0;
}