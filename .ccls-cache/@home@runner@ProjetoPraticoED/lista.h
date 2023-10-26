#ifndef LISTA_H
#define LISTA_H

#include "pilha.h"

#define MAX_LISTA 10

typedef Pilha P;

struct node {
  struct node *proximo, *anterior;
  P data;
};

typedef struct Lista {
  struct node *sentinela;
  int qtd;
} Lista;

void inicializa_lista(Lista *l);

int vazia_lista(Lista *l);
void getLVazia (Lista *l);
void insere_lista(Lista *l);
struct node* remove_lista(struct node *l);

void retira_lista(Lista *l);
void destroi_lista(Lista *l);

#endif