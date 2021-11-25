#include"../include/Graph.h"
#include<bits/stdc++.h>
using namespace std;
bool collatzNums(string l1, string l2){
    int n1 = stoi(l1), n2 = stoi(l2);
    int temp=n1;
    n1 = min(n1, n2);
    n2 = max(temp, n2);
    if(n1%2==1){
        if(n2==3*n1 + 1 || n2 == 2*n1){
            return  true;
        }
    }
    else{
        if(n2==2*n1){
            return true;
        }
    }
    return false;
}
bool isolatedNode(Node* n, SimpleGraph * g){
    return (g->getpathbetween(n, g->getNodeByLabel("1"), {}).size())==0;
}
int main(int argc, char * argv[]){
    
    int numvert = atoi(argv[1]);
    vector<string> labels;
    for(int i=0;i<numvert;i++){
        labels.push_back(to_string(i+1));
        // cout<<labels[i]<<" ";
    }
    SimpleGraph  g = SimpleGraph(labels);
    g.addEdgesByRelation(collatzNums);
    SimpleGraph g2 = g.getInducedSubgraph(g.getNodesIf<SimpleGraph*>(isolatedNode, &g));
    
    g2.setCanvasDimensions(700, 650);
    g2.assignCoords(g2.rc::BFSSYM, g2.getNodeByLabel("1"));
    g2.initServer(7171);
    Sleep(1000);
    g2.syncGraph(true);
    g2.syncGraph(true);
    cout<<g2.getAdjList();
}