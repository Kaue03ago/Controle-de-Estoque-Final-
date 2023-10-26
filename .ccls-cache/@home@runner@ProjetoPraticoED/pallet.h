#ifndef PALLET_H
#define PALLET_H

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "Lista.h"
#include <string.h>
#include <time.h>

void adicionarCaixaNaPilha( Lista *l, char nomeDaCaixa[50], time_t dataValidade);
struct node* menorCaixa(Lista *l, time_t dataAtual);
void ProximoDeEstragar(Lista *l, time_t dataAtual);
void RemoveItens (Lista *l);
void TesteVazio(Lista *l);
void printar(Lista *l);
void numeracaoDePallet(Lista *l, char numeracao);
void insereCaixa(Lista *l, int pallet);
void removerCaixa(Lista *l, int pallet);

#endif