#ifndef TAD_AUTOMATA_H
#define TAD_AUTOMATA_H
#include "TAD_Ast.h"

typedef struct{
	Tdata from;
	
	Tdata symbol;
	
	Tdata destinations;
} DeltaEntry;


typedef struct{
	Tdata Q;
	
	Tdata Sigma;
	
	DeltaEntry* delta;
	
	int deltaCount;
	
	Tdata q0;
	
	Tdata F;
} Automata;


Automata crear_automata();
void agregar_estado(Automata*, Tdata);
void agregar_transicion(Automata*, Tdata, Tdata, Tdata);
void destruir_automata(Automata*);
int buscar(Automata*, Tdata, Tdata);

#endif
