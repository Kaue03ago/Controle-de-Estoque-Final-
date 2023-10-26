#include "lista.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inicializa_lista(Lista *l) {
  l->qtd = 0;
  struct node *n = (struct node *)malloc(sizeof(struct node));
  n->proximo = n->anterior = l->sentinela = n;
}

int vazia_lista(Lista *l) {
  if (l->qtd == 0) {
    return 1;
  }

  else {
    return 0;
  }
}

//void getLVazia (Lista *l){
  //Lista aux;
  //aux = &(l->sentinela->anterior->data);
  //l.sentinela->anterior->data;
  //return (aux);
//}


void insere_lista(Lista *l) { 
  if (l->qtd == MAX_LISTA) {
    printf("ESTOQUE CHEIO\n");
    return;
  }

  else {
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->proximo = l->sentinela;
    n->anterior = l->sentinela->anterior;
    l->sentinela->anterior = n;
    n->anterior->proximo = n;
    l->qtd++;
  }
}

struct node *remove_lista(struct node *l) {

  l->proximo->anterior = l->anterior;
  l->anterior->proximo = l->proximo;
  struct node *a = l; 
  l = l->proximo;     
  free(a);            

  return l;           
}

void retira_lista(Lista *l) {
  struct node *n = (struct node *)malloc(sizeof(struct node));
  n = l->sentinela->anterior;

  if (n != l->sentinela) {
    n->anterior->proximo = l->sentinela;
    n->proximo->anterior = n->anterior;
    free(n);
    l->qtd--;
  }
}

void destroi_lista(Lista *l) {
  while (vazia_lista(l) != 1) {
    retira_lista(l);
  }
  free(l->sentinela);
}