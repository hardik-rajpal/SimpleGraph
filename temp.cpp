#include<bits/stdc++.h>
#include"Graph.h"
using namespace std;
template<typename T>
class jsonEntry{
    public:
    T value;
    string key;
    jsonEntry<T>(string kvpair){
        // kvpair = kvpair.substr(1, kvpair.length()-2);
        vector<string> kv = split(kvpair, ":");
        key = kv[0].substr(1,kv[0].length()-2);
        string dtype = typeid(T).name();
        if(dtype=="i"){
            value = stoi(kv[1]);
        }
        else{
            cout<<"New dtype:"<<dtype<<"\n";

        }
    }
};
// vector<string> getCoords(string data){
//
// }
int main(){
    // string data = "{\"V\":{\"0x1201a58\":{\"x\":361.35054325195097,\"y\":226.57732039139847},\"0x1201ab8\":{\"x\":327.82282544654413,\"y\":208.38826990611196},\"0x1201b18\":{\"x\":83.31516221980166,\"y\":443.6108981611163}}}";
    string data = "{\"V\":[{\"x\":269.67763030360555,\"y\":230.96765163768615},{\"x\":372.5338671077842,\"y\":409.72404941924606},{\"x\":265.07212643808464,\"y\":343.40958276222966}],\"ptrs\":[\"0xf81a58\",\"0xf81ab8\",\"0xf81b18\"]}";
    vector<string> strdata = parseLevel(data, 3);
    vector<string> keys = parseLevel(data, 2);
    cout<<strdata.size()<<"\n";
    for(auto x:strdata){
        cout<<x<<" rec \n";
        vector<int> crds = toCoords(x);
    }
    for(auto y:keys){
        // cout<<y<<"\n";
    }
}