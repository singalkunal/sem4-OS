#include <iostream>
using namespace std;

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>
#include <time.h>
#include<cmath>

sem_t mutex, empty, full;
const int BUFF_SIZE = 5;
int buffer[BUFF_SIZE];
int nextin = 0, nextout = 0;

int count = 0, iters = 9;

void* producer(void*){
    int item = rand() % 100;
    while(++count < iters){
    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[nextin] = item;
    cout<<"Item "<<item<<" produced successfully"<<endl;
    nextin = (nextin+1) % BUFF_SIZE;
    item = rand() % 100;
    sem_post(&mutex);
    sem_post(&full);

    sleep(2);
    }
    
    return NULL;
}

void* consumer(void*){
    while(++count < iters){
    sem_wait(&full);
    sem_wait(&mutex);

    int consumed_item = buffer[nextout];
    cout<<"Consumed item: "<<consumed_item<<endl;
    nextout = (nextout + 1) % BUFF_SIZE;

    sem_post(&mutex);
    sem_post(&empty);

    sleep(2);
}

    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFF_SIZE);
    sem_init(&full, 0, 0);

    pthread_t p1, p2;

    srand(time(0));
    pthread_create(&p1, NULL, &producer, NULL); 
    pthread_create(&p2, NULL, &consumer, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    return 0;
}
