#include<bits/stdc++.h>
#include"../include/Graph.h"
using namespace std;
int main(int argc, char*argv[]){
    srand(0);
    int numvert = atoi(argv[1]);
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
    myg.assignCoords(myg.rc::BFSBW, myg.getNodeByLabel("0"));
    myg.syncGraph(true);
    myg.setAutoRender(true);
    // myg.setRenderDelay(500);
    myg.dfs(myg.getNodeByLabel("0"), true);
    myg.syncGraph(true);
}
