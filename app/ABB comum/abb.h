struct No{
    int chave;
    No *esq;
    No *dir;
};

struct ArvoreABB{
    No *Raiz;
    No* NIL;
};

No *criar_no_abb(ArvoreABB *arvore, int valor);
ArvoreABB *criar_arvore_abb();

No *busca_abb(ArvoreABB *arvore, int valor);
int altura_abb(ArvoreABB *arvore, No *no = nullptr);

void inserir_abb(ArvoreABB *arvore, int valor);
No *remover_abb(ArvoreABB *arvore, No *no, int valor);

No* encontrar_minimo_abb(ArvoreABB *arvore, No *no);

void liberar_nos_abb(ArvoreABB *arvore, No *no);
void liberar_arvore_abb(ArvoreABB *arvore);
