#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

/******* Estruturas da Árvore AVL *********/

//Estrutura que representa o nó de uma árvore avl.
struct noAvl{
    int chave; //Valor do nó
    int fb; //Fator de Balanceamento do nó
    noAvl *Fesq; //Filho esquerdo do nó (Fesq->chave < chave)
    noAvl *Fdir; //Filho direito do nó (Fdir->chave >= chave)
    noAvl *pai; //Pai do nó
};

//Estrutura que representa a árvore avl.
struct avl{
    noAvl *sentinela; //Este nó representa o pai da raíz, ou seja, sua função é armazenar a raíz da árvore no filho direito.
    int numElementos; //Número de nós da árvore, o sentinela não conta.
};

/******* Funções Padrões de Árvore Binária *********/

//Função responsável por criar e inicializar uma estrutura do tipo árvore avl.
avl *criaArvore(){
    //Alocando espaço para uma árvore avl.
    avl *arv = (avl*)malloc(sizeof(avl));
    if(!arv){
        return NULL;
    }
    //Inicializando os elementos da árvore avl.
    arv->numElementos = 0;
    arv->sentinela = (noAvl*)malloc(sizeof(noAvl));
    if(!arv->sentinela){
        free(arv);
        return NULL;
    }
    //Inicializando os elementos do nó sentinela.
    arv->sentinela->pai = arv->sentinela->Fdir = arv->sentinela->Fesq = NULL;
    arv->sentinela->chave = -1000;
    arv->sentinela->fb = 0;
    return arv;
}

//Função responsável por inserir um nó na árvore avl.
//Retorno: 1 - Sucesso na inserção; 0 - Erro na inserção.
int insereNoAvl(avl *arv, int valor, infos *inf){
    //Alocando espaço para um nó da árvore avl.
    noAvl *aux, *atual, *novo = (noAvl*)malloc(sizeof(noAvl));
    if(!novo){
        return 0;
    }
    //Inicializando o nó.
    novo->chave = valor;
    novo->fb = 0;
    novo->Fesq = novo->Fdir = NULL;
    //Verificando se a árvore está vazia.
    if(!arv->numElementos){
        //Se estiver, basta lincar a raíz com o sentinela.
        arv->sentinela->Fdir = novo;
        novo->pai = arv->sentinela;
    }else{
        //Se não estiver, tem que achar a posição do novo nó.
        //Atual é uma variável que irá representar o pai, e o aux é a variável que encontrará a posição (NULL).
        atual = aux = arv->sentinela->Fdir;
        //Percorrendo a árvore até achar a posição.
        while(aux){
            atual = aux;
            if(aux->chave > valor){
                aux = aux->Fesq;
            }else{
                aux = aux->Fdir;
            }
        }
        //Lincando o nó criado com o atual.
        novo->pai = atual;
        if(atual->chave > valor){
            atual->Fesq = novo;
        }else{
            atual->Fdir = novo;
        }
    }
    //Incrementando o número de elementos da árvore.
    arv->numElementos++;
    //Chamando a função responsável por atualizar os fatores de balanceamento na inserção.
    atualizaFB_insercao(arv, novo, inf);
    return 1;
}

//Função responsável por remover um nó na árvore avl, usando a estratégia por cópia com o sucessor.
//Retorno: 1 - Sucesso na remoção; 0 - Árvore Vazia; -1 - Elemento não encontrado.
int removeNoAvl(avl *arv, int valor, infos *inf){
    noAvl *atual, *aux; //Atual será quem percorre a árvore, o aux é um auxiliar utilizado somente quando o nó tiver mais de 1 filho.
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
                if(atual->chave >= atual->pai->chave){
                    atual->pai->Fdir = NULL;
                }else{
                    atual->pai->Fesq = NULL;
                }
            }else if(atual->Fdir && atual->Fesq){
                //O nó possui os dois filhos, logo é necessário pegar o sucessor e trocar as chaves, removendo o sucessor no fim.
                aux = atual; //aux guardará o elemento que será removido.
                atual = atual->Fdir; //atual irá procurar o sucessor.
                while(atual->Fesq){
                    atual = atual->Fesq;
                }
                //Copiando a chave do sucessor.
                aux->chave = atual->chave;
                //Desvinculando o sucessor com o pai dele.
                if(atual->chave >= atual->pai->chave){
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
                if(atual->chave >= atual->pai->chave){
                    atual->pai->Fdir = atual->Fdir;
                }else{
                    atual->pai->Fesq = atual->Fdir;
                }
                //Vinculando o filho com o pai.
                atual->Fdir->pai = atual->pai;
            }else{
                //O nó só possui o filho esquerdo, segue a mesma lógica do de cima.
                //Vinculando o pai com o filho.
                if(atual->chave >= atual->pai->chave){
                    atual->pai->Fdir = atual->Fesq;
                }else{
                    atual->pai->Fesq = atual->Fesq;
                }
                //Vinculando o filho com o pai.
                atual->Fesq->pai = atual->pai;
            }
            //Atualizando a quantidade de elementos da árvore avl.
            arv->numElementos--;
            //Chamando função responsável por atualizar os fatores de balanceamento dos nós na remoção.
            atualizaFB_remocao(arv, atual->pai, atual->chave, inf);
            //Libertando a variável alocada.
            free(atual);
            atual = NULL;
            return 1;
        }
        return -1;
    }
    return 0;
}

