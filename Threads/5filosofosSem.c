#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <cilk/cilk.h>
#include <semaphore.h>

#define N_FILOSOFOS 5
#define ESPERA 500000

pthread_mutex_t tenedor[N_FILOSOFOS];
sem_t sem;

void pensar(int i)
{
  printf("Filosofo %d pensando...\n",i);
  usleep(random() % ESPERA);
}

void comer(int i)
{
  printf("Filosofo %d comiendo...\n",i);
  usleep(random() % ESPERA);
}

void tomar_tenedores(int i)
{
    sem_wait(&sem);
    pthread_mutex_lock(&tenedor[i]); /* Toma el tenedor a su derecha */
    pthread_mutex_lock(&tenedor[(i+1)%N_FILOSOFOS]); /* Toma el tenedor a su izquierda */
}

void dejar_tenedores(int i)
{
    pthread_mutex_unlock(&tenedor[i]); /* Deja el tenedor de su derecha */
    pthread_mutex_unlock(&tenedor[(i+1)%N_FILOSOFOS]); /* Deja el tenedor de su izquierda */
    sem_post(&sem);
}

void filosofo(int i)
{
  for (;;)
  {
    tomar_tenedores(i);
    comer(i);
    dejar_tenedores(i);
    pensar(i);
  }
}

int main()
{
  int i;
  sem_init(&sem,0,N_FILOSOFOS-1);
  for(i=0;i<N_FILOSOFOS;i++)
    pthread_mutex_init(&tenedor[i],NULL);
  for(i=0;i<N_FILOSOFOS;i++)
    cilk_spawn filosofo(i);
  cilk_sync;
  return 0;
}
