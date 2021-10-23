#include<bits/stdc++.h>
#include"Graph.h"
using namespace std;
string labelmaker(queue<int> q){
    // return to_string(q.front());
    string label = to_string(q.back());
    return label;
}
// vector<string> split(string str, string sep){
//     vector<string> parts;
//     int j = 0;
//     for(int i=0;i<str.length();i++){
//         if(str.length()-1-i<sep.length()){break;}
//         if(str.substr(i, sep.length())==sep){
//             // cout<<str.substr(j, i-j)<<" ";
//             parts.push_back(str.substr(j, i-j));
//             j = i+1;
//         }
//     }
//     parts.push_back(str.substr(j,str.length()-j));
//     return parts;
// }
int main(int argc, char *argv[]){
    
    // bool am[MAXV][MAXV];
    // am[1][0] = 0;
    // am[2][0] = 1;
    // am[2][1] = 0;
    // vector<string> lbls = {"a", "b", "c"};
    // SimpleGraph myg(am,lbls);
    // string alstr = myg.getAdjList();
    // cout<<alstr;
    // string test = "1:2:3";
    string adjlist = "1:2,3\n2:1\n3:1";
    // vector<string> list = split(adjlist, "\n");
    // for(auto x:list){
    //     string sublist = (split(x, ":"))[1];
    //     cout<<"*";
    //     for(auto y:sublist){
    //         cout<<y<<"sep";
    //     }
    //     cout<<"*\n";
    // }
    vector<string> branch = {"4", "5", "6"};
    SimpleGraph myg(adjlist);
    // cout<<"Hi";
    // cout<<myg.getNodeByLabel("3")->label;
    // myg.connectNodes(myg.getNodeByLabel("3"), myg.getNodeByLabel("2"));
    myg.addBranch(myg.getNodeByLabel("3"), branch, {});
    // cout<<myg.getAdjList();
    // cout<<"Hi";
//     // queue<int> intq;
//     // vector<queue<int>> vqs;
//     // intq.push(1);
//     // vqs.push_back(intq);
//     // intq.push(2);
//     // vqs.push_back(intq);
//     // intq.push(3);
//     // vqs.push_back(intq);

//     // SimpleGraph myg;
//     // vector<int> vi = {1, 2, 3};
//     // myg = SimpleGraph();
//     // // myg.assignVertices<int>(vi, labelmaker);
//     // myg.assignVertices<queue<int>>(vqs, labelmaker);
    
//     for(auto x:myg.V){
//         cout<<x.label<<" ";
//     }
}