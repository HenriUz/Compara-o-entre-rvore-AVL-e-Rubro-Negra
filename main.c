#include <stdio.h>
#include "ES.h"
#include "avl.h"
#include "rubro_negra.h"
#include <time.h>
#include <stdlib.h>

int main(void) {
    infos *inf;
    arvoreRN *arv1;
    avl *arv2;
    clock_t inicio, fim;
    int num, resp;

    //Criando uma estrutura infos.
    inf = criaInfos();
    if(!inf){
        return 1;
    }

    //Criando o vetor ordenado de 10000 elementos.
    criaVetor(inf);

    printf("Qual árvore você deseja verificar?\n1 - AVL; 2 - Rubro-Negra: ");
    scanf("%d", &resp);
    if(resp == 1){
        /*** Árvore AVL ***/

        //Criando árvore avl.
        arv2 = criaArvore();
        if(!arv2){
            return 1;
        }

        /*** Início do processo de inserção. ***/
        printf("\nInserindo os elementos do vetor.");
        inicio = clock();
        for(int i = 0; i < tamanho; i++){
            insereNoAvl(arv2, getVet(inf)[i], inf);
        }
        fim = clock();
        printf("\nInserções finalizadas.\nNúmero de rotações: %d\nTempo em milissegundos: %f", getRotation(inf), (double)(fim - inicio)/(CLOCKS_PER_SEC/1000));

        //Setando o número de rotações para 0.
        setRotation(inf);

        /*** Início do processo de consulta. ***/
        printf("\n\nConsultando 1000 elementos aleatórios.");

        //Setando a semente dos números aleatórios para o tempo atual do computador.
        srand(time(NULL));

        inicio = clock();
        for(int i = 0; i < 1000; i++){
            num = rand() % (tamanho + 1); //Num vai ser um número aleatório entre 0 e tamanho.
            consultaAvl(arv2, num);
        }
        fim = clock();
        printf("\nConsultas finalizadas.\nTempo em milissegundos: %f", (double)(fim - inicio)/(CLOCKS_PER_SEC/1000));

        /*** Início do processo de remoção. ***/
        printf("\n\nRemovendo os elementos em ordem, a partir do primeiro elemento do vetor.");
        inicio = clock();
        for(int i = 0; i < tamanho; i++){
            removeNoAvl(arv2, getVet(inf)[i], inf);
        }
        fim = clock();
        printf("\nRemoções finalizadas.\nNúmero de rotações: %d\nTempo em milissegundos: %f", getRotation(inf), (double)(fim - inicio)/(CLOCKS_PER_SEC/1000));
        free(arv2);
    }else{
        /*** Árvore Rubro-Negra ***/

        //Criando árvore rubro-negra.
        arv1 = criaArv();
        if(!arv1){
            return 1;
        }

        /*** Início do processo de inserção. ***/
        printf("\nInserindo os elementos do vetor.");
        inicio = clock();
        for(int i = 0; i < tamanho; i++){
            insereNoRN(arv1, getVet(inf)[i], inf);
        }
        fim = clock();
        printf("\nInserções finalizadas.\nNúmero de rotações: %d\nTempo em milissegundos: %f", getRotation(inf), (double)(fim - inicio)/(CLOCKS_PER_SEC/1000));

        //Setando o número de rotações para 0.
        setRotation(inf);

        /*** Início do processo de consulta. ***/
        printf("\n\nConsultando 1000 elementos aleatórios.");

        //Setando a semente dos números aleatórios para o tempo atual do computador.
        srand(time(NULL));

        inicio = clock();
        for(int i = 0; i < 1000; i++){
            num = rand() % (tamanho + 1); //Num vai ser um número aleatório entre 0 e tamanho.
            consultaRN(arv1, num);
        }
        fim = clock();
        printf("\nConsultas finalizadas.\nTempo em milissegundos: %f", (double)(fim - inicio)/(CLOCKS_PER_SEC/1000));

        /*** Início do processo de remoção. ***/
        printf("\n\nRemovendo os elementos em ordem, a partir do primeiro elemento do vetor.");
        inicio = clock();
        for(int i = 0; i < tamanho; i++){
            removeNoRN(arv1, getVet(inf)[i], inf);
        }
        fim = clock();
        printf("\nRemoções finalizadas.\nNúmero de rotações: %d\nTempo em milissegundos: %f", getRotation(inf), (double)(fim - inicio)/(CLOCKS_PER_SEC/1000));
        free(arv1);
    }
    free(getVet(inf));
    free(inf);
    return 0;
}
