#ifndef AST_H
#define AST_H
#include "TAD_STR.h"
#define STR 1
#define SET 2
#define LIST 3

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
void eliminar_generico(Tdata*);


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
int belongs(Tdata, Tdata);
void remove_set(Tdata*, Tdata);
void print_set(Tdata);
Tdata product_cartesiano(Tdata, Tdata);
	
// ** Operaciones algebraicas sobre dos conjuntos **
Tdata union_set(Tdata, Tdata); 
Tdata intersection_set(Tdata, Tdata);
Tdata difference_set(Tdata, Tdata); 
int subset(Tdata, Tdata); 
int equals_set(Tdata, Tdata);

/* << Operaciones sobre LIST >> */
void append(Tdata*, Tdata);
int length(Tdata);
Tdata copy_list(Tdata);
Tdata concat(Tdata, Tdata);
int search(Tdata, Tdata);
void print_list(Tdata);


#endif
