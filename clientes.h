// ============================================================================
// ARQUIVO: clientes.h
// MODULO 1: PERSPECTIVA DE CLIENTES
// Autor: [Integrante A - Alexander Guimarães Gallotti Moreira, 47364548]
// Este arquivo tem a struct, o vetor global e todas as funcoes deste modulo.
// Ele e incluido no main.c com: #include "clientes.h"
// ============================================================================

// ----- DADOS DO MODULO (ESCOPO GLOBAL) -----

// 1. Perspectiva do Integrante A: Clientes da Lan House
struct Cliente {
    int idCliente;
    char nome[50];
    char telefone[20];
    float saldoHoras; // horas compradas e ainda nao usadas
    int ativo; // 1 = Ativo, 0 = Removido
};

struct Cliente listaClientes[50];
int totalClientes = 0;


// ----- FUNCOES DO MODULO -----

// ----------------------------------------------------------------------------
// Procura um cliente ATIVO pelo ID e devolve a posicao dele no vetor.
// Se nao encontrar, devolve -1.
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
int buscarIndiceCliente(int id) {
    int i;
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id && listaClientes[i].ativo == 1) {
            return i; // achou: devolve a posicao
        }
    }
    return -1; // percorreu o vetor todo e nao achou
}

// ----------------------------------------------------------------------------
// Cadastra um novo cliente na proxima posicao livre do vetor.
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void cadastrarCliente() {
    if (totalClientes >= 50) {
        printf("\n[ERRO] Limite de 50 clientes atingido!\n");
    } else {
        // O ID e gerado automaticamente. Como a remocao so marca ativo = 0,
        // totalClientes nunca diminui e o ID nunca se repete.
        listaClientes[totalClientes].idCliente = totalClientes + 1;

        printf("\nNome do cliente: ");
        scanf(" %[^\n]", listaClientes[totalClientes].nome); // le o nome com espacos
        printf("Telefone: ");
        scanf(" %[^\n]", listaClientes[totalClientes].telefone);
        printf("Saldo inicial de horas (ex: 2.5): ");
        scanf("%f", &listaClientes[totalClientes].saldoHoras);
        listaClientes[totalClientes].ativo = 1;

        printf("\nCliente cadastrado com sucesso! ID gerado: %d\n", listaClientes[totalClientes].idCliente);
        totalClientes++;
    }
}

// ----------------------------------------------------------------------------
// Lista todos os clientes ativos.
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void listarClientes() {
    int i;
    int encontrou = 0; // 0 = nenhum cliente mostrado, 1 = mostrou pelo menos um

    printf("\n--- LISTA DE CLIENTES ---\n");
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1) {
            printf("ID: %d | Nome: %s | Telefone: %s | Saldo: %.1f horas\n",
                   listaClientes[i].idCliente, listaClientes[i].nome,
                   listaClientes[i].telefone, listaClientes[i].saldoHoras);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum cliente cadastrado.\n");
    }
}

// ----------------------------------------------------------------------------
// Busca um cliente pelo ID e mostra os dados dele.
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void buscarCliente() {
    int id;
    int indice;

    printf("\nDigite o ID do cliente: ");
    scanf("%d", &id);
    indice = buscarIndiceCliente(id);

    if (indice == -1) {
        printf("\n[ERRO] Cliente nao encontrado!\n");
    } else {
        printf("\n--- CLIENTE ENCONTRADO ---\n");
        printf("ID: %d\n", listaClientes[indice].idCliente);
        printf("Nome: %s\n", listaClientes[indice].nome);
        printf("Telefone: %s\n", listaClientes[indice].telefone);
        printf("Saldo de horas: %.1f\n", listaClientes[indice].saldoHoras);
    }
}

// ----------------------------------------------------------------------------
// Edita nome, telefone e saldo de horas de um cliente.
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void editarCliente() {
    int id;
    int indice;

    printf("\nDigite o ID do cliente que deseja editar: ");
    scanf("%d", &id);
    indice = buscarIndiceCliente(id);

    if (indice == -1) {
        printf("\n[ERRO] Cliente nao encontrado!\n");
    } else {
        printf("Editando: %s\n", listaClientes[indice].nome);
        printf("Novo nome: ");
        scanf(" %[^\n]", listaClientes[indice].nome);
        printf("Novo telefone: ");
        scanf(" %[^\n]", listaClientes[indice].telefone);
        printf("Novo saldo de horas: ");
        scanf("%f", &listaClientes[indice].saldoHoras);
        printf("\nCliente atualizado com sucesso!\n");
    }
}

