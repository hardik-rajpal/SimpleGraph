#include<bits/stdc++.h>
#include"../include/Graph.h"
#define FOS 0.05 //factor of safety
#define EXFOS 0.1 //extra factor of safety
using namespace std;
string quotestring(string tbq){
    return "\""+tbq+"\"";
}
string ptrtostr(void* ptr){
    stringstream ss;
    ss<<ptr;
    string temp;
    ss>>temp;
    return temp;
}
vector<string> split(string str, string sep){
    vector<string> parts;
    int j = 0;
    for(int i=0;i<str.length();i++){
        if(str.length()-i<sep.length()){break;}
        if(str.substr(i, sep.length())==sep){
            // cout<<str.substr(j, i-j)<<" ";
            parts.push_back(str.substr(j, i-j));
            j = i+sep.length();
        }
    }
    parts.push_back(str.substr(j,str.length()-j));
    return parts;
}
vector<int> toCoords(string kvpair){
    // kvpair = kvpair.substr(1, kvpair.length()-2);
    vector<string> coords = split(kvpair, ",");
    vector<int> xy;
    int xc, yc;
    xc = stoi(split(coords[0], ":")[1]);
    yc = stoi(split(coords[1], ":")[1]);
    xy.push_back(xc);
    xy.push_back(yc);
    return xy;   
}
vector<vector<string>> parseLists(string data, int level){
    vector<vector<string>> lists;
    vector<string> datastr;
    for(int i=0;i<data.length();i++){
        if(data[i]=='['){
            for(int j=i;j<data.length();j++){
                if(data[j]==']'){
                    // cout<<data[i]<<" ";
                    // cout<<data[j]<<"\n";
                    // cout<<data.substr(i+1, j-i-1)<<"\n";
                    // cout<<j-i-1 - (i+1);
                    datastr.push_back(data.substr(i+1, j-i-1));
                    i = j;
                    break;
                }
            }
        }
    }
    // cout<<"Elements of datastr:";
    // for(auto x:datastr){
    //     cout<<x<<", ";
    // }
    if(datastr[0].length()==0){
        return lists;
    }
    datastr[0] = datastr[0].substr(1, datastr[0].length()-2);
    lists.push_back(split(datastr[0], "},{"));
    // lists.push_back({datastr[0]});
    for(int i=1;i<datastr.size();i++){
        vector<string> list = split(datastr[i], ",");
        lists.push_back(list);
    }
    return lists;
}
vector<int> rotateXY(int x, int y, int ang_deg_anti){
    vector<int> ans;
    double ratio = 3.1415/180;
    ans.push_back(x*cos(ang_deg_anti*ratio) + y*sin(ang_deg_anti*ratio));
    ans.push_back(-x*sin(ang_deg_anti*ratio) + y*cos(ang_deg_anti*ratio));
    return ans;
}
void getCycle(vector<int> vals, SimpleGraph* g){
    int CW, CH, CCX, CCY;
    CW = g->canvasWidth; CH = g->canvasHeight; CCX = CW/2; CCY = CH/2;
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
    int CW, CH, CCX, CCY;
    CW = g->canvasWidth; CH = g->canvasHeight; CCX = CW/2; CCY = CH/2;vector<Node*> V;
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
    int CW, CH, CCX, CCY;
    CW = g->canvasWidth; CH = g->canvasHeight; CCX = CW/2; CCY = CH/2;
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
    int CW, CH, CCX, CCY;
    CW = g->canvasWidth; CH = g->canvasHeight; CCX = CW/2; CCY = CH/2;
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
    int CW, CH, CCX, CCY;
    CW = g->canvasWidth; CH = g->canvasHeight; CCX = CW/2; CCY = CH/2;
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
    int CW, CH, CCX, CCY;
    CW = g->canvasWidth; CH = g->canvasHeight; CCX = CW/2; CCY = CH/2;
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
    int CW, CH, CCX, CCY;
    CW = g->canvasWidth; CH = g->canvasHeight; CCX = CW/2; CCY = CH/2;
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
int heightFromMeta(Node *n){
    string hdata = n->metadata;
    hdata = hdata.substr(2, hdata.length()-2);
    return stoi(hdata);
}
int maxBranchWidth(Node*n){
    int ht = heightFromMeta(n);
    int wn = n->outlist.size()-1;
    for(int j=0;j<n->outlist.size()-1;j++){
        if(heightFromMeta(n->outlist[j]->end)==ht+1){
            wn = max(wn, maxBranchWidth(n->outlist[j]->end));
        }
    }
    return wn;
}
bool heightis(Node* n, int h){
    return (heightFromMeta(n)==h);
}
void spreadDFSBW(Node *v, int spread, SimpleGraph *main, SimpleGraph *bfstree){
    int CW, CH, CCX, CCY;
    CW = main->canvasWidth; CH = main->canvasHeight; CCX = CW/2; CCY = CH/2;
    vector<Node*> unsetnodes;vector<int> bws;
    int x, y, sepx=40, sepy=CH/(bfstree->height+1), ht;
    SimpleGraph *tr = bfstree;
    ht = heightFromMeta(v);
    if(bfstree->getNodesIf<int>(heightis, ht).size()==1){
        cout<<v->label<<" is solo "<<"\n";
        main->getNodeByLabel(v->label)->coords[0] = CCX;
        spread = (1-2*FOS)*CW;
    }
    // cout<<v->label<<"has kids: ";
    for(int j=0;j<v->outlist.size();j++){
        if(ht+1==heightFromMeta(bfstree->getNodeByLabel(v->outlist[j]->end->label))){
            // cout<<"adding to unset: "<<v->outlist[j]->end->label<<"\n";
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
    x = int(main->getNodeByLabel(v->label)->coords[0] - int(spread*(1/2.0)) + int(spread*(1.0*bws[0]/(2.0*totbws))));
    cout<<"first x: "<<x<<"\n";
    if(unsetnodes.size()>0){
        unsetnodes[0]->coords = {x,sepy*(ht+2)};
        cout<<"passing node: "<<unsetnodes[0]->label<<"\n";
        spreadDFSBW(tr->getNodeByLabel(unsetnodes[0]->label), (1-2*FOS)*spread*bws[0]/(1.0*totbws), main, tr);
    }
    int cumulx = x;
    for(int j= 1;j<unsetnodes.size();j++){
        sepx = spread*(bws[j-1] + bws[j])/(2.0*totbws);
        cout<<"sep btwn"<<unsetnodes[j-1]->label<<" "<<unsetnodes[j]->label<<" "<<sepx<<"\n";
        cumulx +=sepx;
        unsetnodes[j]->coords = {cumulx,sepy*(ht+2)};
        cout<<"passing node: "<<unsetnodes[j]->label<<"\n";
        spreadDFSBW(tr->getNodeByLabel(unsetnodes[j]->label), (1-2*FOS)*spread*bws[j]/(1.0*totbws), main, tr);
    }
}
void spreadDFS(Node *v, int spread, SimpleGraph *main, SimpleGraph *bfstree){
    int CW, CH, CCX, CCY;
    CW = main->canvasWidth; CH = main->canvasHeight; CCX = CW/2; CCY = CH/2;
    vector<Node*> unsetnodes;
    int x, y, sepx=40, sepy=CH/(bfstree->height+1), ht;
    SimpleGraph *tr = bfstree;
    cout<<"At node: "<<v->label<<"\n";
    unsetnodes = {};

    ht = heightFromMeta(v);
    cout<<v->label<<"has kids: ";
    for(int j=0;j<v->outlist.size();j++){
        if(ht+1==heightFromMeta(bfstree->getNodeByLabel(v->outlist[j]->end->label))){
            // cout<<"adding to unset: "<<v->outlist[j]->end->label<<"\n";
            unsetnodes.push_back(main->getNodeByLabel(v->outlist[j]->end->label));
        }else{/*predecessor node cout<<tr->V[i]->outlist[j]->end->label<<"\n";*/}
    }
    int l = unsetnodes.size();
    if(l>1){
        sepx = int((1-2*EXFOS)*spread/(l-1));
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

string Node::serialize(){
        string data = "{ ";
        string temp;
        ostringstream ss;
        ss<<this;
        temp = ss.str();
        data = data +  quotestring("ptr") +" : "+ quotestring(temp) + ",\n";
        data = data + quotestring("color") + " : " + quotestring(this->color) + ",\n";
        data = data + quotestring("label") + " : " + quotestring(this->label) + ",\n";
        data = data + quotestring("meta") + " : " + quotestring(this->metadata) + ",\n";
        data = data + quotestring("weight") + ": " + to_string(this->weight) + ",\n";
        data = data + quotestring("coords") + ": {\n";
        data = data + quotestring("x") + ": "+ to_string(coords[0])+",\n";
        data = data + quotestring("y") + ": "+ to_string(coords[1])+"\n},\n";
        data = data + quotestring("outlist") + " : [\n";
        
        int deg = outlist.size();
        for(int i=0;i<deg-1;i++){
            data = data + outlist[i]->serialize() + ",\n";
        }
        if(deg>=1){
            data = data + outlist[outlist.size()-1]->serialize() + "\n";
        }
        data = data + "\n]";
        data = data + "\n}";
        lastSerialization = data;
        return data;
    }
string HalfEdge::serialize(){
    string d = "{ \n", temp ="";
    ostringstream wss;
    wss<<(this);
    temp = wss.str();
    d = d + quotestring("ptr") + " : " + quotestring(temp) + ",\n";
    ostringstream tss;
    tss<<(end);
    temp = tss.str();
    d = d + quotestring("end") + " : " + quotestring(temp) + ",\n";
    ostringstream ss;
    ss<<(conjugate);
    temp = ss.str();
    d = d + quotestring("conjugate") + " : " + quotestring(temp) + ",\n";
    d = d + quotestring("weight") + " : " + to_string(weight) +",\n";
    d = d + quotestring("color") + " : " + quotestring(color) +",\n";
    d = d + quotestring("label") + " : " + quotestring(label) +"\n}";
    return d;
}