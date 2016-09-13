#include <stdio.h>
#include <stdlib.h>

#define TAM_TAB 41

void printMatriz (char Matriz[][41], int rowMatriz, int columnsMatriz){
     
    int row,columns;
    
    int numberOfLines = rowMatriz;
    int numberColumns = columnsMatriz;
    
    for (int row=0; row<numberOfLines; row++)
    {
        for(int columns=0; columns<numberColumns; columns++)
             printf("%c", Matriz[row][columns]);
        printf("\n");
     }
      
    
}

int main()
{
	char url[]="mapa.txt";
	char ch_campo;                           	//caracter que representa uma casa 
    int i=0, j=0;                        		//indices da matriz TABULEIRO
	
	char mTabuleiro[TAM_TAB][TAM_TAB];       	//O mapa principal representado por uma matriz 41 x 41
	
        FILE* arq= fopen(url, "r");
	
	if (arq == NULL) {
		printf("Erro na abertura do arquivo.\n");
		exit(1); /* aborta programa */
	}


	do{ 
	    ch_campo = fgetc(arq);
		mTabuleiro [i][j] = ch_campo;
		j++;
		    
		if(ch_campo == '\n')
	        i++;
			    
	}while(ch_campo!=EOF && j<41);
	    
	printMatriz(mTabuleiro,TAM_TAB, TAM_TAB);   

	
	
	fclose(arq);
	
	return 0;
}