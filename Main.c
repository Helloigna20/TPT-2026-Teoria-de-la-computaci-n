#include "TAD_Ast.h"


int main(){
	//CONJUNTO VACIO Y REPETIDOS
	
	Tdata s1= create_str_cad("kokushibo");
	Tdata s2= create_str_cad("douma");
	Tdata s3= create_str();
	//print_str(s3); printf("\n");
	carge_str_cad(&s3, "akaza");
	Tdata s4= concat_str(s2, s3);
	Tdata s5= create_str_cad("gyokko");
	Tdata s6= create_str_cad("kaigaku");
	
	Tdata A= create_set();
	
	insert_set(&A, s1);
	insert_set(&A, s2);
	insert_set(&A, s3);
	insert_set(&A, s4);
	insert_set(&A, s5);
	insert_set(&A, s6);
	insert_set(&A, s2); //Intentamos meter "douma" de nuevo, pero no se ingresa.
	printf("\nA= ");
	mostrar_generico(A); 
	
	//UNION e INTERSECCION
	
	Tdata B= create_set();
	Tdata C= create_set();
	
	Tdata s7= create_str_cad("daki");
	Tdata s8= create_str_cad("gyutaro");
	Tdata s9= create_str_cad("hantegu");
	
	insert_set(&B, s6);
	insert_set(&B, s7);
	insert_set(&B, s8);
	
	printf("\nB= ");
	mostrar_generico(B);
	
	
	insert_set(&C, s3);
	insert_set(&C, B);
	printf("\nC= ");
	mostrar_generico(C);
	
	
	Tdata UNION1 = union_set(A, B);
	printf("\n\nUnion (A U B)= ");
	mostrar_generico(UNION1);
	printf("\n");
	
	Tdata UNION2 = union_set(A, C);
	printf("\nUnion (A U C)= ");
	mostrar_generico(UNION2);
	printf("\n");
	
	
	Tdata INTERSECCION1 = intersection_set(A, B);
	printf("\nInterseccion (A n B)= ");
	print_set(INTERSECCION1);
	
	Tdata INTERSECCION2 = intersection_set(A, C);
	printf("\n\nInterseccion (A n C)= ");
	mostrar_generico(INTERSECCION2);
	printf("\n");
	
	remove_set(&UNION1, s1);
	
	printf("\nUnion (A U B)= ");
	mostrar_generico(UNION1);
	
	//LISTAS ANIDADAS Y CONJUNTOS
	
	Tdata lista= create_list();
	Tdata s1_lis= create_str_cad("muzan");
	
	append(&lista, s1_lis);
	append(&lista, A); //Metemos el conjunto A dentro de la lista. 
	
	printf("\n\nLISTA= ");
	mostrar_generico(lista);
	
	Tdata D = create_set();
	Tdata s10 = create_str_cad("yoriichi");
	Tdata s11 = create_str_cad("ubuyashiki");
	
	insert_set(&D, s10);
	insert_set(&D, s11);
	insert_set(&D, lista);
	
	printf("\n\nD= ");
	mostrar_generico(D);
	
	Tdata producto= product_cartesiano(C,B);
	printf("\n\nPRODUCTO DE CxB= ");
	mostrar_generico(producto);
	
	printf("\n\nLIST convertida a STR: ");
	
	Tdata cadena_list= convertir_list_str(lista);
	
	mostrar_generico(cadena_list);
	
	
	
	return 0;
}
