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

#include "DIGRAPHlists.h"
#include <stdio.h>
#include <stdlib.h>

/* Cria um novo no de lista encadeada 
 * com o vertice w no conteudo e proximo no next. */
static link LISTnewNode (Vertex w, link next) {
    link a = malloc (sizeof (Node));
    a->w = w;
    a->next = next;
    return a;
}

/* Remove um no de lista encadeada e devolve o proximo
 * do mesmo. */
static link LISTdestroyNode (link l) {
    link aux = l;
    l = l->next;
    free(aux);
    return l;
}

/* Destroi uma lista encadeada */
static void LISTdestroy (link l) {
    link aux;
    while (l != NULL) {
        aux = l;
        l = l->next;
        free (aux);
    }
}

Digraph DIGRAPHinit (int V) {
    Vertex v;
    Digraph G = malloc (sizeof (digraph));
    G->V = V;
    G->A = 0;
    G->adj = malloc (V * sizeof (link));
    for (v = 0; v < G->V; v++)
        G->adj[v] = NULL;
    G->pre = malloc (V * sizeof (int));
    G->pos = malloc (V * sizeof (int));
    G->pai = malloc (V * sizeof (int));
    return G;
}

void DIGRAPHdestroy (Digraph G) {
    Vertex v;
    for (v = 0; v < G->V; v++)
        LISTdestroy (G->adj[v]);
    free (G->adj);
    free (G->pre);
    free (G->pos);
    free (G->pai);
    free (G);
}

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = LISTnewNode (w, G->adj[v]);
    G->A++;
}

void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) {
            a = LISTdestroyNode (a); 
            G->A--;
            return;
        }
}

void DIGRAPHshow (Digraph G) {
    Vertex v;
    link a;
    for (v = 0; v < G->V; v++) {
        printf ("%d:", v);
        for (a = G->adj[v]; a != NULL; a = a->next)
            printf (" %d",a->w);
        printf ("\n");
    }
}

int DIGRAPHindeg (Digraph G, Vertex v) {
    link a;
    Vertex w;
    int deg = 0;
    for (w = 0; w < G->V; w++) {
        if (v == w) continue;
        for (a = G->adj[w]; a != NULL; a = a->next)
            if (a->w == v) deg++;
    }
    return deg;
}

int DIGRAPHoutdeg (Digraph G, Vertex v) {
    link a;
    int deg = 0;
    for (a = G->adj[v]; a != NULL; a = a->next) deg++;
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
    link a;
    Vertex tmp;
    G->pre[v] = G->contapre++;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        Vertex w = a->w;
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

