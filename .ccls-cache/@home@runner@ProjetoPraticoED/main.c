#include "lista.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node *menorCaixa(Lista *l, time_t dataAtual);
void adicionarCaixaNaPilha(Lista *l, char nomeDaCaixa[MAX_NOME], time_t dataValidade);
void ProximoDeEstragar(Lista *l, time_t dataAtual);
void RemoveItens(Lista *l);
void TesteVazio(Lista *l);
void printar(Lista *l);
void numeracaoDePallet(Lista *l, int numeracao);
void insereCaixa(Lista *l, int pallet);
void removerCaixa(Lista *l, int pallet);
void removerPallet(Lista *l, int pallet);
int testenumeracao(Lista *l, int pallet);
int testeDatas(int dia, int mes, int ano);
int testeValidade(time_t DataAtual, time_t Datadigitada);

int main(void) {

  // Recebe a data atual e armazena na struct tm
  time_t dataAtual = time(NULL);

  // Data temporaria
  struct tm time_info = {0};

  // Cria a lista
  Lista l;

  // Inicializacao da Lista 
  inicializa_lista(&l);

  int diaDigitado, mesDigitado, anoDigitado;
  int qntCaixas, numeracao, i, validadeDaCaixa = 0;
  char nomeDaCaixa[MAX_NOME], instrucao[MAX_NOME];

  printf("O programa pode executar as seguintes instruções:\n\n");
  printf("1️⃣  InserePallet: cria um novo pallet e insere a pilha de caixas nele\n\n");
  printf("2️⃣  ProximoDeEstragar: seleciona as três menores validades entre aquelas no topo de todas as pilhas, depois as junta numa pilha de três caixas e as remove\n\n");
  printf("3️⃣  InsereCaixa: insere uma nova caixa no topo do Pallet escolhido\n\n");
  printf("4️⃣  RemoveCaixa: remove a caixa do topo do Pallet escolhido\n\n");
  printf("5️⃣  RemovePallet: remove o pallet da numeração escolhida\n\n");
  printf("6️⃣  Saida: finaliza o programa\n\n\n\n");
 
  // Laço que verifica a instrucao a ser realizada 
  while (1) {                                       
    qntCaixas = 0;

    printf("\nQual instrução você deseja realizar?\n");
    scanf("%s", instrucao);
    
    if (instrucao[(strlen(instrucao)) - 1] == '\n') {
      instrucao[strlen(instrucao) - 1] = '\0';
    }

    // Se a instrucao a ser utilizada for InserePallet
    if (strcmp(instrucao, "InserePallet") == 0) {
      
      // Verifica se a lista nao esta cheia
      if (l.qtd < 10) {                             
        printf("\nQual número você deseja designar para o pallet?\n");
        scanf("%d", &numeracao);
        
        numeracao = testenumeracao(&l, numeracao);  // Verifica se o numero passado ja nao esta sendo utilizado  
        insere_lista(&l);
        inicializa_pilha(&(l.sentinela->anterior->data));  // Cria uma nova pilha
        
        printf("\nQuantas caixas você deseja adicionar ao novo pallet?\n");
        scanf("%d", &qntCaixas);
        
        // Impede que a quantidade da pilha seja > 5
        while (qntCaixas > MAX_PILHAS) {
          printf("\nQuantidade de caixas excede o limite ⚠️\n");
          printf("\nInsira uma nova quantidade\n");
          scanf("%d", &qntCaixas); 
        }
        
        // Laco para adicionar as caixas
        for (i = 0; i < qntCaixas; i++) {         
          printf("\nQual o nome da caixa?\n");
          scanf("%s", nomeDaCaixa);
          printf("\nQual a validade da caixa? exemplo: 07(dia) 03(mês) 2024(ano)\n");
          scanf("%d %d %d", &diaDigitado, &mesDigitado, &anoDigitado);

          // Impede que a data inserida seja invalida
          while (1) {
            if (testeDatas(diaDigitado, mesDigitado, anoDigitado) == 1) {
              scanf("%d %d %d", &diaDigitado, &mesDigitado, &anoDigitado);
            } else {
              break;
            }
          }
          //recebe a data digitada do usuario e coloca em uma struct tm
          time_info.tm_year = anoDigitado - 1900;
          time_info.tm_mon = mesDigitado - 1;
          time_info.tm_mday = diaDigitado;

          //converte a estrutura de data e hora (time_info) em um valor do tipo time_t
          time_t data_digitada = mktime(&time_info);
  
          int vencido = testeValidade(dataAtual, data_digitada);

          // Caso em que a data eh anterior a data atual, ou seja, esta vencida
          if(vencido == 1) {
            char decisao[4];
            printf("\n⚠️  A caixa está vencida ⚠️ \n\n");
            printf("Deseja inserir mesmo assim?\n");
            printf("\nDigite: Sim ou Nao\n");
            scanf("%s", decisao);

            // Verifica se o usuario digitou corretamente a decisao
            while(1) {
              if(strcmp(decisao, "Sim") != 0 && strcmp(decisao, "Nao") != 0) {
                printf("\nComando inválido  ❗️\n");
                printf("\nDigite novamente\n");
                scanf("%s", decisao);
              }
              else {
                break;
              }
            }
            // Se a decisao for Sim
            if(strcmp(decisao, "Sim") == 0) {
              adicionarCaixaNaPilha(&l, nomeDaCaixa, data_digitada);
              numeracaoDePallet(&l, numeracao);
              printf("\n");
              printar(&l);
            }
            // Se a decisao for Nao
            else {
              printf("\nA caixa '%s' foi descartada  ❗️\n\n", nomeDaCaixa);
            
              if(vazia_pilha(&(l.sentinela->anterior->data)) != 1) {  //quebra do encapsulamento
                printar(&l);
              }
            }
          }
          // Caso em que a data nao esta vencida
          else {
            adicionarCaixaNaPilha(&l, nomeDaCaixa, data_digitada);
            numeracaoDePallet(&l, numeracao);
            printf("\n");
            printar(&l);
          }
        }
        
        if(vazia_pilha(&(l.sentinela->anterior->data)) != 1) {
           printf("Pallet criado com suceso ✔️\n\n");
        }
        else {
          printf("\nErro ao inserir o Pallet ❌\n\n");
          retira_lista(&l);
        }
      }
      // Se a lista estiver cheia
      else {
        printf("\nA quantidade de pallets já está no limite! ❌ ");
      }

      strcpy(instrucao, "vazio");  // Volta a variavel instrucao para vazio 
    }

    // Se a instrucao a ser utilizada for ProximoDeEstragar
    else if (strcmp(instrucao, "ProximoDeEstragar") == 0) { 
      ProximoDeEstragar(&l, dataAtual);        
      TesteVazio(&l);                          
      // Caso a lista nao esteja vazia, printa o estado dos pallets apos a remocao
      if(vazia_lista(&l)  != 1) {              
        printf("\n❗️ Pallets pós remoção  ❗️\n\n");
        printf("\n");                          
        printar(&l);
      }
    }

    // Se a instrucao a ser utilizada for InsereCaixa
    else if (strcmp(instrucao, "InsereCaixa") == 0) { 
      // Caso a lista nao esteja vazia
      if (vazia_lista(&l) != 1) {     //quebrado encapsulamento           
        int num;
        
        printf("\nEm qual pallet você deseja inserir uma caixa?\n");
        scanf("%d", &num);
        insereCaixa(&l, num);
        printf("\n");
        printar(&l);
      }
      // Caso a lista esteja vazia, nao ha pallets
      else {
        printf("\nErro ao inserir a caixa ❌");
        printf("\nNão há Pallet existente para inserir ⚠️\n");
      }
    }

    // Se a instrucao a ser utilizada for RemoveCaixa
    else if (strcmp(instrucao, "RemoveCaixa") == 0) {
      // Caso a lista nao esteja vazia
      if (l.qtd != 0) {             
        int num;
        
        printf("\nDe qual pallet você deseja remover uma caixa?\n");
        scanf("%d", &num);                          
        removerCaixa(&l, num);
        TesteVazio(&l);                              
        printf("\n");
        printar(&l);                                 
        printf("\nCaixa removida com sucesso ✔️\n");
      } 
      // Caso a lista esteja vazia, nao ha pallets
      else {
        printf("\nErro ao remover a caixa ❌");
        printf("\nNão há Pallet existente para remover ⚠️\n");
      }
    }
     // Se a instrucao a ser utilizada for RemovePallet
    else if (strcmp(instrucao, "RemovePallet") == 0){
      if (l.qtd != 0){
        int num;
        printf("\nQual Pallet deseja remover ?\n");
        scanf("%d", &num);
        //for (int i=0;i<=l.qtd;i++){
          
          removerPallet(&l, num);
          //TesteVazio(&l);
          //printf("\nPallet removido com sucesso✔️\n");
          //printar(&l);
        //}
      }
      else {
        printf("\nErro ao remover o Pallet ❌");
        printf("\nNão há Pallet existente para remover ⚠️\n");
      }
    }

    // Se a instrucao a ser utilizada for Saida
    else if (strcmp(instrucao, "Saida") == 0) {
      printf("\n\n🔺 FIM DO PROGRAMA 🔺");
      destroi_lista(&l);
      break;
    }
      
    // Caso a instrução não seja compativel com nenhuma das opções oferecidas 
    else {
      printf("\nFunção inválida ❌\n");              
    }
  }
}

