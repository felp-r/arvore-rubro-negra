#include <iostream>
#include <fstream>
#include <string>

#include "../include/persistencia.h"
#include "../include/arvore_rn.h"

using namespace std;

// Caminho para a pasta dos arquivos binários
string CAMINHO = "binary-files/";

// Salva a arvore em arquivo binario
void salvar_arvore(ArvoreRN *arvore, string nome){
    ofstream arquivo(CAMINHO + nome + ".bin", ios::binary);

    if(!arquivo.is_open()){
        cerr << "Erro ao criar o arquivo.\n";
        return;
    }

    serializar(arvore->Raiz, arvore->NIL, arquivo);
    arquivo.close();

    cout << "Arquivo criado/atualizado\n";
}

// Grava a chave e cor de cada no da arvore em arquivo binario
void serializar(NoFLA *no, NoFLA *NIL, ofstream &arquivo){
    int valor, cor;
    if(no == NIL){
        valor = -1;
        arquivo.write(reinterpret_cast<const char*>(&valor), sizeof(int));
        return;
    }

    valor = no->chave;
    cor = no->cor;
    arquivo.write(reinterpret_cast<const char*>(&valor), sizeof(int));
    arquivo.write(reinterpret_cast<const char*>(&cor), sizeof(int));
    
    serializar(no->esq, NIL, arquivo);
    serializar(no->dir, NIL, arquivo);
}


// Carrega a arvore a partir de um arquivo binario
void carregar_arvore(ArvoreRN *arvore, string nome){
    ifstream arquivo(CAMINHO + nome + ".bin", ios::binary);

    if(!arquivo.is_open()){
        cerr << "Erro ao ler o arquivo.\n";
        return;
    }

    // Libera os nós da arvore atual antes de carregar outra
    liberar_nos(arvore->Raiz, arvore->NIL);

    // Reconstrói a árvore
    arvore->Raiz = desserializar(arquivo, arvore->NIL, arvore->NIL);

    // Atualiza o pai da raiz
    if(arvore->Raiz != arvore->NIL){
        arvore->Raiz->pai = arvore->NIL;
    }

    arquivo.close();

    cout << "Arvore carregada com sucesso!\n";
}


NoFLA* desserializar(ifstream &arquivo, NoFLA *pai, NoFLA *NIL){
    int valor, cor;

    // Tenta ler a chave
    if(!arquivo.read(reinterpret_cast<char*>(&valor), sizeof(int))){
        return NIL;
    }

    // Marcador de nó vazio
    if(valor == -1){
        return NIL;
    }

    // Le a cor do nó
    if(!arquivo.read(reinterpret_cast<char*>(&cor), sizeof(int))){
        return NIL;
    }

    // Cria o novo nó
    NoFLA *novo = new NoFLA;

    novo->chave = valor;
    novo->cor = static_cast<Cor>(cor);;
    novo->pai = pai;

    // Reconstroi as subárvores
    novo->esq = desserializar(arquivo, novo, NIL);
    novo->dir = desserializar(arquivo, novo, NIL);

    return novo;
}
