/*
TODO:
1. Integrate socket communication into SimpleGraph but ensure
   flexibility of inclusion.
    Use if(render==true) {communicate} statements and check if compilation is possible.
    Else maybe use inheritance?
    Or an if statement within serverSocket member functions?

2. Implement cpp functionality completely.

3. Style mainWindow.html up.

*/
#ifndef GRAPH_H
#define GRAPH_H
#include<bits/stdc++.h>
#include <winsock2.h>
#include <stdio.h>
#include<string>
#define MAXV 100
#define MAXE 4950 //100C2
#define literal(expr) #expr
#define MAXBUF 10000
using namespace std;
string ptrtostr(void* ptr);
string quotestring(string tbq);
vector<string> split(string str, string sep);
vector<vector<string>> parseLists(string data, int level);
vector<int> toCoords(string kvpair);
template<class T>
bool contains(vector<T> list, T item);
template<class T>
int indexof(vector<T> list, T item);
// struct Neighbour{
//     Node*n;
//     Edge*e;
//     Neighbour(Node*_n, Edge*_e){
//         n = _n;
//         e = _e;
//     }
// };
class HalfEdge;
class Node{
    public:
    string label="";
    int coords[2]={0, 0};//coordinates for animation program;
    int weight=1;//equivalent to radius for animation program;
    string color="";
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

    //constructors
    /*✅*/SimpleGraph();
    /*✅*/SimpleGraph(vector<string> labels);//constructor with number of vertices
    /*✅*/SimpleGraph(bool adjmat[MAXV][MAXV], vector<string> labels);//constructor using adjacency matrix.
    /*✅*/SimpleGraph(string adjlist);//constructor using adjlist in string.
    SimpleGraph(string notation, bool usenotation);//constructor using mathematical notation.
    //search methods.
    /*✅*/SimpleGraph *bfs(Node *s, bool colornodes=false);//return a bfs tree
    SimpleGraph dfs(Node *s);//return a dfs tree
    vector<Node*> generalSearch(Node *s, function<Node(vector<Node>)> selector);//return a vector of nodes
    
    //subgraphs.
    /*✅*/SimpleGraph getInducedSubgraph(vector<Node*> vToExclude);//return induced subgraphs by deleteing given vertices.
    vector<SimpleGraph> getConnectedComponents();//return connected components

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
    Node* addNode(string label, vector<int> coords, int weight, string color);

    //getters.
    /*✅*/string getAdjList();
    /*✅*/Node *getNodeByLabel(string label);
    /*✅*/bool areConnected(Node*n1, Node*n2);
    /*✅*/HalfEdge *getEdgeByNodes(Node*n1, Node*n2);
    /*✅*/vector<Node*> getpathbetween(Node *n1, Node*n2, vector<Node*> toexclude);
    /*✅*/vector<Node*> getshortestpathbetween(Node *n1, Node*n2);
    /*✅*/int getdistanceBetween(Node *n1, Node *n2);
    
    //export all edit graph operations for animation program.
    /*✅*/string exportShots();
    /*✅*/string serialize();
    /*✅*/void takeShot();
    /*✅*/void appendRendData(string data);
    /*✅*/void parseCommand(string cmd);
};

/*Integrate an object of this into SimpleGraph*/
/*✅*/class ServerSocket{
     public:
     WSADATA            wsaData;
     SOCKET             ListeningSocket, NewConnection;
     SOCKADDR_IN        ServerAddr, SenderInfo;
     int                Port;
     // Receiving part
     char          recvbuff[MAXBUF], sendbuff[MAXBUF];
     int                ByteReceived, BytesSent,i, nlen, SelectTiming;
    /*✅*/ServerSocket(int port, string addr);
    /*✅*/int recvTimeOutTCP(SOCKET socket, long sec, long usec);
    /*✅*/void listenForClient();
    /*✅*/string awaitSignal();
    /*✅*/void sendData(string msg);
    /*✅*/void closeConnection();


    /*Graph specific functions here*/
    /*✅*/void sendDataARP(string msg, SimpleGraph &g){
        sendData(msg);
        awaitRecParse(g);
    }
    /*✅*/string awaitRecParse(SimpleGraph &g){
        sendData("paused");
        while(true){
            string resp = awaitSignal();
            if(resp=="EXIT"){
                closeConnection();
                cout<<"\nError fsr\n";
                return "EXIT";
            }
            if(resp.length()>20){
                g.appendRendData(resp);
            }
            else if(resp=="play"){
                return resp;
            }
            else{
                g.parseCommand(resp);
            }
        }
            
        return "OK";
    }

};
#include"Graph.tpp"
#endif
