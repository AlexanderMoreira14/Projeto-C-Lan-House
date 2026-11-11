// ============================================================================
// ARQUIVO: computadores.h
// MODULO 2: PERSPECTIVA DE COMPUTADORES
// Autor: [Integrante B - João Felipe Alves Silva, 48302422]
// Este arquivo tem a struct, o vetor global e todas as funcoes deste modulo.
// Ele e incluido no main.c com: #include "computadores.h"
// ============================================================================

// ----- DADOS DO MODULO (ESCOPO GLOBAL) -----

// 2. Perspectiva do Integrante B: Computadores da Lan House
struct Computador {
    int idComputador;
    char descricao[40]; // exemplo: PC Gamer 01
    float valorHora; // preco cobrado por hora de uso
    int ocupado; // 1 = Em uso, 0 = Livre
    int ativo; // 1 = Ativo, 0 = Removido
};

struct Computador listaComputadores[50];
int totalComputadores = 0;


// ----- FUNCOES DO MODULO -----

// ----------------------------------------------------------------------------
// Procura um computador ATIVO pelo ID e devolve a posicao dele no vetor.
// Se nao encontrar, devolve -1.
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
int buscarIndiceComputador(int id) {
    int i;
    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].idComputador == id && listaComputadores[i].ativo == 1) {
            return i;
        }
    }
    return -1;
}

// ----------------------------------------------------------------------------
// Cadastra um novo computador (ele comeca Livre).
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void cadastrarComputador() {
    if (totalComputadores >= 50) {
        printf("\n[ERRO] Limite de 50 computadores atingido!\n");
    } else {
        // Mesmo raciocinio do cliente: a remocao e logica, entao o ID nao se repete.
        listaComputadores[totalComputadores].idComputador = totalComputadores + 1;

        printf("\nDescricao do computador (ex: PC Gamer 01): ");
        scanf(" %[^\n]", listaComputadores[totalComputadores].descricao);
        printf("Valor da hora (ex: 5.50): ");
        scanf("%f", &listaComputadores[totalComputadores].valorHora);
        listaComputadores[totalComputadores].ocupado = 0; // todo computador novo comeca livre
        listaComputadores[totalComputadores].ativo = 1;

        printf("\nComputador cadastrado com sucesso! ID gerado: %d\n", listaComputadores[totalComputadores].idComputador);
        totalComputadores++;
    }
}

// ----------------------------------------------------------------------------
// Lista todos os computadores ativos e mostra se estao Livres ou Em uso.
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void listarComputadores() {
    int i;
    int encontrou = 0;

    printf("\n--- LISTA DE COMPUTADORES ---\n");
    for (i = 0; i < totalComputadores; i++) {
        if (listaComputadores[i].ativo == 1) {
            printf("ID: %d | %s | R$ %.2f por hora | Status: ",
                   listaComputadores[i].idComputador, listaComputadores[i].descricao,
                   listaComputadores[i].valorHora);
            if (listaComputadores[i].ocupado == 1) {
                printf("Em uso\n");
            } else {
                printf("Livre\n");
            }
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum computador cadastrado.\n");
    }
}

// ----------------------------------------------------------------------------
// Busca um computador pelo ID e mostra os dados dele.
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void buscarComputador() {
    int id;
    int indice;

    printf("\nDigite o ID do computador: ");
    scanf("%d", &id);
    indice = buscarIndiceComputador(id);

    if (indice == -1) {
        printf("\n[ERRO] Computador nao encontrado!\n");
    } else {
        printf("\n--- COMPUTADOR ENCONTRADO ---\n");
        printf("ID: %d\n", listaComputadores[indice].idComputador);
        printf("Descricao: %s\n", listaComputadores[indice].descricao);
        printf("Valor da hora: R$ %.2f\n", listaComputadores[indice].valorHora);
        if (listaComputadores[indice].ocupado == 1) {
            printf("Status: Em uso\n");
        } else {
            printf("Status: Livre\n");
        }
    }
}

// ----------------------------------------------------------------------------
// Edita descricao, valor da hora e status (Livre / Em uso) de um computador.
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void editarComputador() {
    int id;
    int indice;

    printf("\nDigite o ID do computador que deseja editar: ");
    scanf("%d", &id);
    indice = buscarIndiceComputador(id);

    if (indice == -1) {
        printf("\n[ERRO] Computador nao encontrado!\n");
    } else {
        printf("Editando: %s\n", listaComputadores[indice].descricao);
        printf("Nova descricao: ");
        scanf(" %[^\n]", listaComputadores[indice].descricao);
        printf("Novo valor da hora: ");
        scanf("%f", &listaComputadores[indice].valorHora);

        // repete a pergunta ate o usuario digitar 0 ou 1
        do {
            printf("Status (0 = Livre, 1 = Em uso): ");
            scanf("%d", &listaComputadores[indice].ocupado);
        } while (listaComputadores[indice].ocupado != 0 && listaComputadores[indice].ocupado != 1);

        printf("\nComputador atualizado com sucesso!\n");
    }
}

// ----------------------------------------------------------------------------
// Remove um computador (remocao logica: apenas marca ativo = 0).
// Nao deixa remover um computador que esta em uso.
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void removerComputador() {
    int id;
    int indice;

    printf("\nDigite o ID do computador que deseja remover: ");
    scanf("%d", &id);
    indice = buscarIndiceComputador(id);

    if (indice == -1) {
        printf("\n[ERRO] Computador nao encontrado!\n");
    } else if (listaComputadores[indice].ocupado == 1) {
        printf("\n[ERRO] Nao e possivel remover um computador que esta em uso!\n");
    } else {
        listaComputadores[indice].ativo = 0;
        printf("\nComputador %s removido com sucesso!\n", listaComputadores[indice].descricao);
    }
}

// ----------------------------------------------------------------------------
// ORDENACAO: coloca os computadores do menor para o maior valor da hora (Bubble Sort).
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void ordenarComputadoresPorValor() {
    int i, j;
    struct Computador aux;

    for (i = 0; i < totalComputadores - 1; i++) {
        for (j = 0; j < totalComputadores - 1 - i; j++) {
            if (listaComputadores[j].valorHora > listaComputadores[j + 1].valorHora) {
                aux = listaComputadores[j];
                listaComputadores[j] = listaComputadores[j + 1];
                listaComputadores[j + 1] = aux;
            }
        }
    }
    printf("\nComputadores ordenados por valor da hora (mais barato primeiro)!\n");
    listarComputadores();
}

// ----------------------------------------------------------------------------
// ARQUIVO: salva todos os dados do modulo no arquivo computadores.txt
// Formato: 1a linha = quantidade,
// depois cada campo de cada registro em uma linha.
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void salvarComputadores() {
    FILE *arquivo; // ponteiro que representa o arquivo aberto
    int i;

    arquivo = fopen("computadores.txt", "w"); // "w" = escrita: cria o arquivo ou apaga o conteudo antigo

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo computadores.txt!\n");
    } else {
        fprintf(arquivo, "%d\n", totalComputadores);
        for (i = 0; i < totalComputadores; i++) {
            fprintf(arquivo, "%d\n", listaComputadores[i].idComputador);
            fprintf(arquivo, "%s\n", listaComputadores[i].descricao);
            fprintf(arquivo, "%.2f\n", listaComputadores[i].valorHora);
            fprintf(arquivo, "%d\n", listaComputadores[i].ocupado);
            fprintf(arquivo, "%d\n", listaComputadores[i].ativo);
        }
        fclose(arquivo); // sempre fechar o arquivo depois de usar
        printf("\nDados salvos no arquivo computadores.txt\n");
    }
}

