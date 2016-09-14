/* DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.
// TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE
// SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM.  DECLARO
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.
// 
// Autor:      Gabriel de Russo e Carmo
// Numero USP: 9298041
// Sigla:      GABRIELD
// Data:       2016-09-13
// 
// Este arquivo faz parte da tarefa F
// da disciplina MAC0328.
// 
//////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include "DIGRAPHlists.h"

/* Desloca todos os elementos do vetor v[0..n-1] para
 * a direita. v[0] nao muda. */
void shift (int *v, int n);

int main (int argc, char **argv) {
    int V, k, i, j, p, alg, comp, *size, big[3];
    double A[] = {0.5, 1, 2, 4, 8, 16};
    double avg[3];
    Digraph G;
    Vertex v;

    V = atoi (argv[1]);
    k = atoi (argv[2]);
    alg = atoi (argv[3]);
    size = malloc (V * sizeof (int));
    
    printf ("   V  |   A   |   Tamanho medio das 3 maiores componentes   \n");
    for (i = 0; i < 6; i++) {
        if (A[i] > V - 1) break;
        for (p = 0; p < 3; p++) avg[p] = 0;
        for (j = 0; j < k; j++) {
            G = DIGRAPHrand1 (V, V * A[i]);
            if (alg == 2) comp = DIGRAPHscKS (G);
            else comp = DIGRAPHsc (G);
            for (p = 0; p < comp; p++) size[p] = 0;
            for (p = 0; p < 3; p++) big[p] = 0;
            for (v = 0; v < G->V; v++) size[G->sc[v]]++;
            for (p = 0; p < comp; p++) {
                if (size[p] >= big[0]) {
                    shift (big, 3);
                    big[0] = size[p];
                }
            }
            for (p = 0; p < 3; p++) avg[p] += (double) big[p] / k;
            DIGRAPHdestroy (G);
        }
        printf ("%5d | %4.1fV | %8.2f | %8.2f | %8.2f\n", V, A[i], avg[0], avg[1], avg[2]);
    }   
    
    return 0;
}

void shift (int *v, int n) {
    int i;
    for (i = n - 1; i > 0; i--)
        v[i] = v[i - 1];
}   

