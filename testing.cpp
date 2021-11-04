#include<bits/stdc++.h>
#include"Graph.h"
#include"static.h"

using namespace std;
// vector<string> getCoords(string data){
//
// }
int main(){
    SimpleGraph myg;
    // myg.initServer();
    // myg.setAutoRender(true);
    // myg = SimpleGraph("C", {20, 200});
    // myg = SimpleGraph("K", {15, 200});
    myg = SimpleGraph("KB", {5, 4, 60, 100});
    // myg = SimpleGraph("W", {20, 200});
    // myg = SimpleGraph("P", {10,45, 50});
    // myg = SimpleGraph("CL", {20, 200, 300});
    myg.initServer();
    myg.syncGraph(true);
    myg.setAutoRender(true);
    myg.bfs(myg.getNodeByLabel("B2"), true);
    myg.syncGraph(true);
    // cout<<(SimpleGraph::makers.begin()->second)({})[0]->label;
}