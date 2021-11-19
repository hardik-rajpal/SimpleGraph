#include<iostream>
#include"../include/Graph.h"
int main(){
    // SimpleGraph myg,cycle, complete, bipcomp;
    SimpleGraph myg = SimpleGraph("ST", {5, 100});
    SimpleGraph cycle = SimpleGraph("C", {6, 100});
    SimpleGraph complete = SimpleGraph("K", {7, 100});
    SimpleGraph bipcomp = SimpleGraph("KB", {5, 4, 60, 100});
    complete.translate(-230, -170);
    cycle.translate(200, 200);
    bipcomp.translate(200, -150);
    myg.addGraph(&complete, "K", "", false);
    myg.addGraph(&cycle, "C", "",false);
    myg.addGraph(&bipcomp, "", "", false);
    myg.connectNodes("3", "K1");
    myg.connectNodes("1","C3");
    myg.connectNodes("A4","0");
    myg.connectNodes("A0","4");
    myg.addBranch(myg.getNodeByLabel("2"), {"R1", "R2", "R3", "R4"}, {});
    // myg.assignCoords(myg.rc::BFSSYM, myg.getNodeByLabel("5"), false);
    myg.initServer();
    Sleep(1000);
    myg.syncGraph(true);
    myg.setAutoRender(true);
    myg.setRenderDelay(100);
    SimpleGraph* dfstree = myg.dfs(myg.getNodeByLabel("R4"), true);
    myg.syncGraph(true);
    dfstree->assignCoords(dfstree->rc::BFSSYM, dfstree->V[0]);
    dfstree->initServer(7172);
    Sleep(1000);
    dfstree->syncGraph(true);   
    myg.syncGraph(true);
}