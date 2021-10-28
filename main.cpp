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
    // vector<string> lbls = {"a", "b", "c"};
    // vector<string> brnch = {"4", "5", "6"};
    // bool am[MAXV][MAXV];am[1][0] = 0;am[2][0] = 1;am[2][1] = 0;
    // queue<int> intq;
    // vector<queue<int>> vqs;
    // intq.push(1);
    // vqs.push_back(intq);
    // intq.push(2);
    // vqs.push_back(intq);
    // intq.push(3);
    // vqs.push_back(intq);
    // SimpleGraph myg = SimpleGraph();
    // myg.assignVertices<queue<int>>(vqs, labelmaker);
    // ServerSocket server = ServerSocket(7171, "127.0.0.1");
    SimpleGraph myg = SimpleGraph(adjlist);
    // server.listenForClient();
    // Sleep(3000);
    // server.sendData(myg.serialize());
    // Sleep(10000);
    cout<<myg.serialize();
}