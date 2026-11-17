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
int proximoIdSessao = 1;


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
        indiceCliente = buscarIndiceCliente(idCliente);

        printf("ID do computador: ");
        scanf("%d", &idComputador);
        indiceComputador = buscarIndiceComputador(idComputador);

        if (indiceCliente == -1) {
            printf("\n[ERRO] Cliente nao encontrado! Cadastre o cliente no Modulo 1.\n");
        } else if (indiceComputador == -1) {
            printf("\n[ERRO] Computador nao encontrado! Cadastre o computador no Modulo 2.\n");
        } else {
            do {
                printf("Minutos usados: ");
                minutos = -1;
                scanf("%d", &minutos);
                while (getchar() != '\n') { }
            } while (minutos <= 0);

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
    int indiceMaior = -1;

    for (i = 0; i < totalComputadores; i++) {
        somaMinutos = 0;
        for (j = 0; j < totalSessoes; j++) {
            if (historicoSessoes[j].idComputadorSessao == listaComputadores[i].idComputador) {
                somaMinutos = somaMinutos + historicoSessoes[j].minutosUsados;
            }
        }
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
// RELATORIO COM MATRIZ 2D: minutos de uso de cada cliente em cada computador.
// Linha = cliente, coluna = computador, cada celula = soma dos minutos.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void relatorioMatrizDeUso() {
    int matriz[50][50];
    int i, j, k;

    for (i = 0; i < totalClientes; i++) {
        for (j = 0; j < totalComputadores; j++) {
            matriz[i][j] = 0;
        }
    }

    for (k = 0; k < totalSessoes; k++) {
        i = buscarIndiceCliente(historicoSessoes[k].idClienteSessao);
        j = buscarIndiceComputador(historicoSessoes[k].idComputadorSessao);
        if (i != -1 && j != -1) {
            matriz[i][j] = matriz[i][j] + historicoSessoes[k].minutosUsados;
        }
    }

    printf("\n--- RELATORIO: MATRIZ DE USO (minutos por cliente x computador) ---\n");
    printf("Cliente     ");
    for (j = 0; j < totalComputadores; j++) {
        if (listaComputadores[j].ativo == 1) {
            printf("   PC%2d", listaComputadores[j].idComputador);
        }
    }
    printf("\n");

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1) {
            printf("ID %2d       ", listaClientes[i].idCliente);
            for (j = 0; j < totalComputadores; j++) {
                if (listaComputadores[j].ativo == 1) {
                    printf("%7d", matriz[i][j]);
                }
            }
            printf("\n");
        }
    }
}

// ----------------------------------------------------------------------------
// BUSCA TEXTUAL: mostra as sessoes dos clientes que tem o texto no nome.
// Cruza o Modulo 1 (nome do cliente) com o historico de sessoes.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void buscarSessoesPorNomeCliente() {
    char texto[50];
    int i;
    int indiceCliente;
    int encontrou = 0;

    printf("\nDigite o nome do cliente ou parte do nome: ");
    scanf(" %[^\n]", texto);

    printf("\n--- RESULTADO DA BUSCA ---\n");
    for (i = 0; i < totalSessoes; i++) {
        indiceCliente = buscarIndiceCliente(historicoSessoes[i].idClienteSessao);
        if (indiceCliente != -1 && strstr(listaClientes[indiceCliente].nome, texto) != NULL) {
            printf("Sessao %d | Cliente: %s | ID Computador: %d | %d minutos | R$ %.2f\n",
                   historicoSessoes[i].idSessao, listaClientes[indiceCliente].nome,
                   historicoSessoes[i].idComputadorSessao, historicoSessoes[i].minutosUsados,
                   historicoSessoes[i].valorTotal);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhuma sessao encontrada para clientes com \"%s\" no nome.\n", texto);
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
// ARQUIVO: grava o vetor inteiro no arquivo sessoes.csv
// Formato: uma sessao por linha, campos separados por ;
// Exemplo de linha: 1;3;2;90;12,00
// E chamada depois de registrar ou cancelar, para o arquivo
// ficar sempre igual ao que esta na memoria.
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void salvarSessoes() {
    FILE *arquivo;
    int i;

    arquivo = fopen("sessoes.csv", "w");

    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel salvar o arquivo sessoes.csv!\n");
    } else {
        for (i = 0; i < totalSessoes; i++) {
            fprintf(arquivo, "%d;%d;%d;%d;%.2f\n",
                    historicoSessoes[i].idSessao, historicoSessoes[i].idClienteSessao,
                    historicoSessoes[i].idComputadorSessao, historicoSessoes[i].minutosUsados,
                    historicoSessoes[i].valorTotal);
        }
        fclose(arquivo);
        printf("Dados salvos no arquivo sessoes.csv\n");
    }
}

// ----------------------------------------------------------------------------
// ARQUIVO: le o arquivo sessoes.csv e coloca os dados de volta no vetor.
// E chamada uma vez, no inicio do main().
// Autor: [Integrante D - Guilherme Henrique]
// ----------------------------------------------------------------------------
void carregarSessoes() {
    FILE *arquivo;

    arquivo = fopen("sessoes.csv", "r");

    if (arquivo == NULL) {
        printf("Arquivo sessoes.csv nao encontrado. Comecando sem dados.\n");
    } else {
        totalSessoes = 0;
        while (totalSessoes < 50 &&
               fscanf(arquivo, "%d;%d;%d;%d;%f\n",
                      &historicoSessoes[totalSessoes].idSessao,
                      &historicoSessoes[totalSessoes].idClienteSessao,
                      &historicoSessoes[totalSessoes].idComputadorSessao,
                      &historicoSessoes[totalSessoes].minutosUsados,
                      &historicoSessoes[totalSessoes].valorTotal) == 5) {
            if (historicoSessoes[totalSessoes].idSessao >= proximoIdSessao) {
                proximoIdSessao = historicoSessoes[totalSessoes].idSessao + 1;
            }
            totalSessoes++;
        }
        fclose(arquivo);
        printf("%d sessao(oes) carregada(s) do arquivo sessoes.csv\n", totalSessoes);
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
        printf("8. [RELATORIO] Matriz de Uso (Cliente x Computador)\n");
        printf("9. Buscar Sessoes pelo Nome do Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        opcaoSessao = -1;
        scanf("%d", &opcaoSessao);
        while (getchar() != '\n') { }

        switch (opcaoSessao) {
            case 1:
                registrarSessao();
                salvarSessoes();
                break;
            case 2:
                listarSessoes();
                break;
            case 3:
                cancelarSessao();
                salvarSessoes();
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
            case 8:
                relatorioMatrizDeUso();
                break;
            case 9:
                buscarSessoesPorNomeCliente();
                break;
            case 0:
                salvarSessoes();
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Sessoes!\n");
        }
    } while (opcaoSessao != 0);
}
