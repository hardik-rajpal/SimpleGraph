#include<bits/stdc++.h>
#include"../include/Graph.h"
#include"../include/config.h"
#define  RENDER if(autorender){syncGraph();}
using namespace std;
SimpleGraph::SimpleGraph(){};
SimpleGraph::SimpleGraph(string s, vector<int> vals){
    if((validvals.count(s)==0)){
        cout<<"Invalid Symbol!\n";
        return;
    }
    else{
        if(validvals.at(s)!=vals.size()){
            cout<<"Invalid number vector!\n";
        }
        else{
            makers.at(s)(vals, this);
        }
    }

}
SimpleGraph::SimpleGraph(vector<string> labels){
    for(int i=0;i<labels.size();i++){
        addNode(labels[i]);
        // cout<<V[i]->label<<" is the new label\n";
    }
    head = V[0];
}
SimpleGraph::SimpleGraph(bool adjmat[MAXV][MAXV], vector<string> labels){
    for(int i=0;i<labels.size();i++){
        addNode(labels[i]);
    }
    // cout<<V.size()<<"\n";
    for(int i=0;i<nv;i++){
        for(int j=0;j<i;j++){
            if(adjmat[i][j]){
                // cout<<i<<" "<<j<<"\n";
                connectNodes(V[i], V[j]);
            }
        }
    }
    head = V[0];
}
SimpleGraph::SimpleGraph(string adjlist){
    /*
    Format: No spaces at end/start, \n at end of line.
    v1:v2,v3
    v2:v1
    v3:v1
    */
    string curlabel;
    vector<string> lists = split(adjlist, "\n");
    for(int i=0;i<lists.size();i++){
        curlabel = split(lists[i],":")[0];
        addNode(curlabel);
    }
    // cout<<"Hi";
    Node *currNode;vector<string> neighlabels;
    for(int i=0;i<lists.size();i++){
        curlabel = split(lists[i],":")[0];
        currNode = getNodeByLabel(curlabel);
        if(currNode==NULL){
            cout<<"Node in hlist not in vlist!\n";
            return;
        }
        neighlabels = split((split(lists[i], ":"))[1], ",");
        for(int i=0;i<neighlabels.size();i++){
            connectNodes(currNode, getNodeByLabel(neighlabels[i]));
        }
    }
}
SimpleGraph::~SimpleGraph(){
    // cout<<"Destroyed!";
    for(int i=0;i<nv;i++){
        for(int j=0;j<V[i]->outlist.size();j++){
            delete V[i]->outlist[j];
        }
        delete V[i];
    }
    #ifdef SERVERUSED
    if(server!=NULL){
        server->closeConnection();
    }
    #endif
}
Node* SimpleGraph::addNode(string label){
    Node *n;
    n = new Node(label);
    V.push_back(n);
    nv++;
    RENDER
    return V[V.size()-1];
}
Node* SimpleGraph::addNode(string label, vector<int> coords, int weight, string color){
    Node *n;
    n = new Node(label);
    n->coords = coords;
    n->weight = weight;
    n->color = color;
    V.push_back(n);
    nv++;
    RENDER
    return V[V.size()-1];
}
bool SimpleGraph::deleteNode(Node *n1){
    bool deleted = false;
    for(int i=0;i<nv;i++){
        if(V[i]==n1){
            V[i] = V[V.size()-1];
            V.pop_back();
            deleted = true;
        }
        else{
            for(int j=0;j<V[i]->outlist.size();j++){
                if(V[i]->outlist[j]->end==n1){
                    int sz = V[i]->outlist.size();
                    V[i]->outlist[j]=V[i]->outlist[sz-1];
                    V[i]->outlist.pop_back();
                    ne--;
                    break;
                }
            }
        }
    }
    nv--;
    int etrm = 0;
    if(!deleted){
        cout<<"W:Node to be removed NOT FOUND!";
    }
    return deleted;
}

HalfEdge *SimpleGraph::connectNodes(Node*n1, Node*n2){
    if(n1==n2){return NULL;}
    if(areAdjacent(n1, n2)){
        // cout<<"W:Attempted to connect adjacent nodes!\n";
        return getEdgeByNodes(n1, n2);
    }
    HalfEdge *e1 = new HalfEdge(n2);
    HalfEdge *e2 = new HalfEdge(n1);
    e1->conjugate = e2;
    e2->conjugate = e1;
    ne++;
    for(int i=0;i<nv;i++){
        if(V[i]==n1){
            V[i]->outlist.push_back(e1);
        }
        if(V[i]==n2){
            V[i]->outlist.push_back(e2);
        }
    }
    RENDER
    return e1;
}
HalfEdge *SimpleGraph::connectNodes(string l1, string l2){
    return connectNodes(getNodeByLabel(l1), getNodeByLabel(l2));    
}
int SimpleGraph::addEdgesByRelation(function<bool(string, string)> relation){
    for(int i=0;i<V.size();i++){
        for(int j=0;j<i;j++){
            if(relation(V[i]->label, V[j]->label)||relation(V[j]->label, V[i]->label)){
                connectNodes(V[i], V[j]);
            }
        }
    }
    return ne;
}

