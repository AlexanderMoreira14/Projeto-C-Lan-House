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
    char categoria[20];
    float preco;
    int quantidadeEstoque;
};

struct Produto estoqueProdutos[50];
int totalProdutos = 0;
int proximoIdProduto = 1;


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
        estoqueProdutos[totalProdutos].idProduto = proximoIdProduto;
        proximoIdProduto++;

        printf("\nNome do produto: ");
        scanf(" %[^\n]", estoqueProdutos[totalProdutos].nome);
        printf("Categoria (ex: Bebida, Salgado, Doce): ");
        scanf(" %[^\n]", estoqueProdutos[totalProdutos].categoria);
        do {
            printf("Preco (ex: 4,50): ");
            estoqueProdutos[totalProdutos].preco = -1;
            scanf("%f", &estoqueProdutos[totalProdutos].preco);
            while (getchar() != '\n') { }
        } while (estoqueProdutos[totalProdutos].preco <= 0);

        do {
            printf("Quantidade em estoque: ");
            estoqueProdutos[totalProdutos].quantidadeEstoque = -1;
            scanf("%d", &estoqueProdutos[totalProdutos].quantidadeEstoque);
            while (getchar() != '\n') { }
        } while (estoqueProdutos[totalProdutos].quantidadeEstoque < 0);

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
// BUSCA TEXTUAL: mostra todos os produtos que tem o texto digitado no nome.
// Exemplo: digitando "Coca" aparecem "Coca-Cola Lata" e "Coca-Cola 600ml".
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void buscarProdutoPorNome() {
    char texto[40];
    int i;
    int encontrou = 0;

    printf("\nDigite o nome ou parte do nome: ");
    scanf(" %[^\n]", texto);

    printf("\n--- RESULTADO DA BUSCA ---\n");
    for (i = 0; i < totalProdutos; i++) {
        if (strstr(estoqueProdutos[i].nome, texto) != NULL) {
            printf("ID: %d | %s | Categoria: %s | R$ %.2f | Estoque: %d\n",
                   estoqueProdutos[i].idProduto, estoqueProdutos[i].nome,
                   estoqueProdutos[i].categoria, estoqueProdutos[i].preco,
                   estoqueProdutos[i].quantidadeEstoque);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto encontrado com \"%s\" no nome.\n", texto);
    }
}

// ----------------------------------------------------------------------------
// VENDA: cruza um Cliente (Modulo 1) com um Produto, calcula o total
// e da baixa no estoque.
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void venderProduto() {
    int idCliente, idProduto, quantidade;
    int indiceCliente, indiceProduto;
    float valor;

    printf("\nID do cliente: ");
    scanf("%d", &idCliente);
    indiceCliente = buscarIndiceCliente(idCliente);

    printf("ID do produto: ");
    scanf("%d", &idProduto);
    indiceProduto = buscarIndiceProduto(idProduto);

    if (indiceCliente == -1) {
        printf("\n[ERRO] Cliente nao encontrado! Cadastre o cliente no Modulo 1.\n");
    } else if (indiceProduto == -1) {
        printf("\n[ERRO] Produto nao encontrado!\n");
    } else {
        printf("Quantidade: ");
        scanf("%d", &quantidade);

        if (quantidade <= 0) {
            printf("\n[ERRO] A quantidade precisa ser maior que zero!\n");
        } else if (quantidade > estoqueProdutos[indiceProduto].quantidadeEstoque) {
            printf("\n[ERRO] Estoque insuficiente! Disponivel: %d unidades\n",
                   estoqueProdutos[indiceProduto].quantidadeEstoque);
        } else {
            estoqueProdutos[indiceProduto].quantidadeEstoque = estoqueProdutos[indiceProduto].quantidadeEstoque - quantidade;
            valor = quantidade * estoqueProdutos[indiceProduto].preco;

            printf("\nVenda realizada com sucesso!\n");
            printf("Cliente: %s | %d x %s | Total: R$ %.2f\n",
                   listaClientes[indiceCliente].nome, quantidade,
                   estoqueProdutos[indiceProduto].nome, valor);
            printf("Estoque restante: %d unidades\n", estoqueProdutos[indiceProduto].quantidadeEstoque);
        }
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
// ARQUIVO: grava o vetor inteiro no arquivo produtos.csv
// Formato: um produto por linha, campos separados por ;
// Exemplo de linha: 1;Coca-Cola Lata;Bebida;6,00;24
// E chamada depois de cadastrar, editar, remover ou vender, para o arquivo
// ficar sempre igual ao que esta na memoria.
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void salvarProdutos() {
    FILE *arquivo;
    int i;

    arquivo = fopen("produtos.csv", "w");

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo produtos.csv!\n");
    } else {
        for (i = 0; i < totalProdutos; i++) {
            fprintf(arquivo, "%d;%s;%s;%.2f;%d\n",
                    estoqueProdutos[i].idProduto, estoqueProdutos[i].nome,
                    estoqueProdutos[i].categoria, estoqueProdutos[i].preco,
                    estoqueProdutos[i].quantidadeEstoque);
        }
        fclose(arquivo);
        printf("Dados salvos no arquivo produtos.csv\n");
    }
}

// ----------------------------------------------------------------------------
// ARQUIVO: le o arquivo produtos.csv e coloca os dados de volta no vetor.
// E chamada uma vez, no inicio do main().
// Autor: [Integrante C - Nicolas Bryan]
// ----------------------------------------------------------------------------
void carregarProdutos() {
    FILE *arquivo;

    arquivo = fopen("produtos.csv", "r");

    if (arquivo == NULL) {
        printf("Arquivo produtos.csv nao encontrado. Comecando sem dados.\n");
    } else {
        totalProdutos = 0;
        while (totalProdutos < 50 &&
               fscanf(arquivo, "%d;%[^;];%[^;];%f;%d\n",
                      &estoqueProdutos[totalProdutos].idProduto, estoqueProdutos[totalProdutos].nome,
                      estoqueProdutos[totalProdutos].categoria, &estoqueProdutos[totalProdutos].preco,
                      &estoqueProdutos[totalProdutos].quantidadeEstoque) == 5) {
            if (estoqueProdutos[totalProdutos].idProduto >= proximoIdProduto) {
                proximoIdProduto = estoqueProdutos[totalProdutos].idProduto + 1;
            }
            totalProdutos++;
        }
        fclose(arquivo);
        printf("%d produto(s) carregado(s) do arquivo produtos.csv\n", totalProdutos);
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
        printf("7. Buscar Produto por Nome\n");
        printf("8. Vender Produto (Cruza Cliente + Produto e da Baixa no Estoque)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoProduto = -1;
        scanf("%d", &opcaoProduto);
        while (getchar() != '\n') { }

        switch (opcaoProduto) {
            case 1:
                cadastrarProduto();
                salvarProdutos();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                editarProduto();
                salvarProdutos();
                break;
            case 4:
                removerProduto();
                salvarProdutos();
                break;
            case 5:
                buscarProduto();
                break;
            case 6:
                ordenarProdutosPorPreco();
                break;
            case 7:
                buscarProdutoPorNome();
                break;
            case 8:
                venderProduto();
                salvarProdutos();
                break;
            case 0:
                salvarProdutos();
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Produtos!\n");
        }
    } while (opcaoProduto != 0);
}
