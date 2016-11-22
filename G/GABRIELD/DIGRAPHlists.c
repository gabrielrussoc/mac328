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

#include "DIGRAPHlists.h"
#include <stdio.h>
#include <stdlib.h>

/* Globais auxiliares */
static int contapre, contapos;

/* Cria um novo no de lista encadeada 
 * com o vertice w no conteudo e proximo no next. */
static link LISTnewNode (Vertex w, link next) {
    link a = malloc (sizeof (Node));
    a->w = w;
    a->next = next;
    return a;
}

/* Remove um no de lista encadeada e devolve o proximo
 * do mesmo. */
static link LISTdestroyNode (link l) {
    link aux = l;
    l = l->next;
    free(aux);
    return l;
}

/* Destroi uma lista encadeada */
static void LISTdestroy (link l) {
    link aux;
    while (l != NULL) {
        aux = l;
        l = l->next;
        free (aux);
    }
}

Digraph DIGRAPHinit (int V) {
    Vertex v;
    Digraph G = malloc (sizeof (digraph));
    G->V = V;
    G->A = 0;
    G->adj = malloc (V * sizeof (link));
    for (v = 0; v < G->V; v++)
        G->adj[v] = NULL;
    G->pre = malloc (V * sizeof (int));
    G->pos = malloc (V * sizeof (int));
    G->pai = malloc (V * sizeof (int));
    G->sc = malloc (V * sizeof (int));
    G->dist = malloc (V * sizeof (int));
    return G;
}

void DIGRAPHdestroy (Digraph G) {
    Vertex v;
    for (v = 0; v < G->V; v++)
        LISTdestroy (G->adj[v]);
    free (G->adj);
    free (G->pre);
    free (G->pos);
    free (G->pai);
    free (G->sc);
    free (G->dist);
    free (G);
}

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = LISTnewNode (w, G->adj[v]);
    G->A++;
}

void DIGRAPHremoveA (Digraph G, Vertex v, Vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) {
            a = LISTdestroyNode (a); 
            G->A--;
            return;
        }
}

void DIGRAPHshow (Digraph G) {
    Vertex v;
    link a;
    for (v = 0; v < G->V; v++) {
        printf ("%d:", v);
        for (a = G->adj[v]; a != NULL; a = a->next)
            printf (" %d",a->w);
        printf ("\n");
    }
}

int DIGRAPHindeg (Digraph G, Vertex v) {
    link a;
    Vertex w;
    int deg = 0;
    for (w = 0; w < G->V; w++) {
        if (v == w) continue;
        for (a = G->adj[w]; a != NULL; a = a->next)
            if (a->w == v) deg++;
    }
    return deg;
}

int DIGRAPHoutdeg (Digraph G, Vertex v) {
    link a;
    int deg = 0;
    for (a = G->adj[v]; a != NULL; a = a->next) deg++;
    return deg;
}

/* Devolve um vertice aleatorio do digrafo G. */
static Vertex randV (Digraph G) {
    double r;
    r = rand () / (RAND_MAX + 1.0);
    return r * G->V;
}

Digraph DIGRAPHrand1 (int V, int A) { 
    Vertex v, w;
    Digraph G = DIGRAPHinit (V);
    while (G->A < A) {
        v = randV (G);
        w = randV (G);
        if (v != w) 
            DIGRAPHinsertA (G, v, w);
    }
    return G;
}

Digraph DIGRAPHrand2 (int V, int A) { 
    Vertex v, w;
    double p = (double) A / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = 0; w < V; w++)
            if (v != w && rand () < p * (RAND_MAX + 1.0))
                DIGRAPHinsertA (G, v, w);
    return G;
}

Digraph GRAPHrand1 (int V, int E) { 
    Vertex v, w;
    Digraph G = DIGRAPHinit (V);
    while (G->A < 2 * E) {
        v = randV (G);
        w = randV (G);
        if (v != w) {
            DIGRAPHinsertA (G, v, w);
            DIGRAPHinsertA (G, w, v);
        }
    }
    return G;
}

Digraph GRAPHrand2 (int V, int E) { 
    Vertex v, w;
    double p = (double) (2 * E) / V / (V-1);
    Digraph G = DIGRAPHinit (V);
    for (v = 0; v < V; v++)
        for (w = v + 1; w < V; w++)
            if (rand () < p * (RAND_MAX + 1.0)) {
                DIGRAPHinsertA (G, v, w);
                DIGRAPHinsertA (G, w, v);
            }
    return G;
}

/* Busca um ciclo em G a partir do vertice v. Devolve
 * um vertice de um ciclo ou -1 se nenhum for encontrado. */
static Vertex cycleR (Digraph G, Vertex v) { 
    link a;
    Vertex tmp;
    G->pre[v] = contapre++;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        Vertex w = a->w;
        if (G->pre[w] == -1) {
            G->pai[w] = v;
            tmp = cycleR (G, w);
            if (tmp != -1) return tmp;
        } else { 
            if (G->pos[w] == -1) {
                G->pai[w] = v;
                return w;
            }
        }
    }
    G->pos[v] = contapos++;
    return -1;
}

Vertex DIGRAPHcycleOrTopo (Digraph G) {
    Vertex v, tmp;
    contapre = contapos = 0;
    for (v = 0; v < G->V; v++)
        G->pre[v] = G->pos[v] = -1;
    for (v = 0; v < G->V; v++)
        if (G->pre[v] == -1) {
            G->pai[v] = v;
            tmp = cycleR (G, v);
            if (tmp != -1) return tmp;
        }
    return -1; 
}


Digraph DIGRAPHinputArcs () {
    int V, A, u, v;
    Digraph G;
    scanf ("%d %d", &V, &A);
    G = DIGRAPHinit (V);
    while (A--) {
        scanf ("%d %d", &u, &v);
        DIGRAPHinsertA (G, u, v);
    }
    return G;
}

