#ifndef TAD_SET_H
#define TAD_SET_H
#include "TAD_Ast.h"


void set_insertar(Tdata*, Tdata);

int set_comparar(Tdata, Tdata);

int set_pertenece(Tdata, Tdata);

void set_mostrar(Tdata);

void set_eliminar(Tdata*, Tdata);
	
int set_subconjunto(Tdata, Tdata);

int set_iguales(Tdata, Tdata);

Tdata set_union(Tdata, Tdata);

Tdata set_interseccion(Tdata, Tdata);

Tdata set_diferencia(Tdata, Tdata);

Tdata set_producto(Tdata, Tdata);

Tdata set_copy(Tdata);


#endif
