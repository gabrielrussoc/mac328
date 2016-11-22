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
#include <stdio.h>
#include "DIGRAPHlists.h"

int main (int argc, char **argv) {
    int V, k;
    double d, avg;
    Digraph G;
    printf ("> ");
    while (scanf ("%d", &V) && V != -1) {
        scanf ("%lf %d", &d, &k);
        G = GRAPHclosePoints (V, d);
        GRAPHaddRandEdges (G, k);
        avg = GRAPHsmallWorld (G);
        printf ("distancia media: ");
        if (avg == -1) puts ("infinito");
        else printf ("%.1f\n", avg);
        printf ("> ");
    }
    return 0;
}

