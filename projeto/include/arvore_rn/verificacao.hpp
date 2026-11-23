#ifndef VERIFICACAO_H
#define VERIFICACAO_H

#include "./arvore_rn.hpp"

bool verificar_propriedade1(ArvoreRN *arvore, NoFLA *no = nullptr);
bool verificar_propriedade2(ArvoreRN *arvore);
bool verificar_propriedade3(ArvoreRN *arvore);
bool verificar_propriedade4(ArvoreRN *arvore, NoFLA *no = nullptr);
int verificar_propriedade5(ArvoreRN *arvore, NoFLA *no = nullptr);
bool verificar_arvore(ArvoreRN *arvore);

#endif