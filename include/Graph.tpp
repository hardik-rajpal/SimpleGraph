#ifndef GRAPH_TPP
#define GRAPH_TPP
#include"../include/Graph.h"
template<class T>
void SimpleGraph::assignVertices(vector<T> vertices, function<string(T)> labelmaker){
    string lab;
    for(int i=0;i<vertices.size();i++){
        lab = labelmaker(vertices[i]);
        addNode(lab);
    }
    head = V[0];
}
template<class T>
void SimpleGraph::extractGraph(T graphobj, function<vector<Node*>(T)> nodemaker){
    V = nodemaker(graphobj);
    nv = V.size();
}
template<typename T>
vector<Node*> SimpleGraph::getNodesIf(function<bool(Node*, T)> predicate, T t){
    vector<Node*> ans;
    for(int i=0;i<nv;i++){
        if(predicate(V[i], t)){
            ans.push_back(V[i]);
        }
    }
    return ans;
}
    
template<class T>
bool contains(vector<T> list, T item){
    for(int i=0;i<list.size();i++){
        if(list[i]==item){
            return true;
        }
    }
    return false;
}
template<class T>
int indexof(vector<T> list, T item){
    for(int i=0;i<list.size();i++){
        if(list[i]==item){
            return i;
        }
    }
    return -1;
}

#endif