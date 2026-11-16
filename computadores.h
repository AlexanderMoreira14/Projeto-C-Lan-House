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
        // VALIDACAO: repete a pergunta ate digitar um valor maior que zero
        do {
            printf("Valor da hora (ex: 5,50): ");
            listaComputadores[totalComputadores].valorHora = -1; // comeca invalido: se digitarem letra, pergunta de novo
            scanf("%f", &listaComputadores[totalComputadores].valorHora);
            while (getchar() != '\n') { } // joga fora o que sobrou digitado
        } while (listaComputadores[totalComputadores].valorHora <= 0);
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
// BUSCA TEXTUAL: mostra todos os computadores que tem o texto na descricao.
// Exemplo: digitando "Gamer" aparecem "PC Gamer 01" e "PC Gamer 02".
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void buscarComputadorPorDescricao() {
    char texto[40];
    int i;
    int encontrou = 0;

    printf("\nDigite a descricao ou parte dela: ");
    scanf(" %[^\n]", texto);

    printf("\n--- RESULTADO DA BUSCA ---\n");
    for (i = 0; i < totalComputadores; i++) {
        // strstr procura o texto dentro da descricao: devolve NULL se nao encontrar
        if (listaComputadores[i].ativo == 1 && strstr(listaComputadores[i].descricao, texto) != NULL) {
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
        printf("Nenhum computador encontrado com \"%s\" na descricao.\n", texto);
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
            listaComputadores[indice].ocupado = -1; // comeca invalido: se digitarem letra, pergunta de novo
            scanf("%d", &listaComputadores[indice].ocupado);
            while (getchar() != '\n') { } // joga fora o que sobrou digitado
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
// ARQUIVO: grava o vetor inteiro no arquivo computadores.csv
// Formato: um computador por linha, campos separados por ;
// Exemplo de linha: 1;PC Gamer 01;8,00;0;1
// E chamada depois de cadastrar, editar ou remover, para o arquivo
// ficar sempre igual ao que esta na memoria.
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void salvarComputadores() {
    FILE *arquivo; // ponteiro que representa o arquivo aberto
    int i;

    arquivo = fopen("computadores.csv", "w"); // "w" = escrita: cria o arquivo ou apaga o conteudo antigo

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo computadores.csv!\n");
    } else {
        for (i = 0; i < totalComputadores; i++) {
            fprintf(arquivo, "%d;%s;%.2f;%d;%d\n",
                    listaComputadores[i].idComputador, listaComputadores[i].descricao,
                    listaComputadores[i].valorHora, listaComputadores[i].ocupado,
                    listaComputadores[i].ativo);
        }
        fclose(arquivo); // sempre fechar o arquivo depois de usar
        printf("Dados salvos no arquivo computadores.csv\n");
    }
}

// ----------------------------------------------------------------------------
// ARQUIVO: le o arquivo computadores.csv e coloca os dados de volta no vetor.
// E chamada uma vez, no inicio do main().
// Autor: [Integrante B - João Felipe]
// ----------------------------------------------------------------------------
void carregarComputadores() {
    FILE *arquivo;

    arquivo = fopen("computadores.csv", "r"); // "r" = leitura

    if (arquivo == NULL) {
        // na primeira vez o arquivo ainda nao existe, entao o sistema comeca vazio
        printf("Arquivo computadores.csv nao encontrado. Comecando sem dados.\n");
    } else {
        totalComputadores = 0;
        // %[^;] = le tudo ate encontrar o ; (assim a descricao pode ter espacos)
        // o while para quando o fscanf nao consegue mais ler os 5 campos (fim do arquivo)
        while (totalComputadores < 50 &&
               fscanf(arquivo, "%d;%[^;];%f;%d;%d\n",
                      &listaComputadores[totalComputadores].idComputador,
                      listaComputadores[totalComputadores].descricao,
                      &listaComputadores[totalComputadores].valorHora,
                      &listaComputadores[totalComputadores].ocupado,
                      &listaComputadores[totalComputadores].ativo) == 5) {
            totalComputadores++;
        }
        fclose(arquivo);
        printf("%d computador(es) carregado(s) do arquivo computadores.csv\n", totalComputadores);
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
        printf("7. Buscar Computador por Descricao\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoComputador = -1; // comeca invalida: se digitarem uma letra, cai no default
        scanf("%d", &opcaoComputador);
        while (getchar() != '\n') { } // joga fora o que sobrou digitado (letras e o Enter)

        switch (opcaoComputador) {
            case 1:
                cadastrarComputador();
                salvarComputadores(); // atualiza o .csv na hora
                break;
            case 2:
                listarComputadores();
                break;
            case 3:
                editarComputador();
                salvarComputadores(); // atualiza o .csv na hora
                break;
            case 4:
                removerComputador();
                salvarComputadores(); // atualiza o .csv na hora
                break;
            case 5:
                buscarComputador();
                break;
            case 6:
                ordenarComputadoresPorValor();
                break;
            case 7:
                buscarComputadorPorDescricao();
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
