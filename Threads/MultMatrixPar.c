#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000
#define N_PROCESOS 2
int A[N][N],B[N][N],C[N][N];
void multcol(int i){
    int k,j;
    for(j=0;j<N;j++)for(k=0;k<N;k++)C[k][i] += A[k][i]*B[j][k];
}

int main()
{
    int i, j;
    for (i=0;i<N;i++)
    for (j=0;j<N;j++) {
        A[i][j] = random() % 10;
        B[i][j] = random() % 10;
    }
    double t=omp_get_wtime();
    omp_set_num_threads(N_PROCESOS);
    #pragma omp parallel for
    for(i=0;i<N;i++){
        multcol(i);
    }
    printf("Solucion en %F\n",omp_get_wtime()-t);
return 0;
}

/* El orden en el cual se recorre la matriz depende del orden de los indices.
 * El hecho de cambiar los indices modifica la cantidad de veces que el procesador
 * deba ir a buscar los datos a memoria, pues podria minimizar tiempo haciendo uso
 * de los datos que ya estan en el cache.
 */
