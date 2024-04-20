#include <iostream>

using namespace std;

const int MAX = 100;
const int INF = 1000000;

class Graph
{
private:
    int V;
    int graph[MAX][MAX];

public:
    Graph(int V)
    {
        this->V = V;
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                graph[i][j] = INF;
            }
        }
    }

    void addEdge(int u, int v, int weight)
    {
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    int minKey(int key[], bool mstSet[])
    {
        int min = INF, min_index;

        for (int v = 0; v < V; v++)
        {
            if (!mstSet[v] && key[v] < min)
            {
                min = key[v];
                min_index = v;
            }
        }

        return min_index;
    }

    void printMST(int parent[])
    {
        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; i++)
        {
            cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
        }
    }

    void primMST()
    {
        int parent[MAX];
        int key[MAX];
        bool mstSet[MAX];

        for (int i = 0; i < V; i++)
        {
            key[i] = INF;
            mstSet[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < V - 1; count++)
        {
            int u = minKey(key, mstSet);
            mstSet[u] = true;
            for (int v = 0; v < V; v++)
            {
                if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        printMST(parent);
    }
};

int main()
{
    int V, E;
    cout << "Enter the number of offices (vertices): ";
    cin >> V;
    cout << "Enter the number of connections (edges): ";
    cin >> E;

    Graph g(V);

    cout << "Enter the connections and their respective weights:\n";
    for (int i = 0; i < E; ++i)
    {
        int u, v, weight;
        cout << "Enter connection " << i + 1 << " (u v weight): ";
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    cout << "Minimum Spanning Tree using Prim's Algorithm:\n";
    g.primMST();

    return 0;
}
