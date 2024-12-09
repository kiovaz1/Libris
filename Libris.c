#include <stdio.h>
#include <stdlib.h>

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Para sistemas Windows
    #else
        system("clear"); // Para sistemas Unix (Linux, macOS)
    #endif
}

typedef enum {
    DISPONIVEL = 1,
    EMPRESTADO = 0
} statusLivro;

typedef struct {
    char titulo[100];
    char autor[100];
    int ISBN;
    int anoDePublicacao;
    statusLivro status;
} Livro;

typedef struct {
    char nome[100];
    int ID;
    int contato;
    int numeroDeEmprestimosAtuais;
} Usuario;

typedef struct {
    Usuario usuario;
    Livro livro;
    char dataDeEmprestimo[11];
    char dataDeDevolucao[11];
} Emprestimo;

// Função para validar entradas numéricas
int validaEntrada() {
    int num;
    while (scanf("%d", &num) != 1) {
        while (getchar() != '\n'); // Limpa o buffer de entrada
        printf("Entrada inválida! Digite um número inteiro: ");
    }
    return num;
}

// Função para garantir que o número seja positivo
int validaNumeroPositivo() {
    int num;
    while (1) {
        num = validaEntrada();
        if (num < 0) {
            printf("Número inválido! Digite um número positivo: ");
        } else {
            break;
        }
    }
    return num;
}

// Funções para gerenciamento de livros
int cadastrarLivro() {
    printf("Cadastro de livro realizado com sucesso!\n");
    return 0;
}

int consultarLivro() {
    printf("Consulta de livro realizada com sucesso!\n");
    return 0;
}

int atualizarLivro() {
    printf("Livro atualizado com sucesso!\n");
    return 0;
}

int removerLivro() {
    printf("Livro removido com sucesso!\n");
    return 0;
}

// Funções para gerenciamento de usuários
int cadastrarUsuario() {
    printf("Cadastro de usuário realizado com sucesso!\n");
    return 0;
}

int atualizarUsuario() {
    printf("Usuário atualizado com sucesso!\n");
    return 0;
}

int removerUsuario() {
    printf("Usuário removido com sucesso!\n");
    return 0;
}

// Funções para gerenciamento de empréstimos
int realizarEmprestimo() {
    printf("Empréstimo realizado com sucesso!\n");
    return 0;
}

int registrarDevolucao() {
    printf("Devolução registrada com sucesso!\n");
    return 0;
}

// Funções para outras funcionalidades
void listarLivrosDisponiveis() {
    printf("Livros disponíveis listados com sucesso!\n");
}

void listarLivrosEmprestados() {
    printf("Livros emprestados listados com sucesso!\n");
}

// Função para voltar para o menu anterior
void voltarParaMenu() {
    printf("\nPressione qualquer tecla para voltar ao menu...\n");
    getchar();  // Para capturar o Enter após a última entrada
    getchar();  // Aguarda a pressionamento de uma tecla para continuar
}

void menuLivros() {
    int opcao;
    do {
        clearConsole();
        printf("\n--- Gerenciamento de Livros ---\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Consultar Livro\n");
        printf("3. Atualizar Livro\n");
        printf("4. Remover Livro\n");
        printf("5. Voltar\n");
        printf("Escolha uma opção: ");
        opcao = validaEntrada();

        switch (opcao) {
            case 1: cadastrarLivro(); break;
            case 2: consultarLivro(); break;
            case 3: atualizarLivro(); break;
            case 4: removerLivro(); break;
            case 5: return;
            default: printf("Opção inválida! Tente novamente.\n");
        }
        voltarParaMenu();
    } while (1);
}

void menuUsuarios() {
    int opcao;
    do {
        clearConsole();
        printf("\n--- Gerenciamento de Usuários ---\n");
        printf("1. Cadastrar Usuário\n");
        printf("2. Atualizar Usuário\n");
        printf("3. Remover Usuário\n");
        printf("4. Voltar\n");
        printf("Escolha uma opção: ");
        opcao = validaEntrada();

        switch (opcao) {
            case 1: cadastrarUsuario(); break;
            case 2: atualizarUsuario(); break;
            case 3: removerUsuario(); break;
            case 4: return;
            default: printf("Opção inválida! Tente novamente.\n");
        }
        voltarParaMenu();
    } while (1);
}

void menuEmprestimos() {
    int opcao;
    do {
        clearConsole();
        printf("\n--- Gerenciamento de Empréstimos ---\n");
        printf("1. Realizar Empréstimo\n");
        printf("2. Registrar Devolução\n");
        printf("3. Voltar\n");
        printf("Escolha uma opção: ");
        opcao = validaEntrada();

        switch (opcao) {
            case 1: realizarEmprestimo(); break;
            case 2: registrarDevolucao(); break;
            case 3: return;
            default: printf("Opção inválida! Tente novamente.\n");
        }
        voltarParaMenu();
    } while (1);
}

void menuOutrasFuncoes() {
    int opcao;
    do {
        clearConsole();
        printf("\n--- Outras Funções ---\n");
        printf("1. Listar Livros Disponíveis\n");
        printf("2. Listar Livros Emprestados\n");
        printf("3. Voltar\n");
        printf("Escolha uma opção: ");
        opcao = validaEntrada();

        switch (opcao) {
            case 1: listarLivrosDisponiveis(); break;
            case 2: listarLivrosEmprestados(); break;
            case 3: return;
            default: printf("Opção inválida! Tente novamente.\n");
        }
        voltarParaMenu();
    } while (1);
}

int main() {
    int escolhaOpcao;
    clearConsole();
    printf(" ▄█        ▄█  ▀█████████▄     ▄████████  ▄█     ▄████████ \n");
    printf("███       ███    ███    ███   ███    ███ ███    ███    ███ \n");
    printf("███       ███▌   ███    ███   ███    ███ ███▌   ███    █▀  \n");
    printf("███       ███▌  ▄███▄▄▄██▀   ▄███▄▄▄▄██▀ ███▌   ███        \n");
    printf("███       ███▌ ▀▀███▀▀▀██▄  ▀▀███▀▀▀▀▀   ███▌ ▀███████████ \n");
    printf("███       ███    ███    ██▄ ▀███████████ ███           ███ \n");
    printf("███▌    ▄ ███    ███    ███   ███    ███ ███     ▄█    ███ \n");
    printf("█████▄▄██ █▀   ▄█████████▀    ███    ███ █▀    ▄████████▀  \n");
    printf("▀                             ███    ███                   \n");
    printf("\n---- 𝕲𝖊𝖗𝖊𝖓𝖈𝖎𝖆𝖒𝖊𝖓𝖙𝖔 𝖉𝖊 𝕷𝖎𝖛𝖗𝖔𝖘, 𝖀𝖘𝖚𝖆́𝖗𝖎𝖔𝖘 𝖊 𝕰𝖒𝖕𝖗𝖊́𝖘𝖙𝖎𝖒𝖔𝖘 ----\n");
    printf("1. Gerenciamento de Livros\n");
    printf("2. Gerenciamento de Usuários\n");
    printf("3. Gerenciamento de Empréstimos\n");
    printf("4. Outras Funções\n");
    printf("Escolha uma opção: ");
    escolhaOpcao = validaEntrada();

    switch (escolhaOpcao) {
        case 1: menuLivros(); break;
        case 2: menuUsuarios(); break;
        case 3: menuEmprestimos(); break;
        case 4: menuOutrasFuncoes(); break;
        default: printf("Opção inválida! Tente novamente.\n");
    }

    return 0;
}
