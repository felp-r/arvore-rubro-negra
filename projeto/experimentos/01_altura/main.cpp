#include <iostream>
#include <fstream>
#include <vector>

#include "../../include/arvore_rn/arvore_rn.hpp"
#include "../../include/arvore_rn/insercao.hpp"
#include "../../include/arvore_rn/busca.hpp"
#include "../../include/arvore_abb/abb.hpp"

#include "../comum/gerador_dados.hpp"

// Registra os resultados no CSV
void salvar_resultado(int quantidade, string ordem, int altura_rn, int altura_abb){
    string caminho = "resultados/dados/altura.csv";

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

int main(void){
    testar_altura(1000, true);
    testar_altura(1000, false);

    testar_altura(10000, true);
    testar_altura(10000, false);

    testar_altura(100000, true);
    testar_altura(100000, false);

    return 0;
}