#include <stdio.h>

float tempoClareira (int indexClareira, float docesFornecidos [5]){
    
 float tempo;
 int difClareira = dificuldadeClareira (indexClareira);
   
}

//retorna Nivel de difuldade da clareira
int dificuldadeClareira (int index_clareira){
    
     switch ( tipoDeCasa)
  {
     case 1 :
       return 150;
 
     case 2 :
       return 140;

    
    case 3 :
       return 130;
       
    case 4 :
       return 120;
    
    case 5 :
       return 110; 
     
    case 6 :
       return 100;
    
    case 7 :
       return 95;
    
    case 8 :
       return 90;
    
    case 9 :
       return 85;
       
    case 10 :
       return 80;
    
    default :
       printf ("Valor invalido!\n");
  }
}

int tempoDeLocomocao ( char tipoDeCasa ){

  switch ( tipoDeCasa)
  {
     case 'D' :
       return 200;
 
     case '.' :
       return 1;

    
    case 'G' :
       return 200;
 
     default :
       printf ("Valor invalido!\n");
  }
 
}

/*PARA TESTES
int main()
{
    printf("Hello, World!\n: \t %d",tempoDeLocomocao('D'));
  
    return 0;
}*/

