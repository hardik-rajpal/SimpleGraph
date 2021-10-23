#include<bits/stdc++.h>
using namespace std;
class A{
     
public:
int mn;
A(){};
// template <class T>
    // T mymax(T a, function<string(T)> h)
    // {
    //     cout<<a<<h(a);
    //     return a;
    // }
template<class T>
void printer(function<string(T)> h, vector<T> v){
    for(auto a:v){
        cout<<h(a)<<" ";
    }
}
};
string labelmaker(int v){
    string ans = to_string(v);
    return ans;
}

int main(){
    A a;
    a = A();
    string mystr = "abc";
    a.printer<int>(labelmaker, {1, 2});
    // cout<<a.mymax(1, l)<<" "<<a.mn;
}