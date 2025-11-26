#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

struct Edge {
    int from, to, capacity;
};

struct Graph {
    int numNodes, numEdges; //total number of Nodes and Edges
    int source, sink; //source(start), sink(end)
    vector<Edge> edges; //all edges of the graph
    vector<vector<int>> adjList; //stores indexes each node's of outgoing edges
    
    Graph(int n) : numNodes(n), numEdges(0), source(-1), sink(-1) {
        adjList.resize(n + 1);
    }
    
    void addEdge(int from, int to, int capacity) {
        edges.push_back({from, to, capacity});
        adjList[from].push_back(edges.size() - 1);
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
        char type; // line type
        iss >> type;
        
        if (type == 'c') {
            // Comment line, skip
            continue;
        }
        else if (type == 'p') {
            // Problem line (nodes, links)
            string format;
            int nodes, edges;
            iss >> format >> nodes >> edges;
            graph = new Graph(nodes);
        }
        else if (type == 'n') {
            // Node descriptor: n <id> <type>
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
            // Arc descriptor lines (from, to, capacity)
            int from, to, capacity;
            iss >> from >> to >> capacity;
            graph->addEdge(from, to, capacity);
        }
    }
    
    file.close();
    return graph;
}

Graph numNodes;

bool bfsPath(int residual, Graph source, Graph sink){
}

int maxFlow(int maxGraph, Graph source, Graph sink){
    int u,v;


};


int main() {
    string file_ONE = "small_instance.dimacs";
    string file_TWO = "maxflow.dimacs";
    int fileChoice;

    cout<< "----------"<<endl;
    cout << "MAX FLOW" <<endl;
    cout<< "----------"<<endl;
    cout << "Files Available:"<<endl;
    cout << "1. small_instance.dimacs" << "| Shorter Dimacs file |" << endl;
    cout << "2. maxflow.dimacs" << "| Longer Dimacs file |" << endl;
    cout <<"Type 1 or 2."<<endl;
    cout <<" "<< endl;

    cout << "Insert number of the file of your choice: ";
    cin >> fileChoice; // insert filename

    if(fileChoice==1){
        Graph* graph = readDIMACS(file_ONE); 

        int maxGraph(Graph);
        //int maxGraph[graph->numNodes][graph->numNodes]={};
        cout << "success" <<endl;
        // maxFlow(maxGraph, graph->sink, graph->sink);

    }

    else if(fileChoice==2){
        Graph* graph = readDIMACS(file_TWO); 
        cout << "success" <<endl;

    }

    else{
        cout << "File not found in repository"<<endl;
        return -1;
    }
    
    return 0;
}