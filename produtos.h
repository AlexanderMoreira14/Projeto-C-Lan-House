// ============================================================================
// ARQUIVO: produtos.h
// MODULO 3: PERSPECTIVA DE PRODUTOS DA LANCHONETE
// Autor: [Integrante C - Nicolas Bryan de Oliveira Camargo, 48070068]
// Este arquivo tem a struct, o vetor global e todas as funcoes deste modulo.
// Ele e incluido no main.c com: #include "produtos.h"
// ============================================================================

// ----- DADOS DO MODULO (ESCOPO GLOBAL) -----

// 3. Perspectiva do Integrante C: Produtos da Lanchonete
struct Produto {
    int idProduto;
    char nome[40];
    char categoria[20]; // exemplo: Bebida, Salgado
    float preco;
    int quantidadeEstoque;
};

struct Produto estoqueProdutos[50];
int totalProdutos = 0;
int proximoIdProduto = 1; // proximo ID a ser usado (so aumenta, para nao repetir ID depois de remover)


// ----- FUNCOES DO MODULO -----

// ----------------------------------------------------------------------------
// Procura um produto pelo ID e devolve a posicao dele no vetor.
// Se nao encontrar, devolve -1.
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
int buscarIndiceProduto(int id) {
    int i;
    for (i = 0; i < totalProdutos; i++) {
        if (estoqueProdutos[i].idProduto == id) {
            return i;
        }
    }
    return -1;
}

// ----------------------------------------------------------------------------
// Cadastra um novo produto da lanchonete.
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void cadastrarProduto() {
    if (totalProdutos >= 50) {
        printf("\n[ERRO] Limite de 50 produtos atingido!\n");
    } else {
        // Aqui a remocao apaga o produto do vetor (totalProdutos diminui),
        // por isso usamos um contador separado para o ID nunca se repetir.
        estoqueProdutos[totalProdutos].idProduto = proximoIdProduto;
        proximoIdProduto++;

        printf("\nNome do produto: ");
        scanf(" %[^\n]", estoqueProdutos[totalProdutos].nome);
        printf("Categoria (ex: Bebida, Salgado, Doce): ");
        scanf(" %[^\n]", estoqueProdutos[totalProdutos].categoria);
        printf("Preco (ex: 4.50): ");
        scanf("%f", &estoqueProdutos[totalProdutos].preco);
        printf("Quantidade em estoque: ");
        scanf("%d", &estoqueProdutos[totalProdutos].quantidadeEstoque);

        printf("\nProduto cadastrado com sucesso! ID gerado: %d\n", estoqueProdutos[totalProdutos].idProduto);
        totalProdutos++;
    }
}

// ----------------------------------------------------------------------------
// Lista todos os produtos da lanchonete.
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void listarProdutos() {
    int i;

    printf("\n--- PRODUTOS DA LANCHONETE ---\n");
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        for (i = 0; i < totalProdutos; i++) {
            printf("ID: %d | %s | Categoria: %s | R$ %.2f | Estoque: %d\n",
                   estoqueProdutos[i].idProduto, estoqueProdutos[i].nome,
                   estoqueProdutos[i].categoria, estoqueProdutos[i].preco,
                   estoqueProdutos[i].quantidadeEstoque);
        }
    }
}

// ----------------------------------------------------------------------------
// Busca um produto pelo ID e mostra os dados dele.
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void buscarProduto() {
    int id;
    int indice;

    printf("\nDigite o ID do produto: ");
    scanf("%d", &id);
    indice = buscarIndiceProduto(id);

    if (indice == -1) {
        printf("\n[ERRO] Produto nao encontrado!\n");
    } else {
        printf("\n--- PRODUTO ENCONTRADO ---\n");
        printf("ID: %d\n", estoqueProdutos[indice].idProduto);
        printf("Nome: %s\n", estoqueProdutos[indice].nome);
        printf("Categoria: %s\n", estoqueProdutos[indice].categoria);
        printf("Preco: R$ %.2f\n", estoqueProdutos[indice].preco);
        printf("Estoque: %d unidades\n", estoqueProdutos[indice].quantidadeEstoque);
    }
}

// ----------------------------------------------------------------------------
// Edita o preco e a quantidade em estoque de um produto.
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void editarProduto() {
    int id;
    int indice;

    printf("\nDigite o ID do produto que deseja editar: ");
    scanf("%d", &id);
    indice = buscarIndiceProduto(id);

    if (indice == -1) {
        printf("\n[ERRO] Produto nao encontrado!\n");
    } else {
        printf("Editando: %s\n", estoqueProdutos[indice].nome);
        printf("Novo preco: ");
        scanf("%f", &estoqueProdutos[indice].preco);
        printf("Nova quantidade em estoque: ");
        scanf("%d", &estoqueProdutos[indice].quantidadeEstoque);
        printf("\nProduto atualizado com sucesso!\n");
    }
}

