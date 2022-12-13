#include <bits/stdc++.h>
using namespace std;
#define INF 1e7
#define ll int
#define ld float 
const ll V = 4000;
int main()
{
    ld x1 = 3480, y1 = 3686, x2 = 2005, y2 = 1167;  // start and end points from user selection (0-indexed)
    bool distanceOptimized = true; // true for distance, false for elevation (from user selection)
    FILE* input = fopen("../data/grid.txt", "r");
    ld** graph = (ld**)malloc(sizeof(ld*) * V);
    for (ll i = 0; i < V; i++)
    {
        graph[i] = (ld*)malloc(sizeof(ld) * V);
        for (ll j = 0; j < V; j++) fscanf(input, "%f", &graph[i][j]);
    }
    fclose(input);
    ld** elevation = (ld**)malloc(sizeof(ld*) * V * V);
    for (ll i = 0; i < V * V; i++)
    {
        elevation[i] = (ld*)malloc(sizeof(ld) * V * V);
        for (ll j = 0; j < V * V; j++) elevation[i][j] = INF;
    }
    ifstream fin("../data/slopes.csv");
    ld** slopes = (ld**)malloc(sizeof(ld*) * V);
    for (ll i = 0; i < V; i++)
    {
        slopes[i] = (ld*)malloc(sizeof(ld) * V);
        for (ll j = 0; j < V; j++) fin >> slopes[i][j];
    }
    fin.close();
    if (distanceOptimized == false)
    {
        for (ll i = 0; i < V - 1; i++)
        {
            for (ll j = 0; j < V - 1; j++)
            {
                elevation[V * i + j][V * i + j] = 0;
                elevation[V * i + j][V * i + j + 1] = elevation[V * i + j + 1][V * i + j] = (slopes[i][j+1] < 15) ? abs(graph[i][j + 1] - graph[i][j]) : INF;
                elevation[V * (i + 1) + j][V * i + j] = elevation[V * i + j][V * (i + 1) + j] = (slopes[i+1][j] < 15) ? abs(graph[i][j] - graph[i + 1][j]) : INF;
                elevation[V * i + j][V * (i + 1) + j + 1] = elevation[V * (i + 1) + j + 1][V * i + j] = (slopes[i+1][j+1] < 15) ? abs(graph[i + 1][j + 1] - graph[i][j]) : INF;
            }
        }
        for (ll i = 0; i < V - 1; i++)
        {
            for (ll j = 1; j < V; j++)
            {
                elevation[V * i + j][V * i + j] = 0;
                elevation[V * i + j][V * i + j - 1] = elevation[V * i + j - 1][V * i + j] = (slopes[i][j-1] < 15) ? abs(graph[i][j - 1] - graph[i][j]) : INF;
                elevation[V * (i + 1) + j][V * i + j] = elevation[V * i + j][V * (i + 1) + j] = (slopes[i+1][j] < 15) ? abs(graph[i][j] - graph[i + 1][j]) : INF;
                elevation[V * i + j][V * (i + 1) + j - 1] = elevation[V * (i + 1) + j - 1][V * i + j] = (slopes[i+1][j-1] < 15) ? abs(graph[i + 1][j - 1] - graph[i][j]) : INF;
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
                elevation[V * i + j][V * i + j + 1] = elevation[V * i + j + 1][V * i + j] = (slopes[i][j+1] < 15) ? pow(pow(abs(graph[i][j + 1] - graph[i][j]), 2) + 25, 0.5) : INF;
                elevation[V * (i + 1) + j][V * i + j] = elevation[V * i + j][V * (i + 1) + j] = (slopes[i+1][j] < 15) ? pow(pow(abs(graph[i][j] - graph[i + 1][j]), 2) + 25, 0.5) : INF;
                elevation[V * i + j][V * (i + 1) + j + 1] = elevation[V * (i + 1) + j + 1][V * i + j] = (slopes[i+1][j+1] < 15) ? pow(pow(abs(graph[i + 1][j + 1] - graph[i][j]), 2) + 50, 0.5) : INF;
            }
        }
        for (ll i = 0; i < V - 1; i++)
        {
            for (ll j = 1; j < V; j++)
            {
                elevation[V * i + j][V * i + j] = 0;
                elevation[V * i + j][V * i + j - 1] = elevation[V * i + j - 1][V * i + j] = (slopes[i][j-1] < 15) ? pow(pow(abs(graph[i][j - 1] - graph[i][j]), 2) + 25, 0.5) : INF;
                elevation[V * (i + 1) + j][V * i + j] = elevation[V * i + j][V * (i + 1) + j] = (slopes[i+1][j] < 15) ? pow(pow(abs(graph[i][j] - graph[i + 1][j]), 2) + 25, 0.5) : INF;
                elevation[V * i + j][V * (i + 1) + j - 1] = elevation[V * (i + 1) + j - 1][V * i + j] = (slopes[i+1][j-1] < 15) ? pow(pow(abs(graph[i + 1][j - 1] - graph[i][j]), 2) + 50, 0.5) : INF;
            }
        }
    }
    ld** dis = (ld**)malloc(sizeof(ld*) * V * V);
    for (ll i = 0; i < V * V; i++)
    {
        dis[i] = (ld*)malloc(sizeof(ld) * V * V);
        for (ll j = 0; j < V * V; j++) dis[i][j] = 0;
    }
    ll** Next = (ll**)malloc(sizeof(ll*) * V * V);
    for (ll i = 0; i < V * V; i++)
    {
        Next[i] = (ll*)malloc(sizeof(ll) * V * V);
        for (ll j = 0; j < V * V; j++) Next[i][j] = -1;
    }
    for (ll i = 0; i < V * V; i++)
    {
        for (ll j = 0; j < V * V; j++)
        {
            dis[i][j] = elevation[i][j];
            if (elevation[i][j] != INF) Next[i][j] = j;
        }
    }
    for (ll k = 0; k < V * V; k++)
    {
        for (ll i = 0; i < V * V; i++)
        {
            for (ll j = 0; j < V * V; j++)
            {
                if (dis[i][k] == INF || dis[k][j] == INF) continue;
                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }
    ll u = x1 * V + y2;
    ll v = x2 * V + y2;
    FILE* output = fopen("../data/path.txt", "w");
    if (Next[u][v] != -1)
    {
        fprintf(output, "%d %d %f\n", u / V, u % V, graph[u / V][u % V]);
        while (u != v)
        {
            u = Next[u][v];
            fprintf(output, "%d %d %f\n", u / V, u % V, graph[u / V][u % V]);
        }
    }
    else
    {
        return -1; // tell user "no! these settings will not work!"
    }
    fclose(output);
    return 0;
}