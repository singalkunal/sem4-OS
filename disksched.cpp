#include <bits/stdc++.h>
using namespace std;

void fcfs(vector<int> req, int head){
    int seek_count = 0;
    vector<int> seq;
    seq.push_back(head);
    for(auto it: req){
        seek_count += abs(head-it);
        head = it;
        seq.push_back(it);
    }

    cout<<"Seek count for SCAN: "<<seek_count<<endl;
    cout<<"Sequence: ";
    for(auto it: seq) cout<<it<<" ";
    cout<<endl<<"----------------------------"<<endl;
}

void scan(vector<int> req, int head, int tot, char direc){
    vector<int> l, r;
    for(auto it: req){
        if(it < head)
            l.push_back(it);
        else
            r.push_back(it);
    }

    sort(l.begin(), l.end(), greater<int>());
    sort(r.begin(), r.end());

    direc == 'L'? l.push_back(0):r.push_back(tot-1);    
    int seek_count = 0;

    vector<int> seq;
    seq.push_back(head);
    int scan = 2;
    while(scan--){
        if(direc == 'L'){
            for(auto it: l){
                seq.push_back(it);
                seek_count += (head-it);
                head = it;
            }
            direc = 'R';
        }
        else{
            for(auto it: r){
                seq.push_back(it);
                seek_count += (it-head);
                head = it;
            }
            direc = 'L';

        }
    }
    cout<<"Seek count for SCAN: "<<seek_count<<endl;
    cout<<"Sequence: ";
    for(auto it: seq) cout<<it<<" ";
    cout<<endl<<"----------------------------"<<endl;
}

void look(vector<int> req, int head, char direc){
    vector<int> l, r;
    for(auto it: req){
        if(it < head)
            l.push_back(it);
        else
            r.push_back(it);
    }

    sort(l.begin(), l.end(), greater<int>());
    sort(r.begin(), r.end()); 
    int seek_count = 0;

    vector<int> seq;
    seq.push_back(head);
    int scan = 2;
    while(scan--){
        if(direc == 'L'){
            for(auto it: l){
                seq.push_back(it);
                seek_count += (head-it);
                head = it;
            }
            direc = 'R';
        }
        else{
            for(auto it: r){
                seq.push_back(it);
                seek_count += (it-head);
                head = it;
            }
            direc = 'L';

        }
    }
    cout<<"Seek count for LOOK: "<<seek_count<<endl;
    cout<<"Sequence: ";
    for(auto it: seq) cout<<it<<" ";
    cout<<endl<<"----------------------------"<<endl;
}

void C_look(vector<int> req, int head, char direc){
    vector<int> l, r;
    for(auto it: req){
        if(it < head)
            l.push_back(it);
        else
            r.push_back(it);
    }

    if(direc == 'L'){
        sort(l.begin(), l.end(), greater<int>());
        sort(r.begin(), r.end(), greater<int>()); 
    }
    else{
        sort(l.begin(), l.end());
        sort(r.begin(), r.end()); 

    }
    int seek_count = 0;

    vector<int> seq;
    seq.push_back(head);
    int scan = 2;
    while(scan--){
        if(direc == 'L'){
            for(auto it: l){
                seq.push_back(it);
                seek_count += abs(head-it);
                head = it;
            }
            direc = 'R';
        }
        else{
            for(auto it: r){
                seq.push_back(it);
                seek_count += abs(head-it);
                head = it;
            }
            direc = 'L';
        }
    }
    cout<<"Seek count for C-LOOK: "<<seek_count<<endl;
    cout<<"Sequence: ";
    for(auto it: seq) cout<<it<<" ";
    cout<<endl<<"----------------------------"<<endl;

}

int find_closest(vector<int> v, vector<int>& serviced, int x){
    int idx=0;
    while(serviced[idx] && idx < (int)serviced.size())
        idx++;
    for(int i=0; i<(int)v.size(); i++){
        if((!serviced[i] && abs(x-v[i])<abs(x-v[idx]))){
            idx = i;
        }
    }
    serviced[idx]++;
    return idx;
}

void sstf(vector<int> req, int head, char direc){
    int n = req.size();
    vector<int> serviced(n, 0);

    int seek_count = 0;
    vector<int> seq;
    seq.push_back(head);
    for(int i=0; i<n; i++){
        int idx = find_closest(req, serviced, head);
        seek_count += abs(head-req[idx]);
        seq.push_back(req[idx]);
        head = req[idx];
    }

    cout<<"Seek count for SSTF: "<<seek_count<<endl;
    cout<<"Sequence: ";
    for(auto it: seq) cout<<it<<" ";
    cout<<endl<<"----------------------------"<<endl;
}

int main(){
    int n;
    cout<<"Enter size of req sequence: ";
    cin>>n;
    vector<int> req(n);
    cout<<"Enter request sequence: ";
    for(int i=0; i<n; i++) cin>>req[i];

    int head;
    cout<<"Enter postition of head: ";
    cin>>head;
    int tot;
    cout<<"Enter no. of cylinders: "; 
    cin>>tot;
    char direc;
    cout<<"Enter starting direction of head L/H: "; 
    cin>>direc;

    fcfs(req, head);
    sstf(req, head, direc);
    scan(req, head, tot, direc);
    look(req, head, direc);
    C_look(req, head, direc);
}

