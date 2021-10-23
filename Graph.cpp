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
    Node n(label);
    V.push_back(n);
    nv++;
    vector<Node*> list = {};
    adjlist.push_back(list);
    return &V[V.size()-1];
}
SimpleGraph::SimpleGraph(){};
SimpleGraph::SimpleGraph(vector<string> labels){
    for(int i=0;i<labels.size();i++){
        addNode(labels[i]);
    }
    head = &V[0];
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
                connectNodes(&V[i], &V[j]);
            }
        }
    }
    head = &V[0];
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
        if(V[i].label == label){
            return &V[i];
        }
    }
    return NULL;
}


int SimpleGraph::addEdgesByRelation(function<bool(string, string)> relation){
    for(int i=0;i<V.size();i++){
        for(int j=0;j<i;j++){
            if(relation(V[i].label, V[j].label)){
                connectNodes(&V[i], &V[j]);
            }
        }
    }
    return ne;
}
string SimpleGraph::getAdjList(){
    string alstr = "";
    // for (auto x:adjlist){
    //     cout<<x[0]->label<<" ";
    // }
    for(int i=0;i<nv;i++){
        // cout<<i<<": "<<adjlist[i].size()<<"\n";
        alstr = alstr + V[i].label + ":";
        alstr = alstr + adjlist[i][0]->label;
        for(int j=1;j<adjlist[i].size();j++){
            alstr =alstr + ","+ adjlist[i][j]->label;
        }
        alstr = alstr + "\n";
    }
    return alstr;
}
bool SimpleGraph::areConnected(Node *n1, Node*n2){
    for(int i=0;i<nv;i++){
        if(&V[i]==n1){
            for(int j=0;j<adjlist[i].size();j++){
                if(adjlist[i][j]==n2){
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
    
    E.push_back(Edge(n1, n2));
    ne++;
    for(int i=0;i<nv;i++){
        if(&V[i]==n1){
            adjlist[i].push_back(n2);
        }
        if(&V[i]==n2){
            adjlist[i].push_back(n1);
        }
    }
    return &E[E.size()-1];
}
Node *SimpleGraph::addBranch(Node *root, vector<string> vlabels, vector<string> elabels){
    Node *n2;
    // cout<<root->label<<"\n";
    if(elabels.size()==0){
        for(int i=0;i<vlabels.size();i++){
            // cout<<i<<"\n";
            cout<<root<<"\n";
            n2 = addNode(vlabels[i]);
            cout<<root<<"\n";
            cout<<"Label assigned: "<<n2->label<<".\n";
                for(auto x:adjlist){
                    cout<<x.size()<<":";
                    for(auto y: x){
                        cout<<y->label<<" ";
                    }
                }cout<<"\n";
            connectNodes(root, n2);
            root = n2;
            cout<<root->label<<"\n";
            // cout<<"done\n";
        }
    }
    // for(auto x:V){
    //     cout<<x.label<<"\n";
    // }
    for(auto x:adjlist){
        cout<<x.size()<<":";
        for(auto y: x){
            cout<<y->label<<" ";
        }
    }
    return root;
}