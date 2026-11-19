#include <iostream>

#include "../include/insercao.h"
#include "../include/rotacao.h"

using namespace std;

// Insere um novo no na arvore
void inserir(ArvoreRN *arvore, int valor){
    NoFLA* y = arvore->NIL;   // Guarda o pai do no atual
    NoFLA* x = arvore->Raiz;   // Ponteiro que percorre a arvore

    // 1. Primeiro percorre a arvore buscando a posição
    while (x != arvore->NIL) {
        y = x;
        if (valor < x->chave) {
            x = x->esq;
        } else if (valor > x->chave) {
            x = x->dir;
        } else {
            // A chave ja existe na arvore
            cout << "\nA arvore ja possui um nó com esta chave: " << valor << "\n";
            return;
        }
    }


    // 2. So aloca memoria se a chave for inedita

    // Novo no a ser inserido
    NoFLA* z = criar_no(arvore, valor);

    // Encontra a posição correta para inserir
    while(x != arvore->NIL){
        y = x;
        if(z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }

    // Define o pai de z
    z->pai = y;
        
    // Conecta z na arvore
    if(y == arvore->NIL)
        arvore->Raiz = z;   // A arvore estava vazia, z vira a raiz

    else if(z->chave < y->chave)
        y->esq = z;
    
    else
        y->dir = z;

    // Corrige as propriedades da arvore
    corrigir_insercao(arvore, z);
}

// Verifica e corrige a arvore conforme necessario para se manter dentro das regras
void corrigir_insercao(ArvoreRN *arvore, NoFLA *z){

    // Enquanto o pai de no existir e for vermelho
    while(z != arvore->Raiz && z->pai != arvore->NIL && z->pai->cor == VERMELHO){

        // Caso A: O pai de z é filho a esquerda do avo
        if(z->pai == z->pai->pai->esq){
            
            // y é o tio de z
            NoFLA *y = z->pai->pai->dir;

            // Caso 1: o tio y tambem é vermelho
            if(y->cor == VERMELHO){
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;

                z = z->pai->pai;   // Sobe o ponteiro z para o avo
            }
            else{
                // Caso 2: z é filho a direita
                if(z == z->pai->dir){
                    z = z->pai;
                    rotacionar_esquerda(arvore, z);
                }
                // Caso 3: z é filho a esquerda
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionar_direita(arvore, z->pai->pai);
            }
        }
        // Caso B: O pai de z é o filho a direita do avo
        else{
            // y é o tio de z
            NoFLA *y = z->pai->pai->esq;

            // Caso 1: o tio y também é vermelho
            if(y->cor == VERMELHO){
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;

                z = z->pai->pai;   // Sobe o ponteiro z para o avo
            }
            else{
                // Caso 2: z é filho a esquerda
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacionar_direita(arvore, z);
                }
                // Caso 3: z é filho a direita
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionar_esquerda(arvore, z->pai->pai);
            }
        }
    }

    // Garante que a raiz seja sempre preta
    arvore->Raiz->cor = PRETO;
}