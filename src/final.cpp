#include<iostream>
#include"../include/Graph.h"
int main(){
    SimpleGraph myg,cycle, complete, bipcomp;
    myg = SimpleGraph("ST", {5, 100});
    cycle = SimpleGraph("C", {6, 100});
    complete = SimpleGraph("K", {7, 100});
    bipcomp = SimpleGraph("KB", {5, 4, 60, 100});
    myg.initServer();
    complete.translate(-230, -170);
    cycle.translate(200, 200);
    bipcomp.translate(200, -150);
    myg.addGraph(&complete, "K", "", false);
    myg.addGraph(&cycle, "C", "",false);
    myg.addGraph(&bipcomp, "", "", false);
    myg.connectNodes(myg.getNodeByLabel("3"), myg.getNodeByLabel("K1"));
    myg.connectNodes(myg.getNodeByLabel("1"), myg.getNodeByLabel("C3"));
    myg.connectNodes(myg.getNodeByLabel("A4"), myg.getNodeByLabel("0"));
    myg.connectNodes(myg.getNodeByLabel("A0"), myg.getNodeByLabel("4"));
    myg.addBranch(myg.getNodeByLabel("2"), {"R1", "R2", "R3", "R4"}, {});
    myg.syncGraph(true);
    myg.setAutoRender(true);
    myg.setRenderDelay(500);
    myg.dfs(myg.getNodeByLabel("R4"), true);
    // myg.bfs(myg.getNodeByLabel("5"), true);
    myg.syncGraph(true);
}