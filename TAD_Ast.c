#include "TAD_Ast.h"

Tdata copy_set(Tdata);

Tdata create_str_lis(str cadena){ 
	Tdata nodo= (Tdata)malloc(sizeof(dataType));
	nodo->nodeType= STR;
	nodo->strData= cadena;
	return nodo;
}

void eliminar(Tdata *nodo){
	Tdata aux= *nodo;
	Tdata ant;
	
	while(aux!=NULL){
		if(aux->data!=NULL){
			eliminar_generico(&(aux->data));
		}
		ant= aux;
		aux= aux->next;
		free(ant);
	}
	
	*nodo=NULL;
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

Tdata carge_str_consola(){
	str cadena_leida= cadena_cargar_consola();
	return create_str_lis(cadena_leida);
}
	
	
int compare_str(Tdata nodo1, Tdata nodo2){
	
	if(nodo1->nodeType != STR || nodo2->nodeType!= STR){
		return -1000;
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
		
		Tdata nuevo_nodo_ast= clone(nodo1);
		
		if(nuevo_nodo_ast==NULL){
			return NULL;
		}
		else{
			nuevo_nodo_ast->strData= cadena_concatenar(nuevo_nodo_ast->strData, nodo2->strData);
		}
		
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
	if(elem!=NULL){
		Tdata nuevo= create_set();
		nuevo->data= clone(elem);
		
		if(*set==NULL || (*set)->data==NULL){
			*set= nuevo;
		}
		else{
			if(belongs(*set, elem)==0){
				Tdata aux= *set;
				
				while(aux->next!=NULL){
					aux= aux->next;
				}
				Tdata nuevo = create_set();
				nuevo->data = clone(elem);
				aux->next= nuevo;
				
				
			}
			
		}
	}
	return;
}
	

int belongs(Tdata set, Tdata elem){
	
	if(set!=NULL){
		Tdata aux= set;
		while(aux!=NULL){
			if(compara_generico(aux->data, elem)==0){
				return 1;
			}
			else{
				aux= aux->next;			
			}
		}
		return 0;
	}
	else{
		return -1000;
	}
	
}
	
void print_set(Tdata set){
	if(set == NULL || set->data == NULL){
		printf("{}");
		return;
	}
	
	printf("{ ");
	
	Tdata aux = set;
	
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
	

void remove_set(Tdata* set, Tdata elem){
	
	if(*set==NULL || elem==NULL){
		return;
	}
	
	Tdata actual = *set;
	Tdata anterior = NULL;
	
	while(actual != NULL && compara_generico(actual->data, elem)!=0){
		anterior = actual;
		actual = actual->next;
	}
	
	if(actual != NULL){
		if(anterior == NULL){
			*set = (*set)->next;
		}else{
			anterior->next = actual->next;
		}
		
		actual->next=NULL; 
		//pa que no me elimine todo jjsa
		//total ya se hizo una copia profunda
		
		eliminar_generico(&actual); 
		printf("\n*** Elemento eliminado con exito ***\n");
		
	}else{
		printf("\n*** Elemento no encontrado *** \n");
	}
}
	

// ** Operaciones algebraicas sobre dos conjuntos **
	
Tdata union_set(Tdata set1, Tdata set2){
	
	Tdata nuevo=  NULL;
	nuevo= clone(set1);
	
	Tdata aux= set2;
	
	while(aux!=NULL){
		insert_set(&nuevo, aux->data);
		aux= aux->next;
	}
	return nuevo;
}


Tdata intersection_set(Tdata set1, Tdata set2){
	
	Tdata nuevo= NULL;
	Tdata aux= set1;
	
	while(aux!=NULL){
		//el elemento de A, pertenece a B?
		if(belongs(set2,aux->data)==1){
			insert_set(&nuevo, aux->data);
		}
		aux = aux->next;
	}
	return nuevo;
}


Tdata difference_set(Tdata set1, Tdata set2){
	
	Tdata nuevo= NULL;
	Tdata aux= set1;
	
	while(aux!=NULL){
		//el elemento de A no pertenece a B?
		if(belongs(set2,aux->data)!=1){
			insert_set(&nuevo,aux->data);
		}
		aux = aux->next;
	}
	return nuevo;
}

int subset(Tdata set1, Tdata set2){
	
	Tdata aux1= set1;
	
	if (aux1 == NULL){
		return 1;
	}
	
	while(aux1 != NULL){
		if(belongs(set2,aux1->data)!=1){
			return 0;
		}
		aux1 = aux1->next;
	}
	return 1;
}

	

int equals_set(Tdata set1, Tdata set2){
	
	if(set1==NULL && set2==NULL){
		return 0;
	}
	else{
		if(set1==NULL || set2==NULL){
			return 1;
		}
		else{
			if(subset(set1, set2)==0 && subset(set2, set1)==0){
				return 0;
			}
		}
		return 1;
	}
	
}
	
	
Tdata copy_set(Tdata set){
	
	Tdata aux = set;
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



Tdata product_cartesiano(Tdata set1, Tdata set2){
	Tdata producto= NULL;
	
	if(set1!=NULL && set2!=NULL){
		if(set1->nodeType == SET && set2->nodeType == SET){
			Tdata aux1= set1;
			
			while(aux1 != NULL){
				Tdata aux2= set2;
				
				while(aux2 != NULL){
					if(aux1->data != NULL && aux2->data != NULL){
						Tdata par= create_list();
						append(&par, aux1->data);
						append(&par, aux2->data);
						insert_set(&producto, par);
					}
					aux2= aux2->next;
				}
				aux1= aux1->next;
			}
		}
	}
	
	return producto;
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
	
	if(elem!=NULL){
		Tdata nuevo= create_list();
		nuevo->data= clone(elem);
		
		if(*list==NULL || (*list)->data==NULL){
			*list=nuevo;
		}
		else{
			Tdata aux= *list;
			
			while(aux->next!=NULL){
				aux= aux->next;
			}
			aux->next= nuevo;
		}
	}
	return;
}
	
int length(Tdata list){
	Tdata aux= list;
	int c=0;
	
	while(aux!=NULL){
		c++;
		aux= aux->next;
	}
	return c;
}

	
Tdata copy_list(Tdata list){
	Tdata aux = list;
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

	
Tdata concat(Tdata list1, Tdata list2){
	
	if(list1==NULL && list2==NULL){
		return NULL;
	}
	else{
		if(list1==NULL){
			return clone(list2);
		}
		if(list2==NULL){
			return clone(list1);
		}
	}
	
	Tdata nuevo= clone(list1);
	Tdata copy_list2= list2;
	
	Tdata aux= nuevo;
	
	while(aux->next!=NULL){
		aux= aux->next;
	}
	
	aux->next= copy_list2;
	
	return nuevo;
	
}

int compare_list(Tdata list1, Tdata list2){
	if(list1==NULL && list2==NULL){
		return 0;
	}
	if(list1==NULL || list2==NULL){
		return 1;
	}
	else{
		Tdata aux1= list1;
		Tdata aux2= list2;
		
		while(aux1!=NULL && aux2!=NULL){
			if(compara_generico(aux1->data, aux2->data)!=0){
				return 1;
			}
			aux1=aux1->next;
			aux2=aux2->next;
		}
		
		if(aux1==NULL && aux2==NULL){
			return 0;
		}
		
		return 1;
	}
}

	
int search(Tdata list, Tdata elem){
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

void print_list(Tdata list){
	if(list == NULL || list->data== NULL){
		printf("[]");
		return;
	}
	
	printf("[ ");
	
	Tdata aux = list;
	
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
	
	
Tdata convertir_list_str(Tdata nodo){
	
	if (nodo == NULL) {
		return NULL;
	}
	else{
		if(nodo->nodeType == STR){
			return clone(nodo);
		}
		
		Tdata nuevo = NULL; 
		Tdata aux = nodo;
		
		if(nodo->nodeType==LIST || nodo->nodeType==SET){
			
			while (aux != NULL) {
				if (aux->data != NULL) {
					Tdata nvo_aux= convertir_list_str(aux->data);
					
					if(nvo_aux!=NULL){
						if (nuevo== NULL){
							nuevo = nvo_aux; 
						}
						else {
							Tdata temporal = concat_str(nuevo, nvo_aux);
							
							eliminar_generico(&nuevo);
							eliminar_generico(&nvo_aux);
							nuevo = temporal;
						}
					}
				}
				aux = aux->next;
			}
		}
		return nuevo;
	}
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
		nuevo= copy_set(nodo);
		break;
		
	case LIST:
		nuevo= copy_list(nodo);
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
				return -1000;
			}
			switch(nodo1->nodeType){
			case STR:
				op= compare_str(nodo1, nodo2);
				break;
				
			case SET:
				op= equals_set(nodo1, nodo2);
				break;
				
			case LIST:
				op= compare_list(nodo1, nodo2);
				break;
			}
		}
		
		return op;
	}
}
	

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
	
void eliminar_generico(Tdata* nodo){
	
	if(*nodo==NULL){
		return;
	}
	switch((*nodo)->nodeType){
	case STR:
		cadena_destruir(&((*nodo)->strData));
		free(nodo);
		break;
		
	case SET:
		eliminar(nodo);
		break;
		
	case LIST:
		eliminar(nodo);
		break;
	}
	*nodo= NULL;
}

