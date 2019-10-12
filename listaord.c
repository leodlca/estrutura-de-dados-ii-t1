/* listaord.c
 * Implementacao das operacoes sobre o TAD lista ordenada.
 * 24/04/2019
 */

#include "listaord.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lst_init(lst_ptr * l)
{
    printf("Criando a lista de amigos");
    *l = NULL;
}

void lst_ins(lst_ptr * l, lst_info val) 
{
    lst_ptr n;
    if ((n = (lst_ptr) malloc(sizeof(struct lst_no))) == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria!\n");
        exit(1);
    }
    strcpy(n->dado, val);
    if (*l == NULL || strcmp(val, (*l)->dado) <= 0) {
       n->prox = *l;
       *l = n;
    }
    else {
        lst_ptr p = *l;
        while (p->prox != NULL && strcmp(val, p->prox->dado) > 0) {
            p = p->prox;
        }
        n->prox = p->prox;
        p->prox = n;
    }
}

bool lst_rem(lst_ptr * l, lst_info x) 
{
    if (*l == NULL || x < (*l)->dado) {
        return false;
    }
    else {
        lst_ptr p = *l;
        if (x == (*l)->dado) {
            *l = p->prox;
            free(p);
            return true;
        }
        else {
            while (p->prox != NULL && x > p->prox->dado) {
                p = p->prox;
            }
            if (p->prox != NULL && x == p->prox->dado) {
                lst_ptr n = p->prox;
                p->prox = n->prox;
                free(n);
                return true;
            }
        }
        return false;
    }
}

lst_ptr lst_find(lst_ptr l, lst_info x) 
{
    while (l != NULL && x > l->dado) {
        l = l->prox;
    }
    if (l != NULL && x == l->dado) {
        return l;
    }
    return NULL;
}

void lst_print(lst_ptr l) 
{
    printf("[ ");
    while (l != NULL) {
        printf("%s,", l->dado);
        l = l->prox;
    }
    printf("\b ]\n");
}

void lst_kill(lst_ptr * l)
{
	lst_ptr p;
	while (*l != NULL) {
		p = *l;
		*l = (*l)->prox;
		free(p);
	}
}
