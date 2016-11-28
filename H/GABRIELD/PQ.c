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

/* Este modulo implementa uma fila priorizada de vertices em um heap. 
 * O heap e' armazenado no vetor pq[1..N] */

#include <stdlib.h>
#include "PQ.h"

/* As prioridades sao dadas por um vetor prty indexado por vertices:
 * o vertice na posicao k de pq tem prty[pq[k]]. O heap e'
 * caracterizado pela propriedade prty[pq[k / 2] <= prty[pq[k]],
 * para k = 2, ... , N. Portanto o vertice pq[1] tem prioridade minima. */
#define greater(i, j) (prty[pq[i]] > prty[pq[j]] ? 1 : 0)

static Vertex *pq;
static int N;
static int *qp;

/* Recebe um indice k e transforma pq[1..k] num heap *
 * A funcao supoe que pq[1..k-1] ja e' um heap */
static void fixUp (int k, double prty[]);

/* Recebe um indice k e transforma pq[k..N] num heap *
 * A funcao supoe que pq[k+1..N] ja e' um heap */
static void fixDown (int k, double prty[]);

/* Troca pq[i] com pq[j] e ajusta o vetor qp. 
 * A funcao supoe que 1 <= i, j <= N */
static void exch (int i, int j);

void PQinit (int maxN) {
    pq = malloc ((maxN + 1) * sizeof (Vertex));
    qp = malloc (maxN * sizeof (int));
    N = 0;
}

int PQempty () {
    return N == 0;
}

void PQinsert (Vertex v, double prty[]) {
    qp[v] = ++N;
    pq[N] = v;
    fixUp (N, prty);
}

Vertex PQdelmin (double prty[]) {
    exch (1, N);
    --N;
    fixDown (1, prty);
    return pq[N + 1];
}

void PQdec (Vertex w, double prty[]) {
    fixUp (qp[w], prty);
}

void PQfree () {
    free (pq);
    free (qp);
}

static void fixUp (int k, double prty[]) {
    while (k > 1 && greater (k / 2, k)) {
        exch (k / 2, k);
        k /= 2;
    }
}

static void fixDown (int k, double prty[]) {
    int j;
    while (2 * k <= N) {
        j = 2 * k;
        if (j < N && greater (j, j + 1)) j++;
        if (!greater (k, j)) break;
        exch (k, j);
        k = j;;
    }
}

static void exch (int i, int j) {
    Vertex t;
    t = pq[i]; pq[i] = pq[j]; pq[j] = t;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

