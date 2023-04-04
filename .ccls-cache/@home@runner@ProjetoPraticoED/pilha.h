
#ifndef PILHA_H
#include <time.h>
#define PILHA_H
#define MAX_NOME 50
#define MAX_PILHAS 5

typedef struct{
  char nome[MAX_NOME];
  time_t dataValidade;
  int validade;
} T;

typedef struct Pilha {
  T vetor[MAX_PILHAS];
  int topo;
  int numeracao;
} Pilha;

void inicializa_pilha(Pilha *pilha);
void destroi_pilha(Pilha *pilha);

int vazia_pilha(Pilha *pilha);
int cheia_pilha(Pilha *pilha); 

void insere_pilha(Pilha *pilha, char *nome, int validade);

void tira_pilha(Pilha *pilha);

T topo_pilha(Pilha *pilha);

#endif