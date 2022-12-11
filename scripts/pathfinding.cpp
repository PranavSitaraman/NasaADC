#include <bits/stdc++.h>
using namespace std;
#define INF 1e7

const int V = 4000;

int main()
{
    double x1, y1, x2, y2;
    bool distanceOptimized = true;      // set false for elevation optimized

    FILE* grid = fopen("../data/grid.txt", "r");
    double** graph = (double**)malloc(sizeof(double*) * V);
    for (int i = 0; i < V; i++) {
        graph[i] = (double*)malloc(sizeof(double) * V);
        for (int j = 0; j < V; j++) {
            fscanf(grid, "%lf", &graph[i][j]);
        }
    }

    double** elevation = (double**)malloc(sizeof(double*) * V * V);
    for (int i = 0; i < V * V; i++) {
        elevation[i] = (double*)malloc(sizeof(double) * V * V);
        for (int j = 0; j < V * V; j++) {
            elevation[i][j] = INF;
        }
    }

    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < V - 1; j++) {
            elevation[V * i + j][V * i + j] = 0;
            elevation[V * i + j][V * i + j + 1] = abs(graph[i][j + 1] - graph[i][j]);
            elevation[V * i + j + 1][V * i + j] = abs(graph[i][j] - graph[i][j + 1]);
            elevation[V * (i + 1) + j][V * i + j] = abs(graph[i][j] - graph[i + 1][j]);
            elevation[V * i + j][V * (i + 1) + j] = abs(graph[i + 1][j] - graph[i][j]);
            elevation[V * i + j][V * (i + 1) + j + 1] = abs(graph[i + 1][j + 1] - graph[i][j]);
            elevation[V * (i + 1) + j + 1][V * i + j] = abs(graph[i][j] - graph[i + 1][j + 1]);
        }
    }
    for (int i = 0; i < V - 1; i++) {
        for (int j = 1; j < V; j++) {
            elevation[V * i + j][V * i + j] = 0;
            elevation[V * i + j][V * i + j - 1] = abs(graph[i][j - 1] - graph[i][j]);
            elevation[V * i + j - 1][V * i + j] = abs(graph[i][j] - graph[i][j - 1]);
            elevation[V * (i + 1) + j][V * i + j] = abs(graph[i][j] - graph[i + 1][j]);
            elevation[V * i + j][V * (i + 1) + j] = abs(graph[i + 1][j] - graph[i][j]);
            elevation[V * i + j][V * (i + 1) + j - 1] = abs(graph[i + 1][j - 1] - graph[i][j]);
            elevation[V * (i + 1) + j - 1][V * i + j] = abs(graph[i][j] - graph[i + 1][j - 1]);
        }
    }

    double** dis = (double**)malloc(sizeof(double*) * V * V);
    for (int i = 0; i < V * V; i++) {
        dis[i] = (double*)malloc(sizeof(double) * V * V);
        for (int j = 0; j < V * V; j++) {
            dis[i][j] = 0;
        }
    }

    int** Next = (int**)malloc(sizeof(int*) * V * V);
    for (int i = 0; i < V * V; i++) {
        Next[i] = (int*)malloc(sizeof(int) * V * V);
        for (int j = 0; j < V * V; j++) {
            Next[i][j] = -1;
        }
    }

    for (int i = 0; i < V * V; i++) {
        for (int j = 0; j < V * V; j++) {
            dis[i][j] = elevation[i][j];
            if (elevation[i][j] != INF)
                Next[i][j] = j;
        }
    }

    for (int k = 0; k < V * V; k++) {
        for (int i = 0; i < V * V; i++) {
            for (int j = 0; j < V * V; j++) {
                if (dis[i][k] == INF || dis[k][j] == INF)
                    continue;
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }

    int u = x1 * V + y2;
    int v = x2 * V + y2;
    vector<int> path;
    if (Next[u][v] != -1) {
        path = { u };
        while (u != v) {
            u = Next[u][v];
            path.push_back(u);
        }
    } else
        path = {};
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] / V << " " << path[i] % V << " " << graph[path[i] / V][path[i] % V] << endl;
    }
    return 0;
}