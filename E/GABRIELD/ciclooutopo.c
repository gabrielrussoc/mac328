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

/* O programa le um digrafo G da entrada padrao e imprime seus vertices em
 * ordem topologica ou exibe um ciclo de G. */

#include <stdio.h>
#include "DIGRAPHmatrix.h"

/* Imprime os vertices do digrafo G em ordenacao topologica. 
 * A funcao supoe que a ordenacao existe e que cycleOrTopo tenha
 * sido invocada previamente. */
void printTopo (Digraph G);

/* Imprime um ciclo do digrafo G que contem v.
 * A funcao supoe que o ciclo existe e que cycleOrTopo tenha
 * sido invocada previamente e que 0 <= v < G-> V. */
void printCycle (Digraph G, Vertex v);

int main() {
    int V, A, i;
    Vertex v, w;
    Digraph G;

    scanf ("%d %d", &V, &A);
    G = DIGRAPHinit (V);
    for (i = 0; i < A; i++) {
        scanf ("%d %d", &v, &w);
        DIGRAPHinsertA (G, v, w);
    }

    v = DIGRAPHcycleOrTopo (G);
    if (v == -1) printTopo (G);
    else printCycle (G, v);

    return 0;
}

void printTopo (Digraph G) {
    int cont;
    Vertex v;
    cont = G->V-1;
    printf ("Vertices em ordem topologica: ");
    while (cont >= 0) {
        for (v = 0; v < G->V; v++)
            if (G->pos[v] == cont) {
                printf ("%d ",v);
                break;
            }
        cont--;
    }
    putchar ('\n');
}

/* Imprime um ciclo do digrafo G que comeca em v e termina em first.
 * A funcao supoe que tal ciclo existe, que cycleOrTopo tenha sido
 * invocada previamente e que 0 <= v,first < G->V.*/
static void printCycleR (Digraph G, Vertex v, Vertex first) {
    if (G->pai[v] != first)
        printCycleR (G, G->pai[v], first);
    if (v == first) printf ("%d\n", v);
    else printf ("%d->", v);
}

void printCycle (Digraph G, Vertex v) {
    printf ("Ciclo: ");
    printf ("%d->", v);
    printCycleR (G, v, v);
}


