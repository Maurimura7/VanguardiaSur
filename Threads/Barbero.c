#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#define N 5
#define MAXN 8
struct timeval now;
struct timespec timeout;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t aten = PTHREAD_COND_INITIALIZER;
pthread_cond_t fin = PTHREAD_COND_INITIALIZER;
pthread_cond_t nothing = PTHREAD_COND_INITIALIZER;
pthread_cond_t turno = PTHREAD_COND_INITIALIZER;
pthread_attr_t attr;
pthread_t barb;
volatile int sillas;

void *cliente(void *arg)
{
    pthread_mutex_lock(&mut);
    int c=*(int *)arg;
    printf("LLega cliente %d\n",c);
    if(N<sillas)printf("No hay sillas, ");
    else{
        sillas++;
        printf("Cliente %d espera turno\n",c);
        pthread_cond_signal(&turno);
        pthread_cond_wait(&aten,&mut);
        printf("Atendiendo al cliente %d\n",c);
        pthread_cond_timedwait(&nothing,&mut,&timeout);//El barbero lo esta atendiendo
        pthread_cond_signal(&fin);
        sillas--;
    }
    printf("Cliente %d se va\n",c);
    pthread_mutex_unlock(&mut);
    return NULL;
}

void * barbero(void * b){
    int i;
    for(i=1;;i++){
        pthread_mutex_lock(&mut);
        while(sillas==0){
            puts("Barbero duerme");
            pthread_cond_wait(&turno,&mut);
        }
        pthread_cond_signal(&aten);
        pthread_cond_wait(&fin,&mut);
        pthread_mutex_unlock(&mut);
        sleep(random()%2);
    }
    return NULL;
}

void * simulador(void){
    int * arg,i;
    for(i=0;;i=(i+1)%MAXN){
        sleep(random()%3);
        pthread_t clt;
        arg=malloc(4);
        *arg=abs(i);
        pthread_create(&clt,NULL,cliente,arg);
        pthread_detach(clt);
    }
    return NULL;
}

int main()
{
    gettimeofday(&now,NULL);
    timeout.tv_sec = now.tv_sec + 5;
    timeout.tv_nsec = now.tv_usec * 1000;
    pthread_create(&barb,NULL,barbero,NULL);
    simulador();
    return 0;
}
