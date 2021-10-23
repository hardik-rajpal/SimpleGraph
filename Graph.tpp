#ifndef GRAPH_TPP
#define GRAPH_TPP
#include"Graph.h"
template<class T>
void SimpleGraph::assignVertices(vector<T> vertices, function<string(T)> labelmaker){
    nv = vertices.size();
    Node nd("");
    string lab;
    for(int i=0;i<vertices.size();i++){
        lab = labelmaker(vertices[i]);
        nd.label = lab;
        V.push_back(nd);
    }
}
#endif