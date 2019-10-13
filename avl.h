/* avl.h
 * Definicao do TAD para representar uma arvore AVL e prototipo
 * de suas operacoes.
 *
 * Ciro C. Trindade
 * 30/09/2019
 * 
 * Adaptado por Leonardo Amorim e Luis Durante
 * 14/10/2019 
 */


#ifndef _AVL_H
#define _AVL_H


#include <stdbool.h>
#include "listaord.h"

/*
 * Definicao da estrutura de dados
 */
typedef struct {
    char usuario[21];
    char nome_completo[51];
    char sexo;  
    lst_ptr amigos;
} avl_info;


typedef struct avl_no * avl_tree;


struct avl_no {
    avl_info dado;
    avl_tree esq;
    avl_tree dir;
    int bal; // balanceamento do no
};


/* 
 * Faz uma rotacao para a direita na arvore AVL t. 
 */
void rotacao_dir(avl_tree * t);


/*
 * Faz uma rotacao para a esquerda na arvore AVL t.
 */
void rotacao_esq(avl_tree *);


/*
 * Se a palavra x esta contida na arvore AVL t, x e
 * removida de t, h sinaliza uma diminuicao da altura
 * de t e a funcao devolve verdadeiro; caso contrario,
 * nada e feito e a funcao devolve falso.
 */
bool delete(avl_tree * t, char * x, bool * h);


/*
 * Faz o balanceamento da arvore AVL t apos uma remocao 
 * em sua subarvore esquerda e sinaliza se houve uma 
 * dimuicao da altura dessa subarvore atraves de h.
 */
void balance_esq(avl_tree * t, bool * h);


/*
 * Faz o balanceamento da arvore AVL t apos uma remocao 
 * em sua subarvore direita e sinaliza se houve uma 
 * dimuicao da altura dessa subarvore atraves de h.
 */
void balance_dir(avl_tree *, bool *);


/*
 * Devolve um ponteiro para o no que contem o menor
 * valor na arvore AVL t e sinaliza atraves de h se 
 * houve uma diminuicao da altura de t.
 */
avl_tree get_min(avl_tree * t, bool * h);


#endif
