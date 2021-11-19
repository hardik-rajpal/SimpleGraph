#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>
#include <winsock2.h>
#include <stdio.h>
#include"Server.h"
#define MAXV 1000
#define MAXE 499500 //1000C2
using namespace std;

// classes
class Node;
class HalfEdge;
class SimpleGraph;


//auxiliary functions.
string ptrtostr(void* ptr);
string quotestring(string tbq);
vector<string> split(string str, string sep);
vector<vector<string>> parseLists(string data, int level);
vector<int> toCoords(string kvpair);
vector<int> rotateXY(int x, int y, int ang_deg_anti);
template<class T>
bool contains(vector<T> list, T item);
template<class T>
int indexof(vector<T> list, T item);
void getCycle(vector<int> vals, SimpleGraph *g);
void getComplete(vector<int> vals, SimpleGraph *g);
void getCompleteBipartite(vector<int> vals, SimpleGraph *g);
void getWheel(vector<int> vals, SimpleGraph *g);
void getStar(vector<int> vals, SimpleGraph *g);
void getPath(vector<int> vals, SimpleGraph *g);
void getCircularLadder(vector<int> vals, SimpleGraph *g);
int heightFromMeta(Node *n);
int maxBranchWidth(Node *n);
bool heightis(Node *n, int h);
void spreadDFSBW(Node *v, int spread, SimpleGraph *main, SimpleGraph *bfstree);
void spreadDFS(Node *v, int spread, SimpleGraph *main, SimpleGraph *bfstree);
/*Integrate an object of this into SimpleGraph*/



class Node{
    public:
    string label="";
    string metadata="";
    string lastSerialization = "";
    vector<int> coords = {0, 0};//coordinates for animation program;
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
    //These commands can be interpreted by the animation program.
    vector<Node*> V={};//Vector of vertices.
    Node* head = NULL;//pointer to head for animation purposes
    static const map<string,function<void(vector<int>, SimpleGraph*)>> makers;
    static const map<string, int> validvals;
    //Renderer integration
    bool autorender=false, setCoords = false;
    int renderDelay = 0;
    enum rc{BFSFILL, RAND, BFSBW, BFSFILLBW};
    vector<int> center = {200, 200};
    int height=0;
    int canvasWidth = 700;
    int canvasHeight = 650;
    ServerSocket *server = NULL;
    
    
    //constructors
    /*✅*/SimpleGraph();
    /*✅*/SimpleGraph(vector<string> labels);//constructor with number of vertices
    /*✅*/SimpleGraph(bool adjmat[MAXV][MAXV], vector<string> labels);//constructor using adjacency matrix.
    /*✅*/SimpleGraph(string adjlist);//constructor using adjlist in string.
    /*✅*/SimpleGraph(string graphsymbol, vector<int> vals);//constructor using mathematical notation.
    
    /*✅*/Node* addNode(string label);
    /*✅*/Node* addNode(string label, vector<int> coords, int weight, string color);
    /*✅*/bool deleteNode(Node *n1);

    /*✅*/HalfEdge *connectNodes(Node*n1, Node*n2);//connect nodes.
    /*✅*/HalfEdge *connectNodes(string l1, string l2);//connect nodes.
    /*✅*/int addEdgesByRelation(function<bool(string, string)> relation);//check each pair of nodes for relation between labels and add edge if true.
    /*✅*/Node *addBranch(Node* root, vector<string> vlabels, vector<string> elabels);//add a series of nodes at root.
    /*✅*/void addGraph(SimpleGraph *myg, string labelprefix="",string labelsuffix="",bool duplicate=false);
    /*✅*/bool disconnectNodes(Node *n1, Node*n2);


    //getters.
    /*✅*/string getAdjList();
    /*✅*/Node *getNodeByLabel(string label);
    template<typename T>
    /*✅*/vector<Node*>getNodesIf(function<bool(Node*, T)> predicate, T t);
    /*✅*/bool areAdjacent(Node*n1, Node*n2);
    /*✅*/HalfEdge *getEdgeByNodes(Node*n1, Node*n2);
    //subgraphs.
    /*✅*/SimpleGraph getInducedSubgraph(vector<Node*> vToExclude);//return induced subgraphs by deleteing given vertices.
    /*✅*/vector<vector<Node*>> getCliques();//return connected components
    
    //distance and path functions
    /*✅*/vector<Node*> getpathbetween(Node *n1, Node*n2, vector<Node*> toexclude);
    /*✅*/vector<Node*> getshortestpathbetween(Node *n1, Node*n2);
    /*✅*/int getDistanceBetween(Node *n1, Node *n2);
    //search methods.
    /*✅*/SimpleGraph *bfs(Node *s, bool colornodes=false, vector<string> colorops={"green", "blue", "white"});//return a bfs tree
    /*✅*/SimpleGraph *dfs(Node *s, bool colournodes=false, vector<string> colorops={"green", "blue", "white"});//return a dfs tree

    /*✅*/template<class T>
    void assignVertices(vector<T> vertices, function<string(T)> labelmaker);
    /*✅*/template<class T>
    void extractGraph(T graphobj, function<vector<Node*>(T)> nodemaker);

    //canvas/geometry related methods
    /*✅*/void setCenter(int x, int y);
    /*✅*/void translate(int x, int y);
    /*✅*/void rotate(int angle_anticlockwise);
    /*✅*/void setCanvasDimensions(int width=700, int height=650);
    /*✅*/void assignCoords(int CONFIG, Node* bfsroot, bool overwrite=true);
    /*✅*/void setRenderDelay(int delay);
    
    //methods to serialize/parse data
    /*✅*/string serialize();
    /*✅*/void appendRendData(string data);
    /*✅*/void parseCommand(string cmd);
    
    //methods to connect to/sync with renderer
    /*✅*/ServerSocket* initServer(int port=7171, string host="127.0.0.1");
    /*✅*/ServerSocket* setAutoRender(bool state);
    /*✅*/void syncGraph(bool pausemain=false);

};

#include"Graph.tpp"
#endif
