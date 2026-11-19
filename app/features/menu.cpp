#include <iostream>

#include "../include/menu.h"
#include "../include/insercao.h"
#include "../include/remocao.h"
#include "../include/busca.h"
#include "../include/verificacao.h"
#include "../include/persistencia.h"

using namespace std;

void menu(ArvoreRN *arvore){
    int opcao, valor;

    do{
        cout << "\n===== ARVORE RUBRO-NEGRA =====\n";
        cout << "1. Inserir chave\n";
        cout << "2. Buscar chave\n";
        cout << "3. Remover chave\n";
        cout << "4. Exibir em-ordem\n";
        cout << "5. Exibir arvore (indentada)\n";
        cout << "6. Minimo e Maximo\n";
        cout << "7. Altura e numero de nos\n";
        cout << "8. Verificar propriedades\n";
        cout << "9. Salvar em arquivo binario\n";
        cout << "10. Carregar de arquivo binario\n";
        cout << "0. Sair\n";
        cout << "==============================\n";
        cout << "Escolha uma opcao: ";

        cin >> opcao;

        switch(opcao){
            case 1:{
                cout << "Digite um valor: ";
                cin >> valor;

                inserir(arvore, valor);
                
                break;
            }
                
            case 2:{
                cout << "Digite um valor: ";
                cin >> valor;
                
                NoFLA *busca = buscar(arvore, valor);
                
                if(busca != arvore->NIL)
                    cout << "A chave " << valor << " foi encontrada.\n";
                else
                    cout << "A chave " << valor << " não foi encontrada.\n";
                
                break;
            }

            case 3:{
                cout << "Digite um valor: ";
                cin >> valor;

                NoFLA *busca = buscar(arvore, valor);
                
                if(busca != arvore->NIL){
                    remover(arvore, busca);
                    cout << "A chave " << valor << " foi removida.\n";
                }
                else
                    cout << "A chave " << valor << " não existe.\n";

                break;
            }

            case 4:{
                cout << "Impressão das chaves em ordem crescente:\n";
                exibir_em_ordem(arvore);
                cout << "\n";
                break;
            }

            case 5:{
                cout << "Impressão da arvore indentada:\n";
                exibir_arvore_indentada(arvore);
                break;
            }

            case 6:{
                NoFLA *min = minimo(arvore);
                NoFLA *max = maximo(arvore);

                if(min->chave == -1 || max->chave == -1){
                    cout << "Árvore vazia.\n";
                }
                else{
                    cout << "Valor mínimo: " << min->chave << "\n";
                    cout << "Valor máximo: " << max->chave << "\n"; 
                }

                break;
            }

            case 7:{
                int alt = altura(arvore);
                int nroNos = nro_nos(arvore);

                cout << "Altura: ";
                if(alt == -1)
                    cout << "Árvore vazia.\n";
                else
                    cout << alt << "\n";

                cout << "Número de nós: " << nroNos << "\n";

                break;
            }
            
            case 8:{
                if(verificar_arvore(arvore))
                    cout << "Árvore Rubro-Negra válida!\n";
                else
                    cout << "Árvore Rubro-Negra inválida!\n";

                break;
            }

            case 9:{
                string nomeArquivo;
                cout << "Digite o nome do arquivo: ";
                cin >> nomeArquivo;
                verificar_arquivo(nomeArquivo);
                break;
            }

            case 10:{
                string nomeArquivo;
                cout << "Digite o nome do arquivo: ";
                cin >> nomeArquivo;
                break;
            }

            case 0:{
                cout << "Encerrando o programa..." << endl;
                break;
            }

            default:{
                cout << "Opção inválida!\n";
                break;
            }
        }
    } while(opcao != 0);
}