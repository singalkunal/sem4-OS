#include <iostream>
using namespace std;
 
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>
#define NUM_PHIL 5

char state[NUM_PHIL];
int phil[NUM_PHIL] = {0, 1, 2, 3, 4};

sem_t mutex; //no 2 philosopher can access pickup or putdown simult.
sem_t s[NUM_PHIL];

void test(int i){
    if(state[i] == 'h' && (state[(i+4)%NUM_PHIL] != 'e') && (state[(i+1)%NUM_PHIL] != 'e')){
        state[i] = 'e';
        sleep(2);

        cout<<"Philospher "<<i+1<<" is eating"<<endl;
        sem_post(&s[i]);
    }
}

void pickup(int i){
    sem_wait(&mutex);
    state[i] = 'h';
    cout<<"Philospher "<<i+1<<" is Hungry"<<endl;
    test(i);
    sem_post(&mutex);
    if(state[i] != 'e')
        sem_wait(&s[i]);
    sleep(1);
}

void putdown(int i){
    sem_wait(&mutex);
    state[i] = 't';
    cout<<"Philospher "<<i+1<<" putting down fork"<<endl;
    cout<<"Philospher "<<i+1<<" started thinking"<<endl;
    test((i+4) % NUM_PHIL);
    test((i+1) % NUM_PHIL);
    sem_post(&mutex);
}

void* philospher(void* arg){
    int philno;
    while(1){
    philno = *(int*)arg;
    sleep(2);
    pickup(philno);
    sleep(0);
    putdown(philno);
    }

    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1);
    for(int i=0; i<NUM_PHIL; i++){
        sem_init(&s[i], 0, 1);
    }
    pthread_t phil_id[NUM_PHIL];

    for(int i=0; i<NUM_PHIL; i++)
        pthread_create(&phil_id[i], NULL, &philospher, (void*)&phil[i]);

    for(int i=0; i<NUM_PHIL; i++){
        pthread_join(phil_id[i], NULL);
    }
}