//Função responsável por consultar um elemento na árvore.
//Retorno: 1 - Elemento encontrado; 0 - Árvore vazia; -1 - Elemento não encontrado.
int consultaAvl(avl *arv, int valor){
    noAvl *aux;
    if(arv->numElementos){
        //Percorrendo a árvore a partir da raiz.
        aux = arv->sentinela->Fdir;
        while(aux && aux->chave != valor){
            if(aux->chave > valor){
                aux = aux->Fesq;
            }else{
                aux = aux->Fdir;
            }
        }
        if(aux){
            //Elemento encontrado.
            return 1;
        }
        //Elemento não encontrado.
        return -1;
    }
    return 0;
}

//Função responsável por imprimir a árvore em pré-ordem recursivamente.
void imprimePreOrdemAvl(noAvl *raiz){
    //Verificando se o nó atual é nulo ou não.
    if(raiz){
        //Imprime o nó atual, depois o filho esquerdo e depois o filho direito.
        printf("%d - %d - %d\n",raiz->chave, raiz->pai->chave, raiz->fb);
        imprimePreOrdemAvl(raiz->Fesq);
        imprimePreOrdemAvl(raiz->Fdir);
    }
}

//Função responsável por retornar a raíz da árvore avl (filho direito do sentinela).
noAvl *getRaizAvl(avl *arv){
    return arv->sentinela->Fdir;
}

//Função responsável por retornar a quantidade de elementos da árvore avl.
int getNumElementosAvl(avl *arv){
    return arv->numElementos;
}

/******* Funções da Árvore AVL *********/

//Função responsável por atualizar os fatores de balanceamento dos nós da sub-árvore onde o nó foi inserido.
//Caso um desbalanceamento seja identificado, chama a função do balanceamento.
void atualizaFB_insercao(avl *arv, noAvl *novo, infos *inf){
    noAvl *aux = novo;
    //Percorrendo os nós pais, e atualizando os fatores de balanceamento dos pais.
    //Condições de parada: fb == 0 (altura da sub-árvore não mudou); chegou no sentinela; desbalanceou (fb == 2/-2).
    do{
        if(aux->chave < aux->pai->chave && aux->pai != arv->sentinela){
            aux->pai->fb--;
        }else if(aux->pai != arv->sentinela){
            aux->pai->fb++;
        }
        aux = aux->pai;
    }while(aux->fb != 0 && aux->fb != 2 && aux->fb != -2 && aux != arv->sentinela);
    //Verificando se houve desbalanceamento.
    if(aux->fb == 2 || aux->fb == -2){
        //Chamando função que irá desbalancear.
        balanceamento(arv, aux, inf);
    }
}

//Função responsável por chamar as funções de rotações dependendo do caso.
void balanceamento(avl *arv, noAvl *noDesbal, infos *inf){
    noAvl *filho;
    //Verificando qual sub-árvore está maior.
    if(noDesbal->fb == 2){
        //A sub-árvore direita está maior que a esquerda.

        filho = noDesbal->Fdir;
        if(filho->fb >= 0){
            //Rotação Simples

            //Atualizando os fatores de balanceamento dos nós envolvidos na rotação.
            if(filho->fb == 1){
                noDesbal->fb = filho->fb = 0;
            }else{
                noDesbal->fb = 1;
                filho->fb = -1;
            }

            //Rotacionando
            rotacaoEsqAvl(noDesbal);
            incRotation(inf);

            //Verificando a raiz
            if(arv->sentinela->Fdir == noDesbal){
                arv->sentinela->Fdir = filho;
            }
        }else{
            //Rotação dupla

            //Atualizando os fatores de balanceamento dos nós envolvidos na rotação.
            if(filho->Fesq->fb == 0){
                noDesbal->fb = filho->fb = 0;
            }else if(filho->Fesq->fb == 1){
                noDesbal->fb = -1;
                filho->fb = 0;
            }else{
                noDesbal->fb = 0;
                filho->fb = 1;
            }
            filho->Fesq->fb = 0;

            //Rotacionando
            rotacaoDirAvl(filho);
            rotacaoEsqAvl(noDesbal);
            incRotation(inf);
            incRotation(inf);

            //Verificando a raiz
            if(arv->sentinela->Fdir == noDesbal){
                arv->sentinela->Fdir = noDesbal->pai;
            }
        }
    }else{
        //A sub-árvore esquerda está maior que a direita.

        filho = noDesbal->Fesq;
        if(filho->fb <= 0){
            //Rotação Simples

            //Atualizando os fatores de balanceamento dos nós envolvidos na rotação.
            if(filho->fb == -1){
                noDesbal->fb = filho->fb = 0;
            }else{
                noDesbal->fb = -1;
                filho->fb = 1;
            }

            //Rotacionando
            rotacaoDirAvl(noDesbal);
            incRotation(inf);

            //Verificando a raiz
            if(arv->sentinela->Fdir == noDesbal){
                arv->sentinela->Fdir = filho;
            }
        }else{
            //Rotação Dupla

            //Atualizando os fatores de balanceamento dos nós envolvidos na rotação.
            if(filho->Fdir->fb == 0){
                noDesbal->fb = filho->fb = 0;
            }else if(filho->Fdir->fb == 1){
                noDesbal->fb = 0;
                filho->fb = -1;
            }else{
                noDesbal->fb = 1;
                filho->fb = 0;
            }
            filho->Fdir->fb = 0;

            //Rotacionando
            rotacaoEsqAvl(filho);
            rotacaoDirAvl(noDesbal);
            incRotation(inf);
            incRotation(inf);

            //Verificando a raiz
            if(arv->sentinela->Fdir == noDesbal){
                arv->sentinela->Fdir = noDesbal->pai;
            }
        }
    }
}

