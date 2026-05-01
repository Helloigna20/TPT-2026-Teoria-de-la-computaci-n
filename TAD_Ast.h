#ifndef AST_H
#define AST_H
#include "TAD_String.h"

#define STR 1
#define SET 2
#define LIST 3

//Los comentarios son para guiarme porque sino me pierdo >_<

/* <<< Estructura BASE OBLIGATORIA  >>>*/
typedef struct dataType{
	int nodeType;   /* STR, SET, LIST */
	union{
		str strData;
		struct{
			struct dataType* data;
			struct dataType* next;
		};
	};
}dataType;

typedef dataType * Tdata;

/* << Operaciones generales >>*/
Tdata create_list();
int compara_generico(Tdata, Tdata);
Tdata clone(Tdata);
void mostrar_generico(Tdata);


/* << Operaciones sobre STR >> */
Tdata create_str_cad(const char*);
Tdata create_str();
void carge_str_cad(Tdata*, const char*);
int compare_str(Tdata, Tdata);
Tdata concat_str(Tdata, Tdata);
void print_str(Tdata);

/* << Operaciones sobre SET >> */

Tdata create_set();
void insert_set(Tdata*, Tdata);
int belongs(Tdata set, Tdata elem);
void remove_set(Tdata* set, Tdata elem);
void print_set(Tdata);
Tdata product_cartesiano(Tdata, Tdata);
	
// ** Operaciones algebraicas sobre dos conjuntos **
Tdata union_set(Tdata A, Tdata B); 
Tdata intersection_set(Tdata A, Tdata B);
Tdata difference_set(Tdata A, Tdata B); 
int subset(Tdata A, Tdata B); 
int equals_set(Tdata A, Tdata B);

/* << Operaciones sobre LIST >> */
void append(Tdata*, Tdata);
int length(Tdata);
Tdata copy_list(Tdata);
Tdata concat(Tdata, Tdata);
int search(Tdata, Tdata);
void print_list(Tdata);


#endif
