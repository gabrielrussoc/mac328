/* DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESTE PROGRAMA.
// TODAS AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS
// PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE
// SEDGEWICK OU ROBERTS, FORAM DESENVOLVIDAS POR MIM.  DECLARO
// TAMBEM QUE SOU RESPONSAVEL POR TODAS AS COPIAS DESTE PROGRAMA
// E QUE NAO DISTRIBUI NEM FACILITEI A DISTRIBUICAO DE COPIAS.
// 
// Autor:      Gabriel de Russo e Carmo
// Numero USP: 9298041
// Sigla:      GABRIEDE
// Data:       2016-08-08
// 
// Este arquivo faz parte da tarefa B
// da disciplina MAC0328.
// 
//////////////////////////////////////////////////////////////// */

#include "DIGRAPHmatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Este programa gera V pontos aleatorios no quadrado [0,1) x [0,1)
 * e depois monta um grafo ligando por uma aresta os pontos que estiverem
 * a distancia <= d um do outro. 
 * V e d sao argumentos da linha de comando, nessa ordem. */

/* Recebe x e devolve seu quadrado. */
double sq (double x) {
    return x * x;
}

/* Recebe um inteiro V e um double d. Gera V pontos aleatorios
 * e liga num grafo os pontos que distam ate d um do outro. Imprime
 * a quantidade de arestas e o grafo, se este nao for muito grande. */
void random_points (int V, double d) {
    double *x, *y;
    int i, j;
    Digraph G = DIGRAPHinit (V);
    x = malloc (V * sizeof (double));
    y = malloc (V * sizeof (double));

    srand (time (NULL));
    for (i = 0; i < V; i++) {
        x[i] = rand () / (RAND_MAX + 1.0);
        y[i] = rand () / (RAND_MAX + 1.0);
    }

    for (i = 0; i < V; i++)
        for (j = i + 1; j < V; j++)
            if (sq (x[i]) + sq (x[i]) <= sq (d)) {
                DIGRAPHinsertA (G, i, j);
                DIGRAPHinsertA (G, j, i);
            }

    printf ("Arestas produzidas: %d\n\n", G->A / 2);
    if (G->V > 30) puts ("Grafo muito grande!");
    else {
        printf ("Listas de adjacencia\n");
        DIGRAPHshow (G);
    }

    DIGRAPHdestroy (G);
}

/* Recebe a quantidade V de pontos e a distancia d pela linha
 * de comando, nessa ordem. */
int main (int argc, char **argv) {
    int V = atoi (argv[1]);
    double d = atof (argv[2]);
    random_points (V, d);
    return 0;
}

