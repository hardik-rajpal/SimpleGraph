#include<bits/stdc++.h>
#include"Graph.h"
using namespace std;
vector<string> split(string str, string sep){
    vector<string> parts;
    int j = 0;
    for(int i=0;i<str.length();i++){
        if(str.length()-1-i<sep.length()){break;}
        if(str.substr(i, sep.length())==sep){
            // cout<<str.substr(j, i-j)<<" ";
            parts.push_back(str.substr(j, i-j));
            j = i+1;
        }
    }
    parts.push_back(str.substr(j,str.length()-j));
    return parts;
}
Node* SimpleGraph::addNode(string label){
    Node *n;
    n = new Node(label);
    V.push_back(n);
    nv++;
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
        if(V[i]->adjlist.size()>0){
            alstr = alstr + V[i]->adjlist[0]->label;
            for(int j=1;j<V[i]->adjlist.size();j++){
                alstr =alstr + ","+ V[i]->adjlist[j]->label;
            }
        }
        alstr = alstr + "\n";
    }
    return alstr.substr(0, alstr.length()-1);
}
bool SimpleGraph::areConnected(Node *n1, Node*n2){
    for(int i=0;i<nv;i++){
        if(V[i]==n1){
            for(int j=0;j<V[i]->adjlist.size();j++){
                if(V[i]->adjlist[j]==n2){
                    return true;
                }
            }
        }
    }
    return false;
}
Edge *SimpleGraph::connectNodes(Node*n1, Node*n2){
    if(n1==n2){return NULL;}
    if(areConnected(n1, n2)){
        // cout<<"W:Attempted to connect adjacent nodes!\n";
        return NULL;
    }
    Edge *e = new Edge(n1, n2);
    E.push_back(e);
    ne++;
    for(int i=0;i<nv;i++){
        if(V[i]==n1){
            V[i]->adjlist.push_back(n2);
        }
        if(V[i]==n2){
            V[i]->adjlist.push_back(n1);
        }
    }
    return E[E.size()-1];
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
            for(int j=0;j<V[i]->adjlist.size();j++){
                if(V[i]->adjlist[j]==n1){
                    int sz = V[i]->adjlist.size();
                    V[i]->adjlist[j]=V[i]->adjlist[sz-1];
                    V[i]->adjlist.pop_back();
                }
            }
        }
    }
    nv--;
    int etrm = 0;
    for(int i=0;i<ne;i++){
        if(E[i]->n1 == n1 || E[i]->n2 ==n1){
            E[i] = E[E.size()-1];
            E.pop_back();
            etrm++;
        }
    }
    ne = ne - etrm;
    if(!deleted){
        cout<<"W:Node to be removed NOT FOUND!";
    }
    return deleted;
}
Edge *SimpleGraph::getEdgeByNodes(Node*n1, Node*n2){
    for(int i=0;i<E.size();i++){
        if((E[i]->n1==n1 && E[i]->n2==n2)||(E[i]->n1==n2 && E[i]->n2==n1)){
            return E[i];
        }
    }
    return NULL;
}
bool SimpleGraph::disconnectNodes(Node *n1, Node*n2){
    bool deleted = false;
    for(int i=0;i<E.size();i++){
        if((E[i]->n1==n1 && E[i]->n2==n2)||(E[i]->n1==n2 && E[i]->n2==n1)){
            E[i] = E[E.size()-1];
            E.pop_back();
            deleted = true;
            break;
        }
    }
    ne--;

    for(int i=0;i<n1->adjlist.size();i++){
        if(n1->adjlist[i]==n2){
            n1->adjlist[i] = n1->adjlist[n1->adjlist.size()-1];
            n1->adjlist.pop_back();
            break;
        }   
    }
    for(int i=0;i<n2->adjlist.size();i++){
        if(n2->adjlist[i]==n1){
            n2->adjlist[i] = n2->adjlist[n2->adjlist.size()-1];
            n2->adjlist.pop_back();
            break;
        }   
    }
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
    data = data + V[nv-1]->serialize() + "\n]";       
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
        data = data + quotestring("adjlist") + " : [\n";
        int deg = adjlist.size();
        for(int i=0;i<deg-1;i++){
            ostringstream ss;
            ss<<(this->adjlist[i]);
            temp = ss.str();
            data = data + quotestring(temp) + ",\n";
        }
        if(deg>1){
        ostringstream tss;
        tss<<(this->adjlist[deg-1]);
        temp = tss.str();
        data = data + quotestring(temp);

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