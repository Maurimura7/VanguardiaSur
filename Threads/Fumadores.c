#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <cilk/cilk.h>
#include <pthread.h>
#define metoca(a,b) (((sem_getvalue(&(a),&p)||1) && p>0) && ((sem_getvalue(&(b),&q)||1) && q>0))


sem_t tabaco, papel, fosforos, otra_vez;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int p,q;

void agente()
{
    for(;;){
		int caso = random()%3;
        sem_wait(&otra_vez);
        switch (caso) {
            case 0:
                sem_post(&tabaco);
                sem_post(&papel);
                break;
            case 1:
                sem_post(&fosforos);
                sem_post(&tabaco);
                break;
            case 2:
                sem_post(&papel);
                sem_post(&fosforos);
                break;
        }
    }
}

void fumar(int fumador)
{
    printf("Fumador %d: Puf! Puf! Puf!\n", fumador);
    usleep(50000);
}

void fumador1()
{
    for (;;){
		pthread_mutex_lock(&mutex);
		if(metoca(papel,tabaco)){
			sem_wait(&tabaco);
			sem_wait(&papel);
			fumar(1);
			sem_post(&otra_vez);
		}
		pthread_mutex_unlock(&mutex);
    }
}

void fumador2()
{
    for (;;){
		pthread_mutex_lock(&mutex);
		if(metoca(fosforos,tabaco)){
			sem_wait(&fosforos);
			sem_wait(&tabaco);
			fumar(2);
			sem_post(&otra_vez);
		}
		pthread_mutex_unlock(&mutex);
    }
}

void fumador3()
{
    for (;;){
		pthread_mutex_lock(&mutex);
		if(metoca(fosforos,papel)){
			sem_wait(&papel);
			sem_wait(&fosforos);
			fumar(3);
			sem_post(&otra_vez);
		}
		pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    sem_init(&tabaco, 0, 0);
    sem_init(&papel, 0, 0);
    sem_init(&fosforos, 0, 0);
    sem_init(&otra_vez, 0, 1);
    cilk_spawn fumador1();
    cilk_spawn fumador2();
    cilk_spawn fumador3();
    agente();
    
    return 0 ;
}