// Funcao que adiciona a caixa na pilha
void adicionarCaixaNaPilha(Lista *l, char nomeDaCaixa[50], time_t dataValidade) {

  insere_pilha(&(l->sentinela->anterior->data), nomeDaCaixa, dataValidade);
}

// Funcao que retorna a menor caixa do topo dentre todos os pallets
struct node *menorCaixa(Lista *l, time_t dataAtual) { 

  int quantidadePallet = l->qtd;

  struct node *n = l->sentinela->proximo;
  struct node *m = l->sentinela->proximo;

  double diferencaMenorValidade = difftime(dataAtual, topo_pilha(&(n->data)).dataValidade);  

  // Calcula qual a menor data com base na diferenca de segundos entre a data atual e a data inserida
  while (n != l->sentinela->anterior) {  
    // Compara as diferencas entre as datas
    if (diferencaMenorValidade < difftime(dataAtual, topo_pilha(&(n->proximo->data)).dataValidade)) {

      diferencaMenorValidade = difftime(dataAtual, topo_pilha(&(n->proximo->data)).dataValidade);  

      m = n->proximo; // Caso haja uma data menor, o endereco do pallet com essa caixa e salvo em m
    }

    n = n->proximo;
  }

  return (m); // Retornado o endereco m
}

// Funcao que seleciona as 3 menores validades dentre todas as caixas dos topos dos pallets
void ProximoDeEstragar(Lista *l, time_t dataAtual) {  
  int i;
  struct node *n;
  struct tm *dataRetirada[3];
  int menor;
  time_t menores_validades[3];
  struct tm time_info = {0};

  // Laco realizado 3 vezes para achar as 3 menores validades
  if (l->qtd >= 3) {  
    printf("\n  ❗️ Caixas Removidas ❗️\n\n");
    for (i = 0; i < 3; i++) {

      n = menorCaixa(l, dataAtual);  // Retorna o endereco do pallet que contem a menor validade dentre todas as caixas dos topos

      menores_validades[i] = topo_pilha(&(n->data)).dataValidade;  // Guarda na variavel essa menorvalidade

      struct tm *caixaRetirada = localtime(&menores_validades[i]);  // Volta para data essa validade

      caixaRetirada->tm_mon += 1;   // Acerta os valores de ano e mes
      caixaRetirada->tm_year += 1900;

      printf(" ° 📦 | %d / %d / %d | - %s\n", caixaRetirada->tm_mday, caixaRetirada->tm_mon , caixaRetirada->tm_year , n->data.vetor[n->data.topo - 1].nome); // Printa a caixa selecionada 

      time_info.tm_year = 9999;
      time_info.tm_mon = 12;
      time_info.tm_mday = 31;

      time_t data_limite = mktime(&time_info);

      n->data.vetor[(n->data.topo) - 1].dataValidade = data_limite;  // Troca a validade dessa caixa por uma data limite, que sera usada mais tarde como parametro para remocao 
    }

    printf("➖➖➖➖➖➖➖➖➖➖➖➖\n\n");

    RemoveItens(l);
  } 
  // Caso haja menos de 3 pallets, avisa que a quantidade e insuficiente
  else {
    printf("\nQuantidade de Pallets Insuficiente ❌\n");  
  }
}

