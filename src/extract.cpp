#include<bits/stdc++.h>
#include"../include/Graph.h"
using namespace std;
class graph{
    
    public:
    int nv;
    int V[10];
    int AM[10][10];
    graph(int n){
        nv = n;
        for(int i=0;i<10;i++){
            V[i] = 0;
            for(int j=0;j<10;j++){
                AM[i][j] = 0;
            }
        }
    };
    graph(){};
}
;
graph g;
vector<Node*> extractor(graph g){
    vector<Node*> verts;
    for(int i=0;i<g.nv;i++){
        verts.push_back(new Node(to_string(g.V[i])));
    }
    return verts;
}

bool areAdjacent(string label1, string label2){
    return (g.AM[stoi(label1)][stoi(label2)]==1)||(g.AM[stoi(label2)][stoi(label1)]==1);
}
int main(){
    g = graph(3);
    g.V[0] = 0;
    g.V[1] = 1;
    g.V[2] = 2;
    g.AM[0][1] = 1;
    g.AM[1][2] = 1;
    SimpleGraph myg;
    myg.extractGraph<graph>(g, extractor);
    myg.addEdgesByRelation(areAdjacent);
    myg.initServer();
    myg.syncGraph(true);
}