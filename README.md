# Libris - Sistema de Gerenciamento de Biblioteca

## Descrição do Projeto

O **Libris** é um sistema desenvolvido em linguagem **C** para automatizar o processo de gerenciamento de livros, usuários e empréstimos em uma biblioteca comunitária fictícia. 
Este sistema visa substituir o processo manual, proporcionando mais eficiência e menos erros nas operações cotidianas da biblioteca. 
O sistema permite realizar tarefas como o cadastro e controle de livros e usuários, gerenciar empréstimos e devoluções, e verificar a disponibilidade dos livros.

## Funcionalidades

O sistema oferece as seguintes funcionalidades:

- **Gerenciamento de Livros**:
  - Cadastro, consulta, atualização e remoção de livros do acervo.
  - Verificação da disponibilidade de um livro.
  - Listagem dos livros disponíveis e emprestados.

- **Gerenciamento de Usuários**:
  - Cadastro, atualização e remoção de usuários (leitores).
  - Controle do número de empréstimos atuais por usuário.

- **Gerenciamento de Empréstimos**:
  - Realização de empréstimos de livros.
  - Registro de devolução dos livros emprestados.
  - Indicação de livros com atraso na devolução.

## Requisitos Técnicos

### 1. **Estruturas de Dados (Structs)**

O sistema utiliza as seguintes estruturas para representar os dados:

- **Livro**:
  - `titulo`: Título do livro.
  - `autor`: Autor do livro.
  - `ISBN`: Código único de identificação do livro.
  - `ano_publicacao`: Ano de publicação.
  - `status`: Indica se o livro está disponível ou emprestado.

- **Usuário**:
  - `nome`: Nome do usuário.
  - `id`: Identificação única do usuário.
  - `contato`: Detalhes de contato do usuário.
  - `emprestimos_atuais`: Número de empréstimos que o usuário possui no momento.

- **Empréstimo**:
  - `id_usuario`: ID do usuário que realizou o empréstimo.
  - `isbn_livro`: ISBN do livro emprestado.
  - `data_emprestimo`: Data em que o empréstimo foi realizado.
  - `data_devolucao_prevista`: Data prevista para a devolução do livro.

### 2. **Funções**

O sistema implementa várias funções para gerenciar os dados e realizar operações:

#### Gerenciamento de Livros:
- `cadastrarLivro()`: Cadastra um novo livro no acervo.
- `consultarLivro()`: Consulta informações sobre um livro.
- `atualizarLivro()`: Atualiza os dados de um livro existente.
- `removerLivro()`: Remove um livro do acervo.

#### Gerenciamento de Usuários:
- `cadastrarUsuario()`: Cadastra um novo usuário (leitor).
- `atualizarUsuario()`: Atualiza os dados de um usuário existente.
- `removerUsuario()`: Remove um usuário do sistema.

#### Gerenciamento de Empréstimos:
- `realizarEmprestimo()`: Realiza o empréstimo de um livro.
- `registrarDevolucao()`: Registra a devolução de um livro emprestado.

#### Outras Funções:
- `listarLivrosDisponiveis()`: Lista os livros disponíveis para empréstimo.
- `listarLivrosEmprestados()`: Lista os livros que estão emprestados no momento.

### 3. **Operadores Condicionais**:
- Verificação da disponibilidade de um livro antes de realizar o empréstimo.
- Verificação de validade do ID do usuário e ISBN do livro antes de realizar qualquer operação.
- Determinação de se a data de devolução está dentro do prazo e indicação de livros com atraso.

### 4. **Armazenamento de Dados**:
Inicialmente, os dados são armazenados em memória utilizando arrays ou listas.

## Como Usar

1. Clone o repositório para o seu computador:
   ```bash
   git clone https://github.com/seu-usuario/libris.git
