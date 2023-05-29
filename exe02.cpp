#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

int maxCapacity(int n, int m, vector<vector<int>> &graph, int A, int B)
{
    vector<int> capacity(n + 1, 0);
    priority_queue<pair<int, int>> pq;
    pq.push({INT_MAX, A});
    capacity[A] = INT_MAX;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (int v = 1; v <= n; v++)
        {
            int w = graph[u][v];
            if (w != 0 && capacity[v] < min(capacity[u], w))
            {
                capacity[v] = min(capacity[u], w);
                pq.push({capacity[v], v});
            }
        }
    }
    return capacity[B];
}

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        vector<vector<int>> graph(n + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++)
        {
            int u, v, p;
            cin >> u >> v >> p;
            graph[u][v] = p;
            graph[v][u] = p;
            if (n == 0 && m == 0)
                break;
        }
        int A, B, C;
        cin >> A >> B >> C;
        int capacity = maxCapacity(n, m, graph, A, B);
        cout << (C + capacity - 2) / (capacity - 1) << endl;
    }
    return 0;
}
