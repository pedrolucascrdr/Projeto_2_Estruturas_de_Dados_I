#ifndef USUARIOS_H
#define USUARIOS_H

#define MAX_USUARIOS 100         // Máximo de usuários
#define MAX_NOME 50              // Tamanho máximo para nomes de usuário
#define MAX_SENHA 50             // Tamanho máximo para senhas
#define MAX_HISTORICO 100        // Número máximo de cálculos no histórico
#define MAX_CALCULO 100          // Tamanho máximo de uma entrada de cálculo

// Estrutura para armazenar dados de um usuário
typedef struct {
    int id;                             // Identificador único do usuário
    char nome[MAX_NOME];                // Nome de usuário
    char senha[MAX_SENHA];              // Senha do usuário
    char historico[MAX_HISTORICO][MAX_CALCULO]; // Histórico de cálculos
    int total_calculos;                 // Número de cálculos no histórico
} Usuario;

// Funções para gerenciamento de usuários
void cadastrarUsuario();
void listarUsuarios();
Usuario* login();
void editarUsuario();
void excluirUsuario();
Usuario* buscarUsuarioPorNome(char *nome);

// Funções do menu pós-login
void menuPosLogin(Usuario *usuario);
void calcular(Usuario *usuario);
void falar();
void verDataHora();
void verHistorico(Usuario *usuario);

// Funções para armazenamento de dados
void salvarUsuarios();
void carregarUsuarios();

#endif