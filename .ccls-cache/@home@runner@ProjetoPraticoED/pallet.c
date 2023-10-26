#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "pilha.h"
#include <tim

void adicionarCaixaNaPilha( Lista *l, char nomeDaCaixa[50], time_t dataValidade){

  insere_pilha(&(l->sentinela->proximo->data), nomeDaCaixa, dataValidade);
  
}

struct node* menorCaixa(Lista *l, time_t dataAtual){

  int quantidadePallet = l->qtd;

  struct node *n = l->sentinela->proximo;
  struct node *m = l->sentinela->proximo;


  double diferencaMenorValidade = difftime(dataAtual, topo_pilha(&(n->data)).dataValidade);
  
  
  while(n != l->sentinela->anterior){
             
  //comparar datas, ver se o valor da distancia entre as data e a tada atual é menor que a outra
    if(diferencaMenorValidade < difftime(dataAtual, topo_pilha(&(n->proximo->data)).dataValidade)){
      
      diferencaMenorValidade = difftime(dataAtual, topo_pilha(&(n->proximo->data)).dataValidade);
      
      m = n->proximo;
    }

    n = n->proximo;
  }

  
  return(m);
}

void ProximoDeEstragar(Lista *l, time_t dataAtual) {
  int i;
  struct node *n;
  struct tm *dataRetirada[3];
  int menor;
  time_t menores_validades[3];
  struct tm time_info = {0};

  
  if(l->qtd >= 3) {
    printf("Pilha resultante:\n");
    for(i = 0; i < 3; i++) {
 
      n = menorCaixa(l, dataAtual);
      
      menores_validades[i] = topo_pilha(&(n->data)).dataValidade;
    
      struct tm *caixaRetirada = localtime(&menores_validades[i]);
      
      printf(" | %d / %d / %d | - %s\n", caixaRetirada->tm_mday, caixaRetirada->tm_mon, caixaRetirada->tm_year, n->data.vetor->nome);

        time_info.tm_year = 9999;
        time_info.tm_mon = 12;
        time_info.tm_mday = 31;

        time_t data_limite = mktime(&time_info);

        n->data.vetor[(n->data.topo) - 1].dataValidade = data_limite;     
    }
    
    printf("------\n\n");
    
    RemoveItens(l);
  }
  else {
    printf("Quantidade de Pallets Insuficiente\n");
  }
}


void RemoveItens (Lista *l) {
  struct tm time_info = {0};
  time_info.tm_year = 9999;
  time_info.tm_mon = 12;
  time_info.tm_mday = 31;

  time_t data_limite = mktime(&time_info);


  struct node *n = l->sentinela->proximo;


  while(n != l->sentinela) {
    if(topo_pilha(&(n->data)).dataValidade == data_limite) {
      tira_pilha(&(n->data));
    }
    n = n->proximo;
  }
}

void TesteVazio(Lista *l) {
  struct node *n = l->sentinela->proximo;

  while(n != l->sentinela) {
    if(vazia_pilha(&(n->data)) == 1) {
      l->qtd--;
      printf("O Pallet de número %d foi removido porque estava vazio\n", n->data.numeracao);
      n  = remove_lista(n);
    }
    
    else {
      n = n->proximo;
    }
  }
}

void printar(Lista *l) {
  struct node *n = l->sentinela->proximo;

  while(n != l->sentinela) {
    
    for(int i = n->data.topo - 1; i > -1; i--) {
      
      struct tm *data = localtime(&n->data.vetor[i].dataValidade);
      
      printf("| %d / %d / %d | - %s\n", data->tm_mday, data->tm_mon, data->tm_year , n->data.vetor[i].nome);
    }
    
    printf("-------------------\n");
    printf("    Pallet %d\n\n", n->data.numeracao);
    n = n->proximo;
  }
}

void numeracaoDePallet(Lista *l, char numeracao) {
  l->sentinela->proximo->data.numeracao = numeracao;
}

void insereCaixa(Lista *l, int pallet) {
  struct node *n = l->sentinela->proximo;
  int flag = 0;

  

  while(n != l->sentinela) {
    if(n->data.numeracao == pallet) {
      if(cheia_pilha(&n->data) != 1) {
        char nome_caixa[50];
        int dia, mes, ano;
        struct tm time_info = {0};

        printf("Qual o nome da caixa?\n");
        scanf("%s", nome_caixa);
        printf("Qual a validade da caixa? exemplo: 17 03 2024\n");
        scanf("%d %d %d", &dia, &mes, &ano);

        time_info.tm_year = ano;
        time_info.tm_mon = mes;
        time_info.tm_mday = dia;

        time_t data = mktime(&time_info);
        insere_pilha(&n->data, nome_caixa,data);
        flag = 1;
        break;
      }

      else {
        printf("O está Pallet cheio\n");
        flag = 1;
      }
  
    }
    n = n->proximo;
  }

  if(flag == 0) { //caso nao exista um pallet com o numero, ele  le outro numero e chama a funcao novamente
    printf("o Pallet de número %d não existe\n", pallet);
    printf("Digite um número válido\n");
    int pallet1;
    scanf("%d", &pallet1);
    insereCaixa(l, pallet1);
  }
}

void removerCaixa(Lista *l, int pallet) {
  struct node *n = l->sentinela->proximo;
  int flag = 0;

  while(n != l->sentinela) {
    if(n->data.numeracao == pallet) {
      if(vazia_pilha(&n->data) != 1) {
        printf("\nA caixa de nome '%s' foi removida\n\n", n->data.vetor[n->data.topo - 1].nome);
        tira_pilha(&n->data);
        flag = 1;
      }
    }
    n = n->proximo;
  }

  if(flag == 0) {  //caso nao exista um pallet com o numero, ele  le outro numero e chama a funcao novamente
    printf("o Pallet de número %d não existe\n", pallet);
    printf("Digite um número válido\n");
    int pallet1;
    scanf("%d", &pallet1);
    removerCaixa(l, pallet1);
  }
}