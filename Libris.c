#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>




// Definicao das structs, arrays e variaveis globais
#define MAX_LIVROS 100
#define MAX_USUARIOS 50
#define MAX_EMPRESTIMOS 100

typedef struct {
    char titulo[100];
    char autor[100];
    char ISBN[20];
    int ano_publicacao;
    int status;  // 0 para disponivel, 1 para emprestado
} Livro;

typedef struct {
    char nome[100];
    int id;
    char contato[50];
    int num_emprestimos;
} Usuario;

typedef struct {
    int id_usuario;
    char ISBN[20];
    char data_emprestimo[11];  // formato "dd/mm/yyyy"
    char data_devolucao_prevista[11];  // formato "dd/mm/yyyy"
} Emprestimo;

Livro livros[MAX_LIVROS];
Usuario usuarios[MAX_USUARIOS];
Emprestimo emprestimos[MAX_EMPRESTIMOS];

int num_livros = 0;
int num_usuarios = 0;
int num_emprestimos = 0;

// Funcao (limpar tela) Linux/Windows/Mac

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");  // Limpa o console no Windows
    #else
        system("clear");  // Limpa o console no Linux/Mac
    #endif
}

// Funcoes de gerenciamento de livros

void cadastrarLivro() {
    if (num_livros >= MAX_LIVROS) {
        printf("\nAcervo de livros cheio.\n");
        return;
    }

    Livro livro;
    clearConsole();
    printf("\n --- Cadastrar Livro --- \n");
    printf("Digite o titulo do livro: ");
    fgets(livro.titulo, 100, stdin);
    printf("Digite o autor: ");
    fgets(livro.autor, 100, stdin);
    printf("Digite o ISBN: ");
    fgets(livro.ISBN, 20, stdin);
    printf("Digite o ano de publicacao: ");
    scanf("%d", &livro.ano_publicacao);
    getchar();  // Limpar buffer

    livro.status = 0;  // Inicialmente, o livro esta disponivel
    livros[num_livros++] = livro;
    printf("\nLivro cadastrado com sucesso.\n");
}

void consultarLivro() {
    char ISBN[20];
    clearConsole();
    printf("\n --- Consultar Livro --- \n");
    printf("Digite o ISBN do livro: ");
    fgets(ISBN, 20, stdin);

    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            printf("Titulo: %s", livros[i].titulo);
            printf("Autor: %s", livros[i].autor);
            printf("Ano de publicacao: %d\n", livros[i].ano_publicacao);
            printf("Status: %s\n", livros[i].status == 0 ? "Disponivel" : "Emprestado");
            return;
        }
    }
    printf("\nLivro nao encontrado.\n");
}

void atualizarLivro() {
    char ISBN[20];
    clearConsole();
    printf("\n --- Atualizar Livro --- \n");
    printf("Digite o ISBN do livro a ser atualizado: ");
    fgets(ISBN, 20, stdin);

    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            printf("Atualize o titulo: ");
            fgets(livros[i].titulo, 100, stdin);
            printf("Atualize o autor: ");
            fgets(livros[i].autor, 100, stdin);
            printf("Atualize o ano de publicacao: ");
            scanf("%d", &livros[i].ano_publicacao);
            getchar();  // Limpar buffer
            printf("\nLivro atualizado com sucesso.\n");
            return;
        }
    }
    printf("\nLivro nao encontrado.\n");
}

void removerLivro() {
    char ISBN[20];
    clearConsole();
    printf("\n --- Remover Livro --- \n");
    printf("Digite o ISBN do livro a ser removido: ");
    fgets(ISBN, 20, stdin);

    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            for (int j = i; j < num_livros - 1; j++) {
                livros[j] = livros[j + 1];
            }
            num_livros--;
            printf("\nLivro removido com sucesso.\n");
            return;
        }
    }
    printf("\nLivro nao encontrado.\n");
}

// Funcoes de gerenciamento de usuarios

void cadastrarUsuario() {
    if (num_usuarios >= MAX_USUARIOS) {
        printf("Limite de usuarios atingido.\n");
        return;
    }

    Usuario usuario;
    clearConsole();
    printf("\n --- Cadastrar Usuario --- \n");
    printf("Digite o nome do usuario: ");
    fgets(usuario.nome, 100, stdin);
    printf("Digite o ID do usuario: ");
    scanf("%d", &usuario.id);
    getchar();  // Limpar buffer
    printf("Digite o contato do usuario: ");
    fgets(usuario.contato, 50, stdin);

    usuario.num_emprestimos = 0;
    usuarios[num_usuarios++] = usuario;
    printf("\nUsuario cadastrado com sucesso.\n");
}

void atualizarUsuario() {
    int id;
    clearConsole();
    printf("\n --- Atualizar Usuario --- \n");
    printf("Digite o ID do usuario a ser atualizado: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    for (int i = 0; i < num_usuarios; i++) {
        if (usuarios[i].id == id) {
            printf("Atualize o nome: ");
            fgets(usuarios[i].nome, 100, stdin);
            printf("Atualize o contato: ");
            fgets(usuarios[i].contato, 50, stdin);
            printf("\nUsuario atualizado com sucesso.\n");
            return;
        }
    }
    printf("\nUsuario nao encontrado.\n");
}

