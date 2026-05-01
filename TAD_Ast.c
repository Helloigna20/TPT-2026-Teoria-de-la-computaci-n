#include "TAD_Ast.h"
#include "TAD_Set.h"
#include "TAD_List.h"

Tdata create_str_lis(str cadena){ //TOP SECRET uwu
	
	Tdata nodo= (Tdata)malloc(sizeof(dataType));
	nodo->nodeType= STR;
	nodo->strData= cadena;
	return nodo;
}

/*-----------------------------------------------------------------------------------------*/

// <<-- Sobre TD STR -->> //

Tdata create_str_cad(const char* texto){
	
	Tdata nodo = (Tdata)malloc(sizeof(dataType));
	nodo->nodeType = STR;
	nodo->strData = load2(texto);
	return nodo;
}


Tdata create_str(){
	Tdata nodo = (Tdata)malloc(sizeof(dataType));
	nodo->nodeType = STR;
	nodo->strData = NULL;
	return nodo;
}
	

void carge_str_cad(Tdata* nodo, const char* texto){
	(*nodo)->strData= load2(texto);
}
	
	
int compare_str(Tdata nodo1, Tdata nodo2){
	
	if(nodo1->nodeType != STR || nodo2->nodeType!= STR){
		return -2;
	}else{
		return cadena_comparar(nodo1->strData, nodo2->strData);
	}
}

Tdata concat_str(Tdata nodo1, Tdata nodo2){
	
	if(nodo1==NULL || nodo2==NULL){
		printf("\nError. Los nodos son nulos...");
		return NULL;
	}
	else{
		if(nodo1->nodeType != STR || nodo2->nodeType!= STR){
			printf("\nError.Los nodos no son del mismo tipo...");
			return NULL;
		}
		
		str nueva_cadena= cadena_concatenar(nodo1->strData, nodo2->strData);
		
		Tdata nuevo_nodo_ast= create_str_lis(nueva_cadena);
		
		return nuevo_nodo_ast;
	}
}

	
void print_str(Tdata nodo){
	
	if(nodo!= NULL && nodo->nodeType ==STR){
		cadena_imprimir(nodo->strData);
	}
	else{
		printf("\nError. El nodo es nulo\n");
	}
}

// <<-- Sobre TD SET -->> //

Tdata create_set(){
	Tdata nodo = (Tdata)malloc(sizeof( dataType));
	nodo->nodeType = SET;
	nodo->data = NULL;
	nodo->next = NULL;
	return nodo;
}
	
void insert_set(Tdata* set, Tdata elem){
	set_insertar(set, elem);
}
	

int belongs(Tdata set, Tdata elem){
	if(set!=NULL){
		return set_pertenece(set, elem);
	}
	else{
		printf("\nError: El conjunto esta vacio");
		return -2;
	}
	
}
	
void print_set(Tdata set){
	set_mostrar(set);
}
	

void remove_set(Tdata* set, Tdata elem){
	set_eliminar(set, elem);
}
	


// ** Operaciones algebraicas sobre dos conjuntos **
	
Tdata union_set(Tdata set1, Tdata set2){
	return set_union(set1, set2);
}


Tdata intersection_set(Tdata set1, Tdata set2){
	return set_interseccion(set1, set2);
}


Tdata difference_set(Tdata set1, Tdata set2){
	return set_diferencia(set1, set2);
}


int subset(Tdata set1, Tdata set2){
	return set_subconjunto(set1, set2);
}
	

int equals_set(Tdata set1, Tdata set2){
	return set_comparar(set1, set2);
}


Tdata product_cartesiano(Tdata set1, Tdata set2){
	
}



// <<-- Sobre TD LIST -->> //
Tdata create_list(){
	Tdata nodo = (Tdata)malloc(sizeof( dataType));
	nodo->nodeType = LIST;
	nodo->data = NULL;
	nodo->next = NULL;
	return nodo;
}

void append(Tdata* list, Tdata elem){
	append(list, elem);
}
	
int length(Tdata list){
	return list_tam(list);
}
	
Tdata copy_list(Tdata list){
	list_copy(list);
}
	
Tdata concat(Tdata list1, Tdata list2){
	
}
	
int search(Tdata list, Tdata elem){
	return list_pertenece(list, elem);
}

void print_list(Tdata list){
	lista_mostrar(list);
}
	

	
// <<-- GENERICOS -->> //

Tdata clone(Tdata nodo){

	if(nodo == NULL){
		return NULL;
	}
	
	Tdata nuevo= NULL;
	
	switch(nodo->nodeType){
	case STR:{
		str nueva_cad= cadena_copy(nodo->strData);
		nuevo= create_str_lis(nueva_cad);
		break;
	}	
	case SET:
		nuevo= set_copy(nodo);
		//ya es avaricia >_< FFF
		break;
		
	case LIST:
		nuevo= copy_list(nodo);
		//este tambien FFFefe
		break;
	}
	return nuevo;
}

	
int compara_generico(Tdata nodo1, Tdata nodo2){
	int op;
	
	if(nodo1==NULL && nodo2== NULL){
		return 0;
	}
	else{
		if(nodo1==NULL || nodo2==NULL){
			return -1;
		}
		else{
			if(nodo1->nodeType != nodo2->nodeType){
				return -2;
			}
			switch(nodo1->nodeType){
			case STR:
				op= compare_str(nodo1, nodo2);
				break;
				
			case SET:
				op= set_comparar(nodo1, nodo2);
				break;
				
			case LIST:
				//no llegamos F
				break;
			}
		}
		
		return op;
	}
}
	
// este es solo cuando ya cargaste elementos en un conjunto o lista
// poke antes de eso no sabe de que tipo es lo que va a mostrar
// habria que ver otra forma de insertar_set para que en el main podamos hacer mostrar_genrico(A);
// poke si A= NULL y llamamos a mostrar_generico(A), no muestra nada.
// nos dimos cuenta tarde asi que lo dejamos asi nomas...
	

void mostrar_generico(Tdata nodo){
	if(nodo==NULL){
		return;
	}
	switch(nodo->nodeType){
	case STR:
		print_str(nodo);
		break;
		
	case SET:
		print_set(nodo);
		break;
		
	case LIST:
		print_list(nodo);
		break;
	}
}	
	
void eliminar_generico(Tdata nodo){
	
	if(nodo==NULL){
		return;
	}
	switch(nodo->nodeType){
	case STR:
		cadena_destruir(&(nodo->strData));
		break;
		
	case SET:
		break;
		
	case LIST:
		
		break;
	}
	
	free(nodo);
	nodo=NULL;

}

