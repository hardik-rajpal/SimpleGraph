#include<bits/stdc++.h>
#include"Graph.h"

using namespace std;
string labelmaker(queue<int> q){
    // return to_string(q.front());
    string label = to_string(q.back()*q.back());
    return label;
}

int main(int argc, char *argv[]){
    string adjlist = "1:2,3\n2:1\n3:1";
    SimpleGraph myg = SimpleGraph(adjlist);
    vector<string> lbls = {"4", "5", "6"};
    myg.addBranch(myg.getNodeByLabel("3"), lbls, {});
    // server.awaitRecParse(myg);
    lbls = {"2.1", "2.3", "2.5"};
    myg.addBranch(myg.getNodeByLabel("2"), lbls, {});

    // ServerSocket server = ServerSocket(7171, "127.0.0.1");
    // server.listenForClient();
    // server.sendDataARP(myg.serialize(), myg);
    // server.awaitRecParse(myg);
    
    myg.connectNodes(myg.getNodeByLabel("2.5"), myg.getNodeByLabel("6"));
    cout<<myg.bfs(myg.getNodeByLabel("1"))->getAdjList();
    // server.awaitRecParse(myg);    
}