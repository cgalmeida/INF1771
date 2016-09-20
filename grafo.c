#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include "grafo.h"

/**	
***	ponteiro para um vetor de inteiros, para representar os vertices já visitados
***	0 = não visitado
***	1 = visitado
**/
int * visitado;
typedef struct _dset{
	int n;
	int *v;
} dset;
typedef struct _aresta{
	int noi, nof;
	float peso;
} aresta;

typedef struct _viz Viz;
struct _viz {
	int noj;
	float peso;
	Viz*  prox;
};

struct _grafo {
	int nv;           /* numero de nos ou vertices */
	int na;           /* numero de arestas */
	char orientado;   /* 0 = nao orientado */
	Viz** viz;         /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

/* aux para fila e pilha */
typedef struct _sq SQ;
struct _sq {
	int info;
	SQ* prox;
};

static SQ* push(SQ* stack, int info){
	SQ* novo = (SQ*)malloc(sizeof(SQ));
	assert(novo);
	novo->info = info;
	novo->prox = stack;
	return novo;
}

static SQ* queue(SQ* queue, int info){
	SQ* novo = (SQ*)malloc(sizeof(SQ));
	SQ* aux = queue;
	assert(novo);
	novo->info = info;
	novo->prox = NULL;
	if (!queue){
		return novo;
	}
	while (aux->prox){
		aux = aux->prox;
	}
	aux->prox = novo;
	return queue;
}

static SQ* pop(SQ* stack, int* popped_info){
	SQ* libera;
	if (!stack){
		*popped_info = -1;
		return NULL;
	}
	*popped_info = stack->info;
	libera = stack;
	stack = stack->prox;
	free(libera);
	return stack;
}

static Viz* criaViz(Viz* head, int noj, float peso) {
	Viz* no = (Viz*) malloc(sizeof(Viz));
	assert(no);
	no->noj = noj;
	no->peso = peso;
	no->prox = head;
	return no;
}

Grafo* grafoCria(int nv, int na, int orientado) {

	int i;
	Grafo* g = (Grafo *) malloc(sizeof(Grafo));
	g->orientado = orientado;
	g->nv = nv;
	g->na = na;
	g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
	
	/* alocando o vetor de inteiros visitado com o numero de vertices do grafo criado */
	visitado = (int*)malloc(sizeof(int)*nv);
	
	for (i = 0; i < nv; i++)
		g->viz[i] = NULL;
		
	return g;
}

Grafo* grafoLe( char* filename ) {
	FILE *arq = fopen(filename,"rt");
	int nv, na, orientacao, no1, no2, i = 0;
	float peso;
	Grafo* novo;
	
	fscanf(arq, "%d %d %d", &nv, &na, &orientacao);
	novo = grafoCria(nv, na, orientacao);
	assert(novo);
	while (fscanf(arq, "%d %d %f", &no1, &no2, &peso) == 3) {
		novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
		if (!orientacao)
			novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
	}
	return novo;
}

Grafo* grafoLibera(Grafo* grafo) {
	if (grafo) {
		int i = 0;
		Viz* no,*aux;
		for (i = 0; i < grafo->nv; i++){
			no = grafo->viz[i];
			while (no){
				aux = no->prox;
				free(no);
				no = aux;
			}
		}
		free(grafo->viz);
		free(grafo);
	}
	return NULL;
}

void grafoMostra (char* title, Grafo * grafo) {
	int i;
	if (title)
		printf("%s", title);
	if (grafo)
	{
		printf("NV: %d, NA: %d, %s\n", grafo->nv, grafo->na, (grafo->orientado!=0? "orientado": "nao orientado"));
		for (i = 0; i < grafo->nv; i++){
			Viz* viz = grafo->viz[i];
			printf("[%d]->", i);
			while (viz)
			{
				printf("{%d, %g}->", viz->noj, viz->peso);
				viz = viz->prox;
			}
			printf("NULL\n");
		}
	}
}



void grafoPercorreProfundidade(Grafo * grafo, int no_inicial){
	int i;
	Viz * t;
	SQ * pilha = NULL; //, * tmp = NULL;
	
	/* inicializando todos como não visitado (0) */
	for (i = 0; i < grafo->nv; i++)
		visitado[i]=0;
	
	/* nó inicial marcado como visitado */
	visitado[no_inicial]=1;

	for(i=0; i<grafo->nv; i++){
		/* lista de nós ligados ao nó corrente */
		Viz * viz = grafo->viz[no_inicial];
		
		/* imprime o nó corrente e marca como visitado no vetor global visitado */
		printf("%d", no_inicial);			
	
		/* percorre a lista, incluindo na fila os nós ainda não visitados */
		while (viz){
			/* nome do nó */
			int info=viz->noj;

			/* verifica se ele já foi visitado, se não, enfilerar e marcar como visitado */
			if(!visitado[info]){
				pilha=push(pilha, info);
				visitado[info]=1;
			}
			
			/* avança um nó da lista */
			viz = viz->prox;
		}
		
		/*
		tmp=pilha;
		printf("("); 
		while(tmp){
			printf("%d", tmp->info);
			tmp=tmp->prox;
		}
		printf(")"); 
		*/
		
		/* recupera o primeiro nó da fila */
		pilha=pop(pilha, &no_inicial);
		
		/* caso o nó retornado for -1, significa que a fila chegou ao fim */
		if(no_inicial==-1)
			break;
			
		printf(", ");
	}
	printf("\n");
}



void grafoPercorreLargura(Grafo * grafo, int no_inicial){
	int i;
	Viz * t;
	SQ * fila = NULL; //, * tmp = NULL;
	
	/* inicializando todos como não visitado (0) */
	for (i = 0; i < grafo->nv; i++)
		visitado[i]=0;
	
	/* nó inicial marcado como visitado */
	visitado[no_inicial]=1;

	for(i=0; i<grafo->nv; i++){
		/* lista de nós ligados ao nó corrente */
		Viz * viz = grafo->viz[no_inicial];
		
		/* imprime o nó corrente e marca como visitado no vetor global visitado */
		printf("%d", no_inicial);			
	
		/* percorre a lista, incluindo na fila os nós ainda não visitados */
		while (viz){
			/* nome do nó */
			int info=viz->noj;

			/* verifica se ele já foi visitado, se não, enfilerar e marcar como visitado */
			if(!visitado[info]){
				fila=queue(fila, info);
				visitado[info]=1;
			}
			
			/* avança um nó da lista */
			viz = viz->prox;
		}
		
		/*
		tmp=fila;
		printf("("); 
		while(tmp){
			printf("%d", tmp->info);
			tmp=tmp->prox;
		}
		printf(")"); 
		*/
		
		/* recupera o primeiro nó da fila */
		fila=pop(fila, &no_inicial);
		
		/* caso o nó retornado for -1, significa que a fila chegou ao fim */
		if(no_inicial==-1)
			break;
			
		printf(", ");
	}
	printf("\n");
}



void grafoMostraDijkstra(Grafo* grafo, int no_inicial){
	float *custo, dist, dmin;
	int i, no, falta, *ant;

	custo = (float*)malloc(grafo->nv*sizeof(float));
	ant = (int*)malloc(grafo->nv*sizeof(int)); 
	
	if(custo==NULL || ant==NULL)
		return;

	printf("No de partida: %d\n", no_inicial);
	
	for (i = 0; i < grafo->nv; i++){
		/* inicializando todos os custos com infinito */
		custo[i]=FLT_MAX;
		
		/* inicializando todos como não visitado (0) */
		visitado[i]=0;
	}
	
	/* armazena a distancia do nó, marca como visitado e salva o indice desse nó */
	custo[no_inicial]=0; 
	visitado[no_inicial]=1;
	ant[no_inicial]=no_inicial; 
	no=no_inicial; // nó partindo do inicial
	 
	/* quantidade de nós restantes */
	falta=grafo->nv-1;

	while(falta > 0){
		Viz * viz = grafo->viz[no];
		
		while(viz){
			if(visitado[viz->noj]==0){
				dist = custo[no] + viz->peso;
				
				if(dist<custo[viz->noj]){
					custo[viz->noj] = dist;
					ant[viz->noj] = no;
				}
				
				/* visitado */
				visitado[viz->noj]=1;
			}
			viz=viz->prox;
		}

		dmin=FLT_MAX;
		
		for(i=0; i<grafo->nv; i++){
			if(visitado[i]==1 && custo[i]<dmin){
				dmin=custo[i];
				no = i;
			}
		}
		
		visitado[no] = 2;
		printf("Distancia para o no %d: %.0f\n", no, custo[no]);
		falta--;
	}
}



int dfind (dset *d, int elem){
	if (d->v[elem] == -1)
		return elem;
	else
		return dfind (d, d->v[elem]);
}
void dunion (dset *d, int elem1, int elem2){
	int r1 = dfind (d, elem1);
	int r2 = dfind (d, elem2);
	
	if (r1 != r2)
		d->v[r1] = r2;
}
int compara (const void *vp1, const void *vp2) {	// ordem decrescente
	aresta* p1 = (aresta*)vp1;
	aresta* p2 = (aresta*)vp2;

	if (p1->peso < p2->peso)
		return -1;	// vem primeiro
	else if (p1->peso == p2->peso)
		return 0;
	else
		return 1;
}
void grafoMostraKruskal(Grafo* grafo){
	int i,j;
	aresta *arest = (aresta*)malloc(grafo->na*sizeof(aresta));
	dset *d = (dset*)malloc(sizeof(dset));
	d->v = (int*)malloc(grafo->nv*sizeof(int));
	
	for (i=0; i < grafo->nv; i++)
		d->v[i] = -1;
	for (i=0, j=0; j < grafo->nv; j++) {
		Viz* viz = grafo->viz[j];
		while (viz) {
			if (j < viz->noj) {
				arest[i].noi = j;
				arest[i].nof = viz->noj;
				arest[i].peso = viz->peso;
				i++;
			}
			viz = viz->prox;
		}
	}
	
	qsort(arest,grafo->na, sizeof(aresta), compara);

	for (i=0; i < grafo->na; i++) {
		int r1 = dfind(d, arest[i].noi);
		int r2 = dfind(d, arest[i].nof);
		
		if (r1 != r2) {
			printf("noi: %d, nof: %d, peso: %f\n", arest[i].noi, arest[i].nof, arest[i].peso);
			dunion(d, r1, r2);
		}
	}
}
