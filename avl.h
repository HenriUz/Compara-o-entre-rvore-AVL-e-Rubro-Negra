#include "ES.h"

/******* Estruturas da Árvore AVL *********/

//Estrutura que representa o nó de uma árvore avl.
typedef struct noAvl noAvl;

//Estrutura que representa a árvore avl.
typedef struct avl avl;

/******* Funções Padrões de Árvore Binária *********/

//Função responsável por criar e inicializar uma estrutura do tipo árvore avl.
avl *criaArvore();

//Função responsável por inserir um nó na árvore avl.
//Retorno: 1 - Sucesso na inserção; 0 - Erro na inserção.
int insereNoAvl(avl *arv, int valor, infos *inf);

//Função responsável por remover um nó na árvore avl, usando a estratégia por cópia com o sucessor.
//Retorno: 1 - Sucesso na remoção; 0 - Árvore Vazia; -1 - Elemento não encontrado.
int removeNoAvl(avl *arv, int valor, infos *inf);

//Função responsável por consultar um elemento na árvore.
//Retorno: 1 - Elemento encontrado; 0 - Árvore vazia; -1 - Elemento não encontrado.
int consultaAvl(avl *arv, int valor);

//Função responsável por imprimir a árvore em pré-ordem recursivamente.
void imprimePreOrdemAvl(noAvl *raiz);

//Função responsável por retornar a raíz da árvore avl (filho direito do sentinela).
noAvl *getRaizAvl(avl *arv);

//Função responsável por retornar a quantidade de elementos da árvore avl.
int getNumElementosAvl(avl *arv);

/***********FUNÇÕES DA AVL**************/

//Função responsável por atualizar os fatores de balanceamento dos nós da sub-árvore onde o nó foi inserido.
//Caso um desbalanceamento seja identificado, chama a função do balanceamento.
void atualizaFB_insercao(avl *arv, noAvl *novoNo, infos *inf);

//Função responsável por chamar as funções de rotações dependendo do caso.
void balanceamento(avl *arv, noAvl *noDesbal, infos *inf);

//Função responsável por rotacionar a árvore avl para a direita.
void rotacaoDirAvl(noAvl *noDesbal);

//Função responsável por rotacionar a árvore avl para a esquerda.
void rotacaoEsqAvl(noAvl *noDesbal);

//Função responsável por atualizar os fatores de balanceamento dos nós da sub-árvore onde o nó foi removido.
//Caso um desbalanceamento seja identificado, chama a função do balanceamento.
//Diferente da inserção, a função não pode parar após um desbalanceamento, logo é necessário chamar ela novamente com avó do nó.
void atualizaFB_remocao(avl *arv, noAvl *pai, int chaveRemovida, infos *inf);
