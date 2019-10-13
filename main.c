#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include "avl.h"

//bool add_friend(avl_tree t, char * username, char * friendname);
void wait_and_clear() {
    printf("Pressione qualquer tecla para continuar...");
    getchar();
    getchar();
}

void limpa_avl_info(avl_info * x) {
    strcpy(x->usuario, "");
    strcpy(x->nome_completo, "");
    x->sexo = ' ';
}

void load_users(avl_tree * t, char * filename){
    FILE * arq; // Arquivo l�gico
    avl_info user;
    int lin = 1;
    int linha = 1;
    char info[1000];
    char * token;
    char users[1000][1000];
    int k = 0;
    char friends[1000][1000];
    if ((arq = fopen(filename, "r")) == NULL) {
        fprintf(stderr,"Erro na abertura do arquivo %s\n", filename);
        exit(1);
    }
    int i = 0;

    while (fgets(info, 1000, arq)) {
        if (linha % 2 != 0){
            token = strtok(info, ";");
            while (token != NULL) {
                if (lin == 1) strcpy(user.usuario,token);
                else if(lin == 2) strcpy(user.nome_completo,token);
                else user.sexo = token[0];
                lin++;
                token = strtok(NULL, ";");
            }
            if(lin < 3){
                printf("Erro\n");
                exit(1);
            }
            if(!add_new_user(t, user)){
                printf("Erro!\n\n");
                exit(1);
            }
            strcpy(users[k],user.usuario);
            k++;
        } 
        else{
            // info[strlen(info-1)] = '\0';
            int j = 0;
            for (j = 0; j < strlen(info); j++)
            {
                if(info[j] == '\n'){
                    info[j] = '\0';
                }
            }
            
            printf("%s.", info);
            strcpy(friends[i],info);
            i++;
        }
        lin = 1;
        linha++;
    }

    for (i = 0; i < k; i++){
        token = strtok(friends[i], ";");
        while (token != NULL) {
           if(!add_friend(*t, users[i], token)) {
                printf("\nErro\n\n");
            }
            token = strtok(NULL, ";");
        }
    }
    
    fclose(arq);
}

int main() {
    int escolha = 1;
    avl_tree t = NULL;
    avl_info usuario_A;
    avl_info usuario_B;
    char username[21];
    char friendname[21];

    while(escolha != 0) {
        strcpy(username, "");
        strcpy(friendname, "");

        //limpa_avl_info(&usuario_A);
        //limpa_avl_info(&usuario_B);

        // system("cls || clear");
        printf("=========================================\n");
        printf("Rede Social\n\n");
        printf("0 - Encerrar programa\n"); //feito
        printf("1 - Carregar usuarios\n");
        printf("2 - Adicionar novo usuario\n"); //feito
        printf("3 - Adicionar um amigo\n"); //feito?
        printf("4 - Listar usuarios\n"); //feito
        printf("5 - Listar amigos\n");
        printf("6 - Remover usuario\n");
        printf("7 - Salvar usuarios\n\n");
        printf("Insira sua escolha: ");
        scanf("%d", &escolha);

        system("cls || clear");

        switch(escolha) {
            case 0:
                return 1;

            case 1:
                load_users(&t, "users.txt");
                break;

            case 2:
                printf("Insira o nome de usuario: ");
                scanf(" %21[^\n]", usuario_A.usuario);

                printf("Insira o nome completo: ");
                scanf(" %51[^\n]", usuario_A.nome_completo);

                printf("Insira o sexo (M/F): ");
                scanf(" %c", &usuario_A.sexo);

                if(add_new_user(&t, usuario_A)){
                    printf("\nUsuario inserido com sucesso!\n\n");  
                } else {
                    printf("\nErro\n\n");
                }
                wait_and_clear();

                break;

            case 3:
                printf("Adicionando o usuario A a lista de usuarios do usuario B\n\n");

                printf("Insira o nome de usuario do usuario A: ");
                scanf(" %21[^\n]", usuario_A.usuario);

                printf("Insira o nome de usuario do usuario B: ");
                scanf(" %21[^\n]", usuario_B.usuario);

                if(add_friend(t, usuario_A.usuario, usuario_B.usuario)) {
                    printf("\nAmigo inserido com sucesso!\n\n");
                } else {
                    printf("\nErro");
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
                char user[21];
                scanf(" %21[^\n]", user);

                list_friends(t, user);
                wait_and_clear();
                break;
        }   
    }
    return 0;
}



// bool add_friend(avl_tree t, char * username, char * friendname) {
//     if(t != NULL) {
//         return false;
//     } else {
//          if (strcasecmp(username,t->dado.usuario) > 0) { // Inserir a direita
//             add_friend(t->dir, username, friendname);
//          }
//          else if (strcasecmp(username,t->dado.usuario) < 0) { // Inserir a direita
//             add_friend(t->esq, username, friendname);
//          } else {
//              printf("\nAmigo adicionado com sucesso!\n");
//              lst_ins(t->dado.amigos, friendname);
//              return true;
//          }
//     }
//     return false;
// }

