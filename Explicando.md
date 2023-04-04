<sup><sub>
!!! Clicar no open preview nessa barra de cima
</sub></sup>

# Explicando

👍 O projeto prático em grupo consiste na implementação de uma aplicação que utilize pelo menos duas estruturas de dados lineares implementadas



## 🤯 Como vai ser o projeto:
- Controle de estoque
  - Qual vai ser o proximo pallet que vai sair para entrega?
- Lista com os pallets
- pilha com as caixas
- Olhar para o primeiro elemento da pilha de todos os pallets e colocar na saida
  - Montar um pallet com as caixas qua estao no topo dos outros pallets (analizar as caixas do topo e colocar em um pallet de saida)
- input de lote
  - lote = pallet + caixas empilhadas
  - em cada pallet pode ter qualquer quantidade de caixa ( 1 =< x < 5)
    
- output -> o lote com as 3 caixas com a data de validade mais proximas (lote de saida vai ter um numero fixo de caixas)
- Controle de qualidade
  - se a caixa nao estiver nos conformes ela nao vai sair do estoque mas vai ser descartada
  - se a validade estiver vencida por exemplo
- Controle para quando o estoque estiver cheio (bloquear input)
  
> Não vamos ter que ordenar a lista, nem vamos ter que remover ou adicionar um elemento do meio entao nao vamos ter que implementar a lista com iteradores



# To-do

- [x] Implementar Pilha
- [x] Implementar Lista
- [ ] Interface Gráfica
- [ ] Disponibilizar no GitHub
- [ ] Fazer documentação para deixar pubico



----

### Estruturas a serem utilizadas/implementadas:
1) Pilha, fila ou deque (escolha de acordo com a aplicação) com alocação dinâmica e sequencial.

2) Lista: alocação dinâmica, duplamente encadeada, com sentinela e circular. A lista pode ser ordenada ou não. As inserções e remoções podem ser apenas de início e fim. Para remoções/inserções no meio, faça com o uso de iteradores;

3) Respeitar ao máximo o conceito de TAD, definição e respeito a API (exigência de parâmetros mínimos e nomenclatura).

🔥Todas as estruturas devem ser implementadas em arquivos separados, com os respectivos .h e .c, seguindo uma API definida. Será fundamental respeitar esta API para o uso das estruturas na aplicação.



## Enunciado Completo

O projeto prático em grupo consiste na implementação de uma aplicação que utilize pelo menos duas estruturas de dados lineares implementadas.

A sua aplicação deve ter um objetivo/significado, mas a avaliação irá focar o correto uso das estruturas.

Serão critérios de avaliação:
1) Clareza do código, assim como a documentação;
2) Alocação e desalocação de memória de forma apropriada;
3) Uso das estruturas e complexidade da aplicação;
4) Bônus:
4.1) utilização de uma biblioteca de interface gráfica (https://www.gtk.org/, ou outras),
4.2) testes unitários para a estruturas (https://libcheck.github.io/check/, ou outra),
4.3) entrega também pelo github, com documentação e disponibilização pública.
Estruturas a serem utilizadas/implementadas:
1) Pilha, fila ou deque (escolha de acordo com a aplicação) com alocação dinâmica e sequencial.
2) Lista: alocação dinâmica, duplamente encadeada, com sentinela e circular. A lista pode ser ordenada ou não. As inserções e remoções podem ser apenas de início e fim. Para remoções/inserções no meio, faça com o uso de iteradores;
3) Respeitar ao máximo o conceito de TAD, definição e respeito a API (exigência de parâmetros mínimos e nomenclatura).
Todas as estruturas devem ser implementadas em arquivos separados, com os respectivos .h e .c, seguindo uma API definida. Será fundamental respeitar esta API para o uso das estruturas na aplicação.
