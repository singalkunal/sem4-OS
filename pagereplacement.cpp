#include <iostream>
using namespace std;

#include "fifo.h"
#include "optimal.h"
#include "lru.h"

int main(){
    int n;
    cout<<"Enter size of reference string: ";
    cin>>n;
    cout<<"Enter reference string: ";
    int *refs = new int[n];
    for(int i=0; i<n; i++) cin>>refs[i];
    int capacity;
    cout<<"Enter capacity of page frames: ";
    cin>>capacity;
    
    int pfs;
    pfs = optimal(refs, n, capacity);
    cout<<"Total page faults using optimal: "<<pfs<<endl;

    pfs = fifo(refs, n, capacity);
    cout<<"Total page faults using fifo: "<<pfs<<endl;

    pfs = LRU(refs, n, capacity);
    cout<<"Total page faults using LRU: "<<pfs<<endl;

}

