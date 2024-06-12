#include "rubro_negra.h"
#include <stdlib.h>
#include <stdio.h>

/**Estruturas da Árvore**/

//Representação de um nó da árvore.
struct noRN{
    char cor; //Cor do nó (b significa Preto e r significa vermelho).
    int chave; //Valor do nó.
    noRN *Fdir, *Fesq, *pai; //Filho direito, Filho esquerdo e pai do nó.
};

//Representação da árvore.
struct arvoreRN{
    noRN *sentinela; //Este nó representa o pai da raíz, ou seja, sua função é armazenar a raíz da árvore no filho direito.
    int numElementos; //Número de nós da árvore, o sentinela não conta.
};

/**Funções da Árvore**/

//Função que cria e inicia uma árvore.
arvoreRN *criaArv(){
    //Alocando espaço para uma árvore.
    arvoreRN *arv = (arvoreRN*)malloc(sizeof(arvoreRN));
    if(!arv){
        return NULL;
    }
    //Instanciando elementos da árvore.
    arv->numElementos = 0;
    arv->sentinela = (noRN*)malloc(sizeof(noRN));
    if(!arv->sentinela){
        free(arv);
        return NULL;
    }
    //Instanciando elementos do sentinela.
    arv->sentinela->chave = -1000;
    arv->sentinela->Fdir = arv->sentinela->Fesq = arv->sentinela->pai = NULL;
    arv->sentinela->cor = 'b';
    return arv;
}

//Função que insere um novo nó em uma árvore rubro-negra.
//Entrada: ponteiro da árvore, chave do novo nó.
//Saída: 0 - Erro na inserção, 1 - Sucesso na inserção.
int insereNoRN(arvoreRN *arv, int chave, infos *inf){
    noRN *aux1, *aux2, *novo = (noRN*)malloc(sizeof(noRN));
    if(!novo){
        return 0;
    }
    novo->Fdir = novo->Fesq = NULL;
    novo->chave = chave;
    novo->cor = 'r';
    if(!arv->sentinela->Fdir){
        novo->pai = arv->sentinela;
        arv->sentinela->Fdir = novo;
    }else{
        aux2 = arv->sentinela->Fdir;
        while(aux2){
            aux1 = aux2;
            if(aux2->chave <= chave){
                aux2 = aux2->Fdir;
            }else{
                aux2 = aux2->Fesq;
            }
        }
        novo->pai = aux1;
        if(aux1->chave <= chave){
            aux1->Fdir = novo;
        }else{
            aux1->Fesq = novo;
        }
    }
    arv->numElementos++;
    analisaRN_Insercao(arv, novo, inf);
    return 1;
}

//Função que remove um nó da árvore rubro-negra.
//Entrada: ponteiro da árvore, chave do nó que será removido.
//Saída: -1 - Elemento não encontrado, 0 - Árvore vazia, 1 - Sucesso na remoção.
int removeNoRN(arvoreRN *arv, int valor, infos *inf){
    noRN *atual, *aux = NULL; //Atual será quem percorre a árvore, o aux é um auxiliar utilizado somente quando o nó tiver mais de 1 filho.
    //Verificando se a árvore está vazia.
    if(arv->numElementos){
        //Percorrendo a árvore a partir da raíz.
        atual = arv->sentinela->Fdir;
        while(atual && atual->chave != valor){
            if(atual->chave > valor){
                atual = atual->Fesq;
            }else{
                atual = atual->Fdir;
            }
        }
        //Verificando se o elemento foi encontrado.
        if(atual){
            //Verificando os filhos que o nó possui.
            if(!atual->Fdir && !atual->Fesq){
                //O nó não possui nenhum filho, logo é só desvincular ele do pai.
                if(atual == atual->pai->Fdir){
                    atual->pai->Fdir = NULL;
                }else{
                    atual->pai->Fesq = NULL;
                }
            }else if(atual->Fdir && atual->Fesq){
                //O nó possui os dois filhos, logo é necessário pegar o sucessor e trocar as chaves, removendo o sucessor no fim.
                aux = atual; //aux guardará o elemento que será removido.
                atual = atual->Fdir; //atual irá procurar o sucessor.
                //Buscando o sucessor.
                while(atual->Fesq){
                    atual = atual->Fesq;
                }
                //Copiando a chave do sucessor.
                aux->chave = atual->chave;
                //Desvinculando o sucessor com o pai dele.
                if(atual == atual->pai->Fdir){
                    atual->pai->Fdir = atual->Fdir;
                }else{
                    atual->pai->Fesq = atual->Fdir;
                }
                //Verificando se é possível vincular o filho do sucessor com o pai.
                if(atual->Fdir){
                    atual->Fdir->pai = atual->pai;
                }
            }else if(atual->Fdir){
                //O nó só possui o filho direito, logo é só desvincular o nó atual e vincular o filho direito com o pai do atual.
                //Vinculando o pai com o filho.
                if(atual == atual->pai->Fdir){
                    atual->pai->Fdir = atual->Fdir;
                }else{
                    atual->pai->Fesq = atual->Fdir;
                }
                //Vinculando o filho com o pai.
                atual->Fdir->pai = atual->pai;
            }else{
                //O nó só possui o filho esquerdo, segue a mesma lógica do de cima.
                //Vinculando o pai com o filho.
                if(atual == atual->pai->Fdir){
                    atual->pai->Fdir = atual->Fesq;
                }else{
                    atual->pai->Fesq = atual->Fesq;
                }
                //Vinculando o filho com o pai.
                atual->Fesq->pai = atual->pai;
            }
            //Atualizando a quantidade de elementos da árvore avl.
            arv->numElementos--;
            if(atual->cor == 'b'){
                analisaRN_Remocao(arv, atual, inf);
            }
            //Libertando a variável alocada.
            free(atual);
            atual = NULL;
            return 1;
        }
        return -1;
    }
    return 0;
}

