#include "../include/rotacao.h"


// Move um no para a esquerda e o seu filho direito para a posicao de pai
void rotacionar_esquerda(ArvoreRN *arvore, NoFLA *x){
    NoFLA *y = x->dir;  // y é o filho direito de x

    // 1. O filho esquerdo de y passa a ser o filho direito de x
    x->dir = y->esq;
    if(y->esq != arvore->NIL)
        y->esq->pai = x;

    // 2. Atualiza o pai de y para apontar para o antigo pai de x
    y->pai = x->pai;

    if(x->pai == arvore->NIL)
        arvore->Raiz = y;   // y se torna a nova raiz da arvore
    else if(x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    // 3. Conecta x como filho esquerdo de y
    y->esq = x;
    x->pai = y;
}

// Move um no para a direita e o seu filho esquerdo para a posicao de pai
void rotacionar_direita(ArvoreRN *arvore, NoFLA *y){
    NoFLA *x = y->esq;  // x é o filho esquerdo de y

    // 1. O filho direito de x passa a ser o filho esquerdo de y
    y->esq = x->dir;
    if(x->dir != arvore->NIL)
        x->dir->pai = y;

    // 2. Atualiza o pai de x para apontar para o antigo pai de y
    x->pai = y->pai;

    if(y->pai == arvore->NIL)
        arvore->Raiz = x;
    else if(y == y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;

    // 3. Conecta y como filho direito de x
    x->dir = y;
    y->pai = x;
}