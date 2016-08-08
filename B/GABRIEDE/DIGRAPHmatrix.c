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

/* Aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. 
 * Cada elemento da matriz recebe o valor val. */
static int **MATRIXinit (int r, int c, int val) {
    Vertex i, j;
    int **m = malloc (r * sizeof (int *));
    for (i = 0; i < r; i++) m[i] = malloc (c * sizeof (int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            m[i][j] = val;
    return m;
}

Digraph DIGRAPHinit (int V) {
    Digraph G = malloc (sizeof (digraph));
    G->V = V;
    G->A = 0;
    G->adj = MATRIXinit (V, V, 0);
    return G;
}

void DIGRAPHinsertA (Digraph G, Vertex u, Vertex v) {
    G->A += !G->adj[u][v];
    G->adj[u][v] = 1;
}

void DIGRAPHremoveA (Digraph G, Vertex u, Vertex v) {
    G->A -= G->adj[u][v];
    G->adj[u][v] = 0;
}

void DIGRAPHshow (Digraph G) {
    Vertex u, v;
    for (u = 0; u < G->V; u++) {
        printf("%d:",u);
        for (v = 0; v < G->V; v++)
            if (G->adj[u][v]) printf(" %d", v);
        putchar ('\n');
    }
}

void DIGRAPHdestroy (Digraph G) {
    Vertex u;
    for (u = 0; u < G->V; u++)
        free (G->adj[u]);
    free (G->adj);
    free (G);
}

int DIGRAPHindeg (Digraph G, Vertex u) {
    int deg = 0;
    Vertex v;
    for (v = 0; v < G->V; v++) deg += G->adj[v][u];
    return deg;
} 

int DIGRAPHoutdeg (Digraph G, Vertex u) {
    int deg = 0;
    Vertex v;
    for (v = 0; v < G->V; v++) deg += G->adj[u][v];
    return deg;
}

/* Devolve um vertice aleatorio do digrafo G. */
static Vertex randV (Digraph G) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * G->V;
}

Digraph DIGRAPHrand1 (int V, int A) { 
    Vertex u, v;
    Digraph G = DIGRAPHinit (V);
    while (G->A < A) {
        u = randV (G);
        v = randV (G);
        if (u != v) 
            DIGRAPHinsertA (G, u, v);
    }
    return G;
}

Digraph DIGRAPHrand2 (int V, int A) { 
    Vertex u, v;
    double p = (double) A / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            if (u != v && rand () < p * (RAND_MAX + 1.0))
                DIGRAPHinsertA (G, u, v);
    return G;
}

Digraph GRAPHrand1 (int V, int E) { 
    Vertex u, v;
    Digraph G = DIGRAPHinit (V);
    while (G->A < 2 * E) {
        u = randV (G);
        v = randV (G);
        if (u != v) {
            DIGRAPHinsertA (G, u, v);
            DIGRAPHinsertA (G, v, u);
        }
    }
    return G;
}

Digraph GRAPHrand2 (int V, int E) { 
    Vertex u, v;
    double p = (double) (2*E) / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (u = 0; u < V; u++)
        for (v = u + 1; v < V; v++)
            if (rand () < p * (RAND_MAX + 1.0)) {
                DIGRAPHinsertA (G, u, v);
                DIGRAPHinsertA (G, v, u);
            }
    return G;
}

