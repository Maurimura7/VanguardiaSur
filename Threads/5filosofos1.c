#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <cilk/cilk.h>

#define N_FILOSOFOS 5
#define ESPERA 5000000

pthread_mutex_t tenedor[N_FILOSOFOS];

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
	if(i==0){
	  pthread_mutex_lock(&tenedor[(i+1)%N_FILOSOFOS]); /* Toma el tenedor a su izquierda */
	  pthread_mutex_lock(&tenedor[i]); /* Toma el tenedor a su derecha */
	}else{
	  pthread_mutex_lock(&tenedor[i]); /* Toma el tenedor a su derecha */
	  pthread_mutex_lock(&tenedor[(i+1)%N_FILOSOFOS]); /* Toma el tenedor a su izquierda */
	}
}

void dejar_tenedores(int i)
{
	if(i==0){
	  pthread_mutex_unlock(&tenedor[(i+1)%N_FILOSOFOS]); /* Deja el tenedor de su izquierda */
	  pthread_mutex_unlock(&tenedor[i]); /* Deja el tenedor de su derecha */
	}else{
	  pthread_mutex_unlock(&tenedor[i]); /* Deja el tenedor de su derecha */
	  pthread_mutex_unlock(&tenedor[(i+1)%N_FILOSOFOS]); /* Deja el tenedor de su izquierda */
	}
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
  for (i=0;i<N_FILOSOFOS;i++)
    pthread_mutex_init(&tenedor[i], NULL);
  for (i=0;i<N_FILOSOFOS;i++)
    cilk_spawn filosofo(i);
  cilk_sync;
  return 0;
}
/*
 	Funciona porque el filosofo zurdo tratara de tomar el mismo tenedor que la persona que esta a su izquierda
	No importa quien tome el tenedor primero, lo importante es que rompimos el ciclo		
*/
