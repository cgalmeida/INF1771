#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdio.h>
#include "set.h"

struct set{
	int set_size;  /* numero de elementos do conjunto */
	int vet_size;  /* numero de elementos no vetor de inteiros semi-positivos */
	unsigned int* vet; /* vetor de inteiros que armazena os bits que representam o conjunto */
};

/* cria um conjunto com n elementos */
Set* setCreate(int set_size){
	Set* set = (Set*)malloc(sizeof(Set));
	if (set != NULL){
		int i;
		set->set_size = set_size;
		set->vet_size = (int) ceil(set_size/(8.0*sizeof(unsigned int)));
		set->vet = (unsigned int*)malloc(set->vet_size*sizeof(unsigned int));
		for (i = 0; i < set->vet_size; i++)
			set->vet[i] = 0;
	}
	return set;
}


/* destroi (desaloca) o conjunto */
Set* setDestroy(Set* set) {
	if (set) {
		if (set->vet)
			free(set->vet);
		free(set);
	}
	return NULL;
}

/* insere o elemento i no conjunto */
void setInsert(Set *set, int i){
	set->vet[i/sizeof(int)]|=1<<(i%sizeof(int));
}

/* remove o elemento i do conjunto */
void setRemove(Set *set, int i){
	set->vet[i/sizeof(int)]&=~(1<<(i%sizeof(int))) ;
}

/* cria uma copia do conjunto */
Set* setCopy(Set* set){
	Set * t = setCreate(set->set_size);

	memcpy(t->vet , set->vet , set->vet_size*sizeof(int));

	return t ;
}

/* cria o complemento de conjunto */
Set* setComplement(Set* set){
	Set * t = setCreate(set->set_size);
	int i, num=set->vet_size;

	for (i=0; i<num; i++)
		t->vet[i]=~set->vet[i];

	return t;
}

/* cria a uniao de dois conjunto que podem ter tamanhos diferentes */
/* naturalmente o numero de elementos do universo e' o do maior dos dois */
Set* setUnion( Set *set1,  Set *set2){
	int i, num;
	Set * t;

	if(set1->set_size>=set2->set_size){
		t=setCopy(set1);
		num=set2->vet_size;
	}
	else{
		t=setCopy(set2);
		num=set1->vet_size;
	}

	for(i=0; i<num; i++)
		t->vet[i]|= (set1->set_size>=set2->set_size ? set2->vet[i] : set1->vet[i]);

	return t;
}

/* calcula a intersecao de dois conjuntos, a cardinalidade e' a do menor */
Set* setIntersection( Set *set1,  Set *set2){
	int i, num;
	unsigned int *vtmp=NULL;
	Set * t;

	if(set1->set_size>=set2->set_size){
		t=setCopy(set2);
		num=set2->vet_size;
	}
	else{
		t=setCopy(set1);
		num=set1->vet_size;
	}

	vtmp=set1->set_size>=set2->set_size ? set1->vet : set2->vet;
	for(i=0; i<num; i++)
		t->vet[i]&=vtmp[i];

	return t;
}

/* calcula a diferenca de set1-set2. a cardinalidade e'a de set1. */
Set* setDifference(Set *set1, Set *set2){
	int i;
	int num=set2->vet_size;
	Set * t = setCopy(set1);

	for(i=0; i<num; i++){
		t->vet[i]^=set2->vet[i];
	}

	return t;
}

/* verifica se o elemento i pertence ao conjunto */
int setIsMember( Set *set, int i){
	int t=set->vet[i/sizeof(int)];

	t&=1<<(i%sizeof(int));

	if(t)
		return 0; // pertence

	return 1; // não pertence
}

/* verifica de set2 e' um sub conjunto de set1 */
int setIsSubset( Set *set1,  Set *set2){
	int i;
	int num1=set1->vet_size;
	int num2=set2->vet_size;

	for(i=0; i<num1, (num1-i)>=num2; i++){
		if(set1->vet[i]==set2->vet[i]){
			int j;

			for(i++, j=0; j<num2, i<num1; i++, j++){
				if(set1->vet[i]!=set2->vet[i])
					break;
			}

			if(j==num2)
				return 0; // é subconjunto
		}
	}

	return 1; // não é subconjunto
}

/* verifica se dois conjuntos sao iguais */
int setIsEqual( Set *set1,  Set *set2){
	int i;
	int num=set1->vet_size;
	
	if(set1->set_size!=set2->set_size)
		return 1; // falso

	for(i=0; i<num; i++)
		if(set1->vet[i]!=set2->vet[i])
			return 1; // falso

	return 0;
}

/* informa a cardilaidade do conjunto */
int setNumberOfElements(Set* set){
		return set->set_size;
}

/* mostra os elementos do conjunto */
void setShow(char* title, Set* set){
	int i, first=1;
	printf("%s={", title);
	for (i = 0; i < set->set_size; i++) {
		if (setIsMember(set, i)) {
			if (first) { 
				printf("%d", i); 
				first = 0; 
			}
			else 
				printf(",%d", i);
		}
	}
	printf("}\n");
}