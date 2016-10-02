#include <cstdlib> 
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "mapa.h"
using namespace std;

const int n=41; // Limite horizontal do mapa
const int m=41; // Limite vertical do mapa
static int map[n][m];
static int closed_nodes_map[n][m]; // mapa de nós fechados (tentados) 
static int open_nodes_map[n][m]; // mapa de nós abertos (não tentados ainda) 
static int dir_map[n][m]; // mapa de direções
const int dir=4; // numero de direcoes posicoes a partir de qualquer posicao
static int dx[dir]={1, 0, -1, 0};
static int dy[dir]={0, 1, 0, -1};

class node
{
    // posicao atual
    int xPos;
    int yPos;
    //level = peso de cada nó
    int level;
    // priority = level + heuristica
    int priority;  //quanto menor, maior é a prioridade

    public:
        node(int xp, int yp, int d, int p) 
            {xPos=xp; yPos=yp; level=d; priority=p;}
    
        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        void nextLevel(const int & i) 
        {
			 level+=calcula_custo(map[xPos][yPos]);        
        }
        
        //Distancia de Manhattan aproximada do destino
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-xPos;
            yd=yDest-yPos;         

            // distancia de Manhattan
            d=abs(xd)+abs(yd);
            
            return(d);
        }
};

// Determinação de prioriade (na fila de prioridade)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// ALGORITMO A-ESTRELA
//A rota é retornada como uma string de direçoes a serem percorridas no melhor caminho
string pathFind( const int & xStart, const int & yStart, 
                 const int & xFinish, const int & yFinish )
{
    static priority_queue<node> pq[2]; // lista de nós abertos (não tentads)
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset do mapa de nós
    for(y=0;y<m;y++)
    {
        for(x=0;x<n;x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }

    // cria o nó inicial e da push na lista de nós abertos 
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y]=n0->getPriority(); // marca o nó no mapeamento de nós abertos 

    // BUSCA A* 
    while(!pq[pqi].empty())
    {
        // Obtem o nó corrente com a prioridade mais alta
		// na lista de nós abertos
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), 
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        pq[pqi].pop(); // remove o nó da lista de nós abertos
        open_nodes_map[x][y]=0;
        // marca o nó na lista de nós fechados 
        closed_nodes_map[x][y]=1;

        // Sai da busca quando o estado da busca é atingido (Fim da rota)
        if(x==xFinish && y==yFinish) 
        {
            // Gera o caminho do fim para o início
            // seguindo as direções
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            
            delete n0;
            // esvazia nós que sobraram
            while(!pq[pqi].empty()) pq[pqi].pop();           
            return path;
        }

        // gera 'movimentos' (child nodes) em todas as possíveis direções
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1 
                || closed_nodes_map[xdx][ydy]==1))
            {
                // cria um novo child node
                m0=new node( xdx, ydy, n0->getLevel(), 
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                //adiciona a lista de nós abertos, caso ainda não esteja lá
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    //  marca a direção do nó pai 
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // atualiza prioridade
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    // atualiza informacao de parentalidade (dir)
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // substitui o nó
                    // esvaziado um pq por outro nó
                    // exceto o nó a ser substituido, esse deve ser ignorado
                    // e o novo nó deve ser posto em seu lugar
                    while(!(pq[pqi].top().getxPos()==xdx && 
                           pq[pqi].top().getyPos()==ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop(); // remove  o nó desejado
                    
                    // esvazia o maior lador de pq para o outro lado
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // adiciona  o melhor nó
                }
                else delete m0; //libera nó
            }
        }
        delete n0; // libera o nó (garbage collection)
    } 
    return ""; // nenhuma rota encontrada
}




int main()
{
    srand(time(NULL));
	int custoTotal=0;
	Mapa &mapa_aux = cria_mapa("mapa.txt");
	
	//Durante Testes: Imprimi  a matriz
	for(int x=0;x<41;x++)  
    {
        for(int y=0;y<41;y++)  
        {
            map[x][y] = mapa_aux[x][y];  // exibe o elemento corrente no array 
			cout<<(char)map[x][y];
        }
	  cout<<endl;  // nova linha
	}

    
    // Inicio e fim da trajetória
    int xA=36, yA=4, xB=36, yB=36;
 
    cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
    cout<<"Start: "<<xA<<","<<yA<<endl;
    cout<<"Finish: "<<xB<<","<<yB<<endl;

    // Obter a rota
    clock_t start = clock();
    string route=pathFind(xA, yA, xB, yB);
    if(route=="") cout<<"Rota não encontrada!"<<endl;
    clock_t end = clock();
    double time_elapsed = double(end - start);
    cout<<"Tempo para calcular a rota (ms): "<<time_elapsed<<endl;
    cout<<"Rota:"<<endl;
    cout<<route<<endl<<endl;

    // Seguir rota no mapa e exibi-la  
    if(route.length()>0)
    {
        int j; char c;
        int x=xA;
        int y=yA;
        map[x][y]=2;
        for(int i=0;i<route.length();i++)
        {
            c =route.at(i);
            j=atoi(&c); 
            x=x+dx[j];
            y=y+dy[j];
            map[x][y]=3;
        }
        map[x][y]=4;
    
        // Exibir mapa e rota

        for(int x=0;x<n;x++)
        {
            for(int y=0;y<m;y++){
                if(map[x][y]=='D')
                    cout<<"D";//Obstaculo
                else if(map[x][y]=='.')
                    cout<<"."; //obstaculo
                else if(map[x][y]==2)
                    cout<<"I"; //Inicio
                else if(map[x][y]==3)
                    cout<<"|"; //Rota
                else if(map[x][y]==4)
                    cout<<"F"; //Final
				else if(map[x][y]=='G')
                    cout<<"G"; //Obstaculo
				else if(map[x][y]=='C')
                    cout<<"C"; //Clareira
			}
            cout<<endl;
        }
		
    }
    getchar(); 
    return(0);
}