Node *SimpleGraph::addBranch(Node *root, vector<string> vlabels, vector<string> elabels){
    Node *n2;
    if(elabels.size()==0){
        for(int i=0;i<vlabels.size();i++){
            n2 = addNode(vlabels[i]);
            connectNodes(root, n2);
            root = n2;
        }
    }
    else{
        HalfEdge *e;
        for(int i=0;i<vlabels.size();i++){
            n2 = addNode(vlabels[i]);
            e = connectNodes(root, n2);
            e->label = elabels[i]; e->conjugate->label = elabels[i];
            root = n2;
        }
    }
    return root;
}
void SimpleGraph::addGraph(SimpleGraph *myg, string labelprefix,string labelsuffix,bool duplicate){
    Node *t, *u;
    vector<Node*> news;
    if(!duplicate){
        for(auto x:myg->V){
            x->label = labelprefix + x->label + labelsuffix;
            V.push_back(x);
            nv++;
            RENDER
        }
    }
    else{
        for(int i=0;i<myg->V.size();i++){
            t = myg->V[i];
            news.push_back(addNode(labelprefix + t->label + labelsuffix, {t->coords[0], t->coords[1]}, t->weight, t->color));
        }
        for(int i=0;i<myg->V.size();i++){
            t = myg->V[i];
            for(int j=0;j<i;j++){
                u = myg->V[j];
                if(myg->areAdjacent(t, u)){
                    connectNodes(news[i], news[j]);
                }
            }
        }
    }
}
bool SimpleGraph::disconnectNodes(Node *n1, Node*n2){
    bool deleted = false;
    for(int i=0;i<n1->outlist.size();i++){
        if(n1->outlist[i]->end==n2){
            n1->outlist[i] = n1->outlist[n1->outlist.size()-1];
            n1->outlist.pop_back();
            break;
        }   
    }
    for(int i=0;i<n2->outlist.size();i++){
        if(n2->outlist[i]->end==n1){
            n2->outlist[i] = n2->outlist[n2->outlist.size()-1];
            n2->outlist.pop_back();
            break;
        }   
    }
    ne--;
    if(!deleted){
        cout<<"W:Tried To Delete Absent Edge!\n";
    }
    return deleted;
}

Node* SimpleGraph::getNodeByLabel(string label){
    for(int i=0;i<V.size(); i++){
        if(V[i]->label == label){
            return V[i];
        }
    }
    return NULL;
}
string SimpleGraph::getAdjList(){
    string alstr = "";
    for(int i=0;i<nv;i++){
        alstr = alstr + V[i]->label + ":";
        if(V[i]->outlist.size()>0){
            alstr = alstr + V[i]->outlist[0]->end->label;
            for(int j=1;j<V[i]->outlist.size();j++){
                alstr =alstr + ","+ V[i]->outlist[j]->end->label;
            }
        }
        alstr = alstr + "\n";
    }
    return alstr.substr(0, alstr.length()-1);
}
bool SimpleGraph::areAdjacent(Node *n1, Node*n2){
    for(int i=0;i<nv;i++){
        if(V[i]==n1){
            for(int j=0;j<V[i]->outlist.size();j++){
                if(V[i]->outlist[j]->end==n2){
                    return true;
                }
            }
        }
    }
    return false;
}
HalfEdge *SimpleGraph::getEdgeByNodes(Node*n1, Node*n2){
    for(int i=0;i<nv;i++){
        if(V[i]==n1){
            for(int j=0;j<V[i]->outlist.size();j++){
                if(V[i]->outlist[j]->end==n2){
                    return V[i]->outlist[j];
                }
            }
        }
    }
    return NULL;
}
SimpleGraph SimpleGraph::getInducedSubgraph(vector<Node*> vToExclude){
    SimpleGraph *subgraph = new SimpleGraph(this->getAdjList());
    for(int i=0;i<V.size();i++){
        for(int j=0;j<vToExclude.size();j++){
            if(V[i]==vToExclude[j]){
                subgraph->deleteNode(subgraph->V[i]);
            }
        }
    }
    return (*subgraph);
}
vector<vector<Node*>> SimpleGraph:: getCliques(){
    vector<vector<Node*>> cliques;
    int sumV = 0, i=0;
    while(sumV<nv){
        cliques.push_back({});
        SimpleGraph*bfstree = bfs(V[i],false);
        for(auto x:bfstree->V){
            cliques[cliques.size()-1].push_back(getNodeByLabel(x->label));
        }
        sumV+=bfstree->V.size();
        i = rand()%nv;
    }
    return cliques;
}

