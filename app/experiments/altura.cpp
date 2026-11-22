#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "../include/arvore_rn.h"
#include "../include/insercao.h"
#include "../include/busca.h"
#include "../ABB-comum/abb.h"

#include "../include/experimento.h"

using namespace std;

// Executa o experimento completo
void experimento_altura(){
    testar_altura(10e3, true);
    testar_altura(10e3, false);

    testar_altura(10e4, true);
    testar_altura(10e4, false);

    testar_altura(10e5, true);
    testar_altura(10e5, false);
}

// Executa um cenário para uma quantidade de nos
void testar_altura(int quantidade, bool crescente){
    ArvoreRN *arvore_rn = criar_arvore();
    ArvoreABB *arvore_abb = criar_arvore_abb();

    vector<int> sequencia_valores = valores(quantidade, crescente);

    for(const auto& i : sequencia_valores){
        inserir(arvore_rn, i);
        inserir_abb(arvore_abb, i);
    }

    string ordem = (crescente ? "crescente" : "decrescente");
    int altura_rn = altura(arvore_rn);
    int altura_abb_comum = altura_abb(arvore_abb);

    cout << "\nAltura das arvores em ordem " << ordem << "\n";
    cout << "Arvore Rubro-Negra: " << altura_rn << "\n";
    cout << "Arvore de Busca Binária: " << altura_abb_comum << "\n";

    salvar_resultado(quantidade, ordem, altura_rn, altura_abb_comum);

    liberar_arvore(arvore_rn);
    liberar_arvore_abb(arvore_abb);
}

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

// Registra os resultados no CSV
void salvar_resultado(int quantidade, string ordem, int altura_rn, int altura_abb){
    string caminho = "experiments/resultados/alturas.csv";

    // Verifica se o arquivo ja existe
    ifstream teste(caminho);
    bool existe = teste.good();
    teste.close();

    // Abre o arquivo para adicionar dados
    ofstream arquivo(caminho, ios::app);

    if(!arquivo.is_open()){
        cout << "Erro ao abrir o arquivo CSV.\n";
        return;
    }

    // Escreve o cabecalho caso seja um arquivo novo
    if(!existe)
        arquivo << "quantidade,ordem,altura_rn,altura_abb\n";

    arquivo << quantidade << ","
            << ordem << ","
            << altura_rn << ","
            << altura_abb << "\n";

    arquivo.close();
}