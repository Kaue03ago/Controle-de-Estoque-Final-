#ifndef LISTA_H
#define LISTA_H
#include "pilha.h"
#define MAX 10
typedef Pilha P;

// Pallet
struct node {
  struct node *proximo, *anterior;
  P data; // data acessa a struct pilha
};

typedef struct Lista {
  struct node *sentinela;
  int qtd;
} Lista;

void insere_lista(Lista *l);
struct node* remove_lista(struct node *l);
void inicializar_lista(Lista *l);

#endif