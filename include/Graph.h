#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>
#include <winsock2.h>
#include <stdio.h>
#include"Server.h"
#define MAXV 1000
#define MAXE 499500 //1000C2
#define FOS 0.05 //factor of safety
#define EXFOS 0.1 //extra factor of safety
#define DEG2RAD 3.1415/180
using namespace std;

//Forward declaration of classes
class Node;
class HalfEdge;
class SimpleGraph;


//auxiliary functions.
string ptrtostr(void* ptr);//returns string containing address of given pointer ptr
string quotestring(string tbq);//adds \" marks around the string and returns it.
vector<string> split(string str, string sep);//splits a string str by sep and returns parts in vector
vector<vector<string>> parseLists(string data, int level);//function to parse data received from renderer
vector<int> toCoords(string kvpair);//function to convert string of data from renderer to coordinate pair
vector<int> rotateXY(int x, int y, int ang_deg_anti);//function to rotate given coordinate by an angle, in degrees, anticlockwise
template<class T>
bool contains(vector<T> list, T item);//function to check if list contains item
template<class T>
int indexof(vector<T> list, T item);//get first index of item present in list, -1 if absent
void getCycle(vector<int> vals, SimpleGraph *g);//add a cycle of points to graph object.
//vals are parameters for the cycle, like radius and number of points
void getComplete(vector<int> vals, SimpleGraph *g);//add a complete graph.
void getCompleteBipartite(vector<int> vals, SimpleGraph *g);//add a complete bipartite graph.
void getWheel(vector<int> vals, SimpleGraph *g);//add a wheel graph
void getStar(vector<int> vals, SimpleGraph *g);//add a star
void getPath(vector<int> vals, SimpleGraph *g);//add a path, at an angle, separation and number of points
void getCircularLadder(vector<int> vals, SimpleGraph *g);//add a circular ladder
int heightFromMeta(Node *n);//get the height of a node from its metadata (updated during bfs)
int maxBranchWidth(Node *n);//get maximum number of grandkids in a node's family
bool heightis(Node *n, int h);//check if Node n has heigh h
void spreadDFSBW(Node *v, int spread, SimpleGraph *main, SimpleGraph *bfstree);//rendering algorithm. BW = branch width
void spreadDFS(Node *v, int spread, SimpleGraph *main, SimpleGraph *bfstree);//rendering algorithm




class Node{
    public:
    string label="";//readable identifier
    string metadata="";//data like height in a bfstree, arrival/departure times
    string lastSerialization = "";//last serialization data, to avoid repeating the transfer
    vector<int> coords = {0, 0};//coordinates for animation program;
    int weight=1;//integer data 
    string color="cyan";//categorical data
    vector<HalfEdge*> inlist = {};//adjacency list of edges directed inwards
    //use outlist for simplegraph
    vector<HalfEdge*> outlist = {};//adjacency list of edges directed outwards
    Node(string _label){
        this->label = _label;
    }
    string serialize();//serializer
};

class HalfEdge{
    public:
    Node* end;//end of the arrow. The other end is what points to the edge.
    int weight;//integer data
    string label;
    string color;
    HalfEdge* conjugate = NULL;//pointer to edge from end to start
    HalfEdge(Node *_end){
        end = _end;
    }
    string serialize();//serializer
};


class SimpleGraph{
    public:
    //undirected, uniweight graph, with no self loops
    int nv=0, ne=0;//number of vertices and edges
    //These commands can be interpreted by the animation program.
    vector<Node*> V={};//Vector of vertex pointers.
    Node* head = NULL;//pointer to head for animation purposes
    static const map<string,function<void(vector<int>, SimpleGraph*)>> makers;//templates
    static const map<string, int> validvals;//valid number of arguments to templates
    bool autorender=false;//autorender to render each step or not. 
    int renderDelay = 0;//delay before sending render commands
    enum rc{BFSFILL, RAND, BFSBW, BFSFILLBW, BFSSYM};//rendering algorithms
    vector<int> center = {200, 200};//center of graph about which rotations happen
    int height=0;//set if object is a bfstree
    int canvasWidth = 700;
    int canvasHeight = 650;
    ServerSocket *server = NULL;//server to communicate with renderer
    
    
    //constructors
    /*✅*/SimpleGraph();//default
    /*✅*/SimpleGraph(vector<string> labels);//add vertices with list of labels
    /*✅*/SimpleGraph(bool adjmat[MAXV][MAXV], vector<string> labels);//list of labels and adjacency matrix.
    /*✅*/SimpleGraph(string adjlist);//constructor using adjlist in string format.
    /*✅*/SimpleGraph(string graphsymbol, vector<int> vals);//constructor using mathematical notation (template graphs).
    ~SimpleGraph();//destructor