// Funcao paras remover as caixas que foram selecionadas na funcao ProximoDeEstragar
void RemoveItens(Lista *l) {  
  struct tm time_info = {0};
  time_info.tm_year = 9999;
  time_info.tm_mon = 12;
  time_info.tm_mday = 31;

  time_t data_limite = mktime(&time_info);  

  struct node *n = l->sentinela->proximo; 

  while (n != l->sentinela) {
    if (topo_pilha(&(n->data)).dataValidade == data_limite) {  // Procura as caixas com a validade no limite e as remove da pilha
      tira_pilha(&(n->data));
    }
    n = n->proximo;
  }
}

// Verifica se os pallets estao vazios
void TesteVazio(Lista *l) {  
  struct node *n = l->sentinela->proximo;

  // Atravessa a lista ate atingir o sentinela verificando pallet por pallet
  while (n != l->sentinela) {  
    // Se o  pallet nao tiver caixas, a pilha estiver vazia, esse pallet e desalocado
    if (vazia_pilha(&(n->data)) == 1) {  
      l->qtd--;
      printf("\nO Pallet de número %d foi removido porque estava vazio ❗️\n", n->data.numeracao);
      n = remove_lista(n);  // Desaloca o pallet
    }
    else {
      n = n->proximo;
    }
  }
}

