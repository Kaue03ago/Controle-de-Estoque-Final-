#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "Lista.h"
#include <string.h>
#include <time.h>

#define LIMITE 999999

void adicionarCaixaNaPilha( Lista *l, char nomeDaCaixa[50], int validade);
struct node* menorCaixa(Lista *l);
void ProximoDeEstragar(Lista *l);
void RemoveItens (Lista *l);
void TesteVazio(Lista *l);
void printar(Lista *l);
void numeracaoDePallet(Lista *l, char numeracao);

int main(void) {
  
  //------- Recebe a data atual e armazena na struct tm dataAtual--------------------------
  
    time_t current_time;

    //armazena as informações de data e hora
    struct tm *dataAtual;
  
    //obter o tempo atual e armazená-lo na variável "current_time"
    time(&current_time);

    //para converter o tempo em informações de data e hora locais e armazená-lo na variável "dataAtual".
    dataAtual = localtime(&current_time);

    //adicione esse printf para ter um exemplo de como acessar o ano, mes e dia da nossa struct dataAtual
    printf("Data atual: %d-%d-%d\n", dataAtual->tm_year + 1900, dataAtual->tm_mon + 1, dataAtual->tm_mday);

  //--------------------------------------------------------------------------------

  
  Lista l;
  
  inicializar_lista(&l);

  int diaDigitado, mesDigitado, anoDigitado;

  int qntCaixas;
  char nomeDaCaixa[50];
  int validadeDaCaixa = 0;
  char instrucao[50];
  int i;
  char numeracao = 'a';

  printf("O programa pode executar as seguintes instruções:\n");
  printf("----------------------------------------------------------\n");
  printf("-InserePallet: cria um novo pallet e insere a pilha de caixas nele\n");
  printf("----------------------------------------------------------\n");
  printf("-ProximoDeEstragar: verifica o topo de todas as pilhas, seleciona as três menores validade, as remove do topo e cria uma pilha de ordem decrescente com as três\n");
  printf("----------------------------------------------------------\n");
  printf("-Saida: finaliza o programa\n");
  printf("----------------------------------------------------------\n");

  while(1) {
    qntCaixas = 0;
  
    printf("Qual instrução você deseja realizar?\n");
    printf("----------------------------------------------------------\n");
    scanf("%s", instrucao);
    if(instrucao[(strlen(instrucao)) - 1] == '\n') {
      instrucao[strlen(instrucao) - 1] = '\0';
    }


    if(strcmp(instrucao, "InserePallet") == 0) {
      insere_lista(&l);
      printf("Quantas caixas deseja adicionar ao novo pallet?\n");
      printf("----------------------------------------------------------\n");
      scanf("%d", &qntCaixas);

      //Adicionar caixas
      for(i = 1; i <= qntCaixas; i++) {
        printf("Qual o nome e validade do caixa?\n");
        scanf("%s %d", nomeDaCaixa, &validadeDaCaixa);
        adicionarCaixaNaPilha(&l, nomeDaCaixa, validadeDaCaixa);
        strcpy(instrucao, "vazio");
      }
      numeracaoDePallet(&l, numeracao);
      printf("\n");
      printar(&l);
      numeracao++;
    }

    else if (strcmp(instrucao, "Saida") == 0) {
      printf("-------FIM DO PROGRAMA -------");
      break;
    }

    else if(strcmp(instrucao, "ProximoDeEstragar") == 0) {
      ProximoDeEstragar(&l);
      TesteVazio(&l);
      printf("\n");
      printar(&l);
    }

    else {
      printf("Função inválida\n");  
    }
    
  }
  
}


void adicionarCaixaNaPilha( Lista *l, char nomeDaCaixa[50], int validade){

  insere_pilha(&(l->sentinela->proximo->data), nomeDaCaixa, validade);
  
}

struct node* menorCaixa(Lista *l){

  int quantidadePallet = l->qtd;

  struct node *n = l->sentinela->proximo;
  struct node *m = l->sentinela->proximo;

  int menorValidade = topo_pilha(&(n->data)).validade;

  while(n != l->sentinela->anterior){
             
  
    if(menorValidade > topo_pilha(&(n->proximo->data)).validade){
      
      menorValidade = topo_pilha(&(n->proximo->data)).validade;
      
      m = n->proximo;
    }

    n = n->proximo;
  }


  return(m);
}

void ProximoDeEstragar(Lista *l) {
  int i;
  struct node *n;
  int menor;
  int menores_validades[3];
  char nomes[3][100];

  
  if(l->qtd >= 3) {
    for(i = 0; i < 3; i++) {
    
      n = menorCaixa(l);
      menores_validades[i] = topo_pilha(&(n->data)).validade;
      strcpy(nomes[i], topo_pilha(&(n->data)).nome);
      n->data.vetor[(n->data.topo) - 1].validade = LIMITE;
      
    }

    printf("Pilha resultante:");
    printf(" | %d | - %s\n", menores_validades[0], nomes[0]);
    printf("                  | %d | - %s\n", menores_validades[1], nomes[1]);
    printf("                  | %d | - %s\n", menores_validades[2], nomes[2]);
    printf("                  ------\n\n");
    
    
    RemoveItens(l);
  }
  else {
    printf("Quantidade Insuficiente\n");
  }
}


void RemoveItens (Lista *l) {
  struct node *n = l->sentinela->proximo;


  while(n != l->sentinela) {
    if(topo_pilha(&(n->data)).validade == LIMITE) {
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
      printf("O Pallet %c foi removido porque estava vazio\n", n->data.numeracao);
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
      printf("| %d | - %s\n", n->data.vetor[i].validade, n->data.vetor[i].nome);
    }
    printf("------\n");
    printf("  %c\n\n", n->data.numeracao);
    n = n->proximo;
  }
}

void numeracaoDePallet(Lista *l, char numeracao) {
  l->sentinela->proximo->data.numeracao = numeracao;
}