// ----------------------------------------------------------------------------
// ARQUIVO: le o arquivo computadores.txt e coloca os dados de volta no vetor.
// E chamada uma vez, no inicio do main().
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void carregarComputadores() {
    FILE *arquivo;
    int i;

    arquivo = fopen("computadores.txt", "r"); // "r" = leitura

    if (arquivo == NULL) {
        // na primeira vez o arquivo ainda nao existe, entao o sistema comeca vazio
        printf("Arquivo computadores.txt nao encontrado. Comecando sem dados.\n");
    } else {
        fscanf(arquivo, "%d", &totalComputadores);
        for (i = 0; i < totalComputadores; i++) {
            fscanf(arquivo, "%d", &listaComputadores[i].idComputador);
            fscanf(arquivo, " %[^\n]", listaComputadores[i].descricao);
            fscanf(arquivo, "%f", &listaComputadores[i].valorHora);
            fscanf(arquivo, "%d", &listaComputadores[i].ocupado);
            fscanf(arquivo, "%d", &listaComputadores[i].ativo);
        }
        fclose(arquivo);
        printf("%d computador(es) carregado(s) do arquivo computadores.txt\n", totalComputadores);
    }
}

// ----------------------------------------------------------------------------
// Submenu do Modulo 2
// Autor: [Integrante B - João Felipe Alves Silva, 48302422]
// ----------------------------------------------------------------------------
void moduloComputadores() {
    int opcaoComputador;
    do {
        printf("\n--- [MODULO 2: GESTAO DE COMPUTADORES (Integrante B)] ---\n");
        printf("1. Cadastrar Novo Computador\n");
        printf("2. Listar Computadores / Ver Status (Livre ou Em Uso)\n");
        printf("3. Editar Descricao, Valor da Hora ou Status\n");
        printf("4. Remover Computador\n");
        printf("5. Buscar Computador por ID\n");
        printf("6. [ORDENACAO] Listar Computadores por Valor da Hora\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoComputador = -1; // comeca invalida: se digitarem uma letra, cai no default
        scanf("%d", &opcaoComputador);
        while (getchar() != '\n') { } // joga fora o que sobrou digitado (letras e o Enter)

        switch (opcaoComputador) {
            case 1:
                cadastrarComputador();
                break;
            case 2:
                listarComputadores();
                break;
            case 3:
                editarComputador();
                break;
            case 4:
                removerComputador();
                break;
            case 5:
                buscarComputador();
                break;
            case 6:
                ordenarComputadoresPorValor();
                break;
            case 0:
                salvarComputadores(); // grava os dados no arquivo antes de sair do modulo
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Computadores!\n");
        }
    } while (opcaoComputador != 0);
}
