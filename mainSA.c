#include"SA.h"
#include<stdlib.h>
#include<stdio.h>
#include<math.h>




int main(void){
	char** matriz = mat_cria(10,5);
	double a;
	matriz[0][0] = 0;matriz[0][1] = 1;matriz[0][2] = 0;matriz[0][3] = 1;matriz[0][4] = 1;
	matriz[1][0] = 0;matriz[1][1] = 0;matriz[1][2] = 1;matriz[1][3] = 1;matriz[1][4] = 1;
	matriz[2][0] = 0;matriz[2][1] = 0;matriz[2][2] = 1;matriz[2][3] = 1;matriz[2][4] = 1;
	matriz[3][0] = 0;matriz[3][1] = 0;matriz[3][2] = 1;matriz[3][3] = 1;matriz[3][4] = 1;
	matriz[4][0] = 1;matriz[4][1] = 1;matriz[4][2] = 0;matriz[4][3] = 0;matriz[4][4] = 0;
	matriz[5][0] = 1;matriz[5][1] = 1;matriz[5][2] = 0;matriz[5][3] = 0;matriz[5][4] = 0;
	matriz[6][0] = 1;matriz[6][1] = 1;matriz[6][2] = 0;matriz[6][3] = 0;matriz[6][4] = 0;
	matriz[7][0] = 1;matriz[7][1] = 0;matriz[7][2] = 1;matriz[7][3] = 0;matriz[7][4] = 0;
	matriz[8][0] = 0;matriz[8][1] = 1;matriz[8][2] = 1;matriz[8][3] = 0;matriz[8][4] = 0;
	matriz[9][0] = 1;matriz[9][1] = 0;matriz[9][2] = 0;matriz[9][3] = 1;matriz[9][4] = 0;
	
	SA(matriz,10,5,99999999);
	printf("Busca finalizada\n");

	return 0;
}
#include"SA.h"

double Melhor=999;

static double prob(double variacao,double custoAtual){
	double p;
	if(variacao < 0)
		p = 1;
	else
		p = exp( -variacao / custoAtual );
	return p;

}

static void geraVizinho(char** matriz,int l,int c){
	char aux;
	int sorteiaLinha;
	int sorteiaColuna; 
	int auxAleatorio;

	while( 1 ){	
	sorteiaLinha = rand()%l;
	sorteiaColuna = rand()%c;
	auxAleatorio = rand()%l;
	while(auxAleatorio == sorteiaLinha){
		auxAleatorio = rand()%l;
	}	
	aux = matriz[sorteiaLinha][sorteiaColuna];
	matriz[sorteiaLinha][sorteiaColuna] = matriz[auxAleatorio][sorteiaColuna];
	matriz[auxAleatorio][sorteiaColuna] = aux;
	if( verificaConsistencia(matriz,l,c) == 0 )
			return;
	}
}

static void copiaMatriz(char** essa,char** nessa,int linha,int coluna){
	int i,j;
	for(i=0;i<linha;i++){
		for(j=0;j<coluna;j++){
			nessa[i][j] = essa[i][j];
		}
	}
}

static int verificaConsistencia(char** matriz,int l,int c){
	int i,j;
	int aux = 0;
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			if(matriz[i][j] == 1)
				aux++;
		}
		if( aux == 0)
			return 1; //Inconsistente
		aux = 0;
	}
	return 0;
}


double custo(char** matriz,int linha,int coluna ){
	double soma=0;
	double total=0;
	int i,j;
	for(i=0;i<linha;i++){
		for(j=0;j<coluna;j++){
			if(matriz[i][j] == 1 ){
				switch(j){
					case 0:
						soma+=1.5;break;
					case 1:
						soma+=1.4;break;
					case 2:
						soma+=1.3;break;
					case 3:
						soma+=1.2;break;
					case 4:
						soma+=1.1;break;
				}
			}
		}
		switch(i){
			case 0:
				total += 150/soma;break;
			case 1:
				total += 140/soma;break;
			case 2:
				total += 130/soma;break;
			case 3:
				total += 120/soma;break;
			case 4:
				total += 110/soma;break;
			case 5:
				total += 100/soma;break;
			case 6:
				total += 95/soma;break;
			case 7:
				total += 90/soma;break;
			case 8:
				total += 85/soma;break;
			case 9:
				total += 80/soma;break;
		}
		soma = 0;
	}
		return total;
}

char** mat_cria (int m, int n)
{
	int i;
	char** matriz;
	matriz = (char**)malloc(m*sizeof(char*));
	for( i = 0 ; i < m ; i++ )
	{
		matriz[i] = (char*)malloc(n*sizeof(char));
	}
	return matriz;
}

void mat_libera (int m, char** A)
{
	int i;
	for( i = 0 ; i < m ; i++ )
	{
		free(A[i]);
	}
	free(A);
}

void imprime( int m, int n, char** A)
{
	int i,j;
	for( i = 0 ; i < m ; i++ )
		{
			for( j = 0 ; j < n ; j++ )
			{
				printf("%d ",A[i][j]);
			}
			printf("\n");
		}
}

void SA(char** M,int l,int c,int iteracoes){
	int i;
	double custoAtual,custoVizinho,variacao,melhorCusto;
	char** atual ;
	char** aux = mat_cria(l,c);
	copiaMatriz(M,aux,l,c);

	for(i=0;i<iteracoes;i++){
		atual = M;
		geraVizinho(aux,l,c);
		custoAtual = custo(atual,l,c);		
		custoVizinho = custo(aux,l,c);
		variacao = custoVizinho - custoAtual;
		if( prob(variacao,custoAtual) >= (rand()%100)/100 ){
			atual = aux ;
		}
		copiaMatriz(aux,M,l,c);
		melhorCusto = custo(atual,l,c);
		
		if(melhorCusto < Melhor){
			Melhor = melhorCusto;
			printf("\nCusto da matriz: %f\n",melhorCusto);
			imprime(l,c,atual);
		}
	}
	
	return ;
}






#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double custo(char** matriz,int linha,int coluna);

char** mat_cria (int m, int n);

void mat_libera (int m, char** A);

void imprime( int m, int n, char** A);

void SA(char** M,int l,int c, int iteracoes);











