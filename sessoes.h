// ============================================================================
// ARQUIVO: sessoes.h
// MODULO 4: PERSPECTIVA DE SESSOES E RELATORIOS
// Autor: [Integrante D - Guilherme Henrique Bueno, 47290391]
// Este arquivo tem a struct, o vetor global e todas as funcoes deste modulo.
// Ele e incluido no main.c com: #include "sessoes.h"
// ============================================================================

// ----- DADOS DO MODULO (ESCOPO GLOBAL) -----

// 4. Perspectiva do Integrante D: Sessoes de uso e Relatorios
struct Sessao {
    int idSessao;
    int idClienteSessao;
    int idComputadorSessao;
    int minutosUsados;
    float valorTotal;
};

struct Sessao historicoSessoes[50];
int totalSessoes = 0;
int proximoIdSessao = 1; // proximo ID a ser usado (so aumenta, para nao repetir ID depois de cancelar)


// ----- FUNCOES DO MODULO -----

// ----------------------------------------------------------------------------
// Procura uma sessao pelo ID e devolve a posicao dela no vetor.
// Se nao encontrar, devolve -1.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
int buscarIndiceSessao(int id) {
    int i;
    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].idSessao == id) {
            return i;
        }
    }
    return -1;
}

// ----------------------------------------------------------------------------
// Registra uma sessao: cruza um Cliente com um Computador e calcula o valor.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void registrarSessao() {
    int idCliente, idComputador, minutos;
    int indiceCliente, indiceComputador;
    float valor;

    if (totalSessoes >= 50) {
        printf("\n[ERRO] Limite de 50 sessoes atingido!\n");
    } else {
        printf("\nID do cliente: ");
        scanf("%d", &idCliente);
        indiceCliente = buscarIndiceCliente(idCliente); // funcao do Modulo 1

        printf("ID do computador: ");
        scanf("%d", &idComputador);
        indiceComputador = buscarIndiceComputador(idComputador); // funcao do Modulo 2

        if (indiceCliente == -1) {
            printf("\n[ERRO] Cliente nao encontrado! Cadastre o cliente no Modulo 1.\n");
        } else if (indiceComputador == -1) {
            printf("\n[ERRO] Computador nao encontrado! Cadastre o computador no Modulo 2.\n");
        } else {
            // repete a pergunta ate o usuario digitar um tempo maior que zero
            do {
                printf("Minutos usados: ");
                scanf("%d", &minutos);
            } while (minutos <= 0);

            // usamos 60.0 (e nao 60) para a divisao ter casas decimais
            valor = (minutos / 60.0) * listaComputadores[indiceComputador].valorHora;

            historicoSessoes[totalSessoes].idSessao = proximoIdSessao;
            historicoSessoes[totalSessoes].idClienteSessao = idCliente;
            historicoSessoes[totalSessoes].idComputadorSessao = idComputador;
            historicoSessoes[totalSessoes].minutosUsados = minutos;
            historicoSessoes[totalSessoes].valorTotal = valor;
            totalSessoes++;
            proximoIdSessao++;

            printf("\nSessao registrada com sucesso!\n");
            printf("Cliente: %s | Computador: %s | %d minutos | Total: R$ %.2f\n",
                   listaClientes[indiceCliente].nome, listaComputadores[indiceComputador].descricao,
                   minutos, valor);
        }
    }
}

// ----------------------------------------------------------------------------
// Lista todas as sessoes registradas.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void listarSessoes() {
    int i;

    printf("\n--- HISTORICO DE SESSOES ---\n");
    if (totalSessoes == 0) {
        printf("Nenhuma sessao registrada.\n");
    } else {
        for (i = 0; i < totalSessoes; i++) {
            printf("Sessao %d | ID Cliente: %d | ID Computador: %d | %d minutos | R$ %.2f\n",
                   historicoSessoes[i].idSessao, historicoSessoes[i].idClienteSessao,
                   historicoSessoes[i].idComputadorSessao, historicoSessoes[i].minutosUsados,
                   historicoSessoes[i].valorTotal);
        }
    }
}

// ----------------------------------------------------------------------------
// Cancela (estorna) uma sessao: apaga ela do vetor puxando as proximas
// uma posicao para tras.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void cancelarSessao() {
    int id;
    int indice;
    int i;

    printf("\nDigite o ID da sessao que deseja cancelar: ");
    scanf("%d", &id);
    indice = buscarIndiceSessao(id);

    if (indice == -1) {
        printf("\n[ERRO] Sessao nao encontrada!\n");
    } else {
        printf("\nSessao %d cancelada. Valor estornado: R$ %.2f\n", id, historicoSessoes[indice].valorTotal);
        for (i = indice; i < totalSessoes - 1; i++) {
            historicoSessoes[i] = historicoSessoes[i + 1];
        }
        totalSessoes--;
    }
}

