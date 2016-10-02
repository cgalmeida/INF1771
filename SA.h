#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double custo(char** matriz,int linha,int coluna);

char** mat_cria (int m, int n);

void mat_libera (int m, char** A);

void imprime( int m, int n, char** A);

void SA(char** M,int l,int c, int iteracoes);