int consultaRN(arvoreRN *arv, int chave){
    noRN *aux;
    if(arv->numElementos){
        aux = arv->sentinela->Fdir;
        while(aux && aux->chave != chave){
            if(aux->chave > chave){
                aux = aux->Fesq;
            }else{
                aux = aux->Fdir;
            }
        }
        if(aux){
            return 1;
        }
        return -1;
    }
    return 0;
}

//Função responsável por informar a raíz da árvore.
noRN *getRaizRN(arvoreRN *arv){
    return arv->sentinela->Fdir;
}

//Função responsável por informar a quantidade de elementos da árvore.
int getNumElementosRN(arvoreRN *arv){
    return arv->numElementos;
}

//Função responsável por imprimir a árvore em pré-ordem.
//Recursiva.
void imprimePreOrdemRN(noRN *raiz){
    //Verificando se o nó atual é nulo ou não.
    if(raiz){
        //Imprime o nó atual, depois o filho esquerdo e depois o filho direito.
        printf("%d - %d - %c\n",raiz->chave, raiz->pai->chave, raiz->cor);
        imprimePreOrdemRN(raiz->Fesq);
        imprimePreOrdemRN(raiz->Fdir);
    }
}

/**Funções da Rubro-Negra**/

//Função responsável por rotacionar a árvore avl para a esquerda.
void rotacaoEsqRN(noRN *no){
    //Rotação para Esquerda:
    //O filho direito do nó desbalanceado vai ocupar o lugar do nó desbalanceado.
    //O filho esquerdo do filho direito vai se tornar o filho direito do nó desbalanceado.

    //Desvinculando o pai com o nó desbalanceado, e vinculando ele com o filho direito.
    if(no == no->pai->Fesq){
        no->pai->Fesq = no->Fdir;
    }else{
        no->pai->Fdir = no->Fdir;
    }
    //Vinculando o filho direito com o pai.
    no->Fdir->pai = no->pai;
    //Vinculando o filho direito como o novo pai.
    no->pai = no->Fdir;
    //Vinculando o novo filho direito.
    no->Fdir = no->pai->Fesq;
    if(no->Fdir){
        //Vinculando o novo filho direito com o novo pai.
        no->Fdir->pai = no;
    }
    //Vinculando o nó desbalanceado como filho do novo pai.
    no->pai->Fesq = no;
}

//Função responsável por rotacionar a árvore avl para a direita.
void rotacaoDirRN(noRN *no){
    //Rotação para Direita:
    //O filho esquerdo do nó desbalanceado vai ocupar o lugar do nó desbalanceado.
    //O filho direito do filho esquerdo vai se tornar o filho esquerdo do nó desbalanceado.

    //Desvinculando o pai com o nó desbalanceado, e vinculando ele com o filho esquerdo.
    if(no == no->pai->Fesq){
        no->pai->Fesq = no->Fesq;
    }else{
        no->pai->Fdir = no->Fesq;
    }
    //Vinculando o filho esquerdo com o pai.
    no->Fesq->pai = no->pai;
    //Vinculando o filho esquerdo como o novo pai.
    no->pai = no->Fesq;
    //Vinculando o novo filho esquerdo.
    no->Fesq = no->pai->Fdir;
    if(no->Fesq){
        //Vinculando o novo filho esquerdo com o novo pai.
        no->Fesq->pai = no;
    }
    //Vinculando o nó desbalanceado como filho do novo pai.
    no->pai->Fdir = no;
}

