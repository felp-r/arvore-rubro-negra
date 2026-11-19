#ifndef REMOCAO_H
#define REMOCAO_H

#include "./arvore_rn.h"

void remover(ArvoreRN *arvore, NoFLA *z);
void corrigir_remocao(ArvoreRN *arvore, NoFLA *x);
void rn_transplante(ArvoreRN *arvore, NoFLA *u, NoFLA *v);

#endif