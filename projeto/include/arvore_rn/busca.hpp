#ifndef BUSCA_H
#define BUSCA_H

#include "./arvore_rn.hpp"

NoFLA *buscar(ArvoreRN *arvore, int valor);

NoFLA *minimo(ArvoreRN *arvore, NoFLA *no = nullptr);
NoFLA *maximo(ArvoreRN *arvore, NoFLA *no = nullptr);

int altura(ArvoreRN *arvore, NoFLA *no = nullptr);
int nro_nos(ArvoreRN *arvore, NoFLA *no = nullptr);

#endif