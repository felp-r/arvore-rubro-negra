#include <iostream>
#include "../include/arvore_rn.h"

using namespace std;

// Cria a arvore
ArvoreRN *criar_arvore(){
    ArvoreRN *arvore = new ArvoreRN;

    arvore->NIL = new NoFLA;
    arvore->NIL->chave = -1;
    arvore->NIL->cor = PRETO;

    arvore->NIL->esq = arvore->NIL;
    arvore->NIL->dir = arvore->NIL;
    arvore->NIL->pai = arvore->NIL;

    arvore->Raiz = arvore->NIL;

    return arvore;
}

// Cria o no
NoFLA *criar_no(ArvoreRN *arvore, int valor){
    NoFLA* novo = new NoFLA;

    novo->chave = valor;
    novo->cor = VERMELHO;
    
    novo->dir = arvore->NIL;
    novo->esq = arvore->NIL;
    novo->pai = arvore->NIL;
    
    return novo;
}

// Libera recursivamente os nos da arvore
void liberar_nos(NoFLA *no, NoFLA *NIL){
    if(no == NIL) return;

    liberar_nos(no->esq, NIL);
    liberar_nos(no->dir, NIL);

    delete no;
}

// Libera a memoria utilizada na arvore
void liberar_arvore(ArvoreRN *arvore){
    if(arvore == nullptr)
        return;

    liberar_nos(arvore->Raiz, arvore->NIL);

    delete arvore->NIL;
    delete arvore;
}

// Exibe a arvore em ordem crescente
void exibir_em_ordem(ArvoreRN *arvore, NoFLA *no){
    if(no == nullptr)
        no = arvore->Raiz;

    if(no == arvore->NIL)
        return;

    exibir_em_ordem(arvore, no->esq);

    cout << no->chave << "["
         << (no->cor == PRETO ? "P" : "V")
         << "] ";

    exibir_em_ordem(arvore, no->dir);
}

// Exibe a arvore indentada
void exibir_arvore_indentada(ArvoreRN *arvore, NoFLA *no, int nivel){
    if(no == nullptr)
        no = arvore->Raiz;

    if(no == arvore->NIL)
        return;

    for(int i = 0; i < nivel; i++)
        cout << "    ";

    cout << "|-- " << no->chave << "["
         << (no->cor == PRETO ? "P" : "V")
         << "]\n";

    exibir_arvore_indentada(arvore, no->esq, nivel + 1);
    exibir_arvore_indentada(arvore, no->dir, nivel + 1);
}


