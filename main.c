#include <stdio.h>
#include "usuarios.h"

int main() {
    int opcao;
    carregarUsuarios(); // Carrega os dados ao iniciar o programa

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar\n");
        printf("2. Login\n");
        printf("3. Listar usuarios\n");
        printf("4. Editar usuario\n");
        printf("5. Excluir usuario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                {
                    Usuario *usuario = login();
                    if (usuario != NULL) {
                        menuPosLogin(usuario);
                    }
                }
                break;
            case 3:
                listarUsuarios();
                break;
            case 4:
                editarUsuario();
                break;
            case 5:
                excluirUsuario();
                break;
            case 0:
                printf("Saindo...\n");
                salvarUsuarios(); // Salva os dados ao sair
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}