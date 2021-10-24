#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>
#define MAXV 100
#define MAXE 4950 //100C2
using namespace std;
vector<string> split(string str, string sep);
class Node{
    public:
    string label;
    int coords[2];//coordinates for animation program;
    int weight;//equivalent to radius for animation program;
    string colour;
    vector<Node*> adjlist = {};
    Node(string _label){
        this->label = _label;
    }
};
class Edge{
    public:
    Node* n1;
    Node* n2;
    int weight;
    string label;
    Edge(Node *_n1, Node *_n2){
        n1 = _n1; n2 = _n2;
    }
};
class SimpleGraph{
    public:
    //undirected, uniweight graph, with no self loops
    int nv=0, ne=0;//number of vertices and edges
    string cmds="";//string holding list of commands executed on Simplegraph.
    //These commands can be interpreted by the animation program.
    vector<Node*> V={};//Vector of vertices.
    vector<Edge*> E={};//vector of edges.
    Node* head = NULL;//pointer to head for animation purposes

    //constructors
    /*✅*/SimpleGraph();
    /*✅*/SimpleGraph(vector<string> labels);//constructor with number of vertices
    /*✅*/SimpleGraph(bool adjmat[MAXV][MAXV], vector<string> labels);//constructor using adjacency matrix.
    /*✅*/SimpleGraph(string adjlist);//constructor using adjlist in string.
    SimpleGraph(string notation, bool usenotation);//constructor using mathematical notation.
    //search methods.
    SimpleGraph bfs(Node *s);//return a bfs tree
    SimpleGraph dfs(Node *s);//return a dfs tree
    vector<Node*> generalSearch(Node *s, function<Node(vector<Node>)> selector);//return a vector of nodes
    
    //subgraphs.
    /*✅*/SimpleGraph getInducedSubgraph(vector<Node*> vToExclude);//return induced subgraphs by deleteing given vertices.
    vector<SimpleGraph> getConnectedComponents();//return connected components

    //Edit graph
    /*✅*/template<class T>
    void assignVertices(vector<T> vertices, function<string(T)> labelmaker);
    //add overload with addBranchby label
    //assumes root is a valid pointer in the graph.
    /*✅*/Node *addBranch(Node* root, vector<string> vlabels, vector<string> elabels);//add a series of nodes at root.
    /*✅*/int addEdgesByRelation(function<bool(string, string)> relation);//check each pair of nodes for relation between labels and add edge if true.
    /*✅*/Edge *connectNodes(Node*n1, Node*n2);//connect nodes.
    /*✅*/bool deleteNode(Node *n1);
    /*✅*/bool disconnectNodes(Node *n1, Node*n2);
    /*✅*/Node* addNode(string label);

    //getters.
    /*✅*/string getAdjList();
    /*✅*/Node *getNodeByLabel(string label);
    /*✅*/bool areConnected(Node*n1, Node*n2);
    vector<Node*> getpathbetween(Node *n1, Node*n2);
    int getdistanceBetween(Node *n1, Node *n2);
    /*✅*/Edge *getEdgeByNodes(Node*n1, Node*n2);
    
    //export all edit graph operations for animation program.
    string exportCmds();
};
#include"Graph.tpp"
#endif
