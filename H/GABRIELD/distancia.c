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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wDIGRAPHlists.h"

/* Devolve o diametro do digrafo com custos nos arcos G */
void diameter (Digraph G, int impl);

/* Devolve o maior valor de delta[x-y], onde delta[x-y] e' o
 * maior valor positivo que pode ser subtraido do custo de x-y sem que a SPT
 * representada por G->pai[] seja alterada. A funcao supoe que G->pai[] esta
 * calculada. */
void maxdelta (Digraph G);

/* Executa o algoritmo de Dijsktra a partir do vertice s.
 * Utiliza a implemetacao especificada por impl. */
void run_dijkstra (Digraph G, Vertex s, int impl);

int main (int argc, char **argv) {
    int V, A, impl, seed;
    Digraph G;
    Vertex s;

    if (argc != 6) {
        fprintf (stderr, "Uso: %s V A s impl seed\n", argv[0]);
        return EXIT_FAILURE;
    }

    V = atoi (argv[1]);
    A = atoi (argv[2]);
    s = atoi (argv[3]);
    impl = atoi (argv[4]);
    seed = atoi (argv[5]);

    srand (seed);
    G = DIGRAPHrand2 (V, A, 0, 1);
    if (V < 30) DIGRAPHshow (G);
    run_dijkstra (G, s, impl);

    if (!checkDist (G, G->dist)) {
        fprintf (stderr, "Implementacao %d nao gera um potencial!\n", impl);
        return EXIT_FAILURE;
    }

    maxdelta (G);
    diameter (G, impl);
    
    DIGRAPHdestroy (G);

    return EXIT_SUCCESS;
}

void diameter (Digraph G, int impl) {
    double ans = 0;
    Vertex v, w, s = -1, t = -1, *way;
    int j = 0, size = 0;
    for (v = 0; v < G->V; v++) {
        run_dijkstra (G, v, impl);
        for (w = 0; w < G->V; w++)
            if (G->dist[w] > ans) {
                ans = G->dist[w];
                s = v;
                t = w;
            }
    }
    printf ("Diametro: %.2f\n", ans);
    if (ans != INFINITY) {
        run_dijkstra (G, s, impl);
        way = path (t, G->pai);
        for (j = 0; way[j] != t; j++) size++; 
        if (size < 30) {
            for (j = 0; j < size; j++) printf ("%d->", way[j]);
            printf ("%d\n", t);
        }
        free (way);
    }
}

void maxdelta (Digraph G) {
    Vertex v, x, y;
    link a;
    double ans = 0;
    x = y = -1;
    for (v = 0; v < G->V; v++)
        for (a = G->adj[v]; a != NULL; a = a->next)
            if (a->cst - G->dist[a->w] + G->dist[v] > ans) {
                ans = a->cst - G->dist[a->w] + G->dist[v];
                x = v; y = a->w;
            }
    printf ("Maior delta: %.2f", ans);
    if (x != -1 && y != -1) printf (" (arco %d-%d)", x, y);
    putchar ('\n');
}

void run_dijkstra (Digraph G, Vertex s, int impl) {
    switch (impl) {
        case 0:
            DIGRAPHsptD0 (G, s);
            break;
        case 1:
            DIGRAPHsptD1 (G, s);
            break;
        case 2:
            DIGRAPHsptD2 (G, s);
            break;
        default:
            DIGRAPHsptD2 (G, s);
            break;
    }
}

