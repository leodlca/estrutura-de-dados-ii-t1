rede: main.o avl.o listaord.o
	gcc -o rede main.o avl.o listaord.o -g
	
avl.o: avl.c avl.h
	gcc -c avl.c -g 

listaord.o: listaord.c listaord.h
	gcc -c listaord.c -g
	
main.o: main.c avl.h listaord.h
	gcc -c main.c -g
