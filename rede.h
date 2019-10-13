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


#define DEFAULT_FILENAME "rede.txt"


/*
 */
void load_users(avl_tree * t, char * filename);


/*
 */
void list_users(avl_tree t);


/*
 */
avl_tree search_username(avl_tree t, char * usuario);


/*
 */
void list_friends(avl_tree t, char * username);


/*
 */
bool add_friend(avl_tree t, char * username, char * friendname);


/*
 */
bool remove_user(avl_tree * t, char * username);


/*
 */
void remove_friend_from_all(avl_tree t, char * username);


/*
 */
bool add_new_user(avl_tree * t, avl_info x);


/*
 */
void save_users(avl_tree t);


#endif