/* Realiza uma busca em profundidade no digrafo G a partir do vertice v.
 * A funcao utiliza as variaveis globais contapre e contapos para
 * calcular e armazenar a pre e pos-ordem nos vetores G->pre[] e G->pos[].
 * Supoe que um vertice w foi descoberto se G->pre[w] >= 0. */
static void dfsR (Digraph G, Vertex v) {
    link a;
    Vertex w;
    G->pre[v] = contapre++;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        w = a->w;
        if (G->pre[w] == -1)
            dfsR (G, w);
    }
    G->pos[v] = contapos++;
}

Digraph DIGRAPHreverse (Digraph G) {
    link a;
    Vertex v, w;
    Digraph GR = DIGRAPHinit (G->V);
    for (v = 0; v < G->V; v++)
        for (a = G->adj[v]; a != NULL; a = a->next) {
            w = a->w;
            DIGRAPHinsertA (GR, w, v);
        }
    return GR;
}

/* Atribui o rótulo k a todo vértice w que é acessível a partir de v 
 * e ainda não foi rotulado. Os rótulos são armazenados no vetor G->sc[]. 
 * Um vértice w é considerado rotulado se G->sc[w] >= 0. */
static void dfsRsc (Digraph G, Vertex v, int k) {
    link a;
    Vertex w;
    G->sc[v] = k;
    for (a = G->adj[v]; a != NULL; a = a->next) {
        w = a->w;
        if (G->sc[w] == -1)
            dfsRsc (G, w, k);
    }
}
    
int DIGRAPHscKS (Digraph G) {
    int k, i, *ord;
    Vertex v;
    Digraph GR;
    ord = malloc (G->V * sizeof (int));
    contapre = contapos = k = 0;
    GR = DIGRAPHreverse (G);
    for (v = 0; v < GR->V; v++) GR->pre[v] = -1;
    for (v = 0; v < GR->V; v++)
        if (GR->pre[v] == -1)
            dfsR (GR, v);
    for (v = 0; v < GR->V; v++) ord[GR->pos[v]] = v;
    for (v = 0; v < G->V; v++) G->sc[v] = -1;
    for (i = G->V - 1; i >= 0; i--) {
        v = ord[i];
        if (G->sc[v] == -1) {
            dfsRsc (G, v, k);
            k++;
        } 
    }
    DIGRAPHdestroy (GR);
    free (ord);
    return k;
}

int DIGRAPHreach (Digraph G, Vertex s, Vertex t) {
    Vertex v;
    for (v = 0; v < G->V; v++) G->pre[v] = -1;
    contapre = 0;
    dfsR (G, s);
    return G->pre[t] != -1; 
}

int DIGRAPHsc (Digraph G) {
    Vertex v, w; 
    int k = 0;
    for (v = 0; v < G->V; v++) 
        G->sc[v] = -1;
    for (v = 0; v < G->V; v++) {
        if (G->sc[v] == -1) {
            G->sc[v] = k++;
            for (w = v + 1; w < G->V; w++) 
                if (DIGRAPHreach (G, v, w) && DIGRAPHreach (G, w, v))
                    G->sc[w] = G->sc[v];
        }
    }
    return k;
}   

void DIGRAPHdist (Digraph G, Vertex s) {
    Vertex v, w, *queue;
    link a;
    int front, rear; 
    const int INF = G->V;
    for (v = 0; v < G->V; v++) G->dist[v] = INF;
    queue = malloc (G->V * sizeof (Vertex));
    front = rear = 0;
    G->dist[s] = 0;
    G->pai[s] = s;
    queue[rear++] = s;
    while (front < rear) {
        v = queue[front++];
        for (a = G->adj[v]; a != NULL; a = a->next) {
            w = a->w;
            if (G->dist[w] == INF) {
                G->dist[w] = G->dist[v] + 1;
                G->pai[w] = v;
                queue[rear++] = w;
            }
        }
    }
    free (queue);
}

/* Recebe x e devolve seu quadrado */
static double sq (double x) {
    return x * x;
}

Digraph GRAPHclosePoints (int V, double d) {
    double *x, *y;
    int i, j;
    Digraph G = DIGRAPHinit (V);
    x = malloc (V * sizeof (double));
    y = malloc (V * sizeof (double));
    for (i = 0; i < V; i++) {
        x[i] = rand () / (RAND_MAX + 1.0);
        y[i] = rand () / (RAND_MAX + 1.0);
    }
    for (i = 0; i < V; i++)
        for (j = i + 1; j < V; j++)
            if (sq (x[i] - x[j]) + sq (y[i] - y[j]) <= sq (d))
                GRAPHinsertE (G, i, j);
    return G;
}

void GRAPHinsertE (Digraph G, Vertex v, Vertex w) {
    DIGRAPHinsertA (G, v, w);
    DIGRAPHinsertA (G, w, v);
}

void GRAPHaddRandEdges (Digraph G, int k) {
    Vertex v, w;
    int p;
    for (v = 0; v < G->V; v++)
        for (p = 0; p < k; p++) {
            do {
                w = randV (G);
            } while (w == v);
            GRAPHinsertE (G, v, w);
        }
}

double GRAPHsmallWorld (Digraph G) {
    Vertex v, w;
    double avg = 0;
    const int INF = G->V;
    for (v = 0; v < G->V; v++) {
        DIGRAPHdist (G, v);
        for (w = v + 1; w < G->V; w++) {
            if (G->dist[w] == INF) return -1;
            avg += G->dist[w];
        }
    }
    return avg / (.5 * (G->V * (G->V - 1)));
}

