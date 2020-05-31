#include <iostream>
using namespace std;

#include <stdio.h>
#include <pthread.h>

int turn;
int c1, c2;

int data = 5;

void *func1(void* arg){
    int* selfp = (int*)arg;
    int self = *selfp;

    c1 = 0; //thread1 wants to enter CS

    while(c2 == 0){
        if(turn == 2){
            c1 = 1;
            while(turn == 2);

            c1 = 0;
        }
    }

    cout<<"CS of: "<<self<<endl;
    data += 4;

    turn = 2;
    c1 = 1;

    return NULL;
}

void *func2(void* arg){
    int* selfp = (int*)arg;
    int self = *selfp;

    c2 = 0; //thread2 wants to enter CS

    while(c1 == 0){
        if(turn == 1){
            c2 = 1;
            while(turn == 1);

            c2 = 0;
        }
    }

    cout<<"CS of: "<<self<<endl;
    data += 6;

    turn = 1;
    c2 = 1;

    return NULL;
}
int main(){
    c1 = 1, c2 = 1, turn = 1;
    pthread_t p1, p2;

    int t1=1, t2 = 2;

    pthread_create(&p1, NULL, func1, (void*)&t1);
    pthread_create(&p2, NULL, func1, (void*)&t2);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    cout<<data<<endl;

}
