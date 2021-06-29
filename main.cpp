#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
const int INF = 1000000;
class Edge{
public:
    int from, to, cost, capacity, flow;
    Edge(int from, int to, int cost, int capacity){
        this->from = from;
        this->to = to;
        this->cost = cost;
        this->capacity = capacity;
        this->flow = 0;
    }
    Edge(int from, int to){
        this->from = from;
        this->to = to;
        this->cost = 0;
        this->capacity = 0;
        this->flow = 0;
    }

};

int main(int argc, char const *argv[]) {
    ifstream infile;
    infile.open(argv[1]);

    ofstream outfile;
    outfile.open(argv[2]);
    int numTestCases = 0;
    infile >> numTestCases;

    for(int  i = 0; i < numTestCases; i++){
        vector<Edge> edges;
        int numCables = 0;
        infile >> numCables;
        for (int j = 1; j <= numCables; j++) {
            edges.emplace_back(Edge(0, j, 0,1));
            for (int k = numCables+1; k <= 2*numCables; k++) {
                int cost = 0;
                infile >> cost;
                edges.emplace_back(Edge(j, k, -cost,1));
            }
            edges.emplace_back(Edge(numCables + j, 2*numCables+1, 0, 1));
        }
//This code is adapted from:https://github.com/rizaozcelik/cmpe250-fall20/blob/main/PS12/bellman_ford.cpp
        int maxVoltage = 0;
        for (int j = 0; j < numCables; j++) {
            vector<int> distances(2*numCables+2, INF);
            distances[0] = 0;
            vector<int> predecessors(2*numCables+2, -1);
            vector<int> predecessorsEdgeIndex(2*numCables+2, -1);
            int V = 2*numCables+2;
            int nIter = 0;
            bool isUpdated = true;
            while (nIter < V && isUpdated) {
                isUpdated = false;
                for (int k = 0; k < edges.size(); k++) {
                    Edge& e = edges[k];
                    if ((e.capacity-e.flow) > 0 && (distances[e.from] + e.cost < distances[e.to])) {
                        distances[e.to] = distances[e.from] + e.cost;
                        predecessors[e.to] = e.from;
                        predecessorsEdgeIndex[e.to] = k;
                        isUpdated = true;
                    }
                }
                nIter++;
            }





            int successor = 2*numCables+1;

           int predecess = predecessors.at(2*numCables+1);

           while (true){
               maxVoltage -= edges[predecessorsEdgeIndex[successor]].cost;
               edges[predecessorsEdgeIndex[successor]].flow++;

               edges.emplace_back(Edge(successor,predecess, -edges[predecessorsEdgeIndex[successor]].cost, 0));
               edges[edges.size() - 1].flow--;

               if(predecess == 0){
                   break;
               }
               successor = predecess;
               predecess = predecessors.at(successor);
           }



        }
     
        outfile << maxVoltage << endl;
    }




    return 0;
}