vector<Node*> SimpleGraph::getpathbetween(Node *n1, Node*n2, vector<Node*> toexclude){
    vector<Node*> path = {n1}, temp;
    bool found = false;
    for(int i=0;i<n1->outlist.size();i++){
        if(n1->outlist[i]->end==n2){
            found = true;
            path.push_back(n2);
        }
    }
    toexclude.push_back(n1);
    if(!found){
        for(int i=0;i<n1->outlist.size();i++){
            temp = path;
            if(contains<Node*>(toexclude, n1->outlist[i]->end)){
                continue;
            }
            else{
                temp = getpathbetween(n1->outlist[i]->end, n2, toexclude);
                if(temp[temp.size()-1]==n2){
                    for(int j=0;j<temp.size();j++){
                        path.push_back(temp[j]);
                    }
                    found = true;
                    break;
                }
            }
        }
    }
    if(!found){
        path = {};
    }
    return path;

}
vector<Node*> SimpleGraph::getshortestpathbetween(Node* n1, Node* n2){
    SimpleGraph*bfstree = bfs(n1);
    vector<Node*> sp = bfstree->getpathbetween(bfstree->getNodeByLabel(n1->label), bfstree->getNodeByLabel(n2->label), {});
    return sp;
}
int SimpleGraph::getDistanceBetween(Node *n1, Node *n2){
    return getshortestpathbetween(n1, n2).size();
}
SimpleGraph *SimpleGraph::bfs(Node *s, bool colornodes, vector<string> colorops){
    int colors[MAXV], dist[MAXV];
    for(int i=0;i<V.size();i++){
        colors[i] = 2;//white
        // cout<<i<<" ";
        if(colornodes){V[i]->color = colorops[2];}
    }
    queue<Node*> q;
    Node* u;
    SimpleGraph *bfstree = new SimpleGraph;
    int index=indexof(V,s), i_u;
    
    q.push(s);
    colors[index]=1;//gray
    if(colornodes){s->color = colorops[1];}
    dist[index] = 0;
    bfstree->addNode(s->label);
    bfstree->getNodeByLabel(s->label)->metadata = "L:"+to_string(dist[index]);
    while(!q.empty()){
        u = q.front(); q.pop();
        // cout<<u->label<<"\n";
        i_u = indexof(V,u);
        for(int i=0;i<u->outlist.size();i++){
            index = indexof(V,u->outlist[i]->end);
            if(colors[index]==2){
                bfstree->addBranch(bfstree->getNodeByLabel(u->label), {u->outlist[i]->end->label}, {});
                q.push(u->outlist[i]->end);
                colors[index]=1;
                if(colornodes){V[index]->color = colorops[1];u->outlist[i]->color = "green";u->outlist[i]->conjugate->color = "green"; }
                dist[index] = dist[i_u]+1;
            }
        }
        colors[i_u] = 0;//black
        if(colornodes){V[i_u]->color = colorops[0];}
        RENDER
        V[i_u]->metadata = "L:"+to_string(dist[i_u]);
        bfstree->getNodeByLabel(V[i_u]->label)->metadata = "L:"+to_string(dist[i_u]);
        bfstree->height = max(bfstree->height,dist[i_u]);
    }

    return bfstree;
}
SimpleGraph *SimpleGraph::dfs(Node *s, bool colornodes, vector<string> colorops){
    int colors[MAXV], arr[MAXV], dep[MAXV];
    int t = 0;
    for(int i=0;i<V.size();i++){
        arr[i] = -1;
        colors[i] = 2;
        if(colornodes){V[i]->color = colorops[2];}
    }
    stack<Node*> q;
    Node*u;
    SimpleGraph*dfstree = new SimpleGraph;
    int index = indexof(V,s), i_u;
    q.push(s);
    dfstree->addNode(s->label);
    if(colornodes){s->color = colorops[1];}
    bool newdepth = false;
    while(!q.empty()){
        u = q.top();
        i_u = indexof(V, u);
        colors[i_u]=1;
        if(colornodes){u->color = colorops[1];}
        RENDER
        if(arr[i_u]==-1){arr[i_u] = t;t++;}
        
        for(int i=0;i<u->outlist.size();i++){
            index = indexof(V, u->outlist[i]->end);
            if(colors[index]==2){
                dfstree->addBranch(dfstree->getNodeByLabel(u->label), {u->outlist[i]->end->label},{});
                u->outlist[i]->color = "green";u->outlist[i]->conjugate->color = "green";
                q.push(u->outlist[i]->end);
                newdepth = true;
                break;
            }
        }
        // cout<<newdepth;
        if(newdepth){newdepth = false; continue;}
        // cout<<u->label<<" "<<u->color<<"\n";
        colors[i_u] = 0;
        if(colornodes){u->color = colorops[0];}
        RENDER
        dep[i_u] = t;t++;
        u->metadata = u->metadata+"A:"+to_string(arr[i_u])+"; D:"+to_string(dep[i_u]);
        q.pop();
    }
    return dfstree;
}