//Função responsável por rotacionar a árvore avl para a direita.
void rotacaoDirAvl(noAvl *noDesbal){
    //Rotação para Direita:
    //O filho esquerdo do nó desbalanceado vai ocupar o lugar do nó desbalanceado.
    //O filho direito do filho esquerdo vai se tornar o filho esquerdo do nó desbalanceado.

    //Desvinculando o pai com o nó desbalanceado, e vinculando ele com o filho esquerdo.
    if(noDesbal == noDesbal->pai->Fesq){
        noDesbal->pai->Fesq = noDesbal->Fesq;
    }else{
        noDesbal->pai->Fdir = noDesbal->Fesq;
    }
    //Vinculando o filho esquerdo com o pai.
    noDesbal->Fesq->pai = noDesbal->pai;
    //Vinculando o filho esquerdo como o novo pai.
    noDesbal->pai = noDesbal->Fesq;
    //Vinculando o novo filho esquerdo.
    noDesbal->Fesq = noDesbal->pai->Fdir;
    if(noDesbal->Fesq){
        //Vinculando o novo filho esquerdo com o novo pai.
        noDesbal->Fesq->pai = noDesbal;
    }
    //Vinculando o nó desbalanceado como filho do novo pai.
    noDesbal->pai->Fdir = noDesbal;
}

//Função responsável por rotacionar a árvore avl para a esquerda.
void rotacaoEsqAvl(noAvl *noDesbal){
    //Rotação para Esquerda:
    //O filho direito do nó desbalanceado vai ocupar o lugar do nó desbalanceado.
    //O filho esquerdo do filho direito vai se tornar o filho direito do nó desbalanceado.

    //Desvinculando o pai com o nó desbalanceado, e vinculando ele com o filho direito.
    if(noDesbal == noDesbal->pai->Fesq){
        noDesbal->pai->Fesq = noDesbal->Fdir;
    }else{
        noDesbal->pai->Fdir = noDesbal->Fdir;
    }
    //Vinculando o filho direito com o pai.
    noDesbal->Fdir->pai = noDesbal->pai;
    //Vinculando o filho direito como o novo pai.
    noDesbal->pai = noDesbal->Fdir;
    //Vinculando o novo filho direito.
    noDesbal->Fdir = noDesbal->pai->Fesq;
    if(noDesbal->Fdir){
        //Vinculando o novo filho direito com o novo pai.
        noDesbal->Fdir->pai = noDesbal;
    }
    //Vinculando o nó desbalanceado como filho do novo pai.
    noDesbal->pai->Fesq = noDesbal;
}

//Função responsável por atualizar os fatores de balanceamento dos nós da sub-árvore onde o nó foi removido.
//Caso um desbalanceamento seja identificado, chama a função do balanceamento.
//Diferente da inserção, a função não pode parar após um desbalanceamento, logo é necessário chamar ela novamente com avó do nó.
void atualizaFB_remocao(avl *arv, noAvl *pai, int chaveRemovida, infos *inf){
    noAvl *aux = pai;
    if(aux == arv->sentinela){
        return;
    }
    //Percorrendo os nós, e atualizando seus fatores de balanceamento.
    //Condições de parada: fb == 1/-1 (altura da sub-árvore não mudou); chegou no sentinela; desbalanceou (fb == 2/-2).
    if(chaveRemovida < aux->chave) {
        aux->fb++;
    }else{
        aux->fb--;
    }
    while(aux->pai != arv->sentinela && aux->fb != 2 && aux->fb != -2 && aux->fb != -1 && aux->fb != 1){
        aux = aux->pai;
        if(chaveRemovida < aux->chave) {
            aux->fb++;
        }else{
            aux->fb--;
        }
    }
    //Verificando se houve um desbalanceamento.
    if(aux->fb == 2 || aux->fb == -2){
        balanceamento(arv, aux, inf);
        if(aux->pai != arv->sentinela && aux->pai->fb == 0){
            atualizaFB_remocao(arv, aux->pai->pai, chaveRemovida, inf);
        }
    }
}