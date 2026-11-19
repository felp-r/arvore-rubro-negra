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

struct ArvoreRN{
    NoFLA *Raiz;
    NoFLA *NIL;
};

ArvoreRN *criar_arvore();
NoFLA *criar_no(ArvoreRN *arvore, int valor);

void liberar_nos(NoFLA *no, NoFLA *NIL);
void liberar_arvore(ArvoreRN *arvore);

void exibir_em_ordem(ArvoreRN *arvore, NoFLA *no = nullptr);
void exibir_arvore_indentada(ArvoreRN *arvore, NoFLA *no = nullptr, int nivel = 0);

#endif