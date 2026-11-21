#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "./arvore_rn.h"
#include <string>

using namespace std;

void salvar_arvore(ArvoreRN *arvore, string nome_arquivo);
void serializar(NoFLA *no, NoFLA *NIL, ofstream &arquivo);

void carregar_arvore(ArvoreRN *arvore, string nome_arquivo);
NoFLA* desserializar(ifstream &arquivo, NoFLA *pai, NoFLA *NIL);

#endif