// ----------------------------------------------------------------------------
// Remove um produto do vetor (remocao fisica: puxa os proximos uma posicao
// para tras e diminui o total).
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void removerProduto() {
    int id;
    int indice;
    int i;

    printf("\nDigite o ID do produto que deseja remover: ");
    scanf("%d", &id);
    indice = buscarIndiceProduto(id);

    if (indice == -1) {
        printf("\n[ERRO] Produto nao encontrado!\n");
    } else {
        printf("\nProduto %s removido com sucesso!\n", estoqueProdutos[indice].nome);
        // cada produto depois do removido "anda" uma posicao para tras
        for (i = indice; i < totalProdutos - 1; i++) {
            estoqueProdutos[i] = estoqueProdutos[i + 1];
        }
        totalProdutos--;
    }
}

// ----------------------------------------------------------------------------
// ORDENACAO: coloca os produtos do menor para o maior preco (Bubble Sort).
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void ordenarProdutosPorPreco() {
    int i, j;
    struct Produto aux;

    for (i = 0; i < totalProdutos - 1; i++) {
        for (j = 0; j < totalProdutos - 1 - i; j++) {
            if (estoqueProdutos[j].preco > estoqueProdutos[j + 1].preco) {
                aux = estoqueProdutos[j];
                estoqueProdutos[j] = estoqueProdutos[j + 1];
                estoqueProdutos[j + 1] = aux;
            }
        }
    }
    printf("\nProdutos ordenados por preco (mais barato primeiro)!\n");
    listarProdutos();
}

// ----------------------------------------------------------------------------
// ARQUIVO: salva todos os dados do modulo no arquivo produtos.txt
// Formato: 1a linha = quantidade, 2a linha = proximo ID,
// depois cada campo de cada registro em uma linha.
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void salvarProdutos() {
    FILE *arquivo; // ponteiro que representa o arquivo aberto
    int i;

    arquivo = fopen("produtos.txt", "w"); // "w" = escrita: cria o arquivo ou apaga o conteudo antigo

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo produtos.txt!\n");
    } else {
        fprintf(arquivo, "%d\n", totalProdutos);
        fprintf(arquivo, "%d\n", proximoIdProduto);
        for (i = 0; i < totalProdutos; i++) {
            fprintf(arquivo, "%d\n", estoqueProdutos[i].idProduto);
            fprintf(arquivo, "%s\n", estoqueProdutos[i].nome);
            fprintf(arquivo, "%s\n", estoqueProdutos[i].categoria);
            fprintf(arquivo, "%.2f\n", estoqueProdutos[i].preco);
            fprintf(arquivo, "%d\n", estoqueProdutos[i].quantidadeEstoque);
        }
        fclose(arquivo); // sempre fechar o arquivo depois de usar
        printf("\nDados salvos no arquivo produtos.txt\n");
    }
}

// ----------------------------------------------------------------------------
// ARQUIVO: le o arquivo produtos.txt e coloca os dados de volta no vetor.
// E chamada uma vez, no inicio do main().
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void carregarProdutos() {
    FILE *arquivo;
    int i;

    arquivo = fopen("produtos.txt", "r"); // "r" = leitura

    if (arquivo == NULL) {
        // na primeira vez o arquivo ainda nao existe, entao o sistema comeca vazio
        printf("Arquivo produtos.txt nao encontrado. Comecando sem dados.\n");
    } else {
        fscanf(arquivo, "%d", &totalProdutos);
        fscanf(arquivo, "%d", &proximoIdProduto);
        for (i = 0; i < totalProdutos; i++) {
            fscanf(arquivo, "%d", &estoqueProdutos[i].idProduto);
            fscanf(arquivo, " %[^\n]", estoqueProdutos[i].nome);
            fscanf(arquivo, " %[^\n]", estoqueProdutos[i].categoria);
            fscanf(arquivo, "%f", &estoqueProdutos[i].preco);
            fscanf(arquivo, "%d", &estoqueProdutos[i].quantidadeEstoque);
        }
        fclose(arquivo);
        printf("%d produto(s) carregado(s) do arquivo produtos.txt\n", totalProdutos);
    }
}

// ----------------------------------------------------------------------------
// Submenu do Modulo 3
// Autor: [Integrante C - Nicolas Bryan de Oliveira Camargo, 48070068]
// ----------------------------------------------------------------------------
void moduloProdutos() {
    int opcaoProduto;
    do {
        printf("\n--- [MODULO 3: LANCHONETE E ESTOQUE (Integrante C)] ---\n");
        printf("1. Cadastrar Novo Produto\n");
        printf("2. Listar Todos os Produtos\n");
        printf("3. Editar Preco ou Estoque do Produto\n");
        printf("4. Remover Produto\n");
        printf("5. Buscar Produto por ID\n");
        printf("6. [ORDENACAO] Listar Produtos por Preco\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoProduto = -1; // comeca invalida: se digitarem uma letra, cai no default
        scanf("%d", &opcaoProduto);
        while (getchar() != '\n') { } // joga fora o que sobrou digitado (letras e o Enter)

        switch (opcaoProduto) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                editarProduto();
                break;
            case 4:
                removerProduto();
                break;
            case 5:
                buscarProduto();
                break;
            case 6:
                ordenarProdutosPorPreco();
                break;
            case 0:
                salvarProdutos(); // grava os dados no arquivo antes de sair do modulo
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Produtos!\n");
        }
    } while (opcaoProduto != 0);
}
