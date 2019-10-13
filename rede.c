/* avl.c
 * Implementacao de uma rede social baseada em arvores AVL.
 * 
 * Leonardo Amorim e Luis Durante
 * 14/10/2019
 */


#include "rede.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void load_users(avl_tree * t, char * filename){
    FILE * arq;

    avl_info user;

    int lin = 1;
    int linha = 1;
    int k = 0;
    int i = 0;

    char * token;
    char info[1000];
    char users[1000][1000];
    char friends[1000][1000];

    if ((arq = fopen(filename, "r")) == NULL) {
        fprintf(stderr,"Erro na abertura do arquivo %s\n", filename);
        exit(1);
    }

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
        else {
            info[strlen(info)-1] = '\0';
            int j = 0;
            for (j = 0; j < strlen(info); j++)
            {
                if(info[j] == '\n' || info[j] == '\r'){
                    info[j] = '\0';
                }
            }

            strcpy(friends[i], info);
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


void list_users(avl_tree t) {
    if (t != NULL) {
        list_users(t->esq);
        printf("Usuario: %s\n", t->dado.usuario);
        printf("Nome Completo: %s\n", t->dado.nome_completo);
        printf("Sexo: %c\n\n", t->dado.sexo);
        list_users(t->dir);
    }
}


avl_tree search_username(avl_tree t, char * username) {
    if (t == NULL) {
        return NULL;
    }

    int comparacao = strcmp(t->dado.usuario, username);
    if (comparacao == 0) {
        return t;
    } else if(comparacao > 0){
        return search_username(t->esq, username);
    } else {
        return search_username(t->dir, username);
    }
}


void list_friends(avl_tree t, char * username) {
    if(t == NULL){
        printf("\nUsuario nao encontrado.\n\n");
        return;
    } else {
        avl_tree user = search_username(t, username);
        if (user != NULL) {
            lst_print(user->dado.amigos);
        } else {
            printf("\nUsuario nao encontrado.\n\n");
        }
    }
}


bool add_friend(avl_tree t, char * username, char * friendname) {
    avl_tree usuario_A = search_username(t, username);
    avl_tree usuario_B = search_username(t, friendname);

    if(usuario_A == NULL || usuario_B == NULL) {
        return false;
    }

    lst_ins(&(usuario_A)->dado.amigos, friendname);
    return true; 
}


bool remove_user(avl_tree * t, char * username) {
    avl_tree usuario = search_username(*(t), username);
    bool * h;

    if(usuario == NULL) {
        return false;
    }

    delete(t, username, h);
    remove_friend_from_all(*(t), username);
    return true;
}


void remove_friend_from_all(avl_tree t, char * username) {
    if (t != NULL) {
        lst_rem(&(t)->dado.amigos, username);
        remove_friend_from_all(t->esq, username);
        remove_friend_from_all(t->dir, username);
    }
}


bool add_new_user(avl_tree * t, avl_info x) {
    if ((*t) == NULL) {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        strcpy((*t)->dado.usuario,x.usuario);
        (*t)->dado.sexo = x.sexo;
        strcpy((*t)->dado.nome_completo,x.nome_completo);
        strcpy((*t)->dado.usuario,x.usuario);
        lst_init(&(*t)->dado.amigos);
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    }
    else if (strcmp(x.usuario,(*t)->dado.usuario) < 0) {
        add_new_user(&(*t)->esq, x);
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                        break;
                case 0: (*t)->bal = -1;
                        break;
                case -1:
                    
                    if ((*t)->esq->bal == -1) {
                        rotacao_dir(t);
                        (*t)->dir->bal = 0;
                    }
                    else {
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);
                        
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    (*t)->bal = 0;
                    break;
            }
    }
    else if (strcmp(x.usuario,(*t)->dado.usuario) > 0) {
        add_new_user(&(*t)->dir, x);
        switch ((*t)->bal) {
            case -1: (*t)->bal = 0;
                        break;
            case 0 : (*t)->bal = 1;
                        break;
            case 1:
                if ((*t)->dir->bal == 1) {
                    rotacao_esq(t);
                    
                    (*t)->esq->bal = 0;
                }
                else {
                    rotacao_dir(&(*t)->dir);
                    rotacao_esq(t);
                    
                    if ((*t)->bal == 1) (*t)->esq->bal = -1;
                    else (*t)->esq->bal = 0;
                    if ((*t)->bal == -1) (*t)->dir->bal = 1;
                    else (*t)->dir->bal = 0;
                } 
                (*t)->bal = 0;
                break;
        }
    } else if(strcmp(x.usuario, (*t)->dado.usuario) == 0) {
        return false;
    }

    return true;
}


void save_users(avl_tree t) {

}