void SimpleGraph::setCenter(int x, int y){
    center = {x, y};
}
void SimpleGraph::translate(int x, int y){
    for(int i=0;i<V.size();i++){
        V[i]->coords[0]+=x;V[i]->coords[1]+=y;
    }
    center[0] +=x;
    center[1] +=y;
}
void SimpleGraph::rotate(int angle_deg_anti){
    vector<int> ans;
    int dx, dy;
    for(int i=0;i<V.size();i++){
        dx =V[i]->coords[0]- center[0]; dy = V[i]->coords[1] - center[1];
        ans = rotateXY(dx,dy, angle_deg_anti);
        V[i]->coords={center[0] + ans[0],center[1]+ans[1]};
    }
}
void SimpleGraph::setRenderDelay(int delay){
    renderDelay = delay;
}
void SimpleGraph::setCanvasDimensions(int width, int height){
    canvasWidth = width;
    canvasHeight = height;
}
void SimpleGraph::assignCoords(int config, Node* bfsroot, bool overwrite){
    // cout<<"Hello?";
    int CW, CH, CCX, CCY;
    CW = canvasWidth; CH = canvasHeight; CCX = CW/2; CCY = CH/2;
    if(config==rc::RAND){
        if(overwrite){
            for(int i=0;i<V.size();i++){
                V[i]->coords = {int(CW*FOS)+rand()%(int(CW*(1-2*FOS))), int(CH*FOS)+rand()%(int(CH*(1-2*FOS)))};
            }
        }
        else{
            for(int i=0;i<V.size();i++){
                if(V[i]->coords[0]==0 && V[i]->coords[1]==0){
                    V[i]->coords = {int(CW*FOS)+rand()%(int(CW*(1-2*FOS))), int(CH*FOS)+rand()%(int(CH*(1-2*FOS)))};
                }
            }
        }

    }
    else if(config==rc::BFSFILL){
        int sepy=50;
        int mas = int((1-2*FOS)*CW);//max allowed spread;
        SimpleGraph *tr = bfs(bfsroot, false);
        bfsroot->coords = {CCX, sepy};
        int currh = 0, numnodes=0, y, htemp, sepx, xmin=0;
        sepy = CH/(tr->height);
        for(int i=0;i<tr->V.size();i++){
            numnodes++;
            htemp = heightFromMeta(tr->V[min(i+1, nv-1)]);
            if(htemp>currh || i==nv-1){
                y = max(sepy*currh, 50);
                sepx = int((1-2*FOS)*CW)/max(numnodes-1, 1);
                for(int j=i-numnodes+1;j<i+1;j++){
                    getNodeByLabel(tr->V[j]->label)->coords = {xmin + sepx*(j-(i-numnodes+1)), y};
                }
                numnodes=0;
                currh++;
            }

        }
    }
    else if(config==rc::BFSFILLBW){
        int sepy=50;
        int mas = int((1-2*FOS)*CW);//max allowed spread;
        SimpleGraph *tr = bfs(bfsroot, false);
        bfsroot->coords = {CCX, sepy};
        vector<int> bws;
        int currh = 0, numnodes=0, y, htemp, sepx, xmin=int(FOS*CW), totbws;
        sepy = CH/(tr->height);
        for(int i=0;i<tr->V.size();i++){
            numnodes++;
            htemp = heightFromMeta(tr->V[min(i+1, nv-1)]);
            if(htemp>currh || i==nv-1){
                xmin=int(FOS*CW);
                bws.clear();totbws = 0;
                y = max(sepy*currh, 20);
                for(int j=i-numnodes+1;j<i+1;j++){
                    bws.push_back(max(int(tr->V[j]->outlist.size()-1), 1));
                    totbws+=max(int(tr->V[j]->outlist.size()-1),1);
                }
                // totbws = max(1, totbws);
                xmin += mas*(bws[0])/(2.0*totbws); 
                if(bws.size()>0){
                    getNodeByLabel(tr->V[i-numnodes+1]->label)->coords = {xmin, y};
                }
                for(int j=i-numnodes+2;j<i+1;j++){
                    xmin+=(mas*((bws[j-i+numnodes-2]+bws[j-i+numnodes-1])/(2.0*totbws)));
                    getNodeByLabel(tr->V[j]->label)->coords = {xmin, y};
                }
                numnodes=0;
                currh++;
            }

        }
    }
    else if(config==rc::BFSBW){
        int sepy=20;
        int mas = int((1-2*FOS)*CW);//max allowed spread;
        SimpleGraph *tr = bfs(bfsroot, false);
        bfsroot->coords = {CCX, 20};
        spreadDFSBW(tr->V[0], mas, this, tr);
    }
    else if(config==rc::BFSSYM){
        int sepy=20;
        int mas = int((1-2*EXFOS)*CW);//max allowed spread;
        SimpleGraph *tr = bfs(bfsroot, false);
        bfsroot->coords = {CCX, 20};
        spreadDFS(tr->V[0], mas, this, tr);
    }
}

