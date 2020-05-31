#include <bits/stdc++.h>
using namespace std;

#include "fcfs.h"
#include "sjf.h"
#include "rr.h"

#define endl '\n'

int main(){
    vector<int> process, bt;
    int n; 
    cout<<"Enter no of processes: ";
    cin>>n;
    cout<<"Enter processes: ";
    for(int i=0; i<n; i++){
        int p; cin>>p;
        process.push_back(p);
    }
    cout<<"Enter burst time: ";
    for(int i=0; i<n; i++){
        int b; cin>>b;
        bt.push_back(b);
    }
    int q; 
    cout<<"Enter quantum size ";
    cin>>q;
    fcfs(process, bt);
    sjf(process, bt);
    rr(process, bt, q);
}

