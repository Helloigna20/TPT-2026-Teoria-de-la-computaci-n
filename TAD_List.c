#include "TAD_List.h"

void list_insertar(Tdata* lista, Tdata elem){
	
	if(elem!=NULL){
		Tdata nuevo= create_list();
		nuevo->data= clone(elem);
		
		if(*lista==NULL){
			*lista=nuevo;
		}
		else{
			Tdata aux= *lista;
			
			while(aux->next!=NULL){
				aux= aux->next;
			}
			
			aux->next= nuevo;
		}
	}
	return;
}

int list_tam(Tdata lista){
	
	int c=0;
	
	while(lista!=NULL){
		c++;
		lista= lista->next;
	}
	
	return c;
}
	
int list_pertenece(Tdata list, Tdata elem){
	
	while(list!=NULL){
		if(compara_generico(list->data, elem)==0){
			return 1;
		}
		else{
			list= list->next;			
		}
	}
	return 0;
}
	
void lista_mostrar(Tdata lista){
	
	if(lista == NULL || lista->data== NULL){
		printf("[]");
		return;
	}
	
	printf("[ ");
	
	Tdata aux = lista;
	
	while(aux != NULL){
		
		if(aux->data != NULL){
			mostrar_generico(aux->data);
			
			if(aux->next != NULL){
				printf(", ");
			}
		}
		aux = aux->next;
	}
	
	printf(" ]");
}

	
//Copia Profunda.
Tdata list_copy(Tdata n){
	
	Tdata aux = n;
	Tdata head = NULL;
	Tdata tail = NULL;
	
	while(aux != NULL){
		Tdata nodo_nuevo = create_list();
		
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

//Une(concatena) dos listas. 
Tdata list_concat(Tdata l1, Tdata l2){
	
}

//Busca un elemento en la lista.
int list_search(Tdata list, Tdata elem){
	
}