// ----------------------------------------------------------------------------
// RELATORIO: computador com mais minutos de uso somando todas as sessoes.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void relatorioComputadorMaisUsado() {
    int i, j;
    int somaMinutos;
    int maiorMinutos = 0;
    int indiceMaior = -1; // -1 = ainda nao achou nenhum

    // para cada computador, soma os minutos de todas as sessoes dele
    for (i = 0; i < totalComputadores; i++) {
        somaMinutos = 0;
        for (j = 0; j < totalSessoes; j++) {
            if (historicoSessoes[j].idComputadorSessao == listaComputadores[i].idComputador) {
                somaMinutos = somaMinutos + historicoSessoes[j].minutosUsados;
            }
        }
        // se esse computador passou o maior ate agora, ele vira o novo maior
        if (somaMinutos > maiorMinutos) {
            maiorMinutos = somaMinutos;
            indiceMaior = i;
        }
    }

    printf("\n--- RELATORIO: COMPUTADOR MAIS UTILIZADO ---\n");
    if (indiceMaior == -1) {
        printf("Nenhuma sessao registrada ainda.\n");
    } else {
        printf("Computador: %s (ID %d)\n", listaComputadores[indiceMaior].descricao,
               listaComputadores[indiceMaior].idComputador);
        printf("Tempo total de uso: %d minutos\n", maiorMinutos);
    }
}

// ----------------------------------------------------------------------------
// RELATORIO: cliente VIP = cliente com mais minutos de uso somando as sessoes.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void relatorioClienteVip() {
    int i, j;
    int somaMinutos;
    int maiorMinutos = 0;
    int indiceMaior = -1;

    for (i = 0; i < totalClientes; i++) {
        somaMinutos = 0;
        for (j = 0; j < totalSessoes; j++) {
            if (historicoSessoes[j].idClienteSessao == listaClientes[i].idCliente) {
                somaMinutos = somaMinutos + historicoSessoes[j].minutosUsados;
            }
        }
        if (somaMinutos > maiorMinutos) {
            maiorMinutos = somaMinutos;
            indiceMaior = i;
        }
    }

    printf("\n--- RELATORIO: CLIENTE VIP ---\n");
    if (indiceMaior == -1) {
        printf("Nenhuma sessao registrada ainda.\n");
    } else {
        printf("Cliente VIP: %s (ID %d)\n", listaClientes[indiceMaior].nome,
               listaClientes[indiceMaior].idCliente);
        printf("Tempo total de uso: %d minutos\n", maiorMinutos);
    }
}

// ----------------------------------------------------------------------------
// RELATORIO: mostra todas as sessoes de um cliente e o total gasto por ele.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void relatorioSessoesPorCliente() {
    int id;
    int i;
    int quantidade = 0;
    float totalGasto = 0;

    printf("\nDigite o ID do cliente: ");
    scanf("%d", &id);

    printf("\n--- RELATORIO: SESSOES DO CLIENTE %d ---\n", id);
    for (i = 0; i < totalSessoes; i++) {
        if (historicoSessoes[i].idClienteSessao == id) {
            printf("Sessao %d | ID Computador: %d | %d minutos | R$ %.2f\n",
                   historicoSessoes[i].idSessao, historicoSessoes[i].idComputadorSessao,
                   historicoSessoes[i].minutosUsados, historicoSessoes[i].valorTotal);
            quantidade++;
            totalGasto = totalGasto + historicoSessoes[i].valorTotal;
        }
    }

    if (quantidade == 0) {
        printf("Nenhuma sessao encontrada para esse cliente.\n");
    } else {
        printf("Total: %d sessoes | Valor gasto: R$ %.2f\n", quantidade, totalGasto);
    }
}

// ----------------------------------------------------------------------------
// ORDENACAO: coloca as sessoes da mais cara para a mais barata (Bubble Sort).
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void ordenarSessoesPorValor() {
    int i, j;
    struct Sessao aux;

    for (i = 0; i < totalSessoes - 1; i++) {
        for (j = 0; j < totalSessoes - 1 - i; j++) {
            // aqui o sinal e "<" porque queremos do MAIOR para o menor
            if (historicoSessoes[j].valorTotal < historicoSessoes[j + 1].valorTotal) {
                aux = historicoSessoes[j];
                historicoSessoes[j] = historicoSessoes[j + 1];
                historicoSessoes[j + 1] = aux;
            }
        }
    }
    printf("\nSessoes ordenadas por valor (mais cara primeiro)!\n");
    listarSessoes();
}