// Funcao para printar todos os pallets e suas respectivas caixas
void printar(Lista *l) {  
  struct node *n = l->sentinela->proximo;

  while (n != l->sentinela) {

    for (int i = n->data.topo - 1; i > -1; i--) {

      struct tm *data = localtime(&n->data.vetor[i].dataValidade);

      printf(" ° 📦 | %d / %d / %d | - %s\n", data->tm_mday, data->tm_mon
             + 1, data->tm_year + 1900 , n->data.vetor[i].nome);
    }

    printf("➖➖➖➖➖➖➖➖➖➖➖➖\n");
    printf("        Pallet %d\n\n", n->data.numeracao);
    n = n->proximo;
  }
}

// Funcao que recebe um valor int e atribui esse valor ao pallet criado
void numeracaoDePallet(Lista *l, int numeracao) { 
  l->sentinela->anterior->data.numeracao = numeracao;
}

// Funcao para inserir uma caixa em um pallet especifico
void insereCaixa(Lista *l, int pallet) {  
  struct node *n = l->sentinela->proximo;
  int flag = 0;
  time_t dataAtual = time(NULL);

  // Procura todos os pallets ate achar o selecionado para inserir a caixa
  while (n != l->sentinela) {
    if (n->data.numeracao == pallet) {  
      // Caso o pallet nao esteja cheio
      if (cheia_pilha(&n->data) != 1) {
        char nome_caixa[50];
        int dia, mes, ano;
        struct tm time_info = {0};

        // Recebe os dados da caixa
        printf("\nQual o nome da caixa?\n");  
        scanf("%s", nome_caixa);
        printf("\nQual a validade da caixa? exemplo: 17 03 2024\n");
        scanf("%d %d %d", &dia, &mes, &ano);

        // Impede que a data inserida seja invalida
        while (1) {
          if (testeDatas(dia, mes, ano) == 1) {
            scanf("%d %d %d", &dia, &mes, &ano);  
          } else {
            break;
          }
        }

        time_info.tm_year = ano - 1900;
        time_info.tm_mon = mes - 1;
        time_info.tm_mday = dia;

        time_t data = mktime(&time_info);

        int validade = testeValidade(dataAtual, data);

        // Caso em que a data eh anterior a data atual, ou seja, esta vencida
        if(validade == 1) {
          char decisao[4];
            printf("\n⚠️  A caixa está vencida ⚠️ \n\n");
            printf("Deseja inserir mesmo assim?\n");
            printf("\nDigite: Sim ou Nao\n");
            scanf("%s", decisao);

            // Verifica se o usuario digitou corretamente a decisao
            while(1) {
              if(strcmp(decisao, "Sim") != 0 && strcmp(decisao, "Nao") != 0) {
                printf("\nComando inválido  ❗️\n");
                printf("\nDigite novamente\n");
                scanf("%s", decisao);
              }
              else {
                break;
              }
            }
            // Se a decisao for Sim
            if(strcmp(decisao, "Sim") == 0) {
              adicionarCaixaNaPilha(l, nome_caixa, data);
              flag = 1; 
              printf("\n");
              printf("\nCaixa inserida com sucesso ✔️\n");
            }
            // Se a decisao for Nao
            else {
              printf("\nA caixa '%s' foi descartada  ❗️\n\n", nome_caixa);
              flag = 1;
            }
        }
        // Caso em que a data nao esta vencida
        else {
          insere_pilha(&n->data, nome_caixa, data);  // Insere a caixa na pilha
          flag = 1;  
          printf("\nCaixa inserida com sucesso ✔️\n");
          break;
        }
      }
      // Mostra erro ao inserir caso o pallet esteja cheio
      else {
        printf("\nErro ao inserir a caixa ❌");   
        printf("\nO Pallet %d está cheio ⚠️\n", n->data.numeracao);
        flag = 1;
      }
    }
    n = n->proximo;
  }

  // Caso nao exista um pallet com o numero passado como parametro, ele le outro numero ate achar um numero valido
  if (flag == 0) { 
    printf("\nO Pallet de número %d não existe ⚠️\n", pallet);
    struct node *n = l->sentinela->proximo;
    if(l->qtd > 1) {
      printf("\nOs números dos Pallets válidos são: ");  // Mostra quais numeros sao validos
      while(n != l->sentinela) {
        printf("%d ", n->data.numeracao);
        n = n->proximo;
      }
    } 
    else {
      printf("O número do Pallet válido é: %d", l->sentinela->proximo->data.numeracao);
    }
    printf("\n");
    printf("\nDigite um número válido\n");
    int pallet1;
    scanf("%d", &pallet1);  // Le outro numero
    insereCaixa(l, pallet1); // Chama a funcao novamente
  }
}

