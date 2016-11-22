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
// Data:       2016-10-04
// 
// Este arquivo faz parte da tarefa G
// da disciplina MAC0328.
// 
//////////////////////////////////////////////////////////////// */

/* Biblioteca para manipulacao de digrafos.
 * As listas de adjacencia sao implementadas com
 * listas encadeadas. */

#ifndef _DIGRAPHLIST_H
#define _DIGRAPHLIST_H

#define Vertex int

typedef struct node {
    Vertex w;
    struct node *next;  
} Node;

typedef Node *link;

typedef struct {
    int V, A;
    int *pre, *pos, *sc, *pai, *dist;
    link *adj;
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

/* Gera um grafo aleatorio com vertices 0, 1, .., V-1 e E arestas em 
 * media */
Digraph GRAPHrand2 (int V, int E);

/* Devolve um vertice pertencente a algum ciclo do digrafo G ou -1
 * se este for aciclico. No primeiro caso, o ciclo pode ser facilmente 
 * encontrado com o vetor G->pai[]. No segundo, a ordenacao inversa
 * pode ser encontrada com o vetor G->pos[]. */
Vertex DIGRAPHcycleOrTopo (Digraph G);

/* Devolve um digrafo lido da entrada padrao 
 * Le um inteiro V, um inteiro A e A pares de inteiros
 * no intervalo 0..V-1, representando os arcos. */
Digraph DIGRAPHinputArcs ();
 
/* Devolve o inverso do digrafo G */
Digraph DIGRAPHreverse (Digraph G);

/* Devolve a quantidade de componentes fortes do digrafo G. A componente
 * de um vertice w esta representada no vetor G->sc[w]. Vale que 
 * 0 <= sc[w] < G->V.
 * Utiliza o algoritmo de Kosaraju-Saju. */
int DIGRAPHscKS (Digraph G);

/* Devolve 1 se o vertice s alcanca o vertice t no digrafo G.
 * A funcao supoe que 0 <= s,t < G->V. */
int DIGRAPHreach (Digraph G, Vertex s, Vertex t);

/* Devolve a quantidade de componentes fortes do digrafo G. A componente
 * de um vertice w esta representada no vetor G->sc[w]. Vale que 
 * 0 <= sc[w] < G->V.
 * AVISO: LENTO. */
int DIGRAPHsc (Digraph G);

/* Para cada vertice v do digrafo G, armazena em G->dist[v] a distancia de 
 * s a v. Tambem armazena em G->pai[v] o pai de v na arvore de distancias. */ 
void DIGRAPHdist (Digraph G, Vertex s);

/* Escolhe V pontos aleatorios no quadrado [0,1) x [0,1) e constroi um grafo
 * ligando por uma aresta os pontos que estiverem a distancia <= d um do outro.
 * */
Digraph GRAPHclosePoints (int V, double d);

/* Insere a aresta v-w no grafo G */
void GRAPHinsertE (Digraph G, Vertex v, Vertex w);

/* Para cada vertice v do grafo G, insere ate' k arestas da forma v-w, onde w
 * e escolhido aleatoriamente entre os demais vertices do grafo G */ 
void GRAPHaddRandEdges (Digraph G, int k);

/* Devolve a distancia media entre dos os vertices do grafo G. Caso o grafo seja
 * desconexo, devolve -1. */
double GRAPHsmallWorld (Digraph G);

#endif

