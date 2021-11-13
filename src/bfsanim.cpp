#include<bits/stdc++.h>
#include"../include/Graph.h"
using namespace std;
int main(int argc, char*argv[]){
    srand(0);
    int numvert = 100;
    vector<string> labels, duplabels;int n = numvert;int t=0;
    for(int i=0;i<n;i++){
        labels.push_back(to_string(i));
    }
    duplabels = vector<string>(labels);
    SimpleGraph myg;
    myg.initServer();
    myg.addNode("0");
    labels[0] = "";
    Node* holder;
    n--;
    while(n>0){
        while(labels[t]==""){
            t = rand()%numvert;
        }
        n--;
        holder = myg.addNode(labels[t]);
        labels[t] = "";
        t = rand()%numvert;
        while(!(labels[t]=="" && holder->label!=labels[t])){
            t = rand()%numvert;
        }
        // cout<<"Labels: "<<<<labels[t]<<"\n";
        myg.connectNodes(holder, myg.getNodeByLabel(duplabels[t]));
    }
    while(myg.getCliques().size()>1){
        myg.connectNodes(myg.getNodeByLabel(duplabels[rand()%numvert]), myg.getNodeByLabel(duplabels[rand()%numvert]));
    }
    for(int i=0;i<numvert/5;i++){
        myg.connectNodes(myg.getNodeByLabel(duplabels[rand()%numvert]), myg.getNodeByLabel(duplabels[rand()%numvert]));
    }
    myg.assignCoords(myg.rc::BFSTREE);
    myg.syncGraph(true);
    myg.setAutoRender(true);
    cout<<myg.bfs(myg.getNodeByLabel("0"), true, {"green", "blue", "white"})->getAdjList();
    myg.syncGraph(true);
}
