#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>




// Definição das structs, arrays e variáveis globais
#define MAX_LIVROS 100
#define MAX_USUARIOS 50
#define MAX_EMPRESTIMOS 100

typedef struct {
    char titulo[100];
    char autor[100];
    char ISBN[20];
    int ano_publicacao;
    int status;  // 0 para disponível, 1 para emprestado
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

// Funções de gerenciamento de livros

void cadastrarLivro() {
    if (num_livros >= MAX_LIVROS) {
        printf("Acervo de livros cheio.\n");
        return;
    }

    Livro livro;
    printf("Digite o título do livro: ");
    fgets(livro.titulo, 100, stdin);
    printf("Digite o autor: ");
    fgets(livro.autor, 100, stdin);
    printf("Digite o ISBN: ");
    fgets(livro.ISBN, 20, stdin);
    printf("Digite o ano de publicação: ");
    scanf("%d", &livro.ano_publicacao);
    getchar();  // Limpar buffer

    livro.status = 0;  // Inicialmente, o livro está disponível
    livros[num_livros++] = livro;
    printf("Livro cadastrado com sucesso.\n");
}

void consultarLivro() {
    char ISBN[20];
    printf("Digite o ISBN do livro: ");
    fgets(ISBN, 20, stdin);

    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            printf("Título: %s", livros[i].titulo);
            printf("Autor: %s", livros[i].autor);
            printf("Ano de publicação: %d\n", livros[i].ano_publicacao);
            printf("Status: %s\n", livros[i].status == 0 ? "Disponível" : "Emprestado");
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

void atualizarLivro() {
    char ISBN[20];
    printf("Digite o ISBN do livro a ser atualizado: ");
    fgets(ISBN, 20, stdin);

    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            printf("Atualize o título: ");
            fgets(livros[i].titulo, 100, stdin);
            printf("Atualize o autor: ");
            fgets(livros[i].autor, 100, stdin);
            printf("Atualize o ano de publicação: ");
            scanf("%d", &livros[i].ano_publicacao);
            getchar();  // Limpar buffer
            printf("Livro atualizado com sucesso.\n");
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

void removerLivro() {
    char ISBN[20];
    printf("Digite o ISBN do livro a ser removido: ");
    fgets(ISBN, 20, stdin);

    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            for (int j = i; j < num_livros - 1; j++) {
                livros[j] = livros[j + 1];
            }
            num_livros--;
            printf("Livro removido com sucesso.\n");
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

// Funções de gerenciamento de usuários

void cadastrarUsuario() {
    if (num_usuarios >= MAX_USUARIOS) {
        printf("Limite de usuários atingido.\n");
        return;
    }

    Usuario usuario;
    printf("Digite o nome do usuário: ");
    fgets(usuario.nome, 100, stdin);
    printf("Digite o ID do usuário: ");
    scanf("%d", &usuario.id);
    getchar();  // Limpar buffer
    printf("Digite o contato do usuário: ");
    fgets(usuario.contato, 50, stdin);

    usuario.num_emprestimos = 0;
    usuarios[num_usuarios++] = usuario;
    printf("Usuário cadastrado com sucesso.\n");
}

void atualizarUsuario() {
    int id;
    printf("Digite o ID do usuário a ser atualizado: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    for (int i = 0; i < num_usuarios; i++) {
        if (usuarios[i].id == id) {
            printf("Atualize o nome: ");
            fgets(usuarios[i].nome, 100, stdin);
            printf("Atualize o contato: ");
            fgets(usuarios[i].contato, 50, stdin);
            printf("Usuário atualizado com sucesso.\n");
            return;
        }
    }
    printf("Usuário não encontrado.\n");
}

void removerUsuario() {
    int id;
    printf("Digite o ID do usuário a ser removido: ");
    scanf("%d", &id);
    getchar();  // Limpar buffer

    for (int i = 0; i < num_usuarios; i++) {
        if (usuarios[i].id == id) {
            for (int j = i; j < num_usuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            num_usuarios--;
            printf("Usuário removido com sucesso.\n");
            return;
        }
    }
    printf("Usuário não encontrado.\n");
}

// Funções de gerenciamento de empréstimos

void realizarEmprestimo() {
    int id_usuario;
    char ISBN[20];

    printf("Digite o ID do usuário: ");
    scanf("%d", &id_usuario);
    getchar();  // Limpar buffer

    printf("Digite o ISBN do livro: ");
    fgets(ISBN, 20, stdin);

    // Verificar se o usuário existe
    int usuario_existe = 0;
    for (int i = 0; i < num_usuarios; i++) {
        if (usuarios[i].id == id_usuario) {
            usuario_existe = 1;
            break;
        }
    }

    if (!usuario_existe) {
        printf("Usuário não encontrado.\n");
        return;
    }

    // Verificar se o livro existe e está disponível
    int livro_existe = 0;
    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            livro_existe = 1;
            if (livros[i].status == 1) {
                printf("Livro já está emprestado.\n");
                return;
            }
            break;
        }
    }

    if (!livro_existe) {
        printf("Livro não encontrado.\n");
        return;
    }

    // Realizar empréstimo
    Emprestimo emprestimo;
    emprestimo.id_usuario = id_usuario;
    strcpy(emprestimo.ISBN, ISBN);
    printf("Digite a data de empréstimo (dd/mm/yyyy): ");
    fgets(emprestimo.data_emprestimo, 11, stdin);
    printf("Digite a data de devolução prevista (dd/mm/yyyy): ");
    fgets(emprestimo.data_devolucao_prevista, 11, stdin);

    emprestimos[num_emprestimos++] = emprestimo;
    for (int i = 0; i < num_livros; i++) {
        if (strcmp(livros[i].ISBN, ISBN) == 0) {
            livros[i].status = 1;  // Livro agora está emprestado
            break;
        }
    }

    printf("Empréstimo realizado com sucesso.\n");
}

void registrarDevolucao() {
    int id_usuario;
    char ISBN[20];

    printf("Digite o ID do usuário: ");
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
            printf("Devolução registrada com sucesso.\n");
            return;
        }
    }

    if (!emprestimo_encontrado) {
        printf("Empréstimo não encontrado.\n");
    }
}

void listarLivrosDisponiveis() {
    printf("Livros disponíveis:\n");
    for (int i = 0; i < num_livros; i++) {
        if (livros[i].status == 0) {
            printf("Título: %s", livros[i].titulo);
            printf("Autor: %s", livros[i].autor);
            printf("ISBN: %s", livros[i].ISBN);
            printf("Ano: %d\n", livros[i].ano_publicacao);
        }
    }
}

void listarLivrosEmprestados() {
    printf("Livros emprestados:\n");
    for (int i = 0; i < num_livros; i++) {
        if (livros[i].status == 1) {
            printf("Título: %s", livros[i].titulo);
            printf("Autor: %s", livros[i].autor);
            printf("ISBN: %s", livros[i].ISBN);
            printf("Ano: %d\n", livros[i].ano_publicacao);
        }
    }
}

// Função principal (main)
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;

    do {
        printf("\n--- Sistema de Gerenciamento de Biblioteca ---\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Consultar Livro\n");
        printf("3. Atualizar Livro\n");
        printf("4. Remover Livro\n");
        printf("5. Cadastrar Usuário\n");
        printf("6. Atualizar Usuário\n");
        printf("7. Remover Usuário\n");
        printf("8. Realizar Empréstimo\n");
        printf("9. Registrar Devolução\n");
        printf("10. Listar Livros Disponíveis\n");
        printf("11. Listar Livros Emprestados\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
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
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
