#include "TAD_Automata.h"
#include "TAD_Ast.h"

Automata crear_automata(){
	Automata aux;
	
	aux.Q= create_set();
	aux.Sigma= create_set();
	aux.delta= NULL;
	aux.deltaCount= 0;
	aux.q0= NULL;
	aux.F= create_set();
	
	return aux;
}
	

void agregar_estado(Automata*automata, Tdata estado){
	if(automata!=NULL && estado!=NULL){
		insert_set(&(automata->Q), estado);
	}
}
	

void agregar_transicion(Automata* automata, Tdata origen, Tdata simbolo, Tdata destino){
	if(automata!=NULL && origen!=NULL && simbolo!=NULL && destino!=NULL){
		
		int pos= buscar(automata, origen, simbolo);
		
		if(pos!=-1){
			insert_set(&(automata->delta[pos].destinations), destino);
		}
		else{
			int nuevo_tam= automata->deltaCount+1;
			
			if(automata->deltaCount==0){
				automata->delta= (DeltaEntry*) malloc (nuevo_tam * sizeof(DeltaEntry));
			}
			else{
				automata->delta= (DeltaEntry*) realloc (automata->delta,nuevo_tam * sizeof(DeltaEntry));
			}
			
			int indice= automata->deltaCount;
			
			automata->delta[indice].from= origen;
			automata->delta[indice].symbol= simbolo;
			automata->delta[indice].destinations= create_set();
			insert_set(&(automata->delta[indice].destinations), destino);
			
			automata->deltaCount++;
		}
		
	}
	
	return;
}
	
	
int buscar(Automata *automata, Tdata estado, Tdata simbolo){
	int i=0;
	
	while(i<automata->deltaCount){
		if(compara_generico(automata->delta[i].from, estado) && compara_generico(automata->delta[i].symbol, simbolo)){
			return i;
		}
		i++;
	}
	return -1;
}


void destruir_automata(Automata* automata){
	
}
