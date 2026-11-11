#include <stdio.h>
#include <string.h>

// ============================================================================
// LAN HOUSE BYTE 2000 - CHECKPOINT 2
// Cadastro, listagem, edicao, remocao, relatorios e ordenacao
// Codigo dividido em modulos: um arquivo .h para cada integrante
// Dados salvos em arquivos .txt (FILE *) para nao perder ao fechar
// Equipe: [Alexander, Guilherme Henrique, João Felipe, Nicolas Bryan]
// ============================================================================

// ============================================================================
// PARTE 1: MODULOS DA EQUIPE (1 ARQUIVO .h POR INTEGRANTE)
// Cada arquivo .h tem a struct, o vetor global e as funcoes do integrante.
// Usamos aspas (" ") porque os arquivos estao na mesma pasta do main.c.
// A ordem importa: sessoes.h usa funcoes de clientes.h e computadores.h,
// por isso ele e incluido por ultimo.
// ============================================================================
#include "clientes.h"      // Modulo 1 - Alexander
#include "computadores.h"  // Modulo 2 - João Felipe
#include "produtos.h"      // Modulo 3 - Nicolas Bryan
#include "sessoes.h"       // Modulo 4 - Guilherme Henrique


// ============================================================================
// PARTE 2: FUNCAO COMUM DA EQUIPE
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


// ============================================================================
// PARTE 3: FUNCAO PRINCIPAL (MAIN) - DESPACHANTE DE MENUS
// Autor: [Integrante A - Alexander Guimarães Gallotti Moreira, 47364548]
// ============================================================================
int main() {
    int opcaoPrincipal;

    // carrega os dados salvos nos arquivos .txt (se existirem)
    carregarClientes();
    carregarComputadores();
    carregarProdutos();
    carregarSessoes();

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
        opcaoPrincipal = -1; // comeca invalida: se digitarem uma letra, cai no default
        scanf("%d", &opcaoPrincipal);
        while (getchar() != '\n') { } // joga fora o que sobrou digitado (letras e o Enter)

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
