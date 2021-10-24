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
    vector<string> lbls = {"a", "b", "c"};
    vector<string> brnch = {"4", "5", "6"};
    bool am[MAXV][MAXV];am[1][0] = 0;am[2][0] = 1;am[2][1] = 0;
    queue<int> intq;
    vector<queue<int>> vqs;
    intq.push(1);
    vqs.push_back(intq);
    intq.push(2);
    vqs.push_back(intq);
    intq.push(3);
    vqs.push_back(intq);

    SimpleGraph myg(adjlist);
    // myg.deleteNode(myg.getNodeByLabel("2"));
    // myg.disconnectNodes(myg.getNodeByLabel("1"), myg.getNodeByLabel("2"));
    vector<Node*> vte = {myg.getNodeByLabel("2")};
    // SimpleGraph sg = SimpleGraph(myg.getAdjList());
    // string a = myg.getAdjList();
    SimpleGraph sg = myg.getInducedSubgraph(vte);
    cout<<myg.getAdjList();
    // cout<<"*"<<a<<"*\n";
    cout<<sg.getAdjList();
    // cout<<myg.nv<<" "<<myg.ne<<"\n";
}