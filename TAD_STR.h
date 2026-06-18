#ifndef CADENA_H
#define CADENA_H
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
	char caracter;
	struct nodo *sig;
}t_nodoStr;

typedef t_nodoStr * str;

str cadena_crear();
void cadena_agregar_caracter(str*, char);
str load2(const char*);
str cadena_cargar_consola();
void cadena_eliminar_vocales(str*);
void cadena_imprimir(str);
void cadena_destruir(str*);
int cadena_comparar(str, str);
str cadena_concatenar(str, str);
str cadena_copy(str);

#endif
