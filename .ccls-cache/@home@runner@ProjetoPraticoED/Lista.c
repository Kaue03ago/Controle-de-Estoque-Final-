#include "pilha.h"
#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>

void inicializar_lista(Lista *l) {
  l->qtd = 0;
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->proximo = n->anterior = l->sentinela = n;
}

void insere_lista(Lista *l) {  //insere um novo pallet no começo da pilha
  if(l->qtd == MAX) {
    printf("ESTOQUE CHEIO\n");
    return;
  }

  else {
    struct node *n = (struct node*) malloc(sizeof(struct node));
    n->anterior = l->sentinela;
    n->proximo = l->sentinela->proximo;
    l->sentinela->proximo = n;
    n->proximo->anterior = n;
    l->qtd++;
  }
}

struct node* remove_lista(struct node *l) {

  l->proximo->anterior = l->anterior;
  l->anterior->proximo = l->proximo;
  struct node* a = l;   //salva o endereço de l
  l = l->proximo; //define l como o proximo de l
  free(a);// desaloca o antigo endereco de l

  return l;  //retorna o novo endereco
}

int vazia(Lista *l) {
  if(l->qtd == 0) {
    return 1;
  }

  else {
    return 0;
  }
}

void destroi(Lista *l) {
  while(vazia(l) != 1) {
    retira(l);
  }
  free(l->sentinela);
}

void retira(Lista *l) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n = l->sentinela->proximo;

  if(n != l->sentinela) {
    n->proximo->anterior = n->anterior;
    n->anterior->proximo = n->proximo;
    free(n);
    l->qtd--;
  }
}