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
// Data:       2016-08-30
// 
// Este arquivo faz parte da tarefa E
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
    G->pre = malloc (V * sizeof (int));
    G->pos = malloc (V * sizeof (int));
    G->pai = malloc (V * sizeof (int));
    return G;
}

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    G->A += !G->adj[v][w];
    G->adj[v][w] = 1;
}

void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) {
    G->A -= G->adj[v][w];
    G->adj[v][w] = 0;
}

void DIGRAPHshow (Digraph G) {
    Vertex v, w;
    for (v = 0; v < G->V; v++) {
        printf("%d:",v);
        for (w = 0; w < G->V; w++)
            if (G->adj[v][w]) printf(" %d", w);
        putchar ('\n');
    }
}

void DIGRAPHdestroy (Digraph G) {
    Vertex v;
    for (v = 0; v < G->V; v++)
        free (G->adj[v]);
    free (G->adj);
    free (G->pre);
    free (G->pos);
    free (G->pai);
    free (G);
}

int DIGRAPHindeg (Digraph G, Vertex v) {
    int deg = 0;
    Vertex w;
    for (w = 0; w < G->V; w++) deg += G->adj[w][v];
    return deg;
} 

int DIGRAPHoutdeg (Digraph G, Vertex v) {
    int deg = 0;
    Vertex w;
    for (w = 0; w < G->V; w++) deg += G->adj[v][w];
    return deg;
}

/* Devolve um vertice aleatorio do digrafo G. */
static Vertex randV (Digraph G) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * G->V;
}

Digraph DIGRAPHrand1 (int V, int A) { 
    Vertex v, w;
    Digraph G = DIGRAPHinit (V);
    while (G->A < A) {
        v = randV (G);
        w = randV (G);
        if (v != w) 
            DIGRAPHinsertA (G, v, w);
    }
    return G;
}

Digraph DIGRAPHrand2 (int V, int A) { 
    Vertex v, w;
    double p = (double) A / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            if (v != w && rand () < p * (RAND_MAX + 1.0))
                DIGRAPHinsertA (G, v, w);
    return G;
}

Digraph GRAPHrand1 (int V, int E) { 
    Vertex v, w;
    Digraph G = DIGRAPHinit (V);
    while (G->A < 2 * E) {
        v = randV (G);
        w = randV (G);
        if (v != w) {
            DIGRAPHinsertA (G, v, w);
            DIGRAPHinsertA (G, w, v);
        }
    }
    return G;
}

Digraph GRAPHrand2 (int V, int E) { 
    Vertex v, w;
    double p = (double) (2*E) / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = v + 1; w < V; w++)
            if (rand () < p * (RAND_MAX + 1.0)) {
                DIGRAPHinsertA (G, v, w);
                DIGRAPHinsertA (G, w, v);
            }
    return G;
}


/* Busca um ciclo em G a partir do vertice v. Devolve
 * um vertice de um ciclo ou -1 se nenhum for encontrado. */
static Vertex cycleR (Digraph G, Vertex v) { 
    Vertex w, tmp;
    G->pre[v] = G->contapre++;
    for (w = 0; w < G->V; w++) {
        if (G->adj[v][w] == 0) continue;
        if (G->pre[w] == -1) {
            G->pai[w] = v;
            tmp = cycleR (G, w);
            if (tmp != -1) return tmp;
        } else { 
            if (G->pos[w] == -1) {
                G->pai[w] = v;
                return w;
            }
        }
    }
    G->pos[v] = G->contapos++;
    return -1;
}

Vertex DIGRAPHcycleOrTopo (Digraph G) {
    Vertex v, tmp;
    G->contapre = G->contapos = 0;
    for (v = 0; v < G->V; v++)
        G->pre[v] = G->pos[v] = -1;
    for (v = 0; v < G->V; v++)
        if (G->pre[v] == -1) {
            tmp = cycleR (G, v);
            if (tmp != -1) return tmp;
        }
    return -1; 
}

