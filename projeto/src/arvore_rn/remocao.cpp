#include "../../include/arvore_rn/remocao.hpp"
#include "../../include/arvore_rn/rotacao.hpp"
#include "../../include/arvore_rn/busca.hpp"


// Remove um no da arvore
void remover(ArvoreRN *arvore, NoFLA *z){
    if (z == nullptr || z == arvore->NIL)
        return;

    NoFLA *x;
    NoFLA *y = z;

    // Salva a cor original do no y antes que ele seja movido ou alterado
    Cor y_cor = y->cor;

     // Caso 1: z nao possui filho esquerdo
    if(z->esq == arvore->NIL){
        x = z->dir;
        rn_transplante(arvore, z, z->dir);
    }
    // Caso 2: z nao possui filho direito
    else if(z->dir == arvore->NIL){
        x = z->esq;
        rn_transplante(arvore, z, z->esq);
    }
    // Caso 3: z tem filhos tanto a esquerda quanto a direita
    else{
        // Encontra o sucessor de z, que é o menor valor na subarvore direita de z
        y = minimo(arvore, z->dir);

        y_cor = y->cor;

        // Guarda o filho direito do sucessor em x
        x = y->dir;

        // Verifica se o sucessor y é filho direto do próprio z
        if(y->pai == z){
            x->pai = y;   // Garante que o ponteiro de pai de x aponte corretamente para y
        }
        // Se o sucessor y estiver mais fundo na subarvore direita de z
        else{
            rn_transplante(arvore, y, y->dir);   // Remove y de sua posição original, substituindo-o pelo seu filho direito
            y->dir = z->dir;
            y->dir->pai = y;
        }

        rn_transplante(arvore, z, y);   // Substitui o no antigo z pelo sucessor y na árvore principal
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }

    // Corrige a arvore caso um no preto tenha sido removido
    if(y_cor == PRETO)
        corrigir_remocao(arvore, x);
    
    delete z;

    // Restaura as referencias da raiz e do sentinela
    if (arvore->Raiz != arvore->NIL)
        arvore->Raiz->pai = arvore->NIL;

    arvore->NIL->pai = arvore->NIL;
    arvore->NIL->cor = PRETO;
}

// Corrigi o balanceamento da arvore após a remoção
void corrigir_remocao(ArvoreRN *arvore, NoFLA *x){
    NoFLA *w;

    while(x != arvore->Raiz && x->cor == PRETO){

        if(x == x->pai->esq){
            w = x->pai->dir;

            // Caso 1: O irmão w de x é vermelho
            if(w->cor == VERMELHO){
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacionar_esquerda(arvore, x->pai);
                w = x->pai->dir;
            }

            if(w == arvore->NIL){
                x = x->pai;
                continue;
            }

            // Caso 2: O irmão w é PRETO e ambos os filhos de w são PRETOS
            if(w->esq->cor == PRETO && w->dir->cor == PRETO){
                w->cor = VERMELHO;
                x = x->pai;
            }
            else{
                // Caso 3: w é PRETO, filho esquerdo é VERMELHO e direito é PRETO
                if(w->dir->cor == PRETO){
                    w->esq->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacionar_direita(arvore, w);
                    w = x->pai->dir;
                }

                // Caso 4: w é PRETO e seu filho direito é VERMELHO
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->dir->cor = PRETO;
                rotacionar_esquerda(arvore, x->pai);
                x = arvore->Raiz;
            }
        }

        // Simétrico ao caso do if
        else{
            w = x->pai->esq;

            if(w->cor == VERMELHO){
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacionar_direita(arvore, x->pai);
                w = x->pai->esq;
            }

            if(w == arvore->NIL){
                x = x->pai;
                continue;
            }

            // Caso 2 simétrico
            if(w->dir->cor == PRETO && w->esq->cor == PRETO){
                w->cor = VERMELHO;
                x = x->pai;
            }
            else{
                // Caso 3 simétrico
                if(w->esq->cor == PRETO){
                    w->dir->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacionar_esquerda(arvore, w);
                    w = x->pai->esq;
                }

                // Caso 4 simétrico
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esq->cor = PRETO;
                rotacionar_direita(arvore, x->pai);
                x = arvore->Raiz;
            }
        }
    }

    // Garante que o no seja preto
    x->cor = PRETO;
}

// Substitui um no por outro
void rn_transplante(ArvoreRN *arvore, NoFLA *u, NoFLA *v){
    // Verifica se o nó u que está sendo substituído é a raiz da árvore
    if(u->pai == arvore->NIL)
        arvore->Raiz = v;

    // Se u não é a raiz, verifica se ele ocupa a posição de filho esquerdo do seu pai
    else if(u == u->pai->esq)
        u->pai->esq = v;

    // Caso contrário, significa que u era o filho direito
    else
        u->pai->dir = v;

    // Atualiza o pai de v, inclusive quando v e NIL
    v->pai = u->pai;
}