string SimpleGraph::serialize(string dtype){
    string temp, temp2;
    string data = "{ \"H\":";
    data = data + quotestring(ptrtostr(this->head)) + ",\n";
    data = data +"\"dtype\": " + quotestring(dtype) + ",\n";
    data = data + "\"V\": [\n";
    for(int i=0;i<nv-1;i++){
        temp = V[i]->lastSerialization;
        temp2 = V[i]->serialize();
        if(temp!=temp2){
            data = data + temp2 + ",\n";
        }
    }
    data = data + V[nv-1]->serialize() + "\n]\n";       
    data = data + "\n}";
    return data;
}
void SimpleGraph::appendRendData(string data){
    // cout<<"\n"<<data<<"\n";
    vector<vector<string>> strdata = parseLists(data, 3);
    vector<vector<int>> coords;
    // cout<<strdata.size();
    if(strdata.size()>0){
        for(auto x:strdata[0]){
            coords.push_back(toCoords(x));
        }
        // cout<<"Hi";
        for(int i=0;i<strdata[1].size();i++){
            for(int j=0;j<V.size();j++){
                if(quotestring(ptrtostr((void*)(V[j])))==strdata[1][i]){
                    V[j]->coords = coords[i];
                }
            }
        }
    }

}
void SimpleGraph::parseCommand(string cmd){
    if(cmd=="expjson"){
        ofstream outf;
        outf.open("export.json",ios::out);
        string output = serialize();
        outf.write(output.c_str(), output.length());
        outf.close();
        // cout<<"Exporting json";
    }
    else if(cmd=="expmintxt"){
        ofstream outf;
        outf.open("export.txt",ios::out);
        string output = getAdjList();
        outf.write(output.c_str(), output.length());
        outf.close();
    }
}

ServerSocket* SimpleGraph::initServer(int port, string host){
    #ifdef SERVERUSED
    server = new ServerSocket(port, host);
    // string portstr = to_string(port);
    system((" node .\\fabext\\thread1.js " + to_string(port)).c_str());
    server->listenForClient();
    server->sendDataARP("DIM:"+to_string(canvasWidth)+"x" + to_string(canvasHeight), *this);
    #endif
    return server;
    
}
ServerSocket* SimpleGraph::setAutoRender(bool state){
    #ifdef SERVERUSED
    if(server!=NULL){
        autorender = true;
    }
    else{
        cout<<"E: AutoRender can be enabled only after calling initServer(port, host)!\n";
    }
    #endif
    return server;
    
}
void SimpleGraph::syncGraph(bool pausemain){
    // cout<<"Called123";
    #ifdef SERVERUSED
    // cout<<SERVERUSED<<" ";
    if(server!=NULL){
        assignCoords(rc::RAND, V[0], false);//root is irrelevant in rc::rand
        //assign coordinates to any node without
        if(pausemain){
            // cout<<"Gonna send msgs";
            //subscript with zero to allow broken transmission
            // cout<<server<<"\n";
            server->sendDataARP(this->serialize()+"0", *this);
            // cout<<"awaiting";
        }
        else{
            server->sendData(this->serialize() +"0");
            server->awaitSignal();
            Sleep(renderDelay);
        }
    }
    else{
        cout<<"E: You need to call initServer(port, host) before sync!\n";
    }
    #endif
}
