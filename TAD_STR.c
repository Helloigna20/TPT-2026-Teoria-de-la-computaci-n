
#include "TAD_String.h"

str crea_nodo(char c){
	str nuevo;
	nuevo= (str)malloc(sizeof(t_nodoStr));
	nuevo->caracter= c;
	nuevo->sig= NULL;
	
	return nuevo;
}

	
short es_vocal(char c){
	if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
		return 1;
	}
	else{
		return -1;
	}
}

//-------------------------------------------------------------------------//
str cadena_crear(){
	str cadena=NULL;
	return cadena;
}
	
void cadena_agregar_caracter(str* cad, char c){
	str nodo, aux;
	
	nodo= crea_nodo(c);
	
	if(*cad==NULL){
		*cad= nodo;
	}
	else{
		aux= *cad;
		while(aux->sig!=NULL){
			aux= aux->sig;
		}
		aux->sig= nodo;
	}
}


str load2(const char* texto){
	str cad= cadena_crear();
	
	for(int i=0; texto[i]!='\0'; i++){
		cadena_agregar_caracter(&cad, texto[i]);
	}
	
	return cad;
}
	
void cadena_eliminar_vocales(str* cad){
	str aux, ant;
	
	if(*cad!=NULL){
		
		while(es_vocal((*cad)->caracter)==1 && aux!=NULL){
			aux=*cad;
			*cad= (*cad)->sig;
			free(aux);
			aux=NULL;
		}
		ant=*cad;
		aux= (*cad)->sig;
		
		while(aux!=NULL){
			if(es_vocal(aux->caracter)==1){
				ant->sig= aux->sig;
				free(aux);
				aux= ant->sig;
			}
			else{
				ant= aux;
				aux= aux->sig;
			}
		}
	}
	else{
		printf("\nError, la cadena esta vacia...");
	}

}
void cadena_imprimir(str cad){
	if(cad!=NULL){
		printf(" ");
		while(cad!=NULL){
			printf("%c", cad->caracter);
			cad= cad->sig;
		}
	}
	else{
		printf("\nError, la cadena esta vacia...");
	}
}
void cadena_destruir(str *cad){
	
	if(*cad==NULL){
		printf("*** La cadena no tiene elementos para destruir***\n");
	}
	else{
		while(*cad!=NULL){
			*cad= (*cad)->sig;
		}
		printf("\n*** Cadena destruida ***");
	}
}
	
int cadena_comparar(str cad1, str cad2){
	int op;

	while(cad1!=NULL && cad2!=NULL){
		if(cad1->caracter != cad2->caracter){
			return (cad1->caracter - cad2->caracter);
		}
		cad1= cad1->sig;
		cad2= cad2->sig;
	}
	
	if(cad1==NULL  && cad2==NULL){
		op= 0;
	}
	else{
		if(cad1==NULL){
			op= -1;
		}
		if(cad2==NULL){
			op= 1;
		}
	}
	return op;
	
}


str cadena_concatenar(str cad1, str cad2){
	str aux;
	str nueva= cadena_crear();
	
	if(cad1==NULL || cad2==NULL){
		if(cad1==NULL && cad2==NULL){
			printf("\nError, las cadenaas estan vacias...");
		}
		else{
			if(cad1==NULL){
				nueva= cad1;
			}
			if(cad2==NULL){
				nueva= cad2;
			}
		}
	}
	else{
		aux= cad1;
		while(aux!=NULL){
			cadena_agregar_caracter(&nueva, aux->caracter);
			aux= aux->sig;
		}
		
		aux= cad2;
		while(aux!=NULL){
			cadena_agregar_caracter(&nueva, aux->caracter);
			aux= aux->sig;
		}
	}
	
	return nueva;
}
	
str cadena_copy(str cad){
	str nueva= cadena_crear();
	
	while(cad!=NULL){
		cadena_agregar_caracter(&nueva, cad->caracter);
		cad= cad->sig;
	}
	
	return nueva;
}


