#ifndef INC_12_ATIVIDADE_PRATICA_ES_H
#define INC_12_ATIVIDADE_PRATICA_ES_H

//Estrutura que armazenará o vetor e o número de rotações.
typedef struct infos infos;

//Função responsável por alocar e inicializar uma estrutura infos.
infos *criaInfos();

//Função responsável por criar um vetor de 10000 elementos ordenados.
void criaVetor(infos *inf);

//Função responsável por retornar o número de rotações da estrutura passada.
int getRotation(infos *inf);

//Função responsável por zerar o número de rotações da estrutura passada.
void setRotation(infos *inf);

//Função responsável por incrementar 1 no número de rotações da estrutura passada.
void incRotation(infos *inf);

//Função responsável por retornar o ponteiro para o primeiro elemento do vetor da estrutura passada.
int *getVet(infos *inf);

#endif //INC_12_ATIVIDADE_PRATICA_ES_H
