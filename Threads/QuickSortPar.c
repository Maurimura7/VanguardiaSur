#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>
#include <sys/sysinfo.h>
#define N 1000000
#if N<100000
#define H 0
#else
#define H (int)get_nprocs()
#endif
//~ N = paralelo / sec
//~ 100 = 0.000017/0.000013
//~ 1000 = 0.000199/0.000228
//~ 10000 = 0.002583/0.003096
//~ 100000 = 0.023084/0.030716
//~ 1000000 = 0.237653/0.300192
//~ 10000000 = 1.887642/3.226485
//~ 100000000 = 25.170148/36.576301
typedef struct {
    int *v;
    int b, t,c;
} qsparams;

void swap(int *v, int i, int j)
{
    int tmp=v[i];
    v[i]=v[j];
    v[j]=tmp;
}

int colocar(int *v, int b, int t)
{
    int i;
    int pivote, valor_pivote;
    int temp;

    pivote = b;
    valor_pivote = v[pivote];
    for (i=b+1; i<=t; i++){
        if (v[i] < valor_pivote){
            pivote++;
            swap(v,i,pivote);
        }
    }
    temp=v[b];
    v[b]=v[pivote];
    v[pivote]=temp;
    return pivote;
}

void *Quicksort(void *p)
{
    qsparams *params = (qsparams *)p;
    int *v = params->v;
    int b = params->b;
    int t = params->t;
    int c = params->c;
    int pivote;
    if(b < t){
        pivote=colocar(v, b, t);
        qsparams params1, params2;
        params1.v = v;
        params1.b = b;
        params1.t = pivote-1;
        params1.c = H+1;
        params2.v = v;
        params2.b = pivote+1;
        params2.t = t;
        params2.c = c+1;
        if(c<H && (pivote-1-b)>50000){
            pthread_t t1;
            pthread_create(&t1,0,Quicksort,(void *)&params1);
            Quicksort((void *)&params2);
            pthread_join(t1, NULL);
        }else{
            Quicksort((void *)&params1);
            Quicksort((void *)&params2);
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    int *a,i;
    a = malloc(N*sizeof(int));
    for(i=0;i<N;i++)
        a[i]=random()%N;
    qsparams params;
    params.v = a;
    params.b = 0;
    params.t = N-1;
    params.c = 1;
    double times=omp_get_wtime();       
    Quicksort((void *)&params);
    printf("Tiempo en paralelo=%F\n",omp_get_wtime()-times);
    free(a);
    return 0;
}
