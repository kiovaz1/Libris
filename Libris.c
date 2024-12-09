# include <stdio.h>
# include <stdlib.h>

typedef enum {
    DISPONIVEL =  1,
    EMPRESTADO =  0
} statusLivro;

typedef struct{
    char titulo[100];
    char autor[100];
    int ISBN;
    int anoDePublicacao;
    statusLivro;
} Livro;

typedef struct{
    char nome[100];
    int ID;
    int contato;
    int numeroDeEmprestimosAtuais;
} Usuario;

typedef struct{
    Usuario ID;
    Livro ISBN;
    char dataDeEmprestimo[11];
    char dataDeDevolucao[11];
} Emprestimo;

// GERENCIAMENTO LIVROS
int cadastrarLivro();
int consultarLivro();
int atualizarLivro();
int removerLivro();

// GERENCIAMENTO USUÁRIOS
int cadastrarUsuario();
int atualizarUsuario();
int removerUsuario();

// GERENCIAMENTO DE EMPRESTIMOS
int realizarEmprestimo();
int registrarDevolucao();

// OUTRAS FUNÇÕES
void listarLivrosDisponiveis();
void listarLivrosEmprestados();

int main() {
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
    
    
    //  interface do menu
    
    
        return 0;
}