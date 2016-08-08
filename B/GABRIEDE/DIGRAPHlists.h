#ifndef _DIGRAPHLIST_H
#define _DIGRAPHLIST_H

#define Vertex int

typedef struct node {
    Vertex u;
    struct node *next;  
} Node;

typedef Node *List;

typedef struct {
    int V, A;
    List *adj;
} digraph;

typedef digraph *Digraph;

/* Constroi um digrafo com vertices 0, 1, .., V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V);

/* Destroi o digrafo G. */
void DIGRAPHdestroy (Digraph G);

/* Insere o arco u-v no digrafo G com vertices 0, 1, .., V-1.
 * A funcao assume que u != v e que 0 <= u,v < V.
 * Se o arco ja existe, a funcao nao faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex u, Vertex v);

/* Remove o arco u-v do digrafo G com vertices 0, 1, .., V-1.
 * A funcao assume que u != v e que 0 <= u,v < V.
 * Se o arco nao existe, a funcao nao faz nada. */
void DIGRAPHremoveA (Digraph G, Vertex u, Vertex v);

/* Imprime na saida padrao, para cada vertice v do digrafo G, em uma 
 * linha, todos os vertices adjacentes a v. */
void DIGRAPHshow (Digraph G);

/* Calcula o grau de entrada do vertice u no digrafo G com vertices
 * 0, 1, .., V-1. A funcao assume que 0 <= u < V. */
int DIGRAPHindeg (Digraph G, Vertex u);

/* Calcula o grau de saida do vertice u no digrafo G com vertices.
 * 0, 1, .., V-1. A funcao assume que 0 <= u < V. */
int DIGRAPHoutdeg (Digraph G, Vertex u);

/* Gera um digrafo aleatorio com vertices 0, 1, .., V-1 e A arcos. */
Digraph DIGRAPHrand1 (int V, int A);

/* Gera um digrafo aleatorio com vertices 0, 1, .., V-1 e A arcos em 
 * media. */
Digraph DIGRAPHrand2 (int V, int A);

/* Gera um grafo aleatorio com vertices 0, 1, .., V-1 e E arestas. */
Digraph GRAPHrand1 (int V, int E);

/* Geraum grafo aleatorio com vertices 0, 1, .., V-1 e E arestas em 
 * media */
Digraph GRAPHrand2 (int V, int E);

#endif

