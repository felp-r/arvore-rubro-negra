#include <iostream>
#include "../include/arvore_rn.h"

using namespace std;

int main(void){
    ArvoreRN *arvore = criar_arvore();

    for(int i = 10; i > 0; i--){
        inserir(arvore, i);
    }


    exibir_em_ordem(arvore);
    cout << endl;
    exibir_arvore_indentada(arvore);
    cout << endl;

    cout << "Minimo: " << minimo(arvore)->chave << endl;
    cout << "Maximo: " << maximo(arvore)->chave << endl;

    liberar_arvore(arvore);

    return 0;
}