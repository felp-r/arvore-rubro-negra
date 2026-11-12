#ifndef ARVORE_H
#define ARVORE_H

enum Cor {
    VERMELHO,
    PRETO
};

struct NoFLA {
    int chave;
    Cor cor;

    NoFLA *esq;
    NoFLA *dir;
    NoFLA *pai;
};

NoFLA *criar_no(int chave);
NoFLA *buscar(NoFLA *no, int valor);
void liberar_arvore(NoFLA *no);
void rotacionar_esquerda(NoFLA *&raiz, NoFLA *x);
void rotacionar_direita(NoFLA *&raiz, NoFLA *y);
void inserir(NoFLA *&raiz, int valor);
void corrigir_insercao(NoFLA *&raiz, NoFLA *z);

#endif