#include <stdio.h>
#include <stdlib.h>
#include "dset.h"

struct _dset{
	int  n ;
	int* vet ;
};

/* Cria uma particao dinamica (Dynamic Set) com n elementos dijuntos: 0,1,..,n-1. */
DSet * dsCreate(int n){
	int i;
	DSet* dset = (DSet*) malloc (sizeof(DSet));

	dset->vet = (int*) malloc (n * sizeof(int));
	dset->n = n;

	for (i = 0; i < n; i++){
		dset->vet[i] = -1;
	}

	return dset;
}

/* acha o representante do elemento */
int dsFind (DSet * dset, int elem){
	//return ((dset->vet[elem]==-1) ? elem : dsFind(dset,dset->vet[elem]));
	int i = elem;
	while (dset->vet[i]>=0)
		i=dset->vet[i];
	
	while (dset->vet[elem]>= 0) {
		int p = dset->vet[elem] ;
		dset->vet[elem] = i ;
		elem = p ;
	}
	return i;
}

/* faz a uniao dos sets que contem os elementos 1 e 2 */
int dsUnion (DSet * dset, int elem1, int elem2 ){
	elem1=dsFind(dset, elem1);	
	elem2=dsFind(dset, elem2);	
	dset->vet[elem1]=elem2;	
	return elem1;
}

/* calcula qo numero de conjuntos dijuntos */
int dsNSets(DSet * dset){
	int i, qtd=0;

	for(i=0; i<dset->n; i++){
		if(dset->vet[i]==-1)
			qtd++;
	}

	return qtd;
}

/* mostra */
void dsShow (char * title, DSet * dset){
	int i;
	printf("%s", title);
	for (i = 0; i < dset-> n; i++)
		printf("%d ",dset->vet[i]);
	printf("\n");
}
