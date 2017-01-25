#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <stdlib.h>
using namespace std;

struct NodesQueue {
    list<int> _path;
    int _cost;
    bool operator>(const NodesQueue& rhs) const {
        return _cost > rhs._cost;
    }
};

class NodesQueueComparison {
public:
    bool operator() (NodesQueue p1, NodesQueue p2) const {
        return (p1>p2);
    }
};

class Graph {

public:
    Graph(int nodes):_nodes(nodes) {
        _adjacents = new vector<int>[nodes];
        _weights = new vector<int>[nodes];
    }

    void addEdge(int node1, int node2, int weight){
        _adjacents[node1].push_back(node2);
        _weights[node1].push_back(weight);
    }

    void UCS(int start, int goal){
        int current=0, pos=0;
        NodesPriorityQueue priority_queue;
        NodesQueue vstart;
        vstart._path.push_back(start);
        vstart._cost = 0;
        vector<int>::iterator i;
        priority_queue.push(vstart);
        while(!priority_queue.empty()) {
            NodesQueue currentPQ, tempPQ;
            current = priority_queue.top()._path.back();
            currentPQ = priority_queue.top();
            priority_queue.pop();
            if(current == goal){
                cout<<"found"<<endl;
                displayPath(currentPQ);
                exit(0);
            }else
                for (i = _adjacents[current].begin(); i != _adjacents[current].end(); ++i) {
                    tempPQ = currentPQ;
                    tempPQ._path.push_back(*i);
                    pos = find(_adjacents[current].begin(), _adjacents[current].end(), *i) - _adjacents[current].begin();
                    tempPQ._cost += _weights[current].at(pos);
                    priority_queue.push(tempPQ);
                }
        }
    }

    void displayPath(NodesQueue p){
        list<int>::iterator i;
        cout<<"Path: ";
        for (i = p._path.begin(); i != p._path.end(); ++i)
            cout<<"->"<<*i;
        cout<<endl;
        cout<<"Path length: "<<p._cost<<endl;
    }

protected:
    int _nodes;
    vector<int> *_adjacents;
    vector<int> *_weights;
    typedef priority_queue<NodesQueue,vector<NodesQueue>,NodesQueueComparison> NodesPriorityQueue;
};

int main(int argc, char** argv) {
    int nodes,edges;
    int source = 0, destination = 0;

    ifstream file;
    string line;
    file.open(argv[1]);

    getline(file,line);
    nodes = atoi(line.c_str());
    cout << "No. of nodes: " << nodes << endl;
    line.clear();

    getline(file,line);
    edges = atoi(line.c_str());
    cout << "No. of edges:" << edges << endl;
    line.clear();

    Graph graph(edges);

    for (int i = 0; i < edges; i++) {
        getline(file,line);
        istringstream iss(line);
        int node1,node2,weight;
        iss >> node1 >> node2 >> weight;
        graph.addEdge(node1,node2,weight);
        line.clear();
    }

    getline(file,line);
    source = atoi(line.c_str());
    cout<<"Start node: " << source << endl;
    line.clear();

    getline(file,line);
    destination = atoi(line.c_str());
    cout<<"Goal node: " << destination << endl;
    line.clear();

    graph.UCS(source,destination);
    return 0;
}
