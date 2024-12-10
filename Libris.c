#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LIVROS 200
#define MAX_USUARIOS 50
#define MAX_EMPRESTIMOS 100

// Definições das estruturas
typedef struct {
    char titulo[100];
    char autor[100];
    char anoDePublicacao[10];
    char ISBN[20];
    char status[20]; // "disponivel" ou "emprestado"
} Livro;

typedef struct {
    int ID;
    char nome[100];
    char endereco[200];
    char contato[50];
} Usuario;

typedef struct {
    int livroID;
    int usuarioID;
    char dataEmprestimo[20];
    char dataDevolucao[20];
} Emprestimo;

// Vetores de dados
Livro livros[MAX_LIVROS];
Usuario usuarios[MAX_USUARIOS];
Emprestimo emprestimos[MAX_EMPRESTIMOS];

int numLivros = 0;
int numUsuarios = 0;
int numEmprestimos = 0;


int compararDatas(char *data1, char *data2) {
    // Formato de data: DD/MM/AAAA
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 < ano2) return -1;
    if (ano1 > ano2) return 1;
    if (mes1 < mes2) return -1;
    if (mes1 > mes2) return 1;
    if (dia1 < dia2) return -1;
    if (dia1 > dia2) return 1;
    return 0; // Datas são iguais
}
void registrarDevolucao() {
    clearConsole();
    int livroID, usuarioID;
    char dataDevolucao[11];

    printf("Digite o ID do livro para devolução: ");
    scanf("%d", &livroID);
    printf("Digite o ID do usuário: ");
    scanf("%d", &usuarioID);

    if (livroID < 1 || livroID > numLivros || usuarioID < 1 || usuarioID > numUsuarios) {
        printf("ID inválido.\n");
        return;
    }

    livroID--; usuarioID--;

    if (strcmp(livros[livroID].status, "emprestado") == 0) {
        printf("Digite a data de devolução (DD/MM/AAAA): ");
        scanf("%s", dataDevolucao);

        // Verificar se a devolução está dentro do prazo
        if (compararDatas(emprestimos[livroID].dataDevolucao, dataDevolucao) < 0) {
            printf("A devolução está atrasada! Prazo era até %s.\n", emprestimos[livroID].dataDevolucao);
        } else {
            printf("Devolução dentro do prazo.\n");
        }

        // Atualizar status do livro
        strcpy(livros[livroID].status, "disponivel");
        printf("Livro devolvido com sucesso!\n");
    } else {
        printf("Este livro não foi emprestado.\n");
    }
}
void cadastrarLivro() {
    clearConsole();
    if (numLivros < MAX_LIVROS) {
        Livro livro;
        printf("Digite o título do livro: ");
        scanf(" %[^\n]s", livro.titulo);  // [^\n] permite que o título tenha espaços
        printf("Digite o autor do livro: ");
        scanf(" %[^\n]s", livro.autor);
        printf("Digite o ano de publicação: ");
        scanf("%s", livro.anoDePublicacao);
        printf("Digite o ISBN do livro: ");
        scanf("%s", livro.ISBN);

        // Verificando se o ISBN já existe no sistema
        for (int i = 0; i < numLivros; i++) {
            if (strcmp(livros[i].ISBN, livro.ISBN) == 0) {
                printf("ISBN já cadastrado.\n");
                return;
            }
        }

        strcpy(livro.status, "disponivel");
        livros[numLivros++] = livro;
        printf("Livro cadastrado com sucesso!\n");
    } else {
        printf("Limite de livros atingido.\n");
    }
}
void realizarEmprestimo() {
    clearConsole();
    int livroID, usuarioID;

    printf("Digite o ID do livro para emprestar: ");
    scanf("%d", &livroID);
    printf("Digite o ID do usuário: ");
    scanf("%d", &usuarioID);

    if (livroID < 1 || livroID > numLivros || usuarioID < 1 || usuarioID > numUsuarios) {
        printf("ID inválido.\n");
        return;
    }

    livroID--; usuarioID--;

    if (strcmp(livros[livroID].status, "disponivel") == 0) {
        emprestimos[numEmprestimos].livroID = livroID;
        emprestimos[numEmprestimos].usuarioID = usuarioID;
        printf("Digite a data de empréstimo (DD/MM/AAAA): ");
        scanf("%s", emprestimos[numEmprestimos].dataEmprestimo);
        printf("Digite a data de devolução (DD/MM/AAAA): ");
        scanf("%s", emprestimos[numEmprestimos].dataDevolucao);

        strcpy(livros[livroID].status, "emprestado");
        numEmprestimos++;
        printf("Empréstimo realizado com sucesso!\n");
    } else {
        printf("Este livro já foi emprestado.\n");
    }
}

