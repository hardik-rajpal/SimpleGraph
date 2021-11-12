/*

2. Implement cpp functionality completely.

3. Style mainWindow.html up.

4. Maybe go cross platform?
*/
#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>
#include <winsock2.h>
#include <stdio.h>
#include"Server.h"

#define MAXV 100
#define MAXE 4950 //100C2
#define literal(expr) #expr
#define SERVERUSED
#undef SERVERUSED
using namespace std;
//auxiliary functions.
string ptrtostr(void* ptr);
string quotestring(string tbq);
vector<string> split(string str, string sep);
vector<vector<string>> parseLists(string data, int level);
vector<int> toCoords(string kvpair);
template<class T>
bool contains(vector<T> list, T item);
template<class T>
int indexof(vector<T> list, T item);



/*Integrate an object of this into SimpleGraph*/


class HalfEdge;
class Node{
    public:
    string label="";
    string metadata="";
    int coords[2]={0, 0};//coordinates for animation program;
    int weight=1;//equivalent to radius for animation program;
    string color="cyan";
    // vector<Neighbour> adjlist2= {};
    vector<HalfEdge*> inlist = {};
    //use outlist for simplegraph
    vector<HalfEdge*> outlist = {};
    Node(string _label){
        this->label = _label;
    }
    string serialize();
};
class Edge{
    public:
    Node* n1;
    Node* n2;
    int weight;
    string label;
    string color;
    Edge(Node *_n1, Node *_n2){
        n1 = _n1; n2 = _n2;
    }
    string serialize();
};
class HalfEdge{
    public:
    Node* end;
    int weight;
    string label;
    string color;
    HalfEdge* conjugate = NULL;
    HalfEdge(Node *_end){
        end = _end;
    }
    string serialize();
};


class SimpleGraph{
    public:
    //undirected, uniweight graph, with no self loops
    int nv=0, ne=0;//number of vertices and edges
    string snapshots="[ \n";//string holding list of commands executed on Simplegraph.
    //These commands can be interpreted by the animation program.
    vector<Node*> V={};//Vector of vertices.
    Node* head = NULL;//pointer to head for animation purposes
    static const map<string,function<void(vector<int>, SimpleGraph*)>> makers;
    static const map<string, int> validvals;
    //Renderer integration
    bool autorender=false;
    int renderDelay = 0;
    vector<int> center = {200, 200};
    ServerSocket *server = NULL;
    
    
    //constructors
    /*✅*/SimpleGraph();
    /*✅*/SimpleGraph(vector<string> labels);//constructor with number of vertices
    /*✅*/SimpleGraph(bool adjmat[MAXV][MAXV], vector<string> labels);//constructor using adjacency matrix.
    /*✅*/SimpleGraph(string adjlist);//constructor using adjlist in string.
    /*✅*/SimpleGraph(string graphsymbol, vector<int> vals);//constructor using mathematical notation.
    
    /*✅*/ServerSocket* initServer(int port=7171, string host="127.0.0.1");
    /*✅*/ServerSocket* setAutoRender(bool state);
    /*✅*/void setRenderDelay(int delay);
    /*✅*/void syncGraph(bool pausemain=false);
    
    //search methods.
    /*✅*/SimpleGraph *bfs(Node *s, bool colornodes=false, vector<string> colorops={"green", "blue", "white"});//return a bfs tree
    /*✅*/SimpleGraph *dfs(Node *s, bool colournodes=false, vector<string> colorops={"green", "blue", "white"});//return a dfs tree
    
    //subgraphs.
    /*✅*/SimpleGraph getInducedSubgraph(vector<Node*> vToExclude);//return induced subgraphs by deleteing given vertices.
    /*✅*/vector<vector<Node*>> getCliques();//return connected components

    //Edit graph
    /*✅*/template<class T>
    void assignVertices(vector<T> vertices, function<string(T)> labelmaker);
    template<class T>
    void extractGraph(T graphobj, function<vector<Node*>(T)> nodemaker);
    //add overload with addBranchby label
    //assumes root is a valid pointer in the graph.
    /*✅*/Node *addBranch(Node* root, vector<string> vlabels, vector<string> elabels);//add a series of nodes at root.
    /*✅*/int addEdgesByRelation(function<bool(string, string)> relation);//check each pair of nodes for relation between labels and add edge if true.
    /*✅*/HalfEdge *connectNodes(Node*n1, Node*n2);//connect nodes.
    /*✅*/bool deleteNode(Node *n1);
    /*✅*/bool disconnectNodes(Node *n1, Node*n2);
    /*✅*/Node* addNode(string label);
    /*✅*/Node* addNode(string label, vector<int> coords, int weight, string color);
    void addGraph(SimpleGraph *myg, string labelprefix="",string labelsuffix="",bool duplicate=false);
    //getters.
    /*✅*/string getAdjList();
    /*✅*/Node *getNodeByLabel(string label);
    /*✅*/bool areConnected(Node*n1, Node*n2);
    /*✅*/HalfEdge *getEdgeByNodes(Node*n1, Node*n2);
    /*✅*/vector<Node*> getpathbetween(Node *n1, Node*n2, vector<Node*> toexclude);
    /*✅*/vector<Node*> getshortestpathbetween(Node *n1, Node*n2);
    /*✅*/int getdistanceBetween(Node *n1, Node *n2);
    
    void setCenter(int x, int y);
    void translate(int x, int y);
    void rotate(int angle_anticlockwise);

    //export all edit graph operations for animation program.
    /*✅*/string exportShots();
    /*✅*/string serialize();
    /*✅*/void takeShot();
    /*✅*/void appendRendData(string data);
    /*✅*/void parseCommand(string cmd);
};

#include"Graph.tpp"
#endif
