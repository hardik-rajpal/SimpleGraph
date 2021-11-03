#include<bits/stdc++.h>
#include"Graph.h"
#include"config.h"
using namespace std;
string labelmaker(queue<int> q){
    // return to_string(q.front());
    string label = to_string(q.back()*q.back());
    return label;
}

int main(int argc, char *argv[]){
    string adjlist = "1:2,3\n2:1\n3:1";
    SimpleGraph myg = SimpleGraph(adjlist);

    // myg.initServer();
    // myg.setAutoRender(true);
    vector<string> lbls = {"4", "5", "6"};
    myg.addBranch(myg.getNodeByLabel("3"), lbls, {});
    lbls = {"2.1", "2.3", "2.5"};
    // myg.syncGraph();
    // Sleep(1000);
    myg.addBranch(myg.getNodeByLabel("2"), lbls, {});    
    // myg.syncGraph(true);
    // Sleep(1000);
    myg.connectNodes(myg.getNodeByLabel("2.5"), myg.getNodeByLabel("6"));
    // myg.syncGraph(true);
    cout<<myg.bfs(myg.getNodeByLabel("1"))->getAdjList();

    // myg.syncGraph(true);
}