#include "pilha.h"
#include <string.h>

void inicializa_pilha(Pilha *pilha) {
  pilha->topo = 0;

  for (int i = 0; i < 5; i++) {
    pilha->vetor[i].dataValidade = 0;
    strcpy(pilha->vetor[i].nome, "nulo");
  }
}

int vazia_pilha(Pilha *pilha) {
  if (pilha->topo == 0) {
    return 1;
  } else {
    return 0;
  }
}
/*int getLVazia (Lista *l){
  return l.sentinela->anterior->data
}*/

int cheia_pilha(Pilha *pilha) {
  if (pilha->topo == MAX_PILHAS) {
    return 1;
  } else {
    return 0;
  }
}

void insere_pilha(Pilha *pilha, char *nome, time_t dataValidade) {
  strcpy(pilha->vetor[pilha->topo].nome, nome);
  pilha->vetor[pilha->topo].dataValidade = dataValidade;

  pilha->topo++;
}

void tira_pilha(Pilha *pilha) {
  pilha->topo--;
}

T topo_pilha(Pilha *pilha) {
  return pilha->vetor[pilha->topo - 1]; 
}