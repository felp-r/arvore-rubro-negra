#include "../include/verificacao.h"


// Verifica a propriedade 1: Todo no é vermelho ou preto
bool verificar_propriedade1(ArvoreRN *arvore, NoFLA *no){
    // Se for a chamada inicial, comeca pela Raiz
    if(no == nullptr)
        no = arvore->Raiz;

    // Todo no NIL é preto
    if(no == arvore->NIL)
        return true;

    if(no->cor != VERMELHO && no->cor != PRETO)
        return false;

    return verificar_propriedade1(arvore, no->esq) && verificar_propriedade1(arvore, no->dir);
}

// Verifica a propriedade 2: A raiz é sempre preta
bool verificar_propriedade2(ArvoreRN *arvore){
    if(arvore->Raiz == arvore->NIL)
        return true;

    return arvore->Raiz->cor == PRETO;
}

// Verifica a propriedade 3: Toda folha (NULL) é preta
bool verificar_propriedade3(ArvoreRN *arvore){
    return arvore->NIL->cor == PRETO;
}

// Verifica a propriedade 4: Não há dois nós vermelhos consecutivos
bool verificar_propriedade4(ArvoreRN *arvore, NoFLA *no){
    // Se for a chamada inicial, comeca pela Raiz
    if(no == nullptr)
        no = arvore->Raiz;

    if (no == arvore->NIL)
        return true;

    if(no->cor == VERMELHO){
        if(no->esq->cor == VERMELHO)
            return false;

        if(no->dir->cor == VERMELHO)
            return false;
    }

    return verificar_propriedade4(arvore, no->esq) && verificar_propriedade4(arvore, no->dir);
}

// Verifica a propriedade 5: Todo caminho da raiz a uma folha contem o mesmo numero de nos pretos
int verificar_propriedade5(ArvoreRN *arvore, NoFLA *no){
    // Se for a chamada inicial, comeca pela Raiz
    if(no == nullptr)
        no = arvore->Raiz;

    if(no == arvore->NIL)
        return 1;

    int esq = verificar_propriedade5(arvore, no->esq);
    int dir = verificar_propriedade5(arvore, no->dir);

    if(esq == -1 || dir == -1)
        return -1;

    if(esq != dir)
        return -1;

    if(no->cor == PRETO)
        return esq + 1;

    return esq;
}

// Verifica todas as propriedades da arvore
bool verificar_arvore(ArvoreRN *arvore){
    if(!verificar_propriedade1(arvore))
        return false;

    if(!verificar_propriedade2(arvore))
        return false;

    if(!verificar_propriedade3(arvore))
        return false;

    if(!verificar_propriedade4(arvore))
        return false;

    if(verificar_propriedade5(arvore) == -1)
        return false;

    return true;
}