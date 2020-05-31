#include <iostream>
using namespace std;

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>
#include <time.h>
#include<cmath>

sem_t mutex, wrt;
int readcount;

int data;

void* reader(void*){
    sem_wait(&mutex); //lock readcount
    readcount++;
    if(readcount == 1) //first reader (currently no reader is reading)
        sem_wait(&wrt); //cs acquired by readers
    sem_post(&mutex);

    cout<<"Read data: "<<data<<endl;
    
    sem_wait(&mutex);
    readcount--;
    if(readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);

    sleep(2);
    return NULL;
}

void* writer(void* arg){
    int item;
    item = (*(int*)arg);
    sem_wait(&wrt);

    //writing
    data = item;
    cout<<"Written: "<<data<<endl;
    
    sem_post(&wrt);

    sleep(2);
    return NULL;
}

int main(){
    //Initialization
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    readcount = 0;

    pthread_t r1, r2, w1, w2;

    int item = 10;
        for(int i=0; i< 4; i++){
        pthread_create(&w1, NULL, &writer, (void*)&item);
//        pthread_create(&w2, NULL, &writer, (void*)&item);
        pthread_create(&r1, NULL, &reader, NULL);
        pthread_create(&r2, NULL, &reader, NULL);

        pthread_join(w1, NULL);
//        pthread_join(w2, NULL);
        pthread_join(r1, NULL);
        pthread_join(r2, NULL);
    }
}


