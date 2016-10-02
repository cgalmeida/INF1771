#ifndef MAPA_GUARD
#define MAPA_GUARD

#include <vector>

struct local
{
	int x,y;
	int custo;
	int h;	
};

typedef struct local Local;

typedef std::vector< std::string >  Mapa;

Mapa &cria_mapa(const std::string path);

void imprime_mapa(Mapa& m);

int num_lin(Mapa& m);

int num_col(Mapa& m, Mapa::size_type lin);

void destroi_mapa(Mapa& m);

int heuristica(Local &no, Local &obj);

int calcula_custo(char c);
	
Local &busca_objetivo(Mapa &m);

Local &busca_origem(Mapa &m);

std::vector<Local>& vizinhanca(Mapa& m, Local &no);

#endif
