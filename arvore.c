#include <stdio.h>
#include <stdlib.h>

#include "abb.h"

struct _abb {
   float info;
   Abb* pai;
   Abb* esq;
   Abb* dir;
};

/* testa se algum nó da abb esta errado ***************************************************/
static int respeita_ordem(Abb* r) {
	if (r == NULL) 
		return 1;
	else{
		if ((r->esq != NULL) && (r->info<r->esq->info)) 
			return 0;
		if ((r->dir != NULL) && (r->info>r->dir->info)) 
			return 0;
		return respeita_ordem(r->esq) && respeita_ordem(r->dir);
	}
}
static int respeita_pai(Abb* r) {
	if (r == NULL) 
		return 1;
	else 
	if ((r->esq != NULL && r->esq->pai != r) || (r->dir != NULL && r->dir->pai != r)) 
		return 0;
	else 
		return respeita_pai(r->esq) && respeita_pai(r->dir);
}
int abb_testa(Abb* r) {
	return respeita_ordem(r) && respeita_pai(r);
}

/* ****************************************************************************************/
Abb* abb_cria (void) {
	return NULL;
}

/* imprime a estrutura da abb *************************************************************/
void abb_mostra_arvore(char* titulo, Abb* raiz){
	if(titulo!=NULL) 
		printf("%s\n", titulo);
	printf("<");
	if(raiz!=NULL){//arvore existe
		printf("%.2f", raiz->info);
		abb_mostra_arvore(NULL, raiz->esq);
		abb_mostra_arvore(NULL, raiz->dir);
	}
	printf(">");
}

/* Retorna um ponteiro para o no que tem a informacao. ************************************/
Abb* abb_busca (Abb* r, float info) {
	if(r==NULL)
		return NULL;
	
	if(info<r->info)
		return abb_busca(r->esq, info);
	else
	if(info>r->info)
		return abb_busca(r->dir, info);
	else
		return r;
}

/* Retorna a informacao de um no' *********************************************************/
float abb_info(Abb* no) {
	if(no==NULL)
		return 0.0f;

	return no->info;
}

/* imprime as informacoes que estao nos nos da abb em ordem *******************************/
void abb_mostra_ordem(char* titulo, Abb* raiz){
	Abb* tmp=abb_min(raiz);
	if(titulo!=NULL) 
		printf("%s\n", titulo);

	for(tmp; tmp!=NULL; tmp=abb_prox(tmp))
		printf("%.2f ", tmp->info);
}

/* Retorna um ponteiro para o menor elemento da arvore ************************************/
Abb* abb_min(Abb* r) {
	if(r==NULL)
		return NULL;
	
	while(r->esq!=NULL)
		r=r->esq;
	return r;
}

/* Retorna um ponteiro para o sucessor do nó dado *****************************************/
Abb* abb_prox (Abb* r) {
	if(r==NULL)
		return NULL;
	else
	if(r->dir!=NULL)
		return abb_min(r->dir);
	else{
		Abb* tmp=r->pai;
		while(tmp!=NULL && r==tmp->dir){
			r=tmp;
			tmp=tmp->pai;
		}
		return tmp;
	}
}

/* Insere a informacao na ordem correta ***************************************************/
static Abb* cria_no(Abb* pai, float info){
	Abb* tmp=(Abb*)malloc(sizeof(Abb));
	if(tmp==NULL)
		return NULL;
	tmp->info=info;
	tmp->pai=pai;
	tmp->esq=tmp->dir=NULL;
	return tmp;
}
Abb* abb_insere(Abb* r, float info){
	if(r==NULL)
		return cria_no(r, info);
	else
	if(info<r->info){
		if(r->esq!=NULL)
			r->esq=abb_insere(r->esq, info);
		else
			r->esq=cria_no(r, info);
	}
	else
	if(info>r->info){
		if(r->dir!=NULL)
			r->dir=abb_insere(r->dir, info);
		else
			r->dir=cria_no(r, info);
	}
	return r;
}

/* Retira o nó que tem esta informacao ****************************************************/
Abb* abb_retira(Abb* r, float info){
	if(r==NULL)
		return NULL;
	else 
	//busca nó
	if(info<r->info)
		r->esq=abb_retira(r->esq, info);
	else
	if(info>r->info)
		r->dir=abb_retira(r->dir, info);
	else{//encontrou
		if(r->esq==NULL && r->dir==NULL){//só acontece quando nó é folha
			free(r);
			r=NULL;
		}
		else
		if(r->dir==NULL){
			Abb* tmp=r;
			r=r->esq;
			r->pai=tmp->pai;
			free(tmp);
		}
		else
		if(r->esq==NULL){
			Abb* tmp=r;
			r=r->dir;
			r->pai=tmp->pai;
			free(tmp);
		}
		else{
			Abb* tmp=r->dir;
			tmp=abb_min(tmp);
			r->info=tmp->info;
			tmp->info=info;

			if(tmp->pai->esq==tmp)
				tmp->pai->esq=tmp->dir;
			else
				tmp->pai->dir=tmp->dir;

			if(tmp->dir!=NULL)
				tmp->dir->pai=tmp->pai;

			free(tmp);
		}
	}
	return r;
}

/* Desaloca todos os nos da arvore ********************************************************/
Abb* abb_libera(Abb* r){
	if(r==NULL)
		return NULL;
	if(r->esq!=NULL)
		abb_libera(r->esq);
	if(r->dir!=NULL)
		abb_libera(r->dir);
	
	free(r);
}