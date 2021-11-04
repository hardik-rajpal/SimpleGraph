#include<bits/stdc++.h>
#include"../include/Graph.h"
#include"../include/config.h"
#include"../include/static.h"
using namespace std;
int main(int argc, char*argv[]){
    srand(0);
    vector<string> labels, duplabels;int n=20,k = 20;int t=0;
    char c = 'A';
    for(int i=0;i<n;i++){
        labels.push_back(string(1, c));
        c++;
    }
    duplabels = vector<string>(labels);
    SimpleGraph myg;
    myg.initServer();
    myg.addNode("A");
    labels[0] = "";
    Node* holder;
    n--;
    while(n>0){
        while(labels[t]==""){
            t = rand()%k;
        }
        n--;
        holder = myg.addNode(labels[t]);
        labels[t] = "";
        t = rand()%k;
        while(!(labels[t]=="" && holder->label!=labels[t])){
            t = rand()%k;
        }
        // cout<<"Labels: "<<<<labels[t]<<"\n";
        myg.connectNodes(holder, myg.getNodeByLabel(duplabels[t]));
    }
    while(myg.getCliques().size()>1){
        myg.connectNodes(myg.getNodeByLabel(duplabels[rand()%k]), myg.getNodeByLabel(duplabels[rand()%k]));
    }
    for(int i=0;i<k/2;i++){
        myg.connectNodes(myg.getNodeByLabel(duplabels[rand()%k]), myg.getNodeByLabel(duplabels[rand()%k]));
    }
    myg.syncGraph(true);
    myg.setAutoRender(true);
    cout<<"\n"<<myg.dfs(myg.getNodeByLabel("A"), true, {"green", "blue", "white"})->getAdjList()<<"\n";
    myg.syncGraph(true);
    myg.syncGraph(true);
}
