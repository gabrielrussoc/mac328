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
// Data:       2016-11-27
// 
// Este arquivo faz parte da tarefa H
// da disciplina MAC0328.
// 
//////////////////////////////////////////////////////////////// */
#include "wDIGRAPHlists.h"
#include "PQ.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

/* Cria um novo no de lista encadeada 
 * com o vertice w, peso cst e proximo no' next. */
static link LISTnewNode (Vertex w, double cst, link next) {
    link a = malloc (sizeof (Node));
    a->w = w;
    a->cst = cst;
    a->next = next;
    return a;
}

/* Remove um no de lista encadeada e devolve o proximo
 * do mesmo. */
static link LISTdestroyNode (link l) {
    link aux = l;
    l = l->next;
    free (aux);
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
    G->pai = malloc (V * sizeof (Vertex));
    G->dist = malloc (V * sizeof (double));
    for (v = 0; v < G->V; v++)
        G->adj[v] = NULL;
    return G;
}

void DIGRAPHdestroy (Digraph G) {
    Vertex v;
    for (v = 0; v < G->V; v++)
        LISTdestroy (G->adj[v]);
    free (G->adj);
    free (G->pai);
    free (G->dist);
    free (G);
}

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, double cst) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) {
            a->cst = cst;
            return;
        }
    G->adj[v] = LISTnewNode (w, cst, G->adj[v]);
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
            printf (" (%d, %.2f)", a->w, a->cst);
        printf ("\n");
    }
}

/* Devolve um numero aleatorio no intervalo [cmin, cmax) */
static double randW (double cmin, double cmax) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * (cmax - cmin) + cmin;
}

Digraph DIGRAPHrand2 (int V, int A, double cmin, double cmax) { 
    Vertex v, w;
    double p = (double) A / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            if (v != w && rand () < p * (RAND_MAX + 1.0))
                DIGRAPHinsertA (G, v, w, randW (cmin, cmax));
    return G;
}

Digraph DIGRAPHinputArcs () {
    int V, A, u, v;
    double cst;
    Digraph G;
    scanf ("%d %d", &V, &A);
    G = DIGRAPHinit (V);
    while (A--) {
        scanf ("%d %d %lf", &u, &v, &cst);
        DIGRAPHinsertA (G, u, v, cst);
    }
    return G;
}

void DIGRAPHsptD0 (Digraph G, Vertex s) { 
    Vertex v, x = 0, y = 0;
    double min;
    link a;
    for (v = 0; v < G->V; v++) 
        G->pai[v] = -1, G->dist[v] = INFINITY;
    G->pai[s] = s, G->dist[s] = 0.0; 

    while (TRUE) {
        min = INFINITY;
        for (v = 0; v < G->V; v++) {
            if (G->pai[v] == -1) continue;
            for (a = G->adj[v]; a != NULL; a = a->next) {
                if (G->pai[a->w] == -1 && G->dist[v] + a->cst < min) {
                    min = G->dist[v] + a->cst;
                    x = v, y = a->w;
                }
            }
        }
        if (min == INFINITY) break;
        G->pai[y] = x, G->dist[y] = min;
    }
}

void DIGRAPHsptD1 (Digraph G, Vertex s) { 
    Vertex v, w, y = 0, z, *frj;
    link a;
    double min, c;
    
    frj = malloc (G->V * sizeof (Vertex));
    for (v = 0; v < G->V; v++)
        G->pai[v] = -1, G->dist[v] = INFINITY;
    G->pai[s] = s, G->dist[s] = 0.0;
    for (a = G->adj[s]; a != NULL; a = a->next) {
        G->dist[a->w] = a->cst;
        frj[a->w] = s;
    }

    while (TRUE) {
        min = INFINITY;
        for (z = 0; z < G->V; z++) 
            if (G->pai[z] == -1 && G->dist[z] < min)
                min = G->dist[y = z]; 
        if (min == INFINITY) break;
        G->pai[y] = frj[y];
        for (a = G->adj[y]; a != NULL; a = a->next) {
            w = a->w; c = a->cst;
            if (G->pai[w] == -1 && !(G->dist[y] + c >= G->dist[w])) {
                G->dist[w] = G->dist[y] + c;
                frj[w] = y; 
            } 
        }
    }
}

void DIGRAPHsptD2 (Digraph G, Vertex s) { 
    Vertex v, w, y, *frj;
    link a;
    double c;
    
    frj = malloc (G->V * sizeof (Vertex));
    for (v = 0; v < G->V; v++) {
        G->pai[v] = frj[v] = -1;
        G->dist[v] = INFINITY;
    }

    G->pai[s] = s, G->dist[s] = 0.0;
    PQinit (G->V);
    for (a = G->adj[s]; a != NULL; a = a->next) {
        G->dist[a->w] = a->cst;
        PQinsert (a->w, G->dist);
        frj[a->w] = s;
    }

    while (!PQempty ()) {
        y = PQdelmin (G->dist);
        G->pai[y] = frj[y]; 
        for (a = G->adj[y]; a != NULL; a = a->next) {
            w = a->w; c = a->cst;
            if (G->pai[w] != -1) continue;
            if (frj[w] == -1) {
                G->dist[w] = G->dist[y] + c;
                PQinsert (w, G->dist); 
                frj[w] = y; 
            } 
            else if (!(G->dist[y] + c >= G->dist[w])) {
                G->dist[w] = G->dist[y] + c;
                PQdec (w, G->dist); 
                frj[w] = y; 
            }
        }
    }
    PQfree ();
}

int checkDist (Digraph G, double dist[]) {
    link a;
    Vertex v;
    for (v = 0; v < G->V; v++)
        for (a = G->adj[v]; a != NULL; a = a->next)
            if (dist[v] + a->cst < dist[a->w])
                return FALSE;
    return TRUE;
}

Vertex *path (Vertex t, Vertex pai[]) {
    int size = 0, j = 0;
    Vertex v = t, *ans, aux;
    while (pai[v] != v) {
        size++;
        v = pai[v];
    }
    size++;
    ans = malloc (size * sizeof (Vertex));
    v = t;
    while (pai[v] != v) {
        ans[j++] = v;
        v = pai[v];
    }
    ans[j++] = v;
    for (j = 0; j < size / 2; j++) {
        aux = ans[j];
        ans[j] = ans[size - j - 1];
        ans[size - j - 1] = aux;
    }
    return ans;
}