// Funcao criada para a remocao de uma caixa no topo de um pallet especifico
void removerCaixa(Lista *l, int pallet) {  
  struct node *n = l->sentinela->proximo;  // Recebe o endereco da lista e o numero do pallet que tera uma caixa removida
  int flag = 0;

  // Verifica todos os pallets ate achar aquele em que a caixa deve ser removida
  while (n != l->sentinela) {
    if (n->data.numeracao == pallet) {
      // Caso o pallet nao esteja vazio
      if (vazia_pilha(&n->data) != 1) { 
        printf("\nA caixa de nome '%s' foi removida ❗️\n",  // Printa qual caixa sera removida
               n->data.vetor[n->data.topo - 1].nome);
        tira_pilha(&n->data); // Remove da pilha
        flag = 1;
      }
    }
    n = n->proximo;
  }

  // Caso o pallet inserido nao exista ele avisa quais pallets existem para poder realizar a remocao
  if (flag == 0) { 
    printf("\nO Pallet de número %d não existe ⚠️\n\n", pallet);
    struct node *n = l->sentinela->proximo;
    if(l->qtd > 1) {
      printf("\nOs números dos Pallets válidos são: ");  // Mostra quais numeros sao validos
      while(n != l->sentinela) {
        printf("%d ", n->data.numeracao);
        n = n->proximo;
      }
    } 
    else {
      printf("\nO número do Pallet válido é: %d\n", l->sentinela->proximo->data.numeracao);
    }
    printf("\n");
    printf("\nDigite um número válido\n");  // Depois pede a entrada de um numero valido ate dar entrada em um numero que existe, chamando a funcao novamente
    int pallet1;
    scanf("%d", &pallet1);
    removerCaixa(l, pallet1);
  }
}

