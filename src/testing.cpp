#include<bits/stdc++.h>
#include"../include/Graph.h"
using namespace std;
int main(){
    SimpleGraph myg;
    myg = SimpleGraph("ST", {5, 200});
    myg.initServer();
    myg.syncGraph(true);
    cout<<"synced";
    myg.assignCoords(myg.rc::BFSTREE);
    myg.setAutoRender(true);
    myg.syncGraph(true);
    // cout<<(SimpleGraph::makers.begin()->second)({})[0]->label;
}