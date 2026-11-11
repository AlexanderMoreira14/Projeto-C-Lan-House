# Lan House Byte 2000 - Checkpoint 2

**Disciplina:** Algoritmos e Pensamento Computacional

## Integrantes e módulos

|Módulo|Integrante|Arquivo|Struct|Arquivo de dados|
|-|-|-|-|-|
|1. Clientes|Alexander Guimarães Gallotti Moreira, 47364548|`clientes.h`|`Cliente`|`clientes.txt`|
|2. Computadores|João Felipe Alves Silva, 48302422|`computadores.h`|`Computador`|`computadores.txt`|
|3. Lanchonete / Produtos|Nicolas Bryan de Oliveira Camargo, 48070068|`produtos.h`|`Produto`|`produtos.txt`|
|4. Sessões e Relatórios|Guilherme Henrique Bueno, 47290391|`sessoes.h`|`Sessao`|`sessoes.txt`|

## O que está pronto

* **Cadastro, listagem, busca, edição e remoção** em funções separadas, em todos os módulos.
* **Relatórios (Módulo 4):** computador mais utilizado, cliente VIP e sessões de um cliente específico.
* **Ordenação (Bubble Sort):** clientes por nome, computadores por valor da hora, produtos por preço e sessões por valor.
* **Divisão em módulos (.h):** cada integrante tem seu próprio arquivo `.h` com a struct, o vetor global e as funções do seu módulo.
* **Arquivos (FILE \*):** cada módulo tem `salvar...()` e `carregar...()`.
  * Ao abrir o programa, o `main()` carrega os 4 arquivos `.txt` (se existirem).
  * Ao voltar de um submenu para o menu principal (opção 0), os dados daquele módulo são salvos no `.txt`.

## Como executar

Deixe o `main.c` e os 4 arquivos `.h` na **mesma pasta**. Abra o `main.c` no Dev-C++ e pressione F11.
Os arquivos `.txt` são criados sozinhos na mesma pasta, na primeira vez que você sair de um submenu.
