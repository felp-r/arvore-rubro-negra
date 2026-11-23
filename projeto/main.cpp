#include "include/arvore_rn/menu.hpp"

using namespace std;

int main(void){
    ArvoreRN *arvore = criar_arvore();

    menu(arvore);    

    liberar_arvore(arvore);

    return 0;
}