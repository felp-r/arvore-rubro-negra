#include "../../include/arvore_rn/busca.hpp"


// Busca pelo no a partir da raiz
NoFLA *buscar(ArvoreRN *arvore, int valor){
    NoFLA *atual = arvore->Raiz;

    while(atual != arvore->NIL && atual->chave != valor){
        if(valor < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    return atual;
}

// Encontra o menor valor
NoFLA *minimo(ArvoreRN *arvore, NoFLA *no){
    NoFLA *aux;

    // Se for a chamada inicial, comeca pela Raiz
    if(no == nullptr)
        aux = arvore->Raiz;
    else{
        aux = no;
    }

    while(aux->esq != arvore->NIL)
        aux = aux->esq;

    return aux;
}

// Encontra o maior valor
NoFLA *maximo(ArvoreRN *arvore, NoFLA *no){
    NoFLA *aux;

    // Se for a chamada inicial, comeca pela Raiz
    if(no == nullptr)
        aux = arvore->Raiz;
    else{
        aux = no;
    }

    while(aux->dir != arvore->NIL)
        aux = aux->dir;

    return aux;
}

// Retorna a altura da arvore
int altura(ArvoreRN *arvore, NoFLA *no){
    // Se for a chamada inicial, comeca pela Raiz
    if(no == nullptr){
        no = arvore->Raiz;
    }

    // Caso base: chegou no sentinela NIL
    if(no == arvore->NIL){
        return -1;
    }

    int esq = altura(arvore, no->esq);
    int dir = altura(arvore, no->dir);

    if(esq > dir){
        return esq + 1;
    }else{
        return dir + 1;
    }
}

// Retorna o numero de nos
int nro_nos(ArvoreRN *arvore, NoFLA *no){
    // Se for a chamada inicial, comeca pela Raiz
    if(no == nullptr){
        no = arvore->Raiz;
    }

    // Caso base: chegou no sentinela NIL
    if(no == arvore->NIL){
        return 0;
    }

    int nosEsq = nro_nos(arvore, no->esq);
    int nosDir = nro_nos(arvore, no->dir);

    return 1 + nosEsq + nosDir;
}

