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

/* Biblioteca para manipulacao de digrafos.
 * As listas de adjacencia sao implementadas com
 * listas encadeadas. */

#ifndef _WDIGRAPHLIST_H
#define _WDIGRAPHLIST_H

#define Vertex int

typedef struct node {
    Vertex w;
    double cst;
    struct node *next;  
} Node;

typedef Node *link;

typedef struct {
    int V, A;
    link *adj;
    Vertex *pai;
    double *dist;
} digraph;

typedef digraph *Digraph;

/* Constroi um digrafo com vertices 0, 1, .., V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V);

/* Destroi o digrafo G. */
void DIGRAPHdestroy (Digraph G);

/* Insere o arco v-w com custo cst no digrafo G com vertices 0, 1, .., V-1.
 * A funcao assume que v != w e que 0 <= v,w < V.
 * Se o arco ja existe, a funcao atualiza seu custo. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, double cst);

/* Remove o arco v-w do digrafo G com vertices 0, 1, .., V-1.
 * A funcao assume que v != w e que 0 <= v,w < V.
 * Se o arco nao existe, a funcao nao faz nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w);

/* Imprime na saida padrao, para cada vertice v do digrafo G, todos os arcos
 * v-w no formato (w, cst), onde w e' outro vertice e cst o custo do arco. */
void DIGRAPHshow (Digraph G);

/* Gera um digrafo aleatorio com vertices 0, 1, .., V-1 e A arcos em 
 * media. Os custos dos arcos sao aleatorios no intervalo [cmin, cmax). */
Digraph DIGRAPHrand2 (int V, int A, double cmin, double cmax);

/* Le da entrada padrao um digrafo com custos nos arcos da seguinte forma
 * V A
 * v1 w1 c1
 * ...
 * vA wA cA
 * onde V e' o numero de vertices, A e' o numero de arcos e cada arco vi-wi
 * tem custo ci. 
 * A funcao supoe que 0 <= vi, wi < V.
 * Devolve o digrafo descrito */ 
Digraph DIGRAPHinputArcs ();

/* Recebe um digrafo G com custos positivos nos arcos e um vértice s. 
 * Calcula uma SPT com raiz s e armazena a SPT no vetor G->pai[].
 * As distâncias a partir de s são armazenadas no vetor G->dist[]. 
 * (Se um vértice v não está ao alcance de s, pai[v] vale -1.) */
void DIGRAPHsptD0 (Digraph G, Vertex s); 

/* Recebe um digrafo G com custos positivos nos arcos e um vértice s. 
 * Calcula uma SPT com raiz s e armazena a SPT no vetor G->pai[].
 * As distâncias a partir de s são armazenadas no vetor G->dist[]. 
 * (Se um vértice v não está ao alcance de s, pai[v] vale -1.) */
void DIGRAPHsptD1 (Digraph G, Vertex s); 

/* Recebe um digrafo G com custos positivos nos arcos e um vértice s. 
 * Calcula uma SPT com raiz s e armazena a SPT no vetor G->pai[].
 * As distâncias a partir de s são armazenadas no vetor G->dist[]. 
 * (Se um vértice v não está ao alcance de s, pai[v] vale -1.) */
void DIGRAPHsptD2 (Digraph G, Vertex s);

/* Recebe um digrafo G com custos positivos nos arcos e um vetor suposto
 * vetor de distancias dist (a partir de algum vertice). Devolve 1 se o vetor
 * representa um potencial e 0 c.c */
int checkDist (Digraph G, double dist[]);

/* Receba um vertice t e uma arvore radicada T representada por um vetor de pais.
 * Devolve um vetor contendo a sequencia de vertices de um caminho que começa na 
 * raiz de T e termina em t. Supoe que t esta em T. */
Vertex *path (Vertex t, Vertex pai[]);

#endif

