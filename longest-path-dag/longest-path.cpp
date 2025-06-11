#include <iostream>
#include <vector>
#include <queue>

int longestPathDAG(int V, std::vector<std::vector<int>> edges, int s, int t) {
   std::vector<std::vector<std::vector<int>>> graph(V);
   std::vector<int> inDegree(V, 0);

   // Build adjacency list and in degree
   for(std::vector<int> edge : edges) {
    int u = edge[0];
    int v = edge[1];
    int w = edge[2];

    std::vector<int> adjacent = { v, w };
    graph[u].push_back(adjacent);
    inDegree[v]++;
   }

   // Kahn's
   std::queue<int> q;
   for(size_t i = 0; i < V; ++i) {
    if (inDegree[i] == 0) q.push(i);
   }

   std::vector<int> topoOrder;
   while(!q.empty()) {
    int u = q.front();
    q.pop();
    topoOrder.push_back(u);
    for(std::vector<int> adjacent : graph[u]) {
        int v = adjacent[0];

        inDegree[v]--;
        if(inDegree[v] == 0) q.push(v);
    }
   }

   // Initialize distances
   std::vector<int> dist(V, -1000000);
   dist[s] = 0;

   // Do the dp to find the answer
   for (int u : topoOrder) {
    for(std::vector<int> adjacent : graph[u]) {
        int v = adjacent[0];
        int w = adjacent[1];

        if(dist[u] + w > dist[v]) {
            dist[v] = dist[u] + w;
        }
    }
   }

   return dist[t];
}

int main() {
    int V = 6;
    std::vector<std::vector<int>> edges = {
        {0, 1, 5},
        {0, 2, 3},
        {1, 3, 6},
        {1, 2, 2},
        {2, 4, 4},
        {2, 5, 2},
        {2, 3, 7},
        {3, 5, 1},
        {4, 5, -1}
    };

    int s = 1;
    int t = 5;

    int longest_path = longestPathDAG(V, edges, s, t);

    std::cout << longest_path << std::endl;

    return 0;
}