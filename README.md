# Lan House Byte 2000 - Checkpoint 2

**Disciplina:** Algoritmos e Pensamento Computacional

## Integrantes e módulos

|Módulo|Integrante|Arquivo|Struct|Arquivo de dados|
|-|-|-|-|-|
|1. Clientes|Alexander Guimarães Gallotti Moreira, 47364548|`clientes.h`|`Cliente`|`clientes.csv`|
|2. Computadores|João Felipe Alves Silva, 48302422|`computadores.h`|`Computador`|`computadores.csv`|
|3. Lanchonete / Produtos|Nicolas Bryan de Oliveira Camargo, 48070068|`produtos.h`|`Produto`|`produtos.csv`|
|4. Sessões e Relatórios|Guilherme Henrique Bueno, 47290391|`sessoes.h`|`Sessao`|`sessoes.csv`|

## O que está pronto

* **Divisão em módulos (.h):** o `main.c` só tem o menu principal e inclui o `.h` de cada integrante.
* **Subfunções:** cada opção do `switch-case` chama uma função própria. Todos os módulos têm cadastrar, listar, buscar por ID, editar e remover.
* **Cadastro com validação:** valores numéricos inválidos (negativos, zero ou letras) fazem o programa perguntar de novo.
* **Busca textual (`strstr`):** cliente por nome, computador por descrição, produto por nome e sessões pelo nome do cliente.
* **Arquivos .csv separados por `;` (FILE \*):**
  * Ao abrir o programa, o `main()` carrega os 4 arquivos `.csv`.
  * Depois de cadastrar, editar, remover, vender, registrar ou cancelar, o vetor inteiro é gravado de novo no `.csv`.
  * Cada arquivo já vem com 8 ou mais registros reais.
* **Cruzamento entre módulos:**
  * Sessão: confere se o cliente e o computador existem e calcula o valor pelo tempo.
  * Venda de produto: confere se o cliente e o produto existem, confere o estoque, calcula o total e dá baixa no estoque.
* **Relatórios:** computador mais utilizado, cliente VIP, sessões de um cliente e **Matriz 2D** de uso (cliente x computador).
* **Ordenação (Bubble Sort):** clientes por nome, computadores por valor da hora, produtos por preço e sessões por valor.
* **Console:** `limparTela()` ao entrar em cada módulo e `setlocale` em português (números decimais com vírgula).
* **IDs únicos:** o ID é gerado pelo sistema e nunca se repete.

## Como executar

Deixe o `main.c`, os 4 arquivos `.h` e os 4 arquivos `.csv` na **mesma pasta**. Abra o `main.c` no Dev-C++ e pressione F11.

Ao digitar valores com casas decimais, use **vírgula** (exemplo: `5,50`).
