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

NoFLA *buscar(ArvoreRN *arvore, int valor);
NoFLA *minimo(ArvoreRN *arvore, NoFLA *no = nullptr);
NoFLA *maximo(ArvoreRN *arvore, NoFLA *no = nullptr);

void liberar_nos(NoFLA *no, NoFLA *NIL);
void liberar_arvore(ArvoreRN *arvore);

void rotacionar_esquerda(ArvoreRN *arvore, NoFLA *x);
void rotacionar_direita(ArvoreRN *arvore, NoFLA *y);

void inserir(ArvoreRN *arvore, int valor);
void corrigir_insercao(ArvoreRN *arvore, NoFLA *z);

void remover(ArvoreRN *arvore, NoFLA *z);
void corrigir_remocao(ArvoreRN *arvore, NoFLA *x);
void rn_transplante(ArvoreRN *arvore, NoFLA *u, NoFLA *v);

void exibir_em_ordem(ArvoreRN *arvore, NoFLA *no = nullptr);
void exibir_arvore_indentada(ArvoreRN *arvore, NoFLA *no = nullptr, int nivel = 0);

#endif