void listarLivrosDisponiveis() {
    clearConsole();
    printf("Lista de Livros Disponíveis:\n");
    for (int i = 0; i < numLivros; i++) {
        if (strcmp(livros[i].status, "disponivel") == 0) {
            printf("%d - %s\n", i + 1, livros[i].titulo);
        }
    }
}

void listarLivrosEmprestados() {
    clearConsole();
    printf("Lista de Livros Emprestados:\n");
    for (int i = 0; i < numLivros; i++) {
        if (strcmp(livros[i].status, "emprestado") == 0) {
            printf("%d - %s (Emprestado)\n", i + 1, livros[i].titulo);
        }
    }
}

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");  // Limpa o console no Windows
    #else
        system("clear");  // Limpa o console no Linux/Mac
    #endif
}


int validaEntrada() {
    int escolha;
    char buffer[50];

    while (1) {
        printf("Digite sua escolha: ");
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &escolha) == 1) {
                return escolha;
            } else {
                printf("Entrada inválida. Por favor, digite um número.\n");
            }
        } else {
            printf("Erro ao ler entrada. Tente novamente.\n");
        }
    }
}


// Funções de gerenciamento de livros
void listarLivrosDisponiveis() {
    clearConsole();
    printf("Lista de Livros Disponíveis:\n");
    int livrosDisponiveis = 0;
    for (int i = 0; i < numLivros; i++) {
        if (strcmp(livros[i].status, "disponivel") == 0) {
            printf("%d - %s\n", i + 1, livros[i].titulo);
            livrosDisponiveis++;
        }
    }
    if (livrosDisponiveis == 0) {
        printf("Nenhum livro disponível.\n");
    }
}

void listarLivrosEmprestados() {
    clearConsole();
    printf("----- Lista de Livros Emprestados -----\n");
    int livrosEmprestados = 0;

    for (int i = 0; i < numEmprestimos; i++) {
        int livroID = emprestimos[i].livroID;
        int usuarioID = emprestimos[i].usuarioID;

        if (livroID >= 0 && livroID < numLivros && usuarioID >= 0 && usuarioID < numUsuarios) {
            if (strcmp(livros[livroID].status, "emprestado") == 0) {
                printf("%d - %s (Emprestado por %s)\n", 
                livroID + 1, 
                livros[livroID].titulo, 
                usuarios[usuarioID].nome);
                livrosEmprestados++;
            }
        } else {
            printf("Erro: Empréstimo com dados inválidos detectado.\n");
        }
    }

    if (livrosEmprestados == 0) {
        printf("Nenhum livro emprestado.\n");
    }
    printf("---------------------------------------\n");
}


void cadastrarUsuario() {
    clearConsole();
    if (numUsuarios >= MAX_USUARIOS) {
        printf("Não é possível cadastrar mais usuários. Limite máximo atingido.\n");
        return;
    }

    Usuario novoUsuario;

    // Entrada de dados
    printf("Digite o ID do usuário (número único): ");
    scanf("%d", &novoUsuario.ID);
    getchar(); // Limpa o buffer do teclado
    printf("Digite o nome do usuário: ");
    fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0; // Remove o caractere '\n' gerado pelo fgets
    printf("Digite o endereço do usuário: ");
    fgets(novoUsuario.endereco, sizeof(novoUsuario.endereco), stdin);
    novoUsuario.endereco[strcspn(novoUsuario.endereco, "\n")] = 0; // Remove o '\n'
    printf("Digite o contato do usuário: ");
    fgets(novoUsuario.contato, sizeof(novoUsuario.contato), stdin);
    novoUsuario.contato[strcspn(novoUsuario.contato, "\n")] = 0; // Remove o '\n'

    // Adiciona o novo usuário ao vetor
    usuarios[numUsuarios] = novoUsuario;
    numUsuarios++;
    printf("Usuário cadastrado com sucesso!\n");
}
void atualizarUsuario() {
    clearConsole();
    int idUsuario;

    // Solicita o ID do usuário a ser atualizado
    printf("Digite o ID do usuário a ser atualizado: ");
    scanf("%d", &idUsuario);
    getchar(); // Limpa o buffer

    // Verifica se o usuário existe
    int encontrado = 0;
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].ID == idUsuario) {
            encontrado = 1;
            // Entrada de novos dados
            printf("Digite o novo nome do usuário: ");
            fgets(usuarios[i].nome, sizeof(usuarios[i].nome), stdin);
            usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = 0; // Remove o '\n'
            printf("Digite o novo endereço do usuário: ");
            fgets(usuarios[i].endereco, sizeof(usuarios[i].endereco), stdin);
            usuarios[i].endereco[strcspn(usuarios[i].endereco, "\n")] = 0; // Remove o '\n'
            printf("Digite o novo contato do usuário: ");
            fgets(usuarios[i].contato, sizeof(usuarios[i].contato), stdin);
            usuarios[i].contato[strcspn(usuarios[i].contato, "\n")] = 0; // Remove o '\n'
            printf("Usuário atualizado com sucesso!\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("Usuário com ID %d não encontrado.\n", idUsuario);
    }
}
void removerUsuario() {
    clearConsole();
    int idUsuario;

    // Solicita o ID do usuário a ser removido
    printf("Digite o ID do usuário a ser removido: ");
    scanf("%d", &idUsuario);
    
    int encontrado = 0;
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].ID == idUsuario) {
            encontrado = 1;
            // Remove o usuário
            for (int j = i; j < numUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            numUsuarios--;
            printf("Usuário removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Usuário com ID %d não encontrado.\n", idUsuario);
    }
}


