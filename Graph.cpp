#include<bits/stdc++.h>
#include"Graph.h"
#include"config.h"
using namespace std;

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
    datastr[0] = datastr[0].substr(1, datastr[0].length()-2);
    lists.push_back(split(datastr[0], "},{"));
    // lists.push_back({datastr[0]});
    for(int i=1;i<datastr.size();i++){
        vector<string> list = split(datastr[i], ",");
        lists.push_back(list);
    }
    return lists;
}
Node* SimpleGraph::addNode(string label){
    Node *n;
    n = new Node(label);
    V.push_back(n);
    nv++;
    if(autorender){
        syncGraph();
    }
    return V[V.size()-1];
}
SimpleGraph::SimpleGraph(){};
SimpleGraph::SimpleGraph(vector<string> labels){
    for(int i=0;i<labels.size();i++){
        addNode(labels[i]);
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
//Uncompleted method.
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
        // cout<<"***";
        // for(auto x:neighlabels){
        //     cout<<":"<<x<<":";
        // }
        // cout<<"***\n";
        for(int i=0;i<neighlabels.size();i++){
            connectNodes(currNode, getNodeByLabel(neighlabels[i]));
        }
    }

}
Node* SimpleGraph::getNodeByLabel(string label){
    for(int i=0;i<V.size(); i++){
        if(V[i]->label == label){
            return V[i];
        }
    }
    return NULL;
}


int SimpleGraph::addEdgesByRelation(function<bool(string, string)> relation){
    for(int i=0;i<V.size();i++){
        for(int j=0;j<i;j++){
            if(relation(V[i]->label, V[j]->label)){
                connectNodes(V[i], V[j]);
            }
        }
    }
    return ne;
}
string SimpleGraph::getAdjList(){
    string alstr = "";
    // cout<<V.size()<<"\n";
    // for(int i=0;i<V.size();i++){
    //     cout<<V[i]->adjlist.size()<<" ";
    // }
    // cout<<"\n";
    
    
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
bool SimpleGraph::areConnected(Node *n1, Node*n2){
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
HalfEdge *SimpleGraph::connectNodes(Node*n1, Node*n2){
    if(n1==n2){return NULL;}
    if(areConnected(n1, n2)){
        // cout<<"W:Attempted to connect adjacent nodes!\n";
        return NULL;
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
    return e1;
}
Node *SimpleGraph::addBranch(Node *root, vector<string> vlabels, vector<string> elabels){
    Node *n2;
    // cout<<root->label<<"\n";
    if(elabels.size()==0){
        for(int i=0;i<vlabels.size();i++){
            // cout<<i<<"\n";
            // cout<<root<<"\n";
            n2 = addNode(vlabels[i]);
            // cout<<root<<"\n";
            // cout<<"Label assigned: "<<n2->label<<".\n";
            connectNodes(root, n2);
            root = n2;
            // cout<<root->label<<"\n";
            // cout<<"done\n";
        }
    }
    return root;
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
SimpleGraph SimpleGraph::getInducedSubgraph(vector<Node*> vToExclude){
    SimpleGraph *subgraph = new SimpleGraph(this->getAdjList());string lab;
    // cout<<subgraph->getAdjList();
    for(int i=0;i<vToExclude.size();i++){
        lab = vToExclude[i]->label;
        cout<<this->getNodeByLabel(lab)<<" "<<subgraph->getNodeByLabel(lab)<<"\n";
    }
    for(int i=0;i<V.size();i++){
        for(int j=0;j<vToExclude.size();j++){
            if(V[i]==vToExclude[j]){
                subgraph->deleteNode(subgraph->V[i]);
            }
        }
    }

    cout<<subgraph->V.size()<<" "<<this->V.size()<<"\n";
    return (*subgraph);
}

//recursize serialize function

string SimpleGraph::serialize(){
    string temp;
    ostringstream ss;
    ss<<(this->head);
    temp = ss.str();

    string data = "{ \"H\":";
    data = data + quotestring(temp) + ",\n";
    data = data + "\"V\": [\n";
    for(int i=0;i<nv-1;i++){
        data = data + V[i]->serialize() + ",\n";       
    }
    data = data + V[nv-1]->serialize() + "\n]\n";       
    data = data + "\n}";
    return data;
}
string quotestring(string tbq){
    return "\""+tbq+"\"";
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
        
        return data;
    }
void SimpleGraph::takeShot(){
    snapshots = snapshots+this->serialize() + ",";
};
string SimpleGraph::exportShots(){
    return snapshots.substr(0, snapshots.length()-1) + "\n]";
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
void SimpleGraph::appendRendData(string data){
    cout<<"\n"<<data<<"\n";
    vector<vector<string>> strdata = parseLists(data, 3);
    vector<vector<int>> coords;
    cout<<strdata.size();
    for(auto x:strdata[0]){
        coords.push_back(toCoords(x));
    }
    cout<<"Hi";
    for(int i=0;i<strdata[1].size();i++){
        for(int j=0;j<V.size();j++){
            if(quotestring(ptrtostr((void*)(V[j])))==strdata[1][i]){
                V[j]->coords[0] = coords[i][0];
                V[j]->coords[1] = coords[i][1];
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
int SimpleGraph::getdistanceBetween(Node *n1, Node *n2){
    return getshortestpathbetween(n1, n2).size();
}

SimpleGraph *SimpleGraph::bfs(Node *s, bool colornodes, vector<string> colorops){
    int colors[MAXV], dist[MAXV];
    for(int i=0;i<V.size();i++){
        colors[i] = 2;//white
        if(colornodes){V[i]->color = colorops[2];}
    }
    queue<Node*> q;
    Node* u;
    SimpleGraph *bfstree = new SimpleGraph;
    int index=indexof(V,s), i_u;
    q.push(s);
    bfstree->addNode(s->label);
    colors[index]=1;//gray
    if(colornodes){s->color = colorops[1];}
    dist[index] = 0;
    while(!q.empty()){
        u = q.front(); q.pop();
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
        if(autorender){
            syncGraph();
        }
    }
    return bfstree;
}
//Assigns new ServerSocket objecto to this->server, listens for the renderer application,
//returns server ptr
void SimpleGraph::syncGraph(bool pausemain){
    cout<<"Called";
    #ifdef SERVERUSED
    // cout<<SERVERUSED<<" ";
    if(server!=NULL){
        if(pausemain){
            server->sendDataARP(this->serialize(), *this);
        }
        else{
            server->sendData(this->serialize());
            this->appendRendData(server->awaitSignal());
        }
    }
    else{
        cout<<"You need to call initServer(port, host) before sync!\n";
    }
    #endif
}
#ifdef SERVERUSED
ServerSocket* SimpleGraph::initServer(int port, string host){
    server = new ServerSocket(port, host);
    server->listenForClient();
    return server;
}
ServerSocket* SimpleGraph::setAutoRender(bool state){
    if(server!=NULL){
        autorender = true;
    }
    else{
        cout<<"AutoRender can be enabled only after calling initServer(port, host)!\n";
    }
    return server;

}
#endif