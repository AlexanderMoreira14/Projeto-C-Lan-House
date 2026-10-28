#include <stdio.h>
#include <string.h>

// ============================================================================
// LAN HOUSE BYTE 2000 - CHECKPOINT 1
// Equipe: [Alexander, Guilherme Henrique, João Felipe, Nicolas Bryan]
// ============================================================================

// ============================================================================
// PARTE 1: MODELAGEM DE DADOS (ESCOPO GLOBAL - 1 STRUCT POR INTEGRANTE)
// ============================================================================

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


// ============================================================================
// PARTE 2: FUNCOES DE INTERFACE E MODULOS DE CADA INTEGRANTE
// ============================================================================

// ----------------------------------------------------------------------------
// FUNCAO COMUM DA EQUIPE: Cabecalho do sistema
// Autor: [Integrante A - Alexander Guimarães Gallotti Moreira, 47364548]
// ----------------------------------------------------------------------------
void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("      LAN HOUSE BYTE 2000 - SISTEMA DE GESTAO         \n");
    printf("======================================================\n");
}

// ----------------------------------------------------------------------------
// MODULO 1: PERSPECTIVA DE CLIENTES
// Autor: [Integrante A - Alexander ]
// ----------------------------------------------------------------------------
void moduloClientes() {
    int opcaoCliente;
    do {
        printf("\n--- [MODULO 1: GESTAO DE CLIENTES (Integrante A)] ---\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Listar / Buscar Clientes\n");
        printf("3. Editar Dados ou Saldo de Horas de Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoCliente);

        switch (opcaoCliente) {
            case 1:
                printf("\n[Em construcao] Rotina de Cadastro de Cliente...\n");
                printf("Campos previstos: ID, Nome, Telefone e Saldo de Horas.\n");
                break;
            case 2:
                printf("\n[Em construcao] Rotina de Busca e Listagem de Clientes...\n");
                break;
            case 3:
                printf("\n[Em construcao] Rotina de Edicao de Cliente por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Rotina de Remocao de Cliente...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Clientes!\n");
        }
    } while (opcaoCliente != 0);
}

// ----------------------------------------------------------------------------
// MODULO 2: PERSPECTIVA DE COMPUTADORES
// Autor: [Integrante B - João Felipe Alves Silva, 48302422]
// ----------------------------------------------------------------------------
void moduloComputadores() {
    int opcaoComputador;
    do {
        printf("\n--- [MODULO 2: GESTAO DE COMPUTADORES (Integrante B)] ---\n");
        printf("1. Cadastrar Novo Computador\n");
        printf("2. Listar Computadores / Ver Status (Livre ou Em Uso)\n");
        printf("3. Editar Valor da Hora ou Descricao\n");
        printf("4. Remover Computador\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoComputador);

        switch (opcaoComputador) {
            case 1:
                printf("\n[Em construcao] Cadastrando Computador (ID, Descricao, Valor da Hora)...\n");
                break;
            case 2:
                printf("\n[Em construcao] Listando computadores e se estao livres ou em uso...\n");
                break;
            case 3:
                printf("\n[Em construcao] Atualizando valor da hora ou descricao...\n");
                break;
            case 4:
                printf("\n[Em construcao] Removendo computador fora de uso...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Computadores!\n");
        }
    } while (opcaoComputador != 0);
}

// ----------------------------------------------------------------------------
// MODULO 3: PERSPECTIVA DE PRODUTOS DA LANCHONETE
// Autor: [Integrante C - Nicolas Bryan de Oliveira Camargo, 48070068]
// ----------------------------------------------------------------------------
void moduloProdutos() {
    int opcaoProduto;
    do {
        printf("\n--- [MODULO 3: LANCHONETE E ESTOQUE (Integrante C)] ---\n");
        printf("1. Cadastrar Novo Produto\n");
        printf("2. Listar / Buscar Produtos\n");
        printf("3. Editar Preco ou Estoque do Produto\n");
        printf("4. Remover Produto\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoProduto);

        switch (opcaoProduto) {
            case 1:
                printf("\n[Em construcao] Cadastrando Produto (ID, Nome, Categoria, Preco, Estoque)...\n");
                break;
            case 2:
                printf("\n[Em construcao] Listando produtos da lanchonete...\n");
                break;
            case 3:
                printf("\n[Em construcao] Atualizando preco ou quantidade em estoque...\n");
                break;
            case 4:
                printf("\n[Em construcao] Removendo produto do cardapio...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Produtos!\n");
        }
    } while (opcaoProduto != 0);
}

// ----------------------------------------------------------------------------
// MODULO 4: PERSPECTIVA DE SESSOES E RELATORIOS
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
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoSessao);

        switch (opcaoSessao) {
            case 1:
                printf("\n[Em construcao] Lancamento de sessao vinculando ID Cliente e ID Computador...\n");
                break;
            case 2:
                printf("\n[Em construcao] Exibindo todas as sessoes registradas...\n");
                break;
            case 3:
                printf("\n[Em construcao] Estorno de sessao por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Calculando ranking do computador mais usado...\n");
                break;
            case 5:
                printf("\n[Em construcao] Identificando cliente com maior tempo de uso...\n");
                break;
            case 6:
                printf("\n[Em construcao] Filtrando sessoes por ID de cliente...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Sessoes!\n");
        }
    } while (opcaoSessao != 0);
}


// ============================================================================
// PARTE 3: FUNCAO PRINCIPAL (MAIN) - DESPACHANTE DE MENUS
// Autor: [Integrante A - Alexander Guimarães Gallotti Moreira, 47364548]
// ============================================================================
int main() {
    int opcaoPrincipal;

    do {
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA DO SISTEMA:\n");
        printf("1. Modulo de Clientes (Integrante A)\n");
        printf("2. Modulo de Computadores (Integrante B)\n");
        printf("3. Modulo de Lanchonete / Produtos (Integrante C)\n");
        printf("4. Modulo de Sessoes e Relatorios (Integrante D)\n");
        printf("0. Encerrar o Sistema\n");
        printf("------------------------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
            case 1:
                moduloClientes();
                break;
            case 2:
                moduloComputadores();
                break;
            case 3:
                moduloProdutos();
                break;
            case 4:
                moduloSessoesRelatorios();
                break;
            case 0:
                printf("\nEncerrando o sistema Lan House Byte 2000... Ate logo!\n");
                break;
            default:
                printf("\n[ALERTA] Opcao invalida! Digite um numero de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
