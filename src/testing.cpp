#include<bits/stdc++.h>
#include"../include/Graph.h"
using namespace std;
int main(){
    SimpleGraph myg;
    myg = SimpleGraph("ST", {5, 200});
    myg.initServer();
    int N = 100, dtheta = 5;
    for(int i=0;i<N;i++){
        myg.rotate(dtheta);
        myg.syncGraph(false);
    }
    myg.syncGraph(true);
    myg.setAutoRender(true);
    myg.syncGraph(true);
    // cout<<(SimpleGraph::makers.begin()->second)({})[0]->label;
}