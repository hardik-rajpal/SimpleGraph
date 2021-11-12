#include<bits/stdc++.h>
#include"../include/Graph.h"
#include"../include/static.h"

using namespace std;
// vector<string> getCoords(string data){
//
// }
int main(){
    SimpleGraph myg,mygp;
    // myg.initServer();
    // myg.setAutoRender(true);
    // myg = SimpleGraph("C", {20, 200});
    // myg = SimpleGraph("K", {15, 200});
    // myg = SimpleGraph("KB", {5, 4, 60, 100});
    myg = SimpleGraph("W", {20, 200});

    mygp = SimpleGraph("P", {10,0, 50});
    myg.addGraph(&mygp, true);
    // myg = SimpleGraph("CL", {20, 200, 300});
    myg.initServer();
    myg.syncGraph(true);
    myg.setAutoRender(true);
    myg.bfs(myg.getNodeByLabel("B2"), true);
    myg.syncGraph(true);
    // cout<<(SimpleGraph::makers.begin()->second)({})[0]->label;
}