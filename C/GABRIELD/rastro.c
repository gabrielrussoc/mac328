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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DIGRAPHlists.h"

/* O programa recebe dois inteiros da linha de comando: V e A. 
 * Gera um digrafo aleatorio com V vertices e A arcos e realiza uma
 * busca em profundidade neste, imprimindo seu rastro e os vertices em
 * pre-ordem na saida padrao. 
 * Se o digrafo for a ser gerado for denso, o programa gera um digrafo com
 * A arcos em media. */

/* Imprime na saida padrao o rastro de uma busca em profundidade 
 * no digrafo G, assim como seus vertices em pre-ordem. */
void DIGRAPHdfs (Digraph G);
    
int main (int argc, char **argv) {
    int V, A;
    Digraph G;
    
    V = atoi (argv[1]);
    A = atoi (argv[2]);

    srand (time (NULL));
    if (A <= (V * V) / 10)
        G = DIGRAPHrand1 (V, A);
    else 
        G = DIGRAPHrand2 (V, A);
    DIGRAPHdfs (G);
    
    DIGRAPHdestroy(G);
    
    return 0;    
}

/* Realiza uma busca em profundidade no grafo G a partir do vertice u, 
 * imprimindo seu rastro. Guarda o tempo de descobrimento t no vetor 
 * pre[0..G->V-1] e identa a chamada com base no inteiro dep (a profundidade 
 * da chamada atual). */ 
static void dfsR (Digraph G, Vertex u, int *pre, int dep, int *t) {
    List a;
    Vertex v;
    int i;
    pre[u] = (*t)++;
    for (i = 0; i < dep; i++) printf  ("|  ");
    printf ("DFS (%d)\n",u);
    for (a = G->adj[u]; a != NULL; a = a->next) {
        v = a->u;
        if (pre[v] == -1)
            dfsR (G, v, pre, dep + 1, t);
    }
    for (i = 0; i < dep; i++) printf  ("|  ");
    printf ("FIM (%d)\n", u);
}

void DIGRAPHdfs (Digraph G) {
    Vertex u;
    int t = 0;
    int *aux = malloc (G->V * sizeof (int));
    int *pre = malloc (G->V * sizeof (int));

    printf ("Digrafo com %d vértices e %d arcos.\n\n", G->V, G->A);
    
    for (u = 0; u < G->V; u++)
        pre[u] = -1;
    for (u = 0; u < G->V; u++)
        if (pre[u] == -1)
            dfsR (G, u, pre, 0, &t);

    for (u = 0; u < G->V; u++) aux[pre[u]] = u;
    printf ("\nVértices em pré-ordem:\n");
    for (u = 0; u < G->V; u++) printf ("%d ", aux[u]);
    putchar ('\n');

    free (pre);
    free (aux);
}

