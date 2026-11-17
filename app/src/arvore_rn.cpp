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
    if(no == nullptr)
        aux = arvore->Raiz;
    else{
        aux = no;
    }

    while (aux->esq != arvore->NIL)
        aux = aux->esq;

    return aux;
}

// Encontra o maior valor
NoFLA *maximo(ArvoreRN *arvore, NoFLA *no){
    NoFLA *aux;
    if(no == nullptr)
        aux = arvore->Raiz;
    else{
        aux = no;
    }

    while (aux->dir != arvore->NIL)
        aux = aux->dir;

    return aux;
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
            cout << "A arvore ja possui um no com esta chave: " << valor << endl;
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
         << "]" << endl;

    exibir_arvore_indentada(arvore, no->esq, nivel + 1);
    exibir_arvore_indentada(arvore, no->dir, nivel + 1);
}
