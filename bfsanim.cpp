#include<bits/stdc++.h>
#include"Graph.h"
#include"config.h"
using namespace std;
int main(int argc, char*argv[]){
    srand(0);
    vector<string> labels, duplabels;int n = 20;int t=0;
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
            t = rand()%20;
        }
        n--;
        holder = myg.addNode(labels[t]);
        labels[t] = "";
        t = rand()%20;
        while(!(labels[t]=="" && holder->label!=labels[t])){
            t = rand()%20;
        }
        // cout<<"Labels: "<<<<labels[t]<<"\n";
        myg.connectNodes(holder, myg.getNodeByLabel(duplabels[t]));
    }
    while(myg.getCliques().size()>1){
        myg.connectNodes(myg.getNodeByLabel(duplabels[rand()%20]), myg.getNodeByLabel(duplabels[rand()%20]));
    }
    for(int i=0;i<20;i++){
        myg.connectNodes(myg.getNodeByLabel(duplabels[rand()%20]), myg.getNodeByLabel(duplabels[rand()%20]));
    }
    myg.syncGraph(true);
    myg.setAutoRender(true);
    cout<<myg.bfs(myg.getNodeByLabel("A"), true, {"green", "blue", "white"})->getAdjList();
    myg.syncGraph(true);
}

// int main(int argc, char *argv[]){
//     string adjlist = "1:2,3\n2:1\n3:1";
//     SimpleGraph myg = SimpleGraph(adjlist);

//     myg.initServer();
//     // myg.setAutoRender(true);
//     vector<string> lbls = {"4", "5", "6"};
//     myg.addBranch(myg.getNodeByLabel("1"), lbls, {});
//     lbls = {"2.1", "2.3", "2.5"};
//     // myg.syncGraph();
//     // Sleep(1000);
//     myg.addBranch(myg.getNodeByLabel("2"), lbls, {});    
//     // myg.syncGraph(true);
//     // Sleep(1000);
//     myg.connectNodes(myg.getNodeByLabel("2.5"), myg.getNodeByLabel("6"));
//     myg.connectNodes(myg.getNodeByLabel("2.5"), myg.getNodeByLabel("2"));
//     myg.connectNodes(myg.getNodeByLabel("3"), myg.getNodeByLabel("5"));
//     myg.syncGraph(true);
//     // cout<<myg.bfs(myg.getNodeByLabel("1"))->getAdjList();
//     myg.setAutoRender(true);
//     SimpleGraph *bfstree = myg.bfs(myg.getNodeByLabel("1"), true, {"green", "blue", "white"});
//     myg.syncGraph(true);
//     myg.server->sendDataARP(bfstree->serialize(), *bfstree);
// }