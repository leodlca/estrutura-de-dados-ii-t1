/* rede.h
 * Modelagem de uma rede social baseada em arvores AVL.
 *
 * Leonardo Amorim e Luis Durante
 * 14/10/2019
 */


#ifndef _REDE_H
#define _REDE_H


#include <stdbool.h>
#include "avl.h"
#include "listaord.h"


char filename[31];


/*
 * Carrega configuracao de uma rede social que fora salva
 * no arquivo (filename), num formato especifico.
 */
void load_users(avl_tree * t, char * filename);


/* 
 * Exibe uma listagem em ordem alfabetica de todos os atributos 
 * dos usuarios cadastrados na rede social.
 */
void list_users(avl_tree t);


/*
 * Exibe uma listagem dos amigos de um determinado usuario definido
 * por (username).
 */
void list_friends(avl_tree t, char * username);


/*
 * Adiciona um usuario (friendname) na lista de amigos de um
 * outro usuario (username). Retorna verdadeiro caso bem sucedido,
 * falso caso contrario.
 */
bool add_friend(avl_tree t, char * username, char * friendname);


/*
 * Remove um usuario (username) da rede social. Retorna 
 * verdadeiro caso bem sucedido, falso caso contrario.
 */
bool remove_user(avl_tree * t, char * username);


/*
 * Remove um usuario (username) da lista de amigo de todos os
 * usuarios da rede social.
 */
void remove_friend_from_all(avl_tree t, char * username);


/*
 * Adiciona um novo usuario na rede social. Retorna verdadeiro
 * caso bem sucedido, falso caso contrario.
 */
bool add_new_user(avl_tree * t, avl_info x);


/*
 * Salva a configuracao da rede social num determinado arquivo
 * de texto.
 */
void save_users(avl_tree t);


#endif

