#ifndef STATIC_HFILE
#define STATIC_HFILE
#define CW 700
#define CH 650
#define CCX CW/2
#define CCY CH/2
#include<bits/stdc++.h>
#ifndef GRAPH_H
#include"../include/Graph.h"
#endif
using namespace std;
void getCycle(vector<int> vals, SimpleGraph* g){
    vector<int> coords;
    int n = vals[0];
    int rad = vals[1];
    int  x, y;
    double theta = 0;
    double dtheta = (360/(1.0*n))*(3.1415/180);
    
    for(int i=0;i<n;i++){
        x = CCX + (int)rad*cos(theta + i*dtheta);
        y = CCY + (int)rad*sin(theta + i*dtheta);
        coords = {x, y};
        g->addNode(to_string(i), coords, 1, "");
    }
    for(int i=0;i<n-1;i++){
        g->connectNodes(g->getNodeByLabel(to_string(i)), g->getNodeByLabel(to_string(i+1)));
    }
    g->connectNodes(g->getNodeByLabel(to_string(n-1)), g->getNodeByLabel("0"));
    return;
}
void getComplete(vector<int> vals, SimpleGraph *g){
    vector<Node*> V;
    vector<int> coords;
    int n = vals[0];
    int rad = vals[1];
    int x, y;
    double theta = 0;
    double dtheta = (360/(1.0*n))*(3.1415/180);
    
    for(int i=0;i<n;i++){
        x = CCX + (int)rad*cos(theta + i*dtheta);
        y = CCY + (int)rad*sin(theta + i*dtheta);
        coords = {x, y};
        g->addNode(to_string(i), coords, 1, "");
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            g->connectNodes(g->getNodeByLabel(to_string(i)), g->getNodeByLabel(to_string(j)));
        }
    }
    return;
}
void getCompleteBipartite(vector<int> vals, SimpleGraph*g){
    int n = vals[0];int m = vals[1];int dy = vals[2];int dx = vals[3];
    int x = CCX - dx/2; int y = CCY - (n/2)*dy;
    vector<int> coords;
    for(int i=0;i<n;i++){
        coords = {x, y};
        g->addNode("A"+to_string(i), coords, 1, "");
        y+=dy;
    }
    y = CCY - (m/2)*dy;
    x = CCX + dx;
    for(int i=0;i<m;i++){
        coords = {x, y};
        g->addNode("B"+to_string(i), coords, 1, "");
        y+=dy;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            g->connectNodes(g->getNodeByLabel("A"+to_string(i)), g->getNodeByLabel("B"+to_string(j)));
        }
    }
    return;
}
void getWheel(vector<int> vals, SimpleGraph* g){
    vector<int> coords;
    int n = vals[0];
    int rad = vals[1];
    int x, y;
    double theta = 0;
    double dtheta = (360/(1.0*n))*(3.1415/180);
    for(int i=0;i<n;i++){
        x = CCX + (int)rad*cos(theta + i*dtheta);
        y = CCY + (int)rad*sin(theta + i*dtheta);
        coords = {x, y};
        g->addNode(to_string(i), coords, 1, "");
    }
    coords = {CCX, CCY};
    g->addNode(to_string(n), coords, 1, "");
    for(int i=0;i<n-1;i++){
        g->connectNodes(g->getNodeByLabel(to_string(i)), g->getNodeByLabel(to_string(i+1)));
        g->connectNodes(g->getNodeByLabel(to_string(n)), g->getNodeByLabel(to_string(i)));
    }
    g->connectNodes(g->getNodeByLabel(to_string(n-1)), g->getNodeByLabel("0"));
    g->connectNodes(g->getNodeByLabel(to_string(n-1)), g->getNodeByLabel(to_string(n)));
    return;
}
void getPath(vector<int> vals, SimpleGraph* g){
    int n = vals[0]; int angle = vals[1];int sep = vals[2];
    int x, y;vector<int> coords;
    x = CCX - (n/2)*sep*cos(angle);y = CCY - (n/2)*sep*sin(angle);
    for(int i=0;i<n;i++){
        coords = {x, y};
        g->addNode(to_string(i), coords, 1, "");
        x+=(sep*cos(angle)); y+=(sep*sin(angle));
    }
    for(int i=0;i<n-1;i++){
        g->connectNodes(g->getNodeByLabel(to_string(i)), g->getNodeByLabel(to_string(i+1)));
    }
    return;
}
void getCircularLadder(vector<int> vals, SimpleGraph*g){
    vector<int> coords;
    int n = vals[0];
    int rad = vals[1];
    int radius2 = vals[2];
    int x, y;
    double theta = 0;
    double dtheta = (360/(1.0*n))*(3.1415/180);
    for(int i=0;i<n;i++){
        x = CCX + (int)rad*cos(theta + i*dtheta);
        y = CCY + (int)rad*sin(theta + i*dtheta);
        coords = {x, y};
        g->addNode("A"+to_string(i), coords, 1, "");
    }
    for(int i=0;i<n;i++){
        x = CCX + (int)radius2*cos(theta + i*dtheta);
        y = CCY + (int)radius2*sin(theta + i*dtheta);
        coords = {x, y};
        g->addNode("B"+to_string(i), coords, 1, "");
    }
    coords = {CCX, CCY};
    g->addNode(to_string(n), coords, 1, "");
    
    for(int i=0;i<n-1;i++){
        g->connectNodes(g->getNodeByLabel("A"+to_string(i)), g->getNodeByLabel("A"+to_string(i+1)));
        g->connectNodes(g->getNodeByLabel("B"+to_string(i)), g->getNodeByLabel("B"+to_string(i+1)));
        g->connectNodes(g->getNodeByLabel("B"+to_string(i)), g->getNodeByLabel("A"+to_string(i)));
        g->connectNodes(g->getNodeByLabel(to_string(n)), g->getNodeByLabel("A"+to_string(i)));
    }
    g->connectNodes(g->getNodeByLabel("A"+to_string(n-1)), g->getNodeByLabel("A0"));
    g->connectNodes(g->getNodeByLabel("B"+to_string(n-1)), g->getNodeByLabel("B0"));
    g->connectNodes(g->getNodeByLabel("A"+to_string(n-1)), g->getNodeByLabel(to_string(n)));
    g->connectNodes(g->getNodeByLabel("A"+to_string(n-1)), g->getNodeByLabel("B"+to_string(n-1)));
    
    return;
}
const map<string,int> SimpleGraph::validvals={
    {"K",2},
    {"C",2},
    {"KB", 4},
    {"W", 2},
    {"P", 3},
    {"CL", 3}
};
const map<string,function<void(vector<int>, SimpleGraph*)>> SimpleGraph::makers={
    {"K", getComplete},
    {"C", getCycle},
    {"KB", getCompleteBipartite},
    {"W", getWheel},
    {"P", getPath},
    {"CL", getCircularLadder}
};
#endif