#include <iostream>
using namespace std;

#include <stdio.h>
#include <pthread.h>

int flag[2];
int turn;
//shared data
int accountA = 5, accountB = 9; //after each transacn sum should remain same

void lock_init(){
    flag[0] = flag[1] = 0;
    turn = 1;
}

void lock(int self){
    flag[self] = 1;
    turn = 1 - self;

    while(flag[1-self] && turn == 1-self);
}

void unlock(int self){
    flag[self] = 0;
}

void* transac1(void* arg){
    int *selfp = (int*)arg;
    int self = *selfp;

    lock(self);
    cout<<"Transaction going on: "<<(self+1)<<endl;
    accountA -= 2;
    accountB += 2;
    unlock(self);

    return NULL;
}

void* transac2(void* arg){
    int *selfp = (int*)arg;
    int self = *selfp;

    lock(self);
    cout<<"Transaction going on: "<<(self+1)<<endl; 
    accountA -= 3;
    accountB += 3;
    unlock(self);
    return NULL;
}


int main(){
    cout<<"Initial Sum: "<<accountA+accountB<<endl;
    pthread_t p1, p2;
    lock_init();

    int t0 = 0, t1 =1;

    pthread_create(&p1, NULL, transac1, (void*)&t0);    
    pthread_create(&p2, NULL, transac2, (void*)&t1);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    cout<<"Sum after both transac: "<<accountA+accountB<<endl;
    
}

