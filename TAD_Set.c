#include "TAD_Set.h"


void set_insertar(Tdata* conjunto, Tdata elem){
	
	if(elem!=NULL){
		
		Tdata nuevo= create_set();
		nuevo->data= clone(elem);
		
		if(*conjunto == NULL){
			*conjunto= nuevo;
		}
		else{
			if(set_pertenece(*conjunto, elem)==0){
				Tdata aux= *conjunto;
				
				while(aux->next!=NULL){
					aux= aux->next;
				}
				aux->next= nuevo;
			}
			
		}
	}
	return;
	
}
	
void set_mostrar(Tdata conjunto){
	if(conjunto == NULL || conjunto->data== NULL){
		printf("{}");
		return;
	}
	
	printf("{ ");

	Tdata aux = conjunto;
	
	while(aux != NULL){
		
		if(aux->data != NULL){
			mostrar_generico(aux->data);
			
			if(aux->next != NULL){
				printf(", ");
			}
		}
		aux = aux->next;
	}
	
	printf(" }");
}


int set_pertenece(Tdata conjunto, Tdata elem){
	
	while(conjunto!=NULL){
		if(compara_generico(conjunto->data, elem)==0){
			return 1;
		}
		else{
			conjunto= conjunto->next;			
		}
	}
	return 0;
}


int set_comparar(Tdata conjunto1, Tdata conjunto2){
	
	if(conjunto1==NULL && conjunto2==NULL){
		return 0;
	}
	else{
		if(conjunto1==NULL || conjunto2==NULL){
			return 1;
		}
		else{
			if(set_subconjunto(conjunto1, conjunto2)==0 && set_subconjunto(conjunto2, conjunto1)==0){
				return 0;
			}
		}
		return 1;
	}
	
}

void set_eliminar(Tdata* conjunto, Tdata elem){
	
	if(*conjunto==NULL || elem==NULL){
		return;
	}
	Tdata actual = *conjunto;
	Tdata anterior = NULL;
	
	while(actual != NULL && compara_generico(actual->data, elem)!=0){
		anterior = actual;
		actual = actual->next;
	}
	
	if(actual != NULL){
		if(anterior == NULL){
			*conjunto = (*conjunto)->next;
		}else{
			anterior->next = actual->next;
		}
		
		actual->next=NULL; 
		//pa que no me elimine todo jjsa
		//total ya se hizo una copia profunda
		//Falta hacer el set_compara...
		
		eliminar_generico(actual); //este ta dudoso ?)
		printf("\nElemento eliminado con exito");
		
	}else{
		printf("\nElemento no encontrado");
	}
}

int set_subconjunto(Tdata conjunto1, Tdata conjunto2){
	
	Tdata aux1= conjunto1;
	
	if (conjunto1 == NULL){
		return 1;
	}
	
	while(aux1 != NULL){
		if(set_pertenece(conjunto2,aux1->data)!=1){
			return 0;
		}
		aux1 = aux1->next;
	}
	return 1;
}


int set_iguales(Tdata conjunto1, Tdata conjunto2){
	
	if(set_comparar(conjunto1, conjunto2)==0){
		return 1;
	}
	else{
		return 0;
	}
}
	
Tdata set_union(Tdata conjunto1, Tdata conjunto2){
	
	Tdata nuevo=  NULL;
	nuevo= clone(conjunto1);
	
	while(conjunto2!=NULL){
		set_insertar(&nuevo, conjunto2->data);
		conjunto2= conjunto2->next;
	}
	
	return nuevo;
}
	
Tdata set_interseccion(Tdata conjunto1, Tdata conjunto2){
	Tdata nuevo= NULL;
	
	while(conjunto1!=NULL){
		//el elemento de A, pertenece a B?
		if(set_pertenece(conjunto2,conjunto1->data)==1){
			set_insertar(&nuevo,conjunto1->data);
		}
		conjunto1 = conjunto1->next;
	}
	return nuevo;
}
	
Tdata set_diferencia(Tdata conjunto1, Tdata conjunto2){
	
	Tdata nuevo= NULL;
	
	while(conjunto1 != NULL){
		//el elemento esta en A pero no en B?
		if(set_pertenece(conjunto2,conjunto1->data)!=1){
			set_insertar(&nuevo,conjunto1->data);
		}
		conjunto1 = conjunto1->next;
	}
	return nuevo;
}

	
Tdata set_copy(Tdata n){
	Tdata aux = n;
	Tdata head = NULL;
	Tdata tail = NULL;
	
	while(aux != NULL){
		Tdata nodo_nuevo = create_set();  // nodo contenedor
		
		nodo_nuevo->data = clone(aux->data);
		nodo_nuevo->next = NULL;
		
		if(head == NULL){
			head = nodo_nuevo;
			tail = nodo_nuevo;
		} else {
			tail->next = nodo_nuevo;
			tail = nodo_nuevo;
		}
		
		aux = aux->next;
	}
	
	return head;
}



