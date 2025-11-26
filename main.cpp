#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, capacity;
};

struct Graph {
    int numNodes, numEdges;
    int source, sink;
    vector<Edge> edges;
    vector<vector<int>> adjList;
    vector<vector<int>> capacityMatrix; 
    
    Graph(int n) : numNodes(n), numEdges(0), source(-1), sink(-1) {
        adjList.resize(n + 1);
        capacityMatrix.resize(n + 1, vector<int>(n + 1, 0));
    }
    
    void addEdge(int from, int to, int capacity) {
        edges.push_back({from, to, capacity});
        adjList[from].push_back(edges.size() - 1);
        capacityMatrix[from][to] = capacity; 
        numEdges++;
    }      
};

Graph* readDIMACS(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return nullptr;
    }
    
    Graph* graph = nullptr;
    string line;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        istringstream iss(line);
        char type;
        iss >> type;
        
        if (type == 'c') {
            continue;
        }
        else if (type == 'p') {
            string format;
            int nodes, edges;
            iss >> format >> nodes >> edges;
            graph = new Graph(nodes);
        }
        else if (type == 'n') {
            int nodeId;
            char nodeType;
            iss >> nodeId >> nodeType;
            
            if (nodeType == 's') {
                graph->source = nodeId;
            } else if (nodeType == 't') {
                graph->sink = nodeId;
            }
        }
        else if (type == 'a') {
            int from, to, capacity;
            iss >> from >> to >> capacity;
            graph->addEdge(from, to, capacity);
        }
    }
    
    file.close();
    return graph;
}

int bfs(Graph* graph, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[graph->source] = -2;
    queue<pair<int, int>> q;
    q.push({graph->source, INT_MAX});
    
    while (!q.empty()) {
        int u = q.front().first;
        int cap = q.front().second;
        q.pop();
        
        for (int v = 1; v <= graph->numNodes; v++) {
            if (graph->capacityMatrix[u][v] > 0 && parent[v] == -1) {
                parent[v] = u;
                int min_cap = min(cap, graph->capacityMatrix[u][v]);
                
                if (v == graph->sink) {
                    return min_cap;
                }
                
                q.push({v, min_cap});
            }
        }
    }
    return 0;
}

int maxFlow(Graph* graph) {
    vector<int> parent(graph->numNodes + 1, -1);
    int max_flow = 0;
    int min_cap = 0;
    
    while ((min_cap = bfs(graph, parent)) > 0) {
        max_flow += min_cap;
        int v = graph->sink;
        
        while (v != graph->source) {
            int u = parent[v];
            graph->capacityMatrix[u][v] -= min_cap;
            graph->capacityMatrix[v][u] += min_cap;
            v = u;
        }
    }
    return max_flow;
}

int main() {
    string file_ONE = "small_instance.dimacs";
    string file_TWO = "maxflow.dimacs";
    int fileChoice;

    cout << "----------" << endl;
    cout << "MAX FLOW" << endl;
    cout << "----------" << endl;
    cout << "Files Available:" << endl;
    cout << "1. small_instance.dimacs | Shorter Dimacs file |" << endl;
    cout << "2. maxflow.dimacs | Longer Dimacs file |" << endl;
    cout << "Type 1 or 2." << endl;
    cout << " " << endl;

    cout << "Insert number of the file of your choice: ";
    cin >> fileChoice;

    Graph* graph = nullptr;
    
    if (fileChoice == 1) {
        graph = readDIMACS(file_ONE);
        cout << "Max Flow: " << maxFlow(graph) << endl;
    }
    else if (fileChoice == 2) {
        cout << "Running file two crashes the code. Work in progress" << endl;
        //graph = readDIMACS(file_TWO);
        //cout << "Max Flow: " << maxFlow(graph) << endl;
    }
    else {
        cout << "Invalid choice. File not found in repository" << endl;
        return -1;
    }
    
    delete graph;
    return 0;
}