// ----------------------------------------------------------------------------
// ARQUIVO: salva todos os dados do modulo no arquivo sessoes.txt
// Formato: 1a linha = quantidade, 2a linha = proximo ID,
// depois cada campo de cada registro em uma linha.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void salvarSessoes() {
    FILE *arquivo; // ponteiro que representa o arquivo aberto
    int i;

    arquivo = fopen("sessoes.txt", "w"); // "w" = escrita: cria o arquivo ou apaga o conteudo antigo

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo sessoes.txt!\n");
    } else {
        fprintf(arquivo, "%d\n", totalSessoes);
        fprintf(arquivo, "%d\n", proximoIdSessao);
        for (i = 0; i < totalSessoes; i++) {
            fprintf(arquivo, "%d\n", historicoSessoes[i].idSessao);
            fprintf(arquivo, "%d\n", historicoSessoes[i].idClienteSessao);
            fprintf(arquivo, "%d\n", historicoSessoes[i].idComputadorSessao);
            fprintf(arquivo, "%d\n", historicoSessoes[i].minutosUsados);
            fprintf(arquivo, "%.2f\n", historicoSessoes[i].valorTotal);
        }
        fclose(arquivo); // sempre fechar o arquivo depois de usar
        printf("\nDados salvos no arquivo sessoes.txt\n");
    }
}

// ----------------------------------------------------------------------------
// ARQUIVO: le o arquivo sessoes.txt e coloca os dados de volta no vetor.
// E chamada uma vez, no inicio do main().
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void carregarSessoes() {
    FILE *arquivo;
    int i;

    arquivo = fopen("sessoes.txt", "r"); // "r" = leitura

    if (arquivo == NULL) {
        // na primeira vez o arquivo ainda nao existe, entao o sistema comeca vazio
        printf("Arquivo sessoes.txt nao encontrado. Comecando sem dados.\n");
    } else {
        fscanf(arquivo, "%d", &totalSessoes);
        fscanf(arquivo, "%d", &proximoIdSessao);
        for (i = 0; i < totalSessoes; i++) {
            fscanf(arquivo, "%d", &historicoSessoes[i].idSessao);
            fscanf(arquivo, "%d", &historicoSessoes[i].idClienteSessao);
            fscanf(arquivo, "%d", &historicoSessoes[i].idComputadorSessao);
            fscanf(arquivo, "%d", &historicoSessoes[i].minutosUsados);
            fscanf(arquivo, "%f", &historicoSessoes[i].valorTotal);
        }
        fclose(arquivo);
        printf("%d sessao(oes) carregada(s) do arquivo sessoes.txt\n", totalSessoes);
    }
}

// ----------------------------------------------------------------------------
// Submenu do Modulo 4
// Autor: [Integrante D - Guilherme Henrique Bueno, 47290391]
// ----------------------------------------------------------------------------
void moduloSessoesRelatorios() {
    int opcaoSessao;
    do {
        printf("\n--- [MODULO 4: SESSOES E RELATORIOS (Integrante D)] ---\n");
        printf("1. Registrar Nova Sessao (Cruza Cliente + Computador + Tempo)\n");
        printf("2. Listar Historico de Sessoes\n");
        printf("3. Cancelar / Estornar Sessao\n");
        printf("4. [RELATORIO] Computador Mais Utilizado\n");
        printf("5. [RELATORIO] Cliente VIP (Maior Tempo de Uso)\n");
        printf("6. [RELATORIO] Sessoes de um Cliente Especifico\n");
        printf("7. [ORDENACAO] Listar Sessoes por Valor (Maior para Menor)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoSessao = -1; // comeca invalida: se digitarem uma letra, cai no default
        scanf("%d", &opcaoSessao);
        while (getchar() != '\n') { } // joga fora o que sobrou digitado (letras e o Enter)

        switch (opcaoSessao) {
            case 1:
                registrarSessao();
                break;
            case 2:
                listarSessoes();
                break;
            case 3:
                cancelarSessao();
                break;
            case 4:
                relatorioComputadorMaisUsado();
                break;
            case 5:
                relatorioClienteVip();
                break;
            case 6:
                relatorioSessoesPorCliente();
                break;
            case 7:
                ordenarSessoesPorValor();
                break;
            case 0:
                salvarSessoes(); // grava os dados no arquivo antes de sair do modulo
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Sessoes!\n");
        }
    } while (opcaoSessao != 0);
}
