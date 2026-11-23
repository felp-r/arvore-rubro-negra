#include <algorithm>

#include "gerador_dados.hpp"

// Gera a sequencia de valores
vector<int> valores(int quantidade, bool crescente){
    vector<int> valores;

    for(int i = 1; i <= quantidade; i++){
        valores.push_back(i);
    }

    if(!crescente){
        reverse(valores.begin(), valores.end());
    }

    return valores;
}