// ----------------------------------------------------------------------------
// Remove um cliente (remocao logica: apenas marca ativo = 0).
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void removerCliente() {
    int id;
    int indice;

    printf("\nDigite o ID do cliente que deseja remover: ");
    scanf("%d", &id);
    indice = buscarIndiceCliente(id);

    if (indice == -1) {
        printf("\n[ERRO] Cliente nao encontrado!\n");
    } else {
        listaClientes[indice].ativo = 0;
        printf("\nCliente %s removido com sucesso!\n", listaClientes[indice].nome);
    }
}

// ----------------------------------------------------------------------------
// ORDENACAO: coloca os clientes em ordem alfabetica (Bubble Sort).
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void ordenarClientesPorNome() {
    int i, j;
    struct Cliente aux; // variavel auxiliar para fazer a troca

    for (i = 0; i < totalClientes - 1; i++) {
        for (j = 0; j < totalClientes - 1 - i; j++) {
            // strcmp devolve um numero maior que 0 se o primeiro nome vem depois no alfabeto
            if (strcmp(listaClientes[j].nome, listaClientes[j + 1].nome) > 0) {
                aux = listaClientes[j];
                listaClientes[j] = listaClientes[j + 1];
                listaClientes[j + 1] = aux;
            }
        }
    }
    printf("\nClientes ordenados por nome (A a Z)!\n");
    listarClientes();
}

// ----------------------------------------------------------------------------
// ARQUIVO: salva todos os dados do modulo no arquivo clientes.txt
// Formato: 1a linha = quantidade,
// depois cada campo de cada registro em uma linha.
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void salvarClientes() {
    FILE *arquivo; // ponteiro que representa o arquivo aberto
    int i;

    arquivo = fopen("clientes.txt", "w"); // "w" = escrita: cria o arquivo ou apaga o conteudo antigo

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo clientes.txt!\n");
    } else {
        fprintf(arquivo, "%d\n", totalClientes);
        for (i = 0; i < totalClientes; i++) {
            fprintf(arquivo, "%d\n", listaClientes[i].idCliente);
            fprintf(arquivo, "%s\n", listaClientes[i].nome);
            fprintf(arquivo, "%s\n", listaClientes[i].telefone);
            fprintf(arquivo, "%.2f\n", listaClientes[i].saldoHoras);
            fprintf(arquivo, "%d\n", listaClientes[i].ativo);
        }
        fclose(arquivo); // sempre fechar o arquivo depois de usar
        printf("\nDados salvos no arquivo clientes.txt\n");
    }
}

// ----------------------------------------------------------------------------
// ARQUIVO: le o arquivo clientes.txt e coloca os dados de volta no vetor.
// E chamada uma vez, no inicio do main().
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void carregarClientes() {
    FILE *arquivo;
    int i;

    arquivo = fopen("clientes.txt", "r"); // "r" = leitura

    if (arquivo == NULL) {
        // na primeira vez o arquivo ainda nao existe, entao o sistema comeca vazio
        printf("Arquivo clientes.txt nao encontrado. Comecando sem dados.\n");
    } else {
        fscanf(arquivo, "%d", &totalClientes);
        for (i = 0; i < totalClientes; i++) {
            fscanf(arquivo, "%d", &listaClientes[i].idCliente);
            fscanf(arquivo, " %[^\n]", listaClientes[i].nome);
            fscanf(arquivo, " %[^\n]", listaClientes[i].telefone);
            fscanf(arquivo, "%f", &listaClientes[i].saldoHoras);
            fscanf(arquivo, "%d", &listaClientes[i].ativo);
        }
        fclose(arquivo);
        printf("%d cliente(s) carregado(s) do arquivo clientes.txt\n", totalClientes);
    }
}

// ----------------------------------------------------------------------------
// Submenu do Modulo 1
// Autor: [Integrante A - Alexander ]
// ----------------------------------------------------------------------------
void moduloClientes() {
    int opcaoCliente;
    do {
        printf("\n--- [MODULO 1: GESTAO DE CLIENTES (Integrante A)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar Todos os Clientes\n");
        printf("3. Editar Dados ou Saldo de Horas de Cliente\n");
        printf("4. Remover Cliente\n");
        printf("5. Buscar Cliente por ID\n");
        printf("6. [ORDENACAO] Listar Clientes em Ordem Alfabetica\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoCliente = -1; // comeca invalida: se digitarem uma letra, cai no default
        scanf("%d", &opcaoCliente);
        while (getchar() != '\n') { } // joga fora o que sobrou digitado (letras e o Enter)

        switch (opcaoCliente) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                editarCliente();
                break;
            case 4:
                removerCliente();
                break;
            case 5:
                buscarCliente();
                break;
            case 6:
                ordenarClientesPorNome();
                break;
            case 0:
                salvarClientes(); // grava os dados no arquivo antes de sair do modulo
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Clientes!\n");
        }
    } while (opcaoCliente != 0);
}
