#include<iostream>
using namespace std;

#include <vector>

vector<int> isSafe(int** alloc, int** need, int *available, int n, int r){
    int *work = new int[r];
    for(int i=0; i<r; i++) work[i] = available[i];
    int* completed = new int[n];
    for(int i=0; i<n; i++) completed[i] = 0; 
    int count = 0;
    vector<int>safeseq;
    while(count < 5){
        int process = -1;
        for(int i=0; i<n; i++){
            if(completed[i] == 0){
                process = i;
                for(int j=0; j<r; j++){
                    if(need[i][j] > work[j]){
                        process = -1;
                        break;
                    }
                }
            }

            if(process != -1)
                break;
        }

        if(process == -1){
            return safeseq;
        }
        else{
            safeseq.push_back(process);
            for(int j = 0; j<r; j++){
                work[j] += alloc[process][j];
            }
            completed[process] = 1;
            count++;
        }
    }
    return safeseq;
}

int main() {
    int n, r;
    cout<<"Enter no of processes and no of resources: ";
    cin>>n>>r;
    int **max = new int*[n], **alloc = new int*[n], **need = new int*[n];
    cout<<"Enter max matrix: "<<endl;
    for(int i=0; i<n; i++){
        max[i] = new int[r];
        for(int j=0; j<r; j++)
            cin>>max[i][j];
    }

    cout<<"Enter alloc matrix: "<<endl;
    for(int i=0; i<n; i++){
        alloc[i] = new int[r];
        need[i] = new int[r];
        for(int j=0; j<r; j++){
            cin>>alloc[i][j];
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int *max_res = new int[r];
    int *available = new int[r];
    cout<<"Enter max resources available"<<endl;
    for(int i=0; i<r; i++) {
        cin>>max_res[i];
        available[i] = max_res[i];
        for(int j=0; j<n; j++){
            available[i] -= alloc[j][i];
        }
    }

    vector<int> v = isSafe(alloc, need, available, n, r);
    if((int)v.size() < n){
        cout<<"System is in unsafe state"<<endl;
    }
    else{
        cout<<"Safe Sequence: "<<endl;
        for(int i=0; i<(int)v.size(); i++){
            cout<<v[i]<<" ";
        }
    }

    int req;
    cout<<"Enter no of requests: ";
    cin>>req;
    for(int i=0; i<req; i++){
        int p;
        cout<<"process: ";
        cin>>p;
        int *request = new int[r];
        cout<<"Enter request of process"<<p<<": ";
        for(int j=0; j<r; j++){
            cin>>request[j];
            if(request[j] > need[p][j] || request[j] > available[j]){
                cout<<"Max limit exceeded";
                continue;
            }
        }
        for(int j=0; j<r; j++){
            available[j] -= request[j];
            alloc[p][j] += request[j];
            need[p][j] -= request[j];
        }

        vector<int> ss = isSafe(alloc, need, available, n, r);
    if((int)ss.size() < n){
        cout<<"System is in unsafe state"<<endl;
        for(int j=0; j<r; j++){
            available[j] += request[j];
            alloc[p][j] -= request[j];
            need[p][j] += request[j];
        }

    }
    else{
        cout<<"Safe Sequence: "<<endl;
        for(int i=0; i<(int)v.size(); i++){
            cout<<v[i]<<" ";
        }
    }

 }
    














}
