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
#ifndef _PQ_H
#define _PQ_H

/* Modulo responsavel pela implementacao de uma fila priorizada de vertices.
 * Vertices com menor prioridade ficam no topo. */

#define Vertex int

/* Inicializa uma fila priorizada vazia com tamanho maximo maxN */
void PQinit (int maxN);

/* Devolve 1 se a fila esta vazia e 0 caso contrario */
int PQempty ();

/* Insere o vertice v na fila priorizada, com base no vetor de prioridades
 * prty[]. A funcao supoe que prty[v] esta bem definido */
void PQinsert (Vertex v, double prty[]);

/* Remove e devolve o vertice de menor prioridade fila priorizada. 
 * A fila se ajusta novamente conforme o vetor prty[] */
Vertex PQdelmin (double prty[]);

/* Reajusta a prioridade do vertice w de acordo com o vetor prty[]. A funcao supoe
 * que prty[w] esta bem definido, que o vertice w esta na fila e que o novo valor de
 * prty[] e' menor ou igual ao anterior. */ 
void PQdec (Vertex w, double prty[]);

/* Desaloca a fila priorizada */
void PQfree ();

#endif

