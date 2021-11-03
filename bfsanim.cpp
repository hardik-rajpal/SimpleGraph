#include<bits/stdc++.h>
#include"Graph.h"
#include"config.h"
using namespace std;

int main(int argc, char *argv[]){
    string adjlist = "1:2,3\n2:1\n3:1";
    SimpleGraph myg = SimpleGraph(adjlist);

    myg.initServer();
    // myg.setAutoRender(true);
    vector<string> lbls = {"4", "5", "6"};
    myg.addBranch(myg.getNodeByLabel("1"), lbls, {});
    lbls = {"2.1", "2.3", "2.5"};
    // myg.syncGraph();
    // Sleep(1000);
    myg.addBranch(myg.getNodeByLabel("2"), lbls, {});    
    // myg.syncGraph(true);
    // Sleep(1000);
    myg.connectNodes(myg.getNodeByLabel("2.5"), myg.getNodeByLabel("6"));
    myg.connectNodes(myg.getNodeByLabel("2.5"), myg.getNodeByLabel("2"));
    myg.connectNodes(myg.getNodeByLabel("3"), myg.getNodeByLabel("5"));
    myg.syncGraph(true);
    // cout<<myg.bfs(myg.getNodeByLabel("1"))->getAdjList();
    myg.setAutoRender(true);
    SimpleGraph *bfstree = myg.bfs(myg.getNodeByLabel("1"), true, {"green", "blue", "white"});
    myg.syncGraph(true);
    myg.server->sendDataARP(bfstree->serialize(), *bfstree);
}