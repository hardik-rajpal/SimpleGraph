#include<bits/stdc++.h>
#define MAXV 100
#define MAXE 4950 //100C2
using namespace std;
class Node{
    string label;
    int coords[2];//coordinates for animation program;
    int weight;//equivalent to radius for animation program;
    string colour;
};
class Edge{
    bool directed;
    Node* n1;
    Node* n2;
    int weight;
    string label;
};
class SimpleGraph{
    int nv, ne;//number of vertices and edges
    string cmds;//string holding list of commands executed on Simplegraph.
    //These commands can be interpreted by the animation program.
    vector<Node> V;//Vector of vertices.
    vector<Edge> E;//vector of edges.
    Node* head;//pointer to head for animation purposes

    //constructors
    SimpleGraph(int _nv, int _ne);//constructor with number of vertices, number of edges
    SimpleGraph(int adjmat[10][10]);//constructor using adjacency matrix.
    SimpleGraph(string adjlist);//constructor using adjlist in string.
    SimpleGraph(string notation, bool usenotation);//constructor using mathematical notation.
    
    //search methods.
    SimpleGraph bfs(Node *s);//return a bfs tree
    SimpleGraph dfs(Node *s);//return a dfs tree
    vector<Node*> generalSearch(Node *s, function<Node(vector<Node>)> selector);//return a vector of nodes
    
    //subgraphs.
    SimpleGraph getInducedSubgraph(Node *vToExclude[]);//return induced subgraphs by deleteing given vertices.
    vector<SimpleGraph> getConnectedComponents();//return connected components

    //Edit graph
    Node *addBranch(Node* root, string vlabels[], string elabels);//add a series of nodes at root.
    int addEdgesByRelation(function<bool(string, string)> relation);//check each pair of nodes for relation between labels and add edge if true.
    Edge *connectNodes(Node*n1, Node*n2, bool directed=false);//connect nodes.
    bool deleteNode(Node *n1);
    bool deleteEdge(Edge *e);


    //getters.
    Node *getNodeByLabel(string label);
    bool areConnected(Node*n1, Node*n2);
    vector<Node> getpathbetween(Node *n1, Node*n2);
    int getdistanceBetween(Node *n1, Node *n2);
    Edge *getEdgeByNodes(Node*n1, Node*n2);
    
    //export all edit graph operations for animation program.
    string exportCmds();
};