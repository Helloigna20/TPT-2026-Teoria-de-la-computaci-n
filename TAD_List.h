#ifndef TAD_LIST_H
#define TAD_LIST_H
#include "TAD_Ast.h"


void list_insertar(Tdata* list, Tdata elem);

int list_tam(Tdata list);

int list_pertenece(Tdata, Tdata);

void list_mostrar(Tdata);

//Copia Profunda.
Tdata list_copy(Tdata list);

//Une(concatena) dos listas. 
Tdata list_concat(Tdata l1, Tdata l2);

//Busca un elemento en la lista.
int list_search(Tdata list, Tdata elem);

#endif
