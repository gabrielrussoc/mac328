/* Autor:      Gabriel de Russo e Carmo
// Numero USP: 9298041
// Sigla:      GABRIELD
// Data:       2016-08-18
// Tarefa D - MAC0328 */
#include <stdio.h>
#include "DIGRAPHlists.h"

#define maxV 123
static int pre[maxV], instack[maxV], conta, prof;

/* Realiza uma busca em profundidade no digrafo G
a partir do vértice u, imprimindo seu rastro e classificando
os arcos encontrados. */
static void dfsR (Digraph G, Vertex u) {
    List a;
    Vertex v;
    int i;
    pre[u] = conta++;
    instack[u] = 1;
    prof++;
    for (a = G->adj[u]; a != NULL; a = a->next) {
        v = a->u;
        for (i = 0; i < prof - 1; i++) printf ("  ");
        printf ("%d-%d ", u, v);
        if (pre[v] == -1) {
            puts ("floresta");
            dfsR (G, v);
        } else {
            if (pre[v] > pre[u]) puts ("descendente");
            else {
                if (instack[v]) puts ("retorno");
                else puts ("cruzado");
            }
        }
    }
    instack[u] = 0;
    prof--;
}

/* Realiza uma busca em profundiade no digrafo G, imprimindo seu rastro
e classificando seus arcos. */
void DIGRAPHdfs (Digraph G) {
    Vertex u;
    for (u = 0; u < G->V; u++) {
        pre[u] = -1;
        instack[u] = 0;
    }
    conta = prof = 0;
    for (u = 0; u < G->V; u++)
        if (pre[u] == -1)
            dfsR (G, u);
}