// Função de gerenciamento de empréstimos
void realizarEmprestimo() {
    clearConsole();
    int livroID, usuarioID;
    printf("Digite o ID do livro para emprestar (1 a %d): ", numLivros);
    scanf("%d", &livroID);
    printf("Digite o ID do usuário (1 a %d): ", numUsuarios);
    scanf("%d", &usuarioID);

    if (livroID < 1 || livroID > numLivros || usuarioID < 1 || usuarioID > numUsuarios) {
        printf("ID inválido.\n");
        return;
    }

    livroID--; // Ajusta para índice do vetor
    usuarioID--; // Ajusta para índice do vetor
    
    if (strcmp(livros[livroID].status, "disponivel") == 0) {
        // Registro do empréstimo
        emprestimos[numEmprestimos].livroID = livroID;
        emprestimos[numEmprestimos].usuarioID = usuarioID;

        // Solicitar as datas de empréstimo e devolução
        printf("Digite a data de empréstimo (DD/MM/AAAA): ");
        scanf("%s", emprestimos[numEmprestimos].dataEmprestimo);
        printf("Digite a data de devolução (DD/MM/AAAA): ");
        scanf("%s", emprestimos[numEmprestimos].dataDevolucao);

        // Atualiza o status do livro para "emprestado"
        strcpy(livros[livroID].status, "emprestado");

        // Incrementa o contador de empréstimos
        numEmprestimos++;

        printf("Empréstimo realizado com sucesso!\n");
    } else {
        printf("Este livro já foi emprestado.\n");
    }
}
void registrarDevolucao() {
    clearConsole();
    int livroID, usuarioID;
    printf("Digite o ID do livro a ser devolvido (1 a %d): ", numLivros);
    scanf("%d", &livroID);
    printf("Digite o ID do usuário (1 a %d): ", numUsuarios);
    scanf("%d", &usuarioID);

    if (livroID < 1 || livroID > numLivros || usuarioID < 1 || usuarioID > numUsuarios) {
        printf("ID inválido.\n");
        return;
    }

    livroID--; // Ajusta para índice do vetor
    usuarioID--; // Ajusta para índice do vetor

    int encontrado = 0;

    // Procura o empréstimo registrado para este livro e usuário
    for (int i = 0; i < numEmprestimos; i++) {
        if (emprestimos[i].livroID == livroID && emprestimos[i].usuarioID == usuarioID) {
            // Livro encontrado, registrando devolução
            strcpy(livros[livroID].status, "disponivel");

            // Remove o empréstimo do vetor
            for (int j = i; j < numEmprestimos - 1; j++) {
                emprestimos[j] = emprestimos[j + 1];
            }
            numEmprestimos--;

            printf("Devolução registrada com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Nenhum empréstimo encontrado para esse livro e usuário.\n");
    }
}


// Funções do menu principal
void menuLivros() {
    int escolha;
    do {
        clearConsole();
        printf("\n--- Menu Livros ---\n");
        printf("1. Listar Livros Disponíveis\n");
        printf("2. Listar Livros Emprestados\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        escolha = validaEntrada();

        switch (escolha) {
            case 1: listarLivrosDisponiveis(); break;
            case 2: listarLivrosEmprestados(); break;
            case 0: break;
            default: printf("Opção inválida!\n"); break;
        }
    } while (escolha != 0);
}

void menuUsuarios() {
    int escolha;
    do {
        clearConsole();
        printf("\n--- Menu Usuários ---\n");
        printf("1. Listar Usuários\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        escolha = validaEntrada();

        switch (escolha) {
            case 1: listarUsuarios(); break;
            case 0: break;
            default: printf("Opção inválida!\n"); break;
        }
    } while (escolha != 0);
}

void menuEmprestimos() {
    int escolha;
    do {
        clearConsole();
        printf("\n--- Menu Empréstimos ---\n");
        printf("1. Realizar Empréstimo\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        escolha = validaEntrada();

        switch (escolha) {
            case 1: realizarEmprestimo(); break;
            case 0: break;
            default: printf("Opção inválida!\n"); break;
        }
    } while (escolha != 0);
}

void menuOutrasFuncoes() {
    int escolha;
    do {
        clearConsole();
        printf("\n--- Outras Funções ---\n");
        printf("1. Listar Livros Disponíveis\n");
        printf("2. Listar Livros Emprestados\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        escolha = validaEntrada();

        switch (escolha) {
            case 1: listarLivrosDisponiveis(); break;
            case 2: listarLivrosEmprestados(); break;
            case 0: break;
            default: printf("Opção inválida!\n"); break;
        }
    } while (escolha != 0);
}

// Função principal
int main() {
    // Adicionando livros e usuários de exemplo
    strcpy(livros[0].titulo, "O Pequeno Príncipe");
    strcpy(livros[0].autor, "Antoine de Saint-Exupéry");
    strcpy(livros[0].anoDePublicacao, "1943");
    strcpy(livros[0].ISBN, "978-85-508-0446-7");
    strcpy(livros[0].status, "disponivel");
    numLivros++;

    strcpy(livros[1].titulo, "1984");
    strcpy(livros[1].autor, "George Orwell");
    strcpy(livros[1].anoDePublicacao, "1949");
    strcpy(livros[1].ISBN, "978-0-452-28423-4");
    strcpy(livros[1].status, "disponivel");
    numLivros++;

    strcpy(usuarios[0].nome, "Carlos Silva");
    usuarios[0].ID = 1;
    strcpy(usuarios[0].endereco, "Rua A, 123");
    strcpy(usuarios[0].contato, "1234-5678");
    numUsuarios++;

    strcpy(usuarios[1].nome, "Maria Souza");
    usuarios[1].ID = 2;
    strcpy(usuarios[1].endereco, "Rua B, 456");
    strcpy(usuarios[1].contato, "9876-5432");
    numUsuarios++;

    int escolhaOpcao;
    clearConsole();
    // Exibindo o menu principal
    printf(" ▄█        ▄█  ▀█████████▄     ▄████████  ▄█     ▄████████ \n");
    printf("███       ███    ███    ███   ███    ███ ███    ███    ███ \n");
    printf("███       ███▌   ███    ███   ███    ███ ███▌   ███    █▀  \n");
    printf("███       ███▌  ▄███▄▄▄██▀   ▄███▄▄▄▄██▀ ███▌   ███        \n");
    printf("███       ███▌ ▀▀███▀▀▀██▄  ▀▀███▀▀▀▀▀   ███▌ ▀███████████ \n");
    printf("███       ███    ███    ██▄ ▀███████████ ███           ███ \n");
    printf("███▌    ▄ ███    ███    ███   ███    ███ ███     ▄█    ███ \n");
    printf("█████▄▄██ █▀   ▄█████████▀    ███    ███ █▀    ▄████████▀  \n");
    printf("▀                             ███    ███                   \n");
    printf("\n---- 𝕲𝖊𝖗𝖊𝖓𝖈𝖎𝖆𝖒𝖊𝖓𝖙𝖔 𝖉𝖊 𝕷𝖎𝖛𝖗𝖔𝖘, 𝖀𝖘𝖚𝖆́𝖗𝖎𝖔𝖘 𝖊 𝕰𝖒𝖕𝖗𝖊́𝖘𝖝𝖙𝖎𝖒𝖔𝖘 ----\n");
    printf("1. Gerenciamento de Livros\n");
    printf("2. Gerenciamento de Usuários\n");
    printf("3. Gerenciamento de Empréstimos\n");
    printf("4. Outras Funções\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    escolhaOpcao = validaEntrada();

    switch (escolhaOpcao) {
        case 1: menuLivros(); break;
        case 2: menuUsuarios(); break;
        case 3: menuEmprestimos(); break;
        case 4: menuOutrasFuncoes(); break;
        case 0: exit(0); break;
        default: printf("Opção inválida! Tente novamente.\n"); break;
    }

    return 0;
}
