#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "usuarios.h"

#define ARQUIVO_USUARIOS "usuarios.txt"

// Array global para armazenar os usuários
Usuario usuarios[MAX_USUARIOS];
int totalUsuarios = 0; // Contador global de usuários

// Cadastra um novo usuário
void cadastrarUsuario() {
    if (totalUsuarios >= MAX_USUARIOS) {
        printf("Limite de usuarios atingido!\n");
        return;
    }

    Usuario novoUsuario;
    novoUsuario.id = totalUsuarios + 1; // Define um ID único
    novoUsuario.total_calculos = 0;     // Inicializa o histórico vazio

    printf("Digite o nome de usuario: ");
    scanf("%s", novoUsuario.nome);

    printf("Digite a senha: ");
    scanf("%s", novoUsuario.senha);

    usuarios[totalUsuarios] = novoUsuario; // Adiciona o novo usuário ao array
    totalUsuarios++;

    printf("Usuario cadastrado com sucesso!\n");
    salvarUsuarios(); // Salva os dados após cadastrar
}

// Lista todos os usuários cadastrados
void listarUsuarios() {
    if (totalUsuarios == 0) {
        printf("Nenhum usuario cadastrado!\n");
        return;
    }

    printf("\n--- Lista de Usuarios ---\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("ID: %d | Nome: %s\n", usuarios[i].id, usuarios[i].nome);
    }
}

// Realiza o login de um usuário
Usuario* login() {
    char nome[MAX_NOME], senha[MAX_SENHA];
    printf("Digite o nome de usuario: ");
    scanf("%s", nome);

    printf("Digite a senha: ");
    scanf("%s", senha);

    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            printf("Login bem-sucedido! Bem-vindo, %s!\n", nome);
            return &usuarios[i]; // Retorna o ponteiro para o usuário encontrado
        }
    }

    printf("Nome de usuario ou senha incorretos!\n");
    return NULL; // Falha no login
}

// Edita os dados de um usuário existente
void editarUsuario() {
    char nome[MAX_NOME];
    printf("Digite o nome de usuario que deseja editar: ");
    scanf("%s", nome);

    Usuario *usuario = buscarUsuarioPorNome(nome);
    if (usuario == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    printf("Digite o novo nome de usuario: ");
    scanf("%s", usuario->nome);

    printf("Digite a nova senha: ");
    scanf("%s", usuario->senha);

    printf("Usuario atualizado com sucesso!\n");
    salvarUsuarios(); // Salva os dados após editar
}

// Exclui um usuário existente
void excluirUsuario() {
    char nome[MAX_NOME];
    printf("Digite o nome de usuario que deseja excluir: ");
    scanf("%s", nome);

    Usuario *usuario = buscarUsuarioPorNome(nome);
    if (usuario == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    // Remove o usuário da lista
    Usuario *p = usuario;
    for (int i = p - usuarios; i < totalUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1]; // Move os usuários para preencher o espaço
    }
    totalUsuarios--;

    printf("Usuario excluido com sucesso!\n");
    salvarUsuarios(); // Salva os dados após excluir
}

// Busca um usuário pelo nome e retorna um ponteiro para a estrutura
Usuario* buscarUsuarioPorNome(char *nome) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0) {
            return &usuarios[i]; // Retorna o ponteiro para o usuário encontrado
        }
    }
    return NULL; // Usuário não encontrado
}

// Calcula uma operação matemática e armazena no histórico do usuário
void calcular(Usuario *usuario) {
    double num1, num2, resultado;
    char operacao;

    printf("Digite a operacao (+, -, *, /): ");
    scanf(" %c", &operacao);

    printf("Digite o primeiro numero: ");
    scanf("%lf", &num1);

    printf("Digite o segundo numero: ");
    scanf("%lf", &num2);

    switch (operacao) {
        case '+':
            resultado = num1 + num2;
            break;
        case '-':
            resultado = num1 - num2;
            break;
        case '*':
            resultado = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                resultado = num1 / num2;
            } else {
                printf("Erro: Divisao por zero nao permitida.\n");
                return;
            }
            break;
        default:
            printf("Operacao invalida!\n");
            return;
    }

    // Adiciona o cálculo ao histórico do usuário
    if (usuario->total_calculos < MAX_HISTORICO) {
        char entrada[MAX_CALCULO];
        snprintf(entrada, MAX_CALCULO, "%.2lf %c %.2lf = %.2lf", num1, operacao, num2, resultado);
        strcpy(usuario->historico[usuario->total_calculos], entrada);
        usuario->total_calculos++;
    } else {
        printf("Historico cheio, nao e possivel armazenar mais calculos.\n");
    }

    printf("Resultado: %.2lf\n", resultado);
}

// Imprime uma mensagem para o usuário
void falar() {
    printf(":)\n");
}

// Exibe a data e hora atuais
void verDataHora() {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    printf("Data e Hora atuais: %s", asctime(tm_info));
}

// Exibe o histórico de cálculos do usuário
void verHistorico(Usuario *usuario) {
    if (usuario->total_calculos == 0) {
        printf("Nenhum calculo realizado ainda.\n");
    } else {
        printf("\n--- Historico de Calculos ---\n");
        for (int i = 0; i < usuario->total_calculos; i++) {
            printf("%d. %s\n", i + 1, usuario->historico[i]);
        }
    }
}

// Salva os dados dos usuários em um arquivo
void salvarUsuarios() {
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "w");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo para salvar!\n");
        return;
    }

    for (int i = 0; i < totalUsuarios; i++) {
        fprintf(arquivo, "%d %s %s %d\n", usuarios[i].id, usuarios[i].nome, usuarios[i].senha, usuarios[i].total_calculos);
        for (int j = 0; j < usuarios[i].total_calculos; j++) {
            fprintf(arquivo, "%s\n", usuarios[i].historico[j]);
        }
    }

    fclose(arquivo);
}

// Carrega os dados dos usuários a partir de um arquivo
void carregarUsuarios() {
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo para carregar!\n");
        return;
    }

    totalUsuarios = 0;
    while (fscanf(arquivo, "%d %s %s %d", &usuarios[totalUsuarios].id, usuarios[totalUsuarios].nome, usuarios[totalUsuarios].senha, &usuarios[totalUsuarios].total_calculos) != EOF) {
        for (int i = 0; i < usuarios[totalUsuarios].total_calculos; i++) {
            fgets(usuarios[totalUsuarios].historico[i], MAX_CALCULO, arquivo);
            // Remove a quebra de linha do final
            if (usuarios[totalUsuarios].historico[i][strlen(usuarios[totalUsuarios].historico[i]) - 1] == '\n') {
                usuarios[totalUsuarios].historico[i][strlen(usuarios[totalUsuarios].historico[i]) - 1] = '\0';
            }
        }
        totalUsuarios++;
    }

    fclose(arquivo);
}

// Função para exibir o menu após o login e gerenciar as opções
void menuPosLogin(Usuario *usuario) {
    int opcao;
    do {
        printf("\n---BEM VINDO---\n");
        printf("1. Calcular\n");
        printf("2. Falar\n");
        printf("3. Data e Hora\n");
        printf("4. Ver historico de calculos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                calcular(usuario);
                break;
            case 2:
                falar();
                break;
            case 3:
                verDataHora();
                break;
            case 4:
                verHistorico(usuario);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}