void removerPallet(Lista *l, int pallet){
 /* struct node *n = l->sentinela->proximo;  

  l->sentinela->proximo->anterior = l->sentinela->anterior;
  l->sentinela->anterior->proximo = l->sentinela->proximo;
  n = l->sentinela; 
  l = n->proximo;     
  free(n);
  */
  struct node *k = l->sentinela->proximo;// = k.data.numeracao;
    
   for (int flag=1, i=0; i<=l->qtd;i++){
     
     if (k->data.numeracao == pallet){
       k->proximo->anterior = k->anterior; 
       k->anterior->proximo = k->proximo; 

       free(k);
      

      flag = 0;
          TesteVazio(l);
          printf("\nPallet removido com sucesso✔️\n");
          printar(l);
          l->qtd--;
       
     }
     if ((i==l->qtd)&&(flag==1)){
       printf("\n❌  Pallet inválido  ❌\n");
       break;
       i=i+l->qtd;
     }
     if (flag==1){
     k = k->proximo;  
     }
     
  }
}

// Funcao que verifica se o mumero atribuido a um pallet esta disponivel
int testenumeracao(Lista *l, int pallet) {  
  struct node *n = l->sentinela->proximo;
  int num = pallet;

  // Verifica o numero de todos os pallets existentes e confere se o numero de estrada 'pallet' ja existe
  while (n != l->sentinela) {  
    // Se ja existir ele avisa e pede a entrada de outro numero, processo que se repete ate receber um numero valido
    if (num == n->data.numeracao) {
      printf("\nEsse número já está atribuido a um Pallet ⚠️\n");  
      printf("Por favor, escolha outro\n");
      scanf("%d", &num);
      n = l->sentinela->proximo;
      break;
    } else {
      n = n->proximo;
    }
  }

  return num;  // Retorna o numero que sera atribuido ao pallet
}

// Funcao que verifica a data inserida, retornando 1 caso seja invalida
int testeDatas(int dia, int mes, int ano) {  
  int bissexto = 0;  // Variavel que recebe o valor 1 caso seja ano bissexto

  if (ano % 400 == 0 || ((ano % 4 == 0) && (ano % 100 != 0))) {
    bissexto = 1;  // Teste de ano bissexto
  }

  // Condicoes para que a data seja invalida
  if (dia == 0 || dia == 31 && mes == 2 || dia == 31 && mes == 4 || dia == 31 && mes == 6 || dia == 31 && mes == 9 || dia == 31 && mes == 11 || dia > 29 && mes == 2 || dia == 29 && mes == 2 && bissexto == 0 || dia > 31 || mes > 12 || dia < 0 || mes < 0 || ano < 0) {
    printf("\nData inválida ❌\n");
    printf("\nDigite uma data válida:\n");
    return 1;
  }
  else {
    return 0;
  }
}

// Funcao que verifica se a data digitada eh uma data vencida
int testeValidade(time_t DataAtual, time_t Datadigitada) {
  int vencido = 0;

  if(difftime(Datadigitada, DataAtual) < 0) {
    vencido = 1;
  }
  return vencido;
}