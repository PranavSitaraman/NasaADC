#include <bits/stdc++.h>
using namespace std;
#define INF 1e7
#define ll int
#define ld double 
const ll dimension = 4000;
const ll V = 100;
int main()
{
    ld x1 = 3481 * V/dimension, y1 = 3687 * V/dimension, x2 = 2709 * V/dimension, y2 = 589 * V/dimension;  // start and end points from user selection (0-indexed)
    bool distanceOptimized = true; // true for distance, false for elevation (from user selection)
    ifstream input("../data/grid.txt");
    ld** graph = (ld**)malloc(sizeof(ld*) * V);
    for (ll i = 0; i < V; i++)
    {
        for (ll k = 0; k < dimension/V - 1; k++) input.ignore(100000000L,'\n');
        graph[i] = (ld*)malloc(sizeof(ld) * V);
        for (ll j = 0; j < V; j++)
        {
            ld a;
            for (ll k = 0; k < dimension/V - 1; k++) input >> a;
            input >> graph[i][j];
        }
    }
    input.close();
    ifstream slopeinput("../data/slopes.csv");
    ld** slopes = (ld**)malloc(sizeof(ld*) * V);
    for (ll i = 0; i < V; i++)
    {
        for (ll k = 0; k < dimension/V - 1; k++) slopeinput.ignore(100000000L,'\n');
        slopes[i] = (ld*)malloc(sizeof(ld) * V);
        for (ll j = 0; j < V; j++)
        {
            ld a;
            for (ll k = 0; k < dimension/V - 1; k++) slopeinput >> a;
            slopeinput >> slopes[i][j];
        }
    }
    slopeinput.close();
    ll** Next = (ll**)malloc(sizeof(ll*) * V * V);
    for (ll i = 0; i < V * V; i++)
    {
        Next[i] = (ll*)malloc(sizeof(ll) * V * V);
        for (ll j = 0; j < V * V; j++) Next[i][j] = -1;
    }
    ld** elevation = (ld**)malloc(sizeof(ld*) * V * V);
    for (ll i = 0; i < V * V; i++)
    {
        elevation[i] = (ld*)malloc(sizeof(ld) * V * V);
        for (ll j = 0; j < V * V; j++) elevation[i][j] = INF;
    }
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
    for (ll i = 0; i < V * V; i++)
    {
        for (ll j = 0; j < V * V; j++)
        {
            if (elevation[i][j] != INF) Next[i][j] = j;
        }
    }
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
    ll u = x1 * V + y2;
    ll v = x2 * V + y2;
    ofstream output("../data/path.txt");
    if (Next[u][v] != -1)
    {
        output << u / V << " " << u % V << " " << graph[u / V][u % V] << endl;
        while (u != v)
        {
            u = Next[u][v];
            output << (u / V) * dimension/V << " " << (u % V) * dimension/V << " " << graph[u / V][u % V] << endl;
        }
    }
    else return -1; // tell user "no! these settings will not work!"
    output.close();
    return 0;
}