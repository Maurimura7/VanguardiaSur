#include <stdio.h>
#include <cilk/cilk.h>
#include <pthread.h>

#define N_VISITANTES 100000

int visitantes = 0;
pthread_mutex_t gorra = PTHREAD_MUTEX_INITIALIZER;


void molinete()
{
  int i;
  for (i=0;i<N_VISITANTES;i++){
	pthread_mutex_lock(&gorra);
	    visitantes++;
	pthread_mutex_unlock(&gorra);
  }	
}

int main()
{
  cilk_spawn molinete();
  cilk_spawn molinete();
  cilk_sync;

  printf("Hoy hubo %d visitantes!\n", visitantes);
  return 0;
}
