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

/* Biblioteca para manipulacao de digrafos.
 * As listas de adjacencia sao implementadas com matrizes */

#ifndef _DIGRAPHMATRIX_H
#define _DIGRAPHMATRIX_H

#define Vertex int

typedef struct {
    int V, A, **adj;
    int *pre, *pos, *pai;
    int contapre, contapos;
} digraph;

typedef digraph *Digraph;

/* Constroi um digrafo com vertices 0, 1, .., V-1 e nenhum arco. */
Digraph DIGRAPHinit (int V);

/* Destroi o digrafo G. */
void DIGRAPHdestroy (Digraph G);

/* Insere o arco v-w no digrafo G com vertices 0, 1, .., V-1.
 * A funcao assume que v != w e que 0 <= v,w < V.
 * Se o arco ja existe, a funcao nao faz nada. */
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w);

/* Remove o arco v-w do digrafo G com vertices 0, 1, .., V-1.
 * A funcao assume que v != w e que 0 <= v,w < V.
 * Se o arco nao existe, a funcao nao faz nada. */
void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w);

/* Imprime na saida padrao, para cada vertice v do digrafo G, em uma 
 * linha, todos os vertices adjacentes a v. */
void DIGRAPHshow (Digraph G);

/* Calcula o grau de entrada do vertice u no digrafo G com vertices
 * 0, 1, .., V-1. A funcao assume que 0 <= v < V. */
int DIGRAPHindeg (Digraph G, Vertex v);

/* Calcula o grau de saida do vertice u no digrafo G com vertices.
 * 0, 1, .., V-1. A funcao assume que 0 <= v < V. */
int DIGRAPHoutdeg (Digraph G, Vertex v);

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

/* Devolve um vertice pertencente a algum ciclo do digrafo G ou -1
 * se este for aciclico. No primeiro caso, o ciclo pode ser facilmente 
 * encontrado com o vetor G->pai[]. No segundo, a ordenacao inversa
 * pode ser encontrada com o vetor G->pos[]. */
Vertex DIGRAPHcycleOrTopo (Digraph G);

#endif

