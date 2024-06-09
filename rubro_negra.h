#include "ES.h"

/**Estruturas da Árvore**/

//Representação de um nó da árvore.
typedef struct noRN noRN;

//Representação da árvore.
typedef struct arvoreRN arvoreRN;

/**Funções da Árvore**/

//Função que cria e inicia os elementos iniciais de uma árvore.
arvoreRN *criaArv();

//Função que insere um novo nó em uma árvore rubro-negra.
//Entrada: ponteiro da árvore, chave do novo nó.
//Saída: 0 - Erro na inserção, 1 - Sucesso na inserção.
int insereNoRN(arvoreRN *arv, int chave, infos *inf);

//Função que remove um nó da árvore rubro-negra.
//Entrada: ponteiro da árvore, chave do nó que será removido.
//Saída: -1 - Elemento não encontrado, 0 - Árvore vazia, 1 - Sucesso na remoção.
int removeNoRN(arvoreRN *arv, int chave, infos *inf);

int consultaRN(arvoreRN *arv, int chave);

//Função responsável por informar a raíz da árvore.
noRN *getRaizRN(arvoreRN *arv);

//Função responsável por informar a quantidade de elementos da árvore.
int getNumElementosRN(arvoreRN *arv);

//Função responsável por imprimir a árvore em pré-ordem.
//Recursiva.
void imprimePreOrdemRN(noRN *raiz);

/**Funções da Rubro-Negra**/

//Função responsável por rotacionar a árvore avl para a esquerda.
void rotacaoEsqRN(noRN *no);

//Função responsável por rotacionar a árvore avl para a direita.
void rotacaoDirRN(noRN *no);

//Função responsável por analisar e corrigir violações que possam ocorrer na inserção de uma árvore rubro-negra.
void analisaRN_Insercao(arvoreRN *arv, noRN *novo, infos *inf);

void analisaRN_Remocao(arvoreRN *arv, noRN *no, infos *inf);
