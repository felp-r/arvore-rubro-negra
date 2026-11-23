#include <iostream>
#include "../../include/arvore_abb/abb.hpp"

using namespace std;

ArvoreABB *criar_arvore_abb(){
    ArvoreABB *arvore = new ArvoreABB;

    arvore->NIL = new No;
    arvore->NIL->chave = -1;
    arvore->NIL->esq = arvore->NIL;
    arvore->NIL->dir = arvore->NIL;
    arvore->Raiz = arvore->NIL;

    return arvore;
}

No *criar_no_abb(ArvoreABB *arvore, int valor){
    No *novo = new No;

    novo->chave = valor;
    novo->esq = arvore->NIL;
    novo->dir = arvore->NIL;

    return novo;
}

void inserir_abb(ArvoreABB *arvore, int valor){
    No *pai = arvore->NIL;
    No *atual = arvore->Raiz;

    // Encontra a posicao de insercao
    while(atual != arvore->NIL){
        // Impede a insercao de valores repetidos
        if(valor == atual->chave)
            return;

        pai = atual;

        if(valor < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    // Cria o novo no
    No *novo = criar_no_abb(arvore, valor);

    // Caso a arvore esteja vazia
    if(pai == arvore->NIL){
        arvore->Raiz = novo;
    }
    else if(valor < pai->chave){
        pai->esq = novo;
    }
    else{
        pai->dir = novo;
    }
}

No *busca_abb(ArvoreABB *arvore, int valor){
    No *atual = arvore->Raiz;

    while(atual != arvore->NIL && atual->chave != valor){
        if(valor < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    return atual;
}

int altura_abb(ArvoreABB *arvore, No *no){
    if(no == nullptr)
        no = arvore->Raiz;

    if(no == arvore->NIL)
        return -1;

    int esq = altura_abb(arvore, no->esq);
    int dir = altura_abb(arvore, no->dir);

    if(esq > dir){
        return esq + 1;
    }else{
        return dir + 1;
    }
}

No *remover_abb(ArvoreABB *arvore, No *no, int valor){
    if(no == arvore->NIL)
        return arvore->NIL;

    // Procura o valor na arvore
    if(valor < no->chave){
        no->esq = remover_abb(arvore, no->esq, valor);
    }
    else if(valor > no->chave){
        no->dir = remover_abb(arvore, no->dir, valor);
    }
    else{
        // Caso 1: no sem filhos
        if(no->esq == arvore->NIL && no->dir == arvore->NIL){
            delete no;
            return arvore->NIL;
        }

        // Caso 2: no com apenas um filho a direita
        if(no->esq == arvore->NIL){
            No *temp = no->dir;
            delete no;
            return temp;
        }

        // Caso 2: no com apenas um filho a esquerda
        if(no->dir == arvore->NIL){
            No *temp = no->esq;
            delete no;
            return temp;
        }

        // Caso 3: no com dois filhos
        No *sucessor = encontrar_minimo_abb(arvore, no->dir);

        no->chave = sucessor->chave;

        no->dir = remover_abb(arvore, no->dir, sucessor->chave);
    }

    return no;
}

No* encontrar_minimo_abb(ArvoreABB *arvore, No *no){
    while(no->esq != arvore->NIL){
        no = no->esq;
    }
    return no;
}

void liberar_nos_abb(ArvoreABB *arvore, No *no){
    if(no == arvore->NIL)
        return;

    liberar_nos_abb(arvore, no->esq);
    liberar_nos_abb(arvore, no->dir);

    delete no;
}

void liberar_arvore_abb(ArvoreABB *arvore){
    if(arvore == nullptr)
        return;

    liberar_nos_abb(arvore, arvore->Raiz);

    delete arvore->NIL;
    delete arvore;
}