    /*✅*/Node* addNode(string label);//add node with given label
    /*✅*/Node* addNode(string label, vector<int> coords, int weight, string color);//add node with these properties
    /*✅*/bool deleteNode(Node *n1);

    /*✅*/HalfEdge *connectNodes(Node*n1, Node*n2);//connect nodes by pointers.
    /*✅*/HalfEdge *connectNodes(string l1, string l2);//connect nodes by labels.
    /*✅*/int addEdgesByRelation(function<bool(string, string)> relation);//check each pair of nodes for relation between labels and add edge if true.
    /*✅*/Node *addBranch(Node* root, vector<string> vlabels, vector<string> elabels);//add a series of nodes at root.
    /*✅*/void addGraph(SimpleGraph *myg, string labelprefix="",string labelsuffix="",bool duplicate=false);//add nodes and edges from myg graph
    /*✅*/bool disconnectNodes(Node *n1, Node*n2);//remove edge between


    //Information getters.
    /*✅*/string getAdjList();//get adjacency list in string
    /*✅*/Node *getNodeByLabel(string label);//get pointer to node with label
    template<typename T>
    /*✅*/vector<Node*>getNodesIf(function<bool(Node*, T)> predicate, T t);//get vector of nodes satisfying predicate
    /*✅*/bool areAdjacent(Node*n1, Node*n2);//check if edge exists between n1, n2
    /*✅*/HalfEdge *getEdgeByNodes(Node*n1, Node*n2);//get the pointer to edge between n1, n2. NULL if none exists
    
    //subgraphs.
    /*✅*/SimpleGraph getInducedSubgraph(vector<Node*> vToExclude);//return induced subgraphs by deleteing given vertices.
    /*✅*/vector<vector<Node*>> getCliques();//return connected components as vectors of nodes
    
    //distance and path functions
    /*✅*/vector<Node*> getpathbetween(Node *n1, Node*n2, vector<Node*> toexclude);//get any path between n1, n2, excluding toexclude nodes
    /*✅*/vector<Node*> getshortestpathbetween(Node *n1, Node*n2);//get shortest path (using bfs)
    /*✅*/int getDistanceBetween(Node *n1, Node *n2);//get distance = size of shortest path
    //search methods.
    /*✅*/SimpleGraph *bfs(Node *s, bool colornodes=false, vector<string> colorops={"#50C878", "#6698FF", "white"});//return a bfs tree
    /*✅*/SimpleGraph *dfs(Node *s, bool colournodes=false, vector<string> colorops={"#50C878", "#6698FF", "white"});//return a dfs tree

    /*✅*/template<class T>
    void assignVertices(vector<T> vertices, function<string(T)> labelmaker);//add vertices by applying labelmaker to each item of veritces vector
    /*✅*/template<class T>
    void extractGraph(T graphobj, function<vector<Node*>(T)> nodemaker);//add new vertices by using nodemaker on graphobj

    //canvas/geometry related methods
    /*✅*/void setCenter(int x, int y);//set the center of the graph
    /*✅*/void translate(int x, int y);//translate the graph's center and vertices
    /*✅*/void rotate(int angle_anticlockwise);//rotate the graph about its center
    /*✅*/void setCanvasDimensions(int width=700, int height=650);//set canvas width and height in SimpleGraph Object.
    /*✅*/void assignCoords(int CONFIG, Node* bfsroot, bool overwrite=true);//assign coordinates to vertices, using config
    /*✅*/void setRenderDelay(int delay);//set the renderDelay
    
    //methods to serialize/parse data
    /*✅*/string serialize(string dtype="await");//return serialized data of object, dtype is to classify signal type
    /*✅*/void appendRendData(string data);//change graph data based on data received from renderer.
    /*✅*/void parseCommand(string cmd);//process a command from the renderer.
    
    //methods to connect to/sync with renderer
    /*✅*/ServerSocket* initServer(int port=7171, string host="127.0.0.1");//launch and connect renderer window
    /*✅*/ServerSocket* setAutoRender(bool state);//enable rendering at each step
    /*✅*/void syncGraph(bool pausemain=false);//share any changes with the renderer, use pausemain to pause execution of not.

};

#include"Graph.tpp"
#endif
