/* avl.c
 * Implementacao das operacoes realizadas sobre o TAD que r
 * representa uma arvore AVL.
 *
 * Ciro C. Trindade
 * 30/Set/2019
 */
 
 
#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void list_users(avl_tree t) {
    if (t != NULL) {
        list_users(t->esq);
        printf("Usuario: %s\n", t->dado.usuario);
        printf("Nome Completo: %s\n", t->dado.nome_completo);
        printf("Sexo: %c\n\n", t->dado.sexo);
        list_users(t->dir);
    }
}


void list_friends(avl_tree t, char * username) {
    if(t == NULL){
        printf("Usuario nao encontrado\n");
        return;
    }
    avl_tree user = search_username(t, username);
    if (user != NULL)
    {
        lst_print(user->dado.amigos);
        return;
    }
    printf("Usuario nao encontrado\n");
    
    
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


bool add_friend(avl_tree t, char * username, char * friendname) {
    avl_tree userA = search_username(t, username);
    avl_tree userB = search_username(t, friendname);

    if(userA == NULL || userB == NULL) 
        return false;

    lst_ins(&(userA)->dado.amigos, friendname);
    return true; 
}


// Rotacao para a esquerda
void rotacao_esq(avl_tree * t) {
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}


// Rotacao para a direita
void rotacao_dir(avl_tree * t) {
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}


bool delete(avl_tree * t, char * x, bool * h) {
    avl_tree p;
    bool result;
    if (*t == NULL) // A chave nao se encontra na arvore
        return false;
    else if (strcasecmp(x,(*t)->dado.usuario) == 0) { // a chave esta neste no
        p = *t;
        if ((*t)->esq == NULL) { // no folha ou somente com subarvore direita
            *t = p->dir;
            *h = true;
        }
        else if ((*t)->dir == NULL) { // no com uma unica subarvore esquerda
            *t = p->esq;
            *h = true;
        }
        else { // no com duas subavores
            p = get_min(&(*t)->dir, h);
            (*t)->dado = p->dado;
            if(*h) balance_dir(t, h);
        }
        free(p);
        return true;
    }
    else if (strcasecmp(x,(*t)->dado.usuario) < 0) {
        result = delete(&(*t)->esq, x, h);
        if (*h) balance_esq(t, h);
        return result;
    }
    else {
        result = delete(&(*t)->dir, x, h);
        if (*h) balance_dir(t, h);
        return result;
    }
} // fim do delete


void balance_dir(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case 1: (*t)->bal = 0;
                break;
        case 0: (*t)->bal = -1;
                *h = false;
                break;
        case -1: // rebalanceamento
                p1 = (*t)->esq;
                b1 = p1->bal;
                if (b1 <= 0) { // rotacao simples
                    (*t)->esq = p1->dir;
                    p1->dir = *t;
                    if (b1 == 0) {
                        (*t)->bal = -1;
                        p1->bal = 1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotacao dupla
                    p2 = p1->dir;
                    b2 = p2->bal;
                    p1->dir = p2->esq;
                    p2->esq = p1;
                    p1->esq = p2->dir;
                    p2->dir = *t;
                    if(b2 == -1) (*t)->bal = 1;
                    else (*t)->bal = 0;
                    if(b2 == 1) p1->bal = -1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}


void balance_esq(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1: (*t)->bal = 0;
                 break;
        case 0: (*t)->bal = 1;
                *h = false;
                break;
        case 1: // rebalanceamento
                p1 = (*t)->dir;
                b1 = p1->bal;
                if (b1 >= 0) { // rotacao simples
                    (*t)->dir = p1->esq;
                    p1->esq = *t;
                    if (b1 == 0) {
                        (*t)->bal = 1;
                        p1->bal = -1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotacao dupla
                    p2 = p1->esq;
                    b2 = p2->bal;
                    p1->esq = p2->dir;
                    p2->dir = p1;
                    p1->dir = p2->esq;
                    p2->esq = *t;
                    if (b2 == 1) (*t)->bal = -1;
                    else (*t)->bal = 0;
                    if (b2 == -1) p1->bal = 1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}


avl_tree get_min(avl_tree * t, bool * h) {
    avl_tree q;
    if ((*t)->esq != NULL) {
        q = get_min(&((*t)->esq),h);
        if (*h) balance_esq(t, h);
        return q;
    }
    else {
        *h = true;
        q = *t;
        *t = (*t)->dir;
        return q;
    }
}


int profundidade(avl_tree t)
{
	if (t->esq == NULL && t->dir == NULL) {
		return 0;	
	}
	int e = 0, d = 0;
	if (t->esq != NULL) {
		e = profundidade(t->esq);
	}
	if (t->dir != NULL) {
		d = profundidade(t->dir);
	}
	return 1 + (e > d ? e : d);
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
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) < 0) { // Inserir a esquerda
        add_new_user(&(*t)->esq, x);
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                        break;
                case 0: (*t)->bal = -1;
                        break;
                case -1:
                    // Rebalanceamento
                    if ((*t)->esq->bal == -1) { //Rotacao simples p/ direita
                        rotacao_dir(t);
                        (*t)->dir->bal = 0; //Ajusta o fator de balanceamento
                    }
                    else { // Rotacao dupla para direita
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    (*t)->bal = 0;
                    break;
            } // fim do switch
    } // fim do if
    else if (strcasecmp(x.usuario,(*t)->dado.usuario) > 0) { // Inserir a direita
        add_new_user(&(*t)->dir, x);
        switch ((*t)->bal) {
            case -1: (*t)->bal = 0;
                        break;
            case 0 : (*t)->bal = 1;
                        break;
            case 1: // Rebalanceamento
                if ((*t)->dir->bal == 1) { // Rotacao simples p/ esquerda
                    rotacao_esq(t);
                    // Ajusta o fator de balanceamento
                    (*t)->esq->bal = 0;
                }
                else { // Rotacao dupla para esquerda
                    rotacao_dir(&(*t)->dir);
                    rotacao_esq(t);
                    // Ajusta o fator de balanceamento
                    if ((*t)->bal == 1) (*t)->esq->bal = -1;
                    else (*t)->esq->bal = 0;
                    if ((*t)->bal == -1) (*t)->dir->bal = 1;
                    else (*t)->dir->bal = 0;
                } // fim do else
                (*t)->bal = 0;
                break;
        } // fim do switch
    } else if(strcasecmp(x.usuario, (*t)->dado.usuario) == 0) {
        return false;
    }

    return true;
} // fim de add_new_user

