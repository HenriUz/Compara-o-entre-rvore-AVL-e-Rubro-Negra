# Comparaçao entre Árvore AVL e Rubro-Negra
## Autor: HenriUz
Este projeto tem como objetivo comparar as Árvores AVL e Rubro-Negra em quesito ao tempo para inserir e remover 10.000, 100.000, 1.000.000, e 10.000.000 elementos ordenados, e consultar 1.000 elementos aleatórios, também será comparado o número de rotações que cada árvore fez em suas operações de remoção e inserção.

# Arquivos
Os arquivos `ES.c` e `ES.h` são destinadas a entrada e saída dos dados, são neles que estão as funções para gerar o vetor, incrementar o número de rotações, entre outras auxiliares. Já os arquivos `avl.c`, `avl.h`, `rubro_negra.c` e `rubro_negra.h` são os arquivos que contém as estruturas e funções das árvores dos seus respectivos nomes. Por fim a `main.c` é o código principal, é lá que as funções das árvores serão chamadas, e o tempo de cada operação será calculado.

# Resultados
Os testes foram realizados em um computador de mesa com as seguintes especificações:
- Sistema Operacional: Windows 10 pro.
- Processador: AMD Ryzen 5 5600X 6-Core Processor 3.70 GHz.
- RAM: 16 GB.

## AVL
**Inserção**
|  | 10.000 | 100.000 | 1.000.000 | 10.000.000 |
| --------- | ------ | ------- | --------- | ---------- |
| Tempo | 1ms | 9ms | 93ms | 1036ms
| Rotações | 9986 | 99983 | 999980 | 9999976 |

**Remoção** 
|  | 10.000 | 100.000 | 1.000.000 | 10.000.000 |
| --------- | ------ | ------- | --------- | ---------- |
| Tempo | 1ms | 7ms | 67ms | 733ms
| Rotações | 4988 | 49984 | 499981 | 4999978 |

**Consulta:**
A consulta leva aproximadamente 1 milissegundo em todos os casos.

## Rubro-Negra
|  | 10.000 | 100.000 | 1.000.000 | 10.000.000 |
| --------- | ------ | ------- | --------- | ---------- |
| Tempo | 1ms | 11ms | 111ms | 1216ms
| Rotações | 9976 | 99969 | 999963 | 9999956 |

**Remoção** 
|  | 10.000 | 100.000 | 1.000.000 | 10.000.000 |
| --------- | ------ | ------- | --------- | ---------- |
| Tempo | 1ms | 7ms | 69ms | 770ms
| Rotações | 4989 | 49985 | 499982 | 4999979 |

**Consulta:**
A consulta leva aproximadamente 1 milissegundo em todos os casos.

# Conclusão

No geral, a Árvore Rubro-Negra é muito mais utilizada em cenários reais por possuir um melhor pior caso que a Árvore AVL, que é mais lenta na inserção e remoção, por ser bem mais restrita. Mas com estes testes é possível verificar o caso onde a Árvore Rubro-Negra realiza mais rotações que a Árvore AVL, remoção, e é interessante notar isso porque no papel era para a Árvore Rubro-Negra realizar menos rotações, mas a maneira como o balanceamento é propagado pode fazer com que mais rotações sejam realizadas em cenários específicos, como quando elementos são removidos de uma sequência de nós altamente desbalanceados. Por outro lado, a Árvore AVL possui um balanceamento muito mais estrito, e, portanto, podem precisar de rotações mais profundas para reequilibrar após uma remoção, mas essas rotações são focadas em menos nós, pois a altura das subárvores é estritamente controlada. 

