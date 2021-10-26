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
string quotestring(string tbq);
vector<string> split(string str, string sep);
// struct Neighbour{
//     Node*n;
//     Edge*e;
//     Neighbour(Node*_n, Edge*_e){
//         n = _n;
//         e = _e;
//     }
// };
class Node{
    public:
    string label="";
    int coords[2]={0, 0};//coordinates for animation program;
    int weight=1;//equivalent to radius for animation program;
    string color="";
    // vector<Neighbour> adjlist2= {};
    vector<Node*> adjlist = {};
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
class SimpleGraph{
    public:
    //undirected, uniweight graph, with no self loops
    int nv=0, ne=0;//number of vertices and edges
    string snapshots="[ \n";//string holding list of commands executed on Simplegraph.
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
    /*✅*/string exportShots();
    /*✅*/string serialize();
    /*✅*/void takeShot();
};
class ServerSocket{
     public:
     WSADATA            wsaData;
     SOCKET             ListeningSocket, NewConnection;
     SOCKADDR_IN        ServerAddr, SenderInfo;
     int                Port;
     // Receiving part
     char          recvbuff[MAXBUF], sendbuff[MAXBUF];
     int                ByteReceived, BytesSent,i, nlen, SelectTiming;
    ServerSocket(int port, string addr);
    int recvTimeOutTCP(SOCKET socket, long sec, long usec);
    void listenForClient();
    string awaitSignal();
    void sendData(string msg);
    void closeConnection();
};
#include"Graph.tpp"
#endif
