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

#define maxV 100
static int conta, pre[maxV], prof;

/* Imprime na saida padrao o rastro de uma busca em profundidade 
 * no digrafo G. Cada linha da tabela registra o momento em que um arco 
 * é percorrido e a correspondente invocação de dfsR (), quando ocorre. */
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
 * imprimindo seu rastro. Guarda o tempo de descoberta conta no vetor global 
 * pre[0..maxV-1] e identa a chamada com base no inteiro global prof 
 * (a profundidade da chamada atual). */ 
static void dfsR (Digraph G, Vertex u) {
    List a;
    Vertex v;
    int i;
    pre[u] = conta++;
    prof++;
    for (a = G->adj[u]; a != NULL; a = a->next) {
        v = a->u;
        for (i = 0; i < prof; i++) printf ("  ");
        printf ("%d-%d", u, v);
        if (pre[v] == -1) {
            printf (" dfsR (G, %d)\n",v);
            dfsR (G, v);
        } else putchar ('\n');
    }
    prof--;
}

void DIGRAPHdfs (Digraph G) {
    Vertex u;
    
    conta = prof = 0;
    for (u = 0; u < G->V; u++)
        pre[u] = -1;

    for (u = 0; u < G->V; u++)
        if (pre[u] == -1) {
            printf ("dfsR (G, %d)\n", u);
            dfsR (G, u);
            putchar ('\n');
        }
}

