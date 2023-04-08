#include <bits/stdc++.h>
using namespace std;
#define INF 1e7
#define ll int
#define ld double 
const ll dimension = 4000;
const ll V = 50;
int main()
{
    ll x1 = 480, y1 = 320, x2 = 2000, y2 = 2800;
    bool distanceOptimized = true;
    x1 *= ((ld)V)/dimension;
    y1 *= ((ld)V)/dimension;
    x2 *= ((ld)V)/dimension;
    y2 *= ((ld)V)/dimension;
    ifstream inputgrid("../data/grid.txt");
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
    ll** Next = (ll**)malloc(sizeof(ll*) * V * V);
    for (ll i = 0; i < V * V; i++) Next[i] = (ll*)malloc(sizeof(ll) * V * V);
    if (distanceOptimized)
    {
        ifstream input("../data/distancegrid.txt");
        for (ll i = 0; i < V * V; i++) for (ll j = 0; j < V * V; j++) input >> Next[i][j];
        input.close();
    }
    else
    {
        ifstream input("../data/elevationgrid.txt");
        for (ll i = 0; i < V * V; i++) for (ll j = 0; j < V * V; j++) input >> Next[i][j];
        input.close();
    }
    ll u = x1 * V + y1;
    ll v = x2 * V + y2;
    ofstream output("../data/path.txt");
    if (Next[u][v] != -1)
    {
        output << (u / V) * dimension/V << " " << (u % V) * dimension/V << " " << graph[u / V][u % V] << endl;
        while (u != v)
        {
            u = Next[u][v];
            output << (u / V) * dimension/V << " " << (u % V) * dimension/V << " " << graph[u / V][u % V] << endl;
        }
    }
    output.close();
    return 0;
}