void removerUsuario() {
    int id;
    clearConsole();
    printf("\n --- Remover Usuario --- \n");
    printf("Digite o ID do usuario a ser removido: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    for (int i = 0; i < num_usuarios; i++) {
        if (usuarios[i].id == id) {
            for (int j = i; j < num_usuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            num_usuarios--;
            printf("\nUsuario removido com sucesso.\n");
            return;
        }
    }
    printf("\nUsuario nao encontrado.\n");
}

// Funcoes de gerenciamento de emprestimos

void realizarEmprestimo() {
    int id_usuario;
    char ISBN[20];
    clearConsole();
    printf("\n --- Realizar Emprestimo --- \n");
    printf("Digite o ID do usuario: ");
    scanf("%d", &id_usuario);
    getchar();  // Limpar buffer

    printf("Digite o ISBN do livro: ");
    fgets(ISBN, 20, stdin);

    // Verificar se o usuario existe
    int usuario_existe = 0;
    for (int i = 0; i < num_usuarios; i++) {
        if (usuarios[i].id == id_usuario) {
            usuario_existe = 1;
            break;
        }
    }

    if (!usuario_existe) {
        printf("\nUsuario nao encontrado.\n");
        return;
    }

    // Verificar se o livro existe e esta disponivel
    int livro_existe = 0;
    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            livro_existe = 1;
            if (livros[i].status == 1) {
                printf("\nLivro ja esta emprestado.\n");
                return;
            }
            break;
        }
    }

    if (!livro_existe) {
        printf("\nLivro nao encontrado.\n");
        return;
    }

    // Realizar emprestimo
    Emprestimo emprestimo;
    emprestimo.id_usuario = id_usuario;
    strcpy(emprestimo.ISBN, ISBN);
    printf("Digite a data de emprestimo (dd/mm/yyyy): ");
    fgets(emprestimo.data_emprestimo, 11, stdin);
    printf("Digite a data de devolucao prevista (dd/mm/yyyy): ");
    fgets(emprestimo.data_devolucao_prevista, 11, stdin);

    emprestimos[num_emprestimos++] = emprestimo;
    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            livros[i].status = 1;  // Livro agora esta emprestado
            break;
        }
    }

    printf("\nEmprestimo realizado com sucesso.\n");
}

void registrarDevolucao() {
    int id_usuario;
    char ISBN[20];
    clearConsole();
    printf("\n --- Registrar Devolucao --- \n");
    printf("Digite o ID do usuario: ");
    scanf("%d", &id_usuario);
    getchar();  // Limpar buffer

    printf("Digite o ISBN do livro: ");
    fgets(ISBN, 20, stdin);

    int emprestimo_encontrado = 0;
    for (int i = 0; i < num_emprestimos; i++) {
        if (emprestimos[i].id_usuario == id_usuario && strcmp(emprestimos[i].ISBN, ISBN) == 0) {
            emprestimo_encontrado = 1;
            for (int j = 0; j < num_livros; j++) {
                if (strcmp(livros[j].ISBN, ISBN) == 0) {
                    livros[j].status = 0;  // Livro devolvido
                    break;
                }
            }
            printf("\nDevolucao registrada com sucesso.\n");
            return;
        }
    }

    if (!emprestimo_encontrado) {
        printf("\nEmprestimo nao encontrado.\n");
    }
}

void listarLivrosDisponiveis() {
    clearConsole();
    printf("\n --- Livros Disponiveis --- \n");
    for (int i = 0; i < num_livros; i++) {
        if (livros[i].status == 0) {
            printf("Titulo: %s", livros[i].titulo);
            printf("Autor: %s", livros[i].autor);
            printf("ISBN: %s", livros[i].ISBN);
            printf("Ano: %d\n", livros[i].ano_publicacao);
        }
    }
}

void listarLivrosEmprestados() {
    clearConsole();
    printf("\n --- Livros Emprestados --- \n");
    for (int i = 0; i < num_livros; i++) {
        if (livros[i].status == 1) {
            printf("Titulo: %s", livros[i].titulo);
            printf("Autor: %s", livros[i].autor);
            printf("ISBN: %s", livros[i].ISBN);
            printf("Ano: %d\n", livros[i].ano_publicacao);
        }
    }
}

// Funcao principal (main)
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;

    do {
        printf("\t\t                                                     \n");
        printf("\t\t     _|        _|  _|                  _|            \n");
        printf("\t\t     _|            _|_|_|    _|  _|_|        _|_|_|  \n");
        printf("\t\t     _|        _|  _|    _|  _|_|      _|  _|_|      \n");
        printf("\t\t     _|        _|  _|    _|  _|        _|      _|_|  \n");
        printf("\t\t     _|_|_|_|  _|  _|_|_|    _|        _|  _|_|_|    \n");
        printf("\t\t                                                     ");
        printf("\n\t\t\tSistema de Gerenciamento de Biblioteca \n");
        printf("\t\t______________________________________________________\n\n");
        printf("\t(1) Cadastrar Livro\t\t\t");
        printf("\t(2) Consultar Livro\n");
        printf("\t(3) Atualizar Livro\t\t\t");
        printf("\t(4) Remover Livro\n");
        printf("\t(5) Cadastrar Usuario\t\t\t");
        printf("\t(6) Atualizar Usuario\n");
        printf("\t(7) Remover Usuario\t\t\t");
        printf("\t(8) Realizar Emprestimo\n");
        printf("\t(9) Registrar Devolucao\t\t\t");
        printf("\t(10) Listar Livros Disponiveis\n");
        printf("\t(11) Listar Livros Emprestados\t\t\t\n");
        printf("\n\t\t\t\t\t(0) Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer

        switch(opcao) {
            case 1:
                cadastrarLivro();
                break;
            case 2:
                consultarLivro();
                break;
            case 3:
                atualizarLivro();
                break;
            case 4:
                removerLivro();
                break;
            case 5:
                cadastrarUsuario();
                break;
            case 6:
                atualizarUsuario();
                break;
            case 7:
                removerUsuario();
                break;
            case 8:
                realizarEmprestimo();
                break;
            case 9:
                registrarDevolucao();
                break;
            case 10:
                listarLivrosDisponiveis();
                break;
            case 11:
                listarLivrosEmprestados();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}