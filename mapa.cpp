/**

	Nome do módulo: MAPA
	Código:			MP
	Autor(es):		
	
	Este módulo é responsável pela leitura, armazenamento e controle do mapa.

	
	**/

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "mapa.h"

using namespace std;

Mapa& cria_mapa(const string path)
{
	ifstream fl_mapa;
	fl_mapa.open(path.c_str()); 
	Mapa *mapa = new Mapa;
	
	if(fl_mapa.is_open())
	{
		// lê todas colunas	
		string l;
		do
		{
			//lê cada linha
			getline(fl_mapa, l);
			mapa->push_back(l);
		}while( !fl_mapa.eof() );
		
	} else	cout <<  "Erro ao tentar ler mapa" << endl;
	fl_mapa.close();
	return *mapa;
}

void imprime_mapa(Mapa& m)
{
	for(Mapa::size_type i = 0; i != m.size(); i++)
	{
		for(string::size_type j = 0; j != m[i].size(); j++)
			cout << m[i][j];
		cout << endl;
	}
}


int num_lin(Mapa& m)
{
	return m.size();
}

int num_col(Mapa& m, Mapa::size_type lin)
{
	return m[lin].size();
}

void destroi_mapa(Mapa& m)
{
	delete &m;
}




int heuristica( Local& no, Local& obj)
{
	return abs(no.x - obj.x) + abs(no.y - obj.y);
}

int calcula_custo(char c)
{
	switch(c)
	{
	case 'D': 
		return 200;
	case '.':
		return 1;
	case 'C':
		return 0; // retornara valor de acordo com calculado por função 
	case 'G':
		return 5;
	}
	return 0;
}

Local &busca_objetivo(Mapa &m)
{
	Local *l = new Local;
	l->custo = 0;
	l->h = 0;

	for(Mapa::size_type i = 0; i != m.size(); i++)
	{
		for(string::size_type j = 0; j != m[i].size(); j++)
			if (m[i][j] == 'F')
			{
				l->x =(int) i;
				l->y =(int) j;
				return *l;
			}
	}
}

Local &busca_origem(Mapa &m)
{
	Local *l = new Local;
	l->custo = 0;
	l->h = 0;

	for(Mapa::size_type i = 0; i != m.size(); i++)
	{
		for(string::size_type j = 0; j != m[i].size(); j++)
			if (m[i][j] == 'I')
			{
				l->x =(int) i;
				l->y =(int) j;
				return *l;
			}
	}
}

vector<Local>& vizinhanca(Mapa& m, Local &no)
{
	vector<Local> *vet= new vector<Local>;
	Local &obj = busca_objetivo(m);
	
	if(no.y - 1 < m[0].size() && no.y -1 >= 0)
	{
		Local esq;
		esq.x = no.x;
		esq.y = no.y -1;
		esq.custo = no.custo + calcula_custo(m[esq.x][esq.y]);
		esq.h = heuristica(esq, obj);
		vet->push_back(esq);
	}
	if(no.y + 1 < m[0].size() && no.y +1 >= 0)
	{
		Local dir;
		dir.x = no.x;
		dir.y = no.y +1;
		dir.custo  = no.custo + calcula_custo(m[dir.x][dir.y]);
		dir.h = heuristica(dir, obj);
		vet->push_back(dir);
	}
	if(no.x - 1 < m[0].size() && no.x -1 >= 0)
	{
		Local cima;
		cima.x = no.x -1;
		cima.y = no.y ;
		cima.custo = no.custo + calcula_custo(m[cima.x][cima.y]);
		cima.h = heuristica(cima, obj);
		vet->push_back(cima);
	}
	if(no.x + 1 < m[0].size() && no.x +1 >= 0)
	{
		Local baixo;
		baixo.x = no.x +1;
		baixo.y = no.y;
		baixo.custo = no.custo +  calcula_custo(m[baixo.x][baixo.y]);
		baixo.h = heuristica(baixo, obj);
		vet->push_back(baixo);
	}
	return *vet;
}

