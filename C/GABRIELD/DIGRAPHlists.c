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
// Data:       2016-08-15
// 
// Este arquivo faz parte da tarefa C
// da disciplina MAC0328.
// 
//////////////////////////////////////////////////////////////// */

#include "DIGRAPHlists.h"
#include <stdio.h>
#include <stdlib.h>

/* Cria um novo no de lista encadeada 
 * com o vertice u no conteudo e proximo no next. */
static List LISTnewNode (Vertex u, List next) {
    List a = malloc (sizeof (Node));
    a->u = u;
    a->next = next;
    return a;
}

/* Remove um no de lista encadeada e devolve o proximo
 * do mesmo. */
static List LISTdestroyNode (List l) {
    List aux = l;
    l = l->next;
    free(aux);
    return l;
}

/* Destroi uma lista encadeada */
static void LISTdestroy (List l) {
    List aux;
    while (l != NULL) {
        aux = l;
        l = l->next;
        free (aux);
    }
}

Digraph DIGRAPHinit (int V) {
    Vertex u;
    Digraph G = malloc (sizeof (digraph));
    G->V = V;
    G->A = 0;
    G->adj = malloc (V * sizeof (List));
    for (u = 0; u < G->V; u++)
        G->adj[u] = NULL;
    return G;
}

void DIGRAPHdestroy (Digraph G) {
    Vertex u;
    for (u = 0; u < G->V; u++)
        LISTdestroy (G->adj[u]);
    free (G->adj);
    free (G);
}

void DIGRAPHinsertA (Digraph G, Vertex u, Vertex v) {
    List a;
    for (a = G->adj[u]; a != NULL; a = a->next)
        if (a->u == v) return;
    G->adj[u] = LISTnewNode (v, G->adj[u]);
    G->A++;
}

void DIGRAPHremoveA (Digraph G, Vertex u, Vertex v) {
    List a;
    for (a = G->adj[u]; a != NULL; a = a->next)
        if (a->u == v) {
            a = LISTdestroyNode (a); 
            G->A--;
            return;
        }
}

void DIGRAPHshow (Digraph G) {
    Vertex u;
    List a;
    for (u = 0; u < G->V; u++) {
        printf ("%d:", u);
        for (a = G->adj[u]; a != NULL; a = a->next)
            printf (" %d",a->u);
        printf ("\n");
    }
}

int DIGRAPHindeg (Digraph G, Vertex u) {
    List a;
    Vertex v;
    int deg = 0;
    for (v = 0; v < G->V; v++) {
        if (u == v) continue;
        for (a = G->adj[v]; a != NULL; a = a->next)
            if (a->u == u) deg++;
    }
    return deg;
}

int DIGRAPHoutdeg (Digraph G, Vertex u) {
    List a;
    int deg = 0;
    for (a = G->adj[u]; a != NULL; a = a->next) deg++;
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

