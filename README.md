# Comparaçao entre Árvore AVL e Rubro-Negra
Este projeto tem como objetivo comparar as Árvores AVL e Rubro-Negra em quesito ao tempo para inserir e remover 10.000 elementos ordenados, e consultar 1.000 elementos aleatórios, também será comparado o número de rotações que cada árvore fez em suas operações de remoção e inserção.

## Arquivos
Os arquivos `ES.c` e `ES.h` são destinadas a entrada e saída dos dados, são neles que estão as funções para gerar o vetor, incrementar o número de rotações, entre outras auxiliares. Já os arquivos `avl.c`, `avl.h`, `rubro_negra.c` e `rubro_negra.h` são os arquivos que contém as estruturas e funções das árvores dos seus respectivos nomes. Por fim a `main.c` é o código principal, é lá que as funções das árvores serão chamadas, e o tempo de cada operação será calculado.
