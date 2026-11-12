#include <iostream>
#include "../include/arvore.h"

using namespace std;

int main(void){
    NoFLA* raiz = nullptr;

    inserir(raiz, 70);
    inserir(raiz, 70);
    inserir(raiz, 20);
    inserir(raiz, 20);
    inserir(raiz, 60);
    inserir(raiz, 60);
    inserir(raiz, 40);
    inserir(raiz, 40);
    inserir(raiz, 80);
    inserir(raiz, 80);
    inserir(raiz, 50);
    inserir(raiz, 50);
    inserir(raiz, 30);
    inserir(raiz, 30);

    NoFLA* aux = buscar(raiz, 40);

    cout << "Pai: " << aux->pai->chave << endl;
    cout << "Filho: " << aux->chave << endl;

    liberar_arvore(raiz);

    return 0;
}