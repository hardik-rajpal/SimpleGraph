#ifndef STATIC_H
#define STATIC_H
#define CW 700
#define CH 650
#define CCX CW/2
#define CCY CH/2
#include<bits/stdc++.h>
#include"../include/Graph.h"
using namespace std;
void getCycle(vector<int> vals, SimpleGraph* g){
    vector<int> coords;
    int n = vals[0];
    int rad = vals[1];
    int  x, y;
    double theta = 0;
    double dtheta = (360/(1.0*n))*(3.1415/180);
    g->setCenter(CCX, CCY);
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
    g->setCenter(CCX, CCY);
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
    g->setCenter(CCX, CCY);
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
    g->setCenter(CCX, CCY);
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
void getStar(vector<int>  vals, SimpleGraph* g){
    g->setCenter(CCX, CCY);
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
    for(int i=0;i<n;i++){
        g->connectNodes(g->getNodeByLabel(to_string(n)), g->getNodeByLabel(to_string(i)));
    }
    return;
}
void getPath(vector<int> vals, SimpleGraph* g){
    g->setCenter(CCX, CCY);
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
    g->setCenter(CCX, CCY);
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
    {"ST", 2},
    {"P", 3},
    {"CL", 3}
};
const map<string,function<void(vector<int>, SimpleGraph*)>> SimpleGraph::makers={
    {"K", getComplete},
    {"C", getCycle},
    {"KB", getCompleteBipartite},
    {"W", getWheel},
    {"ST", getStar},
    {"P", getPath},
    {"CL", getCircularLadder}
};
int maxBranchWidth(Node*n){
    string hdata = n->metadata;
    hdata = hdata.substr(2, hdata.length()-2);
    // cout<<"hdata? "<<hdata<<"\n";
    int ht = stoi(hdata);
    int wn = n->outlist.size()-1;
    for(int j=0;j<n->outlist.size()-1;j++){
        hdata = n->outlist[j]->end->metadata;
        hdata = hdata.substr(2, hdata.length()-2);
        if(stoi(hdata)==ht+1){
            wn = max(wn, maxBranchWidth(n->outlist[j]->end));
        }
    }
    return wn;
    
}
void spreadDFSBW(Node *v, int spread, SimpleGraph *main, SimpleGraph *bfstree){
    string hdata, hdatachild;
    vector<Node*> unsetnodes;vector<int> bws;
    int x, y, sepx=40, sepy=CH/(bfstree->height+1), ht;
    SimpleGraph *tr = bfstree;
    cout<<"At node: "<<v->label<<"\n";
    hdata = v->metadata;
    hdata = hdata.substr(2, hdata.length()-2);
    cout<<"hdata? "<<hdata<<"\n";
    ht = stoi(hdata);
    cout<<v->label<<"has kids: ";
    for(int j=0;j<v->outlist.size();j++){
        cout<<v->outlist[j]->end->label<<", ";
        hdatachild = bfstree->getNodeByLabel(v->outlist[j]->end->label)->metadata;
        cout<<"heights of comrades"<<hdatachild<<" ";
        hdatachild = hdatachild.substr(2, hdatachild.length()-2);
        if(stoi(hdata)+1==stoi(hdatachild)){
            cout<<"adding to unset: "<<v->outlist[j]->end->label<<"\n";
            unsetnodes.push_back(main->getNodeByLabel(v->outlist[j]->end->label));
        }else{/*predecessor node cout<<tr->V[i]->outlist[j]->end->label<<"\n";*/}
    }
    int l = unsetnodes.size();
    int totbws=0, itemp;
    for(int j=0;j<l;j++){
        itemp = maxBranchWidth(unsetnodes[j]);
        bws.push_back(itemp);
        totbws +=itemp;
    }
    bws.push_back(spread);
    totbws = max(totbws, 1);
    // if(l%2==1){
    x = int(main->getNodeByLabel(v->label)->coords[0] - int(spread*(1/2.0)) + int(spread*(1.0*bws[0]/(2.0*totbws))));
    // }
    // else{
    // x = int(main->getNodeByLabel(v->label)->coords[0] - int(sepx*((l-1)/2.0)));
    // }

    cout<<"first x: "<<x<<"\n";
    if(unsetnodes.size()>0){
        unsetnodes[0]->coords = {x,sepy*(ht+2)};
        cout<<"passing node: "<<unsetnodes[0]->label<<"\n";
        spreadDFSBW(tr->getNodeByLabel(unsetnodes[0]->label), spread*bws[0]/(1.0*totbws), main, tr);
    }
    int cumulx = x;
    for(int j= 1;j<unsetnodes.size();j++){
        sepx = spread*(bws[j-1] + bws[j])/(2.0*totbws);
        cout<<"sep btwn"<<unsetnodes[j-1]->label<<" "<<unsetnodes[j]->label<<" "<<sepx<<"\n";
        cumulx +=sepx;
        unsetnodes[j]->coords = {cumulx,sepy*(ht+2)};
        cout<<"passing node: "<<unsetnodes[j]->label<<"\n";
        spreadDFSBW(tr->getNodeByLabel(unsetnodes[j]->label), spread*bws[j]/(1.0*totbws), main, tr);
    }
}
void spreadDFS(Node *v, int spread, SimpleGraph *main, SimpleGraph *bfstree){
    string hdata, hdatachild;
    vector<Node*> unsetnodes;
    int x, y, sepx=40, sepy=CH/(bfstree->height+1), ht;
    SimpleGraph *tr = bfstree;
    cout<<"At node: "<<v->label<<"\n";
    unsetnodes = {};
    hdata = v->metadata;
    hdata = hdata.substr(2, hdata.length()-2);
    cout<<"hdata? "<<hdata<<"\n";
    ht = stoi(hdata);
    cout<<v->label<<"has kids: ";
    for(int j=0;j<v->outlist.size();j++){
        cout<<v->outlist[j]->end->label<<", ";
        hdatachild = bfstree->getNodeByLabel(v->outlist[j]->end->label)->metadata;
        cout<<"heights of comrades"<<hdatachild<<" ";
        hdatachild = hdatachild.substr(2, hdatachild.length()-2);
        if(stoi(hdata)+1==stoi(hdatachild)){
            cout<<"adding to unset: "<<v->outlist[j]->end->label<<"\n";
            unsetnodes.push_back(main->getNodeByLabel(v->outlist[j]->end->label));
        }else{/*predecessor node cout<<tr->V[i]->outlist[j]->end->label<<"\n";*/}
    }
    int l = unsetnodes.size();
    if(l>1){
        sepx = int(0.8*spread/(l-1));
        cout<<"numchil: "<<l<<",sep"<<sepx<<"\n";
    }
    else if(l==1){
        sepx = 30;//doesn't matter
    }
    if(l%2==1){
    x = int(main->getNodeByLabel(v->label)->coords[0] - int(sepx*((l-1)/2.0)));
    }
    else{
    x = int(main->getNodeByLabel(v->label)->coords[0] - int(sepx*((l-1)/2.0)));
    }

    cout<<"first x: "<<x<<"\n";
    for(int j=0;j<unsetnodes.size();j++){
        unsetnodes[j]->coords = {x + sepx*j,sepy*(ht+2)};
        cout<<"passing node: "<<unsetnodes[j]->label<<"\n";
        spreadDFS(tr->getNodeByLabel(unsetnodes[j]->label), int(spread/l), main, tr);
    }
}
void SimpleGraph::assignCoords(int config){
    if(config==rc::RAND){
        for(int i=0;i<V.size();i++){
            V[i]->coords = {int(CW*0.05)+rand()%(int(CW*0.9)), int(CH*0.05)+rand()%(int(CH*0.9))};
        }
    }
    else if(config==rc::BFSTREE){
        int sepy=50;
        int mas = int(0.99*CW);//max allowed spread;
        SimpleGraph *tr = bfs(V[0], false);
        V[0]->coords = {CCX, sepy};
        spreadDFSBW(tr->V[0], mas, this, tr);
    }
}
#endif