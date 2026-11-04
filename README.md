# Trabalho Final — Árvore Rubro-Negra

**Disciplina:** Algoritmos e Programação I (STCO01)  
**Curso:** Bacharelado em Sistemas de Informação (SIN)  
**Período:** 2º semestre / 2026  
**Professor:** Sávio S. Dias

---

## 1. Visão Geral do Trabalho

O objetivo é implementar uma **Árvore Rubro-Negra (Red-Black Tree)** completa em C ou C++, com operações de manipulação, menu interativo e persistência em arquivo binário.

### Informações gerais

- **Integrantes:** grupos de até 2 pessoas.
- **Linguagem:** C ou C++.
- **Entrega:** código-fonte via Moodle (repositório Git ou arquivo ZIP).
- **Prazo de entrega:** 02/12/2026.
- **Apresentações:** 03 e 04/12/2026.
- **Duração da apresentação:** 10 a 15 minutos, mais 5 minutos para perguntas.
- **Peso:** até 40% da N2.

---

## 2. Critérios de Avaliação

| Critério | Peso |
|---|---:|
| Corretude da implementação | 35% |
| Qualidade do código (legibilidade, modularização e testes) | 20% |
| Menu e persistência em arquivo binário | 15% |
| Experimentação e análise dos resultados | 15% |
| Apresentação oral didática | 15% |
| **Total** | **100%** |

---

## 3. Conceito e Propriedades da Árvore Rubro-Negra

A Árvore Rubro-Negra é uma **árvore binária de busca auto-balanceada** que garante altura `O(log n)` no pior caso.

Cada nó possui uma cor: vermelho ou preto.

### As cinco propriedades

1. Todo nó deve ser vermelho ou preto.
2. A raiz deve ser sempre preta.
3. Toda folha (`NULL`) deve ser preta.
4. Se um nó é vermelho, seus dois filhos devem ser pretos. Portanto, não podem existir dois nós vermelhos consecutivos.
5. Todo caminho da raiz até uma folha deve conter o mesmo número de nós pretos (altura negra).

A implementação deve garantir que essas cinco propriedades sejam mantidas após as operações de inserção e remoção.

---

## 4. Estrutura de Dados

Cada nó da árvore deve armazenar:

- `chave`: valor inteiro.
- `cor`: vermelho ou preto.
- `esq`: ponteiro para o filho esquerdo.
- `dir`: ponteiro para o filho direito.
- `pai`: ponteiro para o nó pai.

### Estrutura sugerida em C

```c
enum Cor {
    VERMELHO,
    PRETO
};

struct NoFLA {
    int chave;
    Cor cor;

    struct NoFLA *esq;
    struct NoFLA *dir;
    struct NoFLA *pai;
};

```

## 5. Operações Obrigatórias

A implementação deve contemplar as seguintes operações:

| Operação | Descrição |
|---|---|
| Inserção (`insert`) | Inserir um nó e corrigir as propriedades por meio de rotações e recoloração. |
| Busca (`search`) | Procurar uma chave na árvore. |
| Remoção (`delete`) | Remover um nó e corrigir as propriedades. |
| Rotação à esquerda | Reorganizar a árvore por meio de uma rotação à esquerda. |
| Rotação à direita | Reorganizar a árvore por meio de uma rotação à direita. |
| Percurso em-ordem | Exibir as chaves em ordem crescente. |
| Mínimo e máximo | Encontrar o menor e o maior valor da árvore. |
| Altura | Calcular a altura da árvore. |
| Contagem de nós | Contar o número total de nós. |
| Verificação | Verificar se as cinco propriedades são respeitadas. |
| Salvamento | Salvar a árvore em arquivo binário. |
| Carregamento | Carregar a árvore de um arquivo binário. |

---

## 6. Menu Interativo

O programa deve apresentar o seguinte menu:

