#include <stdlib.h>
#include "pilha.h"
#include <string.h>

//inicializa a pilha e aloca o vetor
void inicializa_pilha(Pilha *pilha) {
  
	pilha->topo = 0;
  
}


//retorna o valor do topo
T topo_pilha(Pilha *pilha){
  
  return pilha->vetor[pilha->topo - 1];

};

//se a pilha estiver vazia retorna 1, se nao retorna 0
int vazia_pilha(Pilha *pilha){

  if(pilha->topo == 0){
      return 1;
  }else{
      return 0;
  }
  
};

//se a pilha estiver cheia retorna 1, se nao retorna 0
int cheia_pilha(Pilha *pilha){

  if(pilha->topo == MAX_PILHAS){
      return 1;
  }else{
      return 0;
  }
  
}; 

//insere um elemento no topo da pilha
void insere_pilha(Pilha *pilha, char* nome, int validade){

  strcpy(pilha->vetor[pilha->topo].nome, nome);
  pilha->vetor[pilha->topo].validade = validade;

  pilha->topo++;
    
};

//tira o elemento do topo da pilha
void tira_pilha(Pilha *pilha){
  
  //o topo agora aponta para o elemento anterior
  pilha->topo--;
  
};