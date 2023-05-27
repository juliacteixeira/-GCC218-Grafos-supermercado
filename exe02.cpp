#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = 1000;
int capacity[MAXN][MAXN];
int flow[MAXN][MAXN];
vector<int> adj[MAXN];

int bfs(int s, int t) {
    vector<int> parent(MAXN, -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int cur_flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > flow[cur][next]) {
                parent[next] = cur;
                int new_flow = min(cur_flow, capacity[cur][next] - flow[cur][next]);
                if (next == t) {
                    // atualiza o fluxo ao longo do caminho
                    while (cur != s) {
                        flow[parent[cur]][cur] += new_flow;
                        flow[cur][parent[cur]] -= new_flow;
                        cur = parent[cur];
                    }
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            flow[i][j] = 0;

    int total_flow = 0;
    int new_flow;

    while (new_flow = bfs(s, t)) {
        total_flow += new_flow;
    }

    return total_flow;
}

int main() {
    int n,m;
    while(cin >> n >> m){
        if(n == 0 && m == 0) break; // verifica se a entrada é válida
        for (int i = 0; i < MAXN; i++) {
            for (int j = 0; j < MAXN; j++) {
                capacity[i][j] = 0;
            }
            adj[i].clear();
        }
        for(int i=0;i<m;i++){
            int u,v,w; cin >> u >> v >> w;
            capacity[u][v] = w;
            capacity[v][u] = w;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int a,b,c; cin >> a >> b >> c;
        cout << (c + maxflow(a,b) - 1) / maxflow(a,b) << endl; 
    }
}