```text
===== ARVORE RUBRO-NEGRA =====

1. Inserir chave
2. Buscar chave
3. Remover chave
4. Exibir em-ordem
5. Exibir arvore (indentada)
6. Minimo e Maximo
7. Altura e numero de nos
8. Verificar propriedades
9. Salvar em arquivo binario
10. Carregar de arquivo binario
0. Sair

==============================
Escolha uma opcao:
```

### Regras do menu

| Opção | Funcionamento |
|---|---|
| 1 | Ler uma chave inteira e inserir. Avisar se ela já existir. |
| 2 | Ler uma chave e informar se foi encontrada. |
| 3 | Ler uma chave e remover. Avisar se ela não existir. |
| 4 | Imprimir as chaves em ordem crescente. |
| 5 | Exibir a árvore hierarquicamente, indicando a cor de cada nó (ex.: `50[P]`). |
| 6 | Exibir o menor e o maior valor. |
| 7 | Exibir a altura e o número de nós. |
| 8 | Verificar as cinco propriedades e informar se a árvore é válida. |
| 9 | Solicitar o nome do arquivo e salvar a árvore. |
| 10 | Solicitar o nome do arquivo e carregar a árvore. |
| 0 | Liberar a memória e encerrar o programa. |

---

## 7. Persistência em Arquivo Binário

A árvore deve ser armazenada em um arquivo binário utilizando o percurso em **pré-ordem**, com um marcador para representar nós vazios.

### Dados gravados para cada nó

- `int chave`
- `int cor`
  - `0` = vermelho
  - `1` = preto

### Representação de nós vazios

Para cada nó vazio, gravar:

- `int chave = -1` (marcador de `NULL`).

### Regras de carregamento

Durante a desserialização:

1. Reconstruir a árvore na mesma ordem em que foi salva.
2. Restaurar as chaves e as cores dos nós.
3. Recalcular os ponteiros para os nós pais.

---

## 8. Experimentos Obrigatórios

É necessário realizar experimentos comparando a Árvore Rubro-Negra com uma Árvore Binária de Busca comum (ABB).

### 8.1 Comparação de altura

- Inserir `N = 10³`, `10⁴` e `10⁵` chaves.
- Realizar inserções em ordem crescente e decrescente.
- Comparar as alturas das duas árvores.
- Verificar se a Rubro-Negra mantém altura `O(log n)`.

### 8.2 Tempo das operações

Medir o tempo de execução das seguintes operações:

- Inserção.
- Busca.
- Remoção.

Realizar as medições para as mesmas instâncias utilizadas na comparação de altura.

### 8.3 Número de rotações

Contabilizar quantas rotações foram necessárias durante as inserções.

### 8.4 Verificação das propriedades

Para cada instância, verificar se as cinco propriedades da Árvore Rubro-Negra continuam sendo respeitadas após as operações.

### 8.5 Teste de persistência

- Criar uma árvore com `10⁴` nós.
- Salvar a árvore em arquivo binário.
- Carregar a árvore novamente.
- Comparar a árvore original com a carregada.

A comparação deve considerar:

- Percurso em-ordem.
- Altura.
- Cores dos nós.

---

## 9. Resultados Esperados

Os resultados dos experimentos devem ser apresentados por meio de tabelas e gráficos.

Devem ser incluídos:

1. Comparação da altura média da Árvore Rubro-Negra com a ABB para chaves em ordem crescente.
2. Tempo de execução de cada operação, em microssegundos (`µs`), para cada valor de `N`.
3. Número médio de rotações por inserção.
4. Taxa de sucesso na verificação das cinco propriedades.

---

## 10. Requisitos de Implementação e Apresentação

- Utilizar C ou C++ puro, sem dependências externas.
- Restringir ao máximo o uso de bibliotecas e algoritmos padrão da linguagem.
- Desenvolver código modularizado, separando arquivos `.h` e `.c`/`.cpp`.
- Implementar testes para validar as operações.
- Desenvolver o menu interativo padronizado.
- Implementar a persistência em arquivo binário.
