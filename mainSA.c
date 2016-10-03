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







