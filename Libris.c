#include <stdio.h>
#include <string.h>

// Definições e constantes
#define MAX_LIVROS 100
#define MAX_USUARIOS 50
#define MAX_EMPRESTIMOS 100

// Estruturas
typedef struct {
    char titulo[100];
    char autor[100];
    char anoDePublicacao[10];
    char ISBN[20];
    char status[20];  // "disponivel" ou "emprestado"
} Livro;

typedef struct {
    int livroID;
    int usuarioID;
    char dataDeEmprestimo[20];
    char dataDeDevolucao[20];
} Emprestimo;

// Variáveis globais
Livro livros[MAX_LIVROS];
int numLivros = 0;
int numUsuarios = 0;
Emprestimo emprestimos[MAX_EMPRESTIMOS];
int numEmprestimos = 0;

// Funções
void clearConsole(); // Declaração da função

// Função de limpeza de tela (para sistemas Windows)
void clearConsole() {
    system("cls");
}

// Funções relacionadas a livros
void cadastrarLivro() {
    if (numLivros < MAX_LIVROS) {
        Livro livro;
        printf("Digite o título do livro: ");
        scanf(" %[^\n]s", livro.titulo);
        printf("Digite o autor do livro: ");
        scanf(" %[^\n]s", livro.autor);
        printf("Digite o ano de publicação: ");
        scanf("%s", livro.anoDePublicacao);
        printf("Digite o ISBN do livro: ");
        scanf("%s", livro.ISBN);
        strcpy(livro.status, "disponivel");
        
        // Verifica se o livro já existe pelo ISBN
        for (int i = 0; i < numLivros; i++) {
            if (strcmp(livros[i].ISBN, livro.ISBN) == 0) {
                printf("Erro: Livro com este ISBN já cadastrado.\n");
                return;
            }
        }
        
        livros[numLivros++] = livro;
        printf("Livro cadastrado com sucesso!\n");
    } else {
        printf("Erro: Não é possível cadastrar mais livros. Limite alcançado.\n");
    }
}

void listarLivrosDisponiveis() {
    printf("Livros disponíveis:\n");
    for (int i = 0; i < numLivros; i++) {
        if (strcmp(livros[i].status, "disponivel") == 0) {
            printf("Título: %s, Autor: %s, Ano: %s, ISBN: %s\n", livros[i].titulo, livros[i].autor, livros[i].anoDePublicacao, livros[i].ISBN);
        }
    }
}

void listarLivrosEmprestados() {
    printf("Livros emprestados:\n");
    for (int i = 0; i < numLivros; i++) {
        if (strcmp(livros[i].status, "emprestado") == 0) {
            printf("Título: %s, Autor: %s, Ano: %s, ISBN: %s\n", livros[i].titulo, livros[i].autor, livros[i].anoDePublicacao, livros[i].ISBN);
        }
    }
}

void realizarEmprestimo() {
    int livroID, usuarioID;
    char dataEmprestimo[20], dataDevolucao[20];
    
    printf("Digite o ID do livro: ");
    scanf("%d", &livroID);
    printf("Digite o ID do usuário: ");
    scanf("%d", &usuarioID);
    printf("Digite a data de empréstimo (dd/mm/aaaa): ");
    scanf("%s", dataEmprestimo);
    printf("Digite a data de devolução (dd/mm/aaaa): ");
    scanf("%s", dataDevolucao);
    
    if (livroID < 1 || livroID > numLivros || usuarioID < 1 || usuarioID > numUsuarios) {
        printf("Erro: ID do livro ou do usuário inválido.\n");
        return;
    }

    if (strcmp(livros[livroID - 1].status, "disponivel") == 0) {
        emprestimos[numEmprestimos].livroID = livroID;
        emprestimos[numEmprestimos].usuarioID = usuarioID;
        strcpy(emprestimos[numEmprestimos].dataDeEmprestimo, dataEmprestimo);
        strcpy(emprestimos[numEmprestimos].dataDeDevolucao, dataDevolucao);
        
        livros[livroID - 1].status[0] = 'e';  // Marca como emprestado
        numEmprestimos++;
        printf("Empréstimo realizado com sucesso!\n");
    } else {
        printf("Erro: Livro não disponível para empréstimo.\n");
    }
}

void registrarDevolucao() {
    int livroID;
    char dataDevolucao[20];
    
    printf("Digite o ID do livro: ");
    scanf("%d", &livroID);
    printf("Digite a data de devolução (dd/mm/aaaa): ");
    scanf("%s", dataDevolucao);
    
    if (livroID < 1 || livroID > numLivros) {
        printf("Erro: ID do livro inválido.\n");
        return;
    }
    
    if (strcmp(livros[livroID - 1].status, "emprestado") == 0) {
        livros[livroID - 1].status[0] = 'd';  // Marca como disponível
        printf("Devolução registrada com sucesso!\n");
    } else {
        printf("Erro: Livro não está emprestado.\n");
    }
}

void listarUsuarios() {
    printf("Função listarUsuarios ainda não implementada.\n");
}

void menuUsuarios() {
    int opcao;
    do {
        printf("\nMenu de Usuários:\n");
        printf("1. Listar Usuários\n");
        printf("2. Cadastrar Livro\n");
        printf("3. Listar Livros Disponíveis\n");
        printf("4. Listar Livros Emprestados\n");
        printf("5. Realizar Empréstimo\n");
        printf("6. Registrar Devolução\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: listarUsuarios(); break;
            case 2: cadastrarLivro(); break;
            case 3: listarLivrosDisponiveis(); break;
            case 4: listarLivrosEmprestados(); break;
            case 5: realizarEmprestimo(); break;
            case 6: registrarDevolucao(); break;
            case 0: break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    menuUsuarios();
    return 0;
}
