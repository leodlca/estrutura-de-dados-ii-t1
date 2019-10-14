/* main.c
 * Interface e arquivo principal do projeto Rede Social de EDII.
 *
 * Leonardo Amorim e Luis Durante
 * 14/10/2019
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "rede.h"


void wait_and_clear() {
    printf("Pressione qualquer tecla para continuar... ");
    getchar();
    getchar();
    system("cls || clear");
}


int main() {
    int escolha = 0;

    avl_tree t = NULL;
    avl_info usuario_A;
    avl_info usuario_B;

    char username[21];
    char friendname[21];
    char deseja_continuar = 'N';

    system("cls || clear");

    while (escolha != 7) {
        strcpy(username, "");
        strcpy(friendname, "");

        printf("Rede Social\n\n");
        printf("1 - Carregar usuarios\n");
        printf("2 - Adicionar um novo usuario\n");
        printf("3 - Adicionar um amigo\n");
        printf("4 - Listar usuarios\n");
        printf("5 - Listar amigos\n");
        printf("6 - Remover usuario\n");
        printf("7 - Finalizar o programa (e salvar rede)\n\n");
        printf("Insira sua escolha: ");
        scanf("%d", &escolha);

        system("cls || clear");

        switch (escolha) {
            case 1:
                printf("Insira o caminho completo e nome do arquivo: ");
                scanf(" %31[^\n]", filename);

                load_users(&t, filename);

                printf("\nInformacoes carregadas com sucesso!\n\n");
                wait_and_clear();

                break;

            case 2:
                printf("Insira o nome de usuario: ");
                scanf(" %21[^\n]", usuario_A.usuario);

                printf("Insira o nome completo: ");
                scanf(" %51[^\n]", usuario_A.nome_completo);

                printf("Insira o sexo (M/F): ");
                scanf(" %c[^\n]", &usuario_A.sexo);

                if (add_new_user(&t, usuario_A)) {
                    printf("\nUsuario inserido com sucesso!\n\n");
                } else {
                    printf("\nOcorreu um erro durante a insercao do novo usuario.\n\n");
                }
                wait_and_clear();

                break;

            case 3:
                printf("Adicionando o usuario A a lista de amigos do usuario B\n\n");

                printf("Insira o nome de usuario do usuario A: ");
                scanf(" %21[^\n]", usuario_A.usuario);

                printf("Insira o nome de usuario do usuario B: ");
                scanf(" %21[^\n]", usuario_B.usuario);

                if(strcmp(usuario_A.usuario, usuario_B.usuario) == 0){
                    printf("\nUm usuario nao pode adicionar a si mesmo.\n\n");
                } else if (add_friend(t, usuario_A.usuario, usuario_B.usuario)) {
                    printf("\nAmigo inserido com sucesso!\n\n");
                } else {
                    printf("\nOcorreu um erro ao tentar inserir um amigo no usuario informado.\n\n");
                }
                wait_and_clear();

                break;

            case 4:
                printf("Lista de usuarios:\n\n");
                list_users(t);
                wait_and_clear();

                break;

            case 5:
                printf("Insira o nome de usuario: ");
                scanf(" %21[^\n]", username);

                list_friends(t, username);
                wait_and_clear();

                break;

            case 6:
                printf("Insira o nome de usuario: ");
                scanf(" %21[^\n]", username);

                if (remove_user(&t, username)) {
                    printf("\nUsuario removido com sucesso!\n\n");
                } else {
                    printf("\nOcorreu um erro ao tentar remover o usuario informado.\n\n");
                }
                wait_and_clear();

                break;

            case 7:
                if(strcmp(filename, "") == 0) {
                    printf("Nenhum arquivo foi informado na opcao 1, encerrando programa sem salvar.\n\n");
                    wait_and_clear();
                } else {
                    printf("As configuracoes da rede serao guardadas no arquivo %s.\n", filename);
                    printf("Quaisquer dados contidos no arquivo serao sobrescritos. Deseja continuar? (S/N) ");
                    scanf(" %c[^\n]", &deseja_continuar);

                    if(deseja_continuar == 'S' || deseja_continuar == 's') {
                        save_users(t);
                        printf("\nConfiguracoes armazenadas com sucesso!\n\n");
                        wait_and_clear();
                    }
                }

                exit(1);

                break;

            default:
                printf("Opcao invalida!\n\n");
                wait_and_clear();
        }
    }
    return 0;
}