//Função responsável por analisar e corrigir violações que possam ocorrer na inserção em uma árvore rubro-negra.
void analisaRN_Insercao(arvoreRN *arv, noRN *novo, infos *inf){
    //Se o nó não for a raíz, e o pai for vermelho devemos analisar os casos.
    while(novo->pai != arv->sentinela && novo->pai->cor == 'r'){
        //Verificando onde está tio.
        if(novo->pai == novo->pai->pai->Fesq){
            //Tio é o filho direito do avô.
            if(novo->pai->pai->Fdir && novo->pai->pai->Fdir->cor == 'r'){
                //Caso 1: Nó, Pai e Tio são vermelhos.
                //Pai e Tio se tornam pretos.
                //Avô se torna vermelho.
                //Analisa o avô recursivamente.
                novo->pai->cor = novo->pai->pai->Fdir->cor = 'b';
                novo->pai->pai->cor = 'r';
                novo = novo->pai->pai;
            }else{
                if(novo == novo->pai->Fdir){
                    //Caso 2: Tio é preto ou nulo, e o nó analisado é um filho direito.
                    //Rotação à esquerda no pai, que passará a ser o nó analisado.
                    novo = novo->pai;
                    rotacaoEsqRN(novo);
                    incRotation(inf);
                }
                //Caso 3: Tio é preto ou nulo, e o nó analisado é um filho esquerdo.
                //Pai se torna preto.
                //Avô se torna vermelho.
                //Rotação à direita no avô.
                novo->pai->cor = 'b';
                novo->pai->pai->cor = 'r';
                rotacaoDirRN(novo->pai->pai);
                incRotation(inf);
            }
        }else{
            //Tio é filho esquerdo do avô.
            if(novo->pai->pai->Fesq && novo->pai->pai->Fesq->cor == 'r'){
                //Caso 1: Nó, Pai e Tio são vermelhos.
                //Pai e Tio se tornam pretos.
                //Avô se torna vermelho.
                //Avalia o avô recursivamente.
                novo->pai->cor = novo->pai->pai->Fesq->cor = 'b';
                novo->pai->pai->cor = 'r';
                novo = novo->pai->pai;
            }else{
                if(novo == novo->pai->Fesq){
                    //Caso 2: O tio é preto ou nulo, e o nó analisado é um filho esquerdo.
                    //Rotação à direita no pai, que passará a ser o nó analisado.
                    novo = novo->pai;
                    rotacaoDirRN(novo);
                    incRotation(inf);
                }
                //Caso 3: O tio é preto ou nulo, e o nó analisado é um filho direito.
                //Pai se torna preto.
                //Avô se torna vermelho.
                //Rotação à esquerda no avô.
                novo->pai->cor = 'b';
                novo->pai->pai->cor = 'r';
                rotacaoEsqRN(novo->pai->pai);
                incRotation(inf);
            }
        }
    }
    //Raíz da árvore deve ser preto.
    arv->sentinela->Fdir->cor = 'b';
}

