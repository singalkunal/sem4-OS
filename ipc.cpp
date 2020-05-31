#include <bits/stdc++.h>
using namespace std;

#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>

#define BUFF_SIZE 5
int nextin=0, nextout=0;

void producer(int seg_id){
    char item;
    char *str = (char*) shmat(seg_id, NULL, 0);
    item = (char)(rand()%100);
    cout<<"prod";
    while(1){
        cout<<"Producer";
        cout<<"Produceing item: "<<item;
        str[nextin] = item;
        nextin = (nextin+1)%BUFF_SIZE;
         item = (char)(rand()%100);
         sleep(1);
    }
}

void consumer(int seg_id){
    char* str = (char*) shmat(seg_id, NULL, 0);
    while(1){
        if(nextin == nextout){
            cout<<"Buffer is empty "<<endl;
            sleep(2);
        }
        char item = str[nextout];
        cout<<"Consumed item: "<<item<<endl;
        nextout = (nextout+1)%BUFF_SIZE;
        sleep(2);
    }

}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    int seg_id = shmget(IPC_PRIVATE, 1024, S_IRUSR | S_IWUSR);
    if(fork() == 0)
        consumer(seg_id);
    else{
        producer(seg_id);
    }
}

