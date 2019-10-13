/* listaord.h
 * Definicao do TAD para representar uma lista ordenada implementada
 * de forma encadeada e prototipo das operacoes sobre esse TAD.
 * 
 * Ciro C. Trindade
 * 24/04/2019
 * 
 * Adaptado por Leonardo Amorim e Luis Durante
 * 14/10/2019 
 */


#ifndef _LISTAORD_H
#define _LISTAORD_H
#include <stdbool.h>


typedef char lst_info[21];
typedef struct lst_no * lst_ptr;
struct lst_no {
    lst_info dado;
    lst_ptr prox;
};


/* 
 * Inicializa a lista ordenada 
 */
void lst_init(lst_ptr *);


/* 
 * Insere um novo elemento na lista ordenada 
 */
void lst_ins(lst_ptr *, lst_info);


/* 
 * Remove um elemento da lista ordenada 
 */
bool lst_rem(lst_ptr *, lst_info);


/* 
 * Procura e devolve o ponteiro para o no da lista
 * que contem um valor, ou NULL, caso o valor nao
 * seja localizado 
 */
lst_ptr lst_find(lst_ptr, lst_info);


/* 
 * Imprime os elementos da lista ordenada 
 */
void lst_print(lst_ptr);


/* 
 * Destroi uma lista ordenada 
 */
void lst_kill(lst_ptr *);


#endif