//Função responsável por analisar e corrigir violações que possam ocorrer na remoção em uma árvore rubro-negra.
void analisaRN_Remocao(arvoreRN *arv, noRN *noRem, infos *inf){
    noRN *aux = NULL; //Variável que representa o nó substituto, ou o irmão, caso o sucessor seja preto ou inexistente.
    //Verificando se existe algum substituto. É impossível haver mais de 1.
    if(noRem->Fdir){
        aux = noRem->Fdir;
    }else{
        aux = noRem->Fesq;
    }
    //Se o substituto existir e for da cor vermelha, só troca a cor dele. Se ele não existir, ou for preto, mais verificações são necessárias.
    if(aux && aux->cor == 'r'){
        aux->cor = 'b';
    }else {
        while (noRem->pai != arv->sentinela && noRem->cor == 'b') {
            //Verificando onde está o irmão.
            if(noRem->chave < noRem->pai->chave){
                //Irmão é filho direito.
                aux = noRem->pai->Fdir;
                if(aux->cor == 'r'){
                    //Caso 1: O irmão é vermelho.
                    //Irmão se torna preto.
                    //Pai se torna vermelho.
                    //Rotação à esquerda no pai.
                    //Corrigi o irmão (filho direito do pai).
                    //Leva a alguns dos casos 2, 3 ou 4.
                    aux->cor = 'b';
                    noRem->pai->cor = 'r';
                    rotacaoEsqRN(noRem->pai);
                    incRotation(inf);
                    aux = noRem->pai->Fdir;
                }
                if((!aux->Fesq || aux->Fesq->cor == 'b') && (!aux->Fdir || aux->Fdir->cor == 'b')){
                    //Caso 2: O irmão é preto, e seus dois filhos são pretos ou não existem.
                    //Irmão se torna vermelho.
                    //O nó analisado passa a ser o pai (se for vermelho sai do loop e vira preto, se for preto é analisado novamente).
                    aux->cor = 'r';
                    noRem = noRem->pai;
                }else{
                    if(!aux->Fdir || aux->Fdir->cor == 'b'){
                        //Caso 3: O irmão é preto e seu filho esquerdo é vermelho e seu direito é preto, ou nulo.
                        //Filho esquerdo do irmão se torna preto.
                        //Irmão se torna vermelho.
                        //Rotação direita no irmão.
                        //Corrigi o irmão (filho direito do pai).
                        //Leva ao caso 4.
                        aux->Fesq->cor = 'b';
                        aux->cor = 'r';
                        rotacaoDirRN(aux);
                        incRotation(inf);
                        aux = noRem->pai->Fdir;
                    }
                    //Caso 4: O irmão é preto e seu filho direito é vermelho.
                    //Cor do irmão se torna a cor do pai.
                    //Pai se torna preto.
                    //Filho direito do irmão se torna preto.
                    //Rotação à esquerda no pai.
                    //Finaliza.
                    aux->cor = noRem->pai->cor;
                    noRem->pai->cor = 'b';
                    if(aux->Fdir){
                        aux->Fdir->cor = 'b';
                    }
                    rotacaoEsqRN(noRem->pai);
                    incRotation(inf);
                    noRem = arv->sentinela->Fdir;
                }
            }else{
                //Irmão é filho esquerdo.
                aux = noRem->pai->Fesq;
                if(aux->cor == 'r'){
                    //Caso 1: O irmão é vermelho.
                    //Irmão se torna preto.
                    //Pai se torna vermelho.
                    //Rotação à direita no pai.
                    //Corrigi o irmão (filho esquerdo do pai).
                    //Leva a alguns dos casos 2, 3 ou 4.
                    aux->cor = 'b';
                    noRem->pai->cor = 'r';
                    rotacaoDirRN(noRem->pai);
                    incRotation(inf);
                    aux = noRem->pai->Fesq;
                }
                if((!aux->Fesq || aux->Fesq->cor == 'b') && (!aux->Fdir || aux->Fdir->cor == 'b')){
                    //Caso 2: O irmão é preto, e seus dois filhos são pretos ou não existem.
                    //Irmão se torna vermelho.
                    //O nó analisado passa a ser o pai (se for vermelho sai do loop e vira preto, se for preto é analisado novamente).
                    aux->cor = 'r';
                    noRem = noRem->pai;
                }else{
                    if(!aux->Fesq || aux->Fesq->cor == 'b'){
                        //Caso 3: O irmão é preto e seu filho direito é vermelho e seu esquerdo é preto, ou nulo.
                        //Filho direito do irmão se torna preto.
                        //Irmão se torna vermelho.
                        //Rotação esquerda no irmão.
                        //Corrigi o irmão (filho esquerdo do pai).
                        //Leva ao caso 4.
                        aux->Fdir->cor = 'b';
                        aux->cor = 'r';
                        rotacaoEsqRN(aux);
                        incRotation(inf);
                        aux = noRem->pai->Fesq;
                    }
                    //Caso 4: O irmão é preto e seu filho esquerdo é vermelho.
                    //Cor do irmão se torna a cor do pai.
                    //Pai se torna preto.
                    //Filho esquerdo do irmão se torna preto.
                    //Rotação à direita no pai.
                    //Finaliza.
                    aux->cor = noRem->pai->cor;
                    noRem->pai->cor = 'b';
                    if(aux->Fesq){
                        aux->Fesq->cor = 'b';
                    }
                    rotacaoDirRN(noRem->pai);
                    incRotation(inf);
                    noRem = arv->sentinela->Fdir;
                }
            }
        }
        //Deixando a raíz preta ou colorindo o pai de preto (após o caso 2).
        noRem->cor = 'b';
    }
}
