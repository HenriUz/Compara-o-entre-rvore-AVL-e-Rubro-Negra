#include "ES.h"
#include <stdlib.h>

//Estrutura que armazenará o vetor e o número de rotações.
struct infos{
    int *vet; //Vetor com os elementos que serão inseridos/removidos.
    int rotation; //Número de rotações
};

//Função responsável por alocar e inicializar uma estrutura infos.
infos *criaInfos(){
    infos *inf = (infos*)malloc(sizeof(infos));
    if(!inf){
        return NULL;
    }
    inf->rotation = 0;
    return inf;
}

//Função responsável por criar um vetor de 10000 elementos ordenados.
void criaVetor(infos *inf){
    inf->vet = (int*)malloc(sizeof(int) * tamanho);
    for(int i = 1; i <= tamanho; i++){
        inf->vet[i-1] = i;
    }
}

//Função responsável por retornar o número de rotações da estrutura passada.
int getRotation(infos *inf){
    return inf->rotation;
}

//Função responsável por zerar o número de rotações da estrutura passada.
void setRotation(infos *inf){
    inf->rotation = 0;
}

//Função responsável por incrementar 1 no número de rotações da estrutura passada.
void incRotation(infos *inf){
    inf->rotation+=1;
}

//Função responsável por retornar o ponteiro para o primeiro elemento do vetor da estrutura passada.
int *getVet(infos *inf){
    return inf->vet;
}
