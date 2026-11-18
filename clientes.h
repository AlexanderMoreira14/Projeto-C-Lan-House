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
    float saldoHoras;
    int ativo;
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
            return i;
        }
    }
    return -1;
}

// ----------------------------------------------------------------------------
// Cadastra um novo cliente na proxima posicao livre do vetor.
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void cadastrarCliente() {
    if (totalClientes >= 50) {
        printf("\n[ERRO] Limite de 50 clientes atingido!\n");
    } else {
        listaClientes[totalClientes].idCliente = totalClientes + 1;

        printf("\nNome do cliente: ");
        scanf(" %[^\n]", listaClientes[totalClientes].nome);
        printf("Telefone: ");
        scanf(" %[^\n]", listaClientes[totalClientes].telefone);
        do {
            printf("Saldo inicial de horas (ex: 2,5): ");
            listaClientes[totalClientes].saldoHoras = -1;
            scanf("%f", &listaClientes[totalClientes].saldoHoras);
            while (getchar() != '\n') { }
        } while (listaClientes[totalClientes].saldoHoras < 0);
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
    int encontrou = 0;

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
// BUSCA TEXTUAL: mostra todos os clientes que tem o texto digitado no nome.
// Exemplo: digitando "Silva" aparecem "Ana Silva" e "Bruno Silva".
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void buscarClientePorNome() {
    char texto[50];
    int i;
    int encontrou = 0;

    printf("\nDigite o nome ou parte do nome: ");
    scanf(" %[^\n]", texto);

    printf("\n--- RESULTADO DA BUSCA ---\n");
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1 && strstr(listaClientes[i].nome, texto) != NULL) {
            printf("ID: %d | Nome: %s | Telefone: %s | Saldo: %.1f horas\n",
                   listaClientes[i].idCliente, listaClientes[i].nome,
                   listaClientes[i].telefone, listaClientes[i].saldoHoras);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum cliente encontrado com \"%s\" no nome.\n", texto);
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
        do {
            printf("Novo saldo de horas (ex: 2,5): ");
            listaClientes[indice].saldoHoras = -1;
            scanf("%f", &listaClientes[indice].saldoHoras);
            while (getchar() != '\n') { }
        } while (listaClientes[indice].saldoHoras < 0);
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
    struct Cliente aux;

    for (i = 0; i < totalClientes - 1; i++) {
        for (j = 0; j < totalClientes - 1 - i; j++) {
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
// ARQUIVO: grava o vetor inteiro no arquivo clientes.csv
// Formato: um cliente por linha, campos separados por ;
// Exemplo de linha: 1;Ana Souza;11987654321;5,0;1
// E chamada depois de cadastrar, editar ou remover, para o arquivo
// ficar sempre igual ao que esta na memoria.
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void salvarClientes() {
    FILE *arquivo;
    int i;

    arquivo = fopen("clientes.csv", "w");

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo clientes.csv!\n");
    } else {
        for (i = 0; i < totalClientes; i++) {
            fprintf(arquivo, "%d;%s;%s;%.1f;%d\n",
                    listaClientes[i].idCliente, listaClientes[i].nome,
                    listaClientes[i].telefone, listaClientes[i].saldoHoras,
                    listaClientes[i].ativo);
        }
        fclose(arquivo);
        printf("Dados salvos no arquivo clientes.csv\n");
    }
}

// ----------------------------------------------------------------------------
// ARQUIVO: le o arquivo clientes.csv e coloca os dados de volta no vetor.
// E chamada uma vez, no inicio do main().
// Autor: [Integrante A - Alexander]
// ----------------------------------------------------------------------------
void carregarClientes() {
    FILE *arquivo;

    arquivo = fopen("clientes.csv", "r");

    if (arquivo == NULL) {
        printf("Arquivo clientes.csv nao encontrado. Comecando sem dados.\n");
    } else {
        totalClientes = 0;
        while (totalClientes < 50 &&
               fscanf(arquivo, "%d;%[^;];%[^;];%f;%d\n",
                      &listaClientes[totalClientes].idCliente, listaClientes[totalClientes].nome,
                      listaClientes[totalClientes].telefone, &listaClientes[totalClientes].saldoHoras,
                      &listaClientes[totalClientes].ativo) == 5) {
            totalClientes++;
        }
        fclose(arquivo);
        printf("%d cliente(s) carregado(s) do arquivo clientes.csv\n", totalClientes);
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
        printf("7. Buscar Cliente por Nome\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoCliente = -1;
        scanf("%d", &opcaoCliente);
        while (getchar() != '\n') { }

        switch (opcaoCliente) {
            case 1:
                cadastrarCliente();
                salvarClientes();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                editarCliente();
                salvarClientes();
                break;
            case 4:
                removerCliente();
                salvarClientes();
                break;
            case 5:
                buscarCliente();
                break;
            case 6:
                ordenarClientesPorNome();
                break;
            case 7:
                buscarClientePorNome();
                break;
            case 0:
                salvarClientes();
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Clientes!\n");
        }
    } while (opcaoCliente != 0);
}
