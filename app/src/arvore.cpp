#include <iostream>
#include "../include/arvore.h"

using namespace std;

// Cria o no
NoFLA *criar_no(int valor){
    NoFLA* novo = new NoFLA;
    novo->chave = valor;
    novo->cor = VERMELHO;
    novo->dir = nullptr;
    novo->esq = nullptr;
    novo->pai = nullptr;
    return novo;
}

// Busca pelo no apartir da raiz
NoFLA *buscar(NoFLA *no, int valor){
    // Casos base:
    // 1. Retorna o NULL caso o no esteja vazio
    if(no == nullptr)
        return nullptr;

    // 2. Retorna o no ao encontrar um no com chave correspondente ao valor 
    if(no->chave == valor)
        return no;

    // Busca na subarvore apropriada
    if(no->chave > valor)
        return buscar(no->esq, valor);
    else
        return buscar(no->dir, valor);
}

// Libera a memoria utilizada na arvore
void liberar_arvore(NoFLA *no){
    // Caso base: o no é nulo
    if(no == nullptr)
        return;

    // Percorre todos os filhos
    liberar_arvore(no->esq);
    liberar_arvore(no->dir);

    // Apos liberar a memoria alocada de todos os filhos, libera a memoria alocada pelo no
    delete no;
}

// Move um no para a esquerda e o seu filho direito para a posicao de pai
void rotacionar_esquerda(NoFLA *&raiz, NoFLA *x){
    NoFLA *y = x->dir;  // y é o filho direito de x

    // 1. O filho esquerdo de y passa a ser o filho direito de x
    x->dir = y->esq;
    if(y->esq != nullptr)
        y->esq->pai = x;

    // 2. Atualiza o pai de y para apontar para o antigo pai de x
    y->pai = x->pai;

    if(x->pai == nullptr)
        raiz = y;   // y se torna a nova raiz da arvore
    else if(x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    // 3. Conecta x como filho esquerdo de y
    y->esq = x;
    x->pai = y;
}

// Move um no para a direita e o seu filho esquerdo para a posicao de pai
void rotacionar_direita(NoFLA *&raiz, NoFLA *y){
    NoFLA *x = y->esq;  // x é o filho esquerdo de y

    // 1. O filho direito de x passa a ser o filho esquerdo de y
    y->esq = x->dir;
    if(x->dir != nullptr)
        x->dir->pai = y;

    // 2. Atualiza o pai de x para apontar para o antigo pai de y
    x->pai = y->pai;

    if(y->pai == nullptr)
        raiz = x;
    else if(y == y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;

    // 3. Conecta y como filho direito de x
    x->dir = y;
    y->pai = x;
}

// Insere um novo no na arvore
void inserir(NoFLA *&raiz, int valor){
    NoFLA* y = nullptr;   // Guarda o pai do no atual
    NoFLA* x = raiz;      // Ponteiro que percorre a arvore

    // 1. Primeiro percorre a arvore buscando a posição
    while (x != nullptr) {
        y = x;
        if (valor < x->chave) {
            x = x->esq;
        } else if (valor > x->chave) {
            x = x->dir;
        } else {
            // A chave ja existe na arvore
            cout << "A arvore já possui um no com esta chave: " << valor << endl;
            return;
        }
    }


    // 2. So aloca memoria se a chave for inedita

    // Novo no a ser inserido
    NoFLA* z = criar_no(valor);

    // Encontra a posição correta para inserir
    while(x != nullptr){
        y = x;
        if(z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }

    // Define o pai de z
    z->pai = y;
        
    // Conecta z na arvore
    if(y == nullptr)
        raiz = z;   // A arvore estava vazia, z vira a raiz

    else if(z->chave < y->chave)
        y->esq = z;
    
    else
        y->dir = z;

    // Corrige as propriedades da arvore
    corrigir_insercao(raiz, z);
}

// Verifica e corrige a arvore conforme necessario para se manter dentro das regras
void corrigir_insercao(NoFLA *&raiz, NoFLA *z){

    // Enquanto o pai de no existir e for vermelho
    while(z != raiz && z->pai != nullptr && z->pai->cor == VERMELHO){

        // Caso A: O pai de z é filho a esquerda do avo
        if(z->pai == z->pai->pai->esq){
            
            // y é o tio de z
            NoFLA *y = z->pai->pai->dir;

            // Caso 1: o tio y tambem é vermelho
            if(y != nullptr && y->cor == VERMELHO){
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;

                z = z->pai->pai;   // Sobe o ponteiro z para o avo
            }
            else{
                // Caso 2: z é filho a direita
                if(z == z->pai->dir){
                    z = z->pai;
                    rotacionar_esquerda(raiz, z);
                }
                // Caso 3: z é filho a esquerda
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionar_direita(raiz, z->pai->pai);
            }
        }
        // Caso B: O pai de z é o filho a direita do avo
        else{
            // y é o tio de z
            NoFLA *y = z->pai->pai->esq;

            // Caso 1: o tio y também é vermelho
            if(y != nullptr && y->cor == VERMELHO){
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;

                z = z->pai->pai;   // Sobe o ponteiro z para o avo
            }
            else{
                // Caso 2: z é filho a esquerda
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacionar_direita(raiz, z);
                }
                // Caso 3: z é filho a direita
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacionar_esquerda(raiz, z->pai->pai);
            }
        }
    }

    // Garante que a raiz seja sempre preta
    raiz->cor = PRETO;
}