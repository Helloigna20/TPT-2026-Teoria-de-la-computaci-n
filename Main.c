#include "TAD_Ast.h"


int main(){
	
	//CONJUNTO VACIO Y REPETIDOS
	
	Tdata A= NULL;
	
	//falta modificar mostrar_generico para set (por eso usamos print_set))
	print_set(A);
	printf("\n");
	
	Tdata s1= create_str_cad("perro");
	Tdata s2= create_str_cad("gato");
	Tdata s3= create_str();
	//print_str(s3); printf("\n");
	carge_str_cad(&s3, "garfield");
	Tdata s4= concat_str(s2, s3);
	Tdata s5= create_str_cad("perro");
	
	insert_set(&A, s1);
	insert_set(&A, s2);
	insert_set(&A, s3);
	insert_set(&A, s4);
	insert_set(&A, s5);
	
	printf("\n");
	mostrar_generico(A);
	
	//UNION e INTERSECCION
	
	Tdata B= NULL;
	Tdata C= NULL;
	
	Tdata s6= create_str_cad("vaca");
	Tdata s7= create_str_cad("caballo");
	Tdata s8= create_str_cad("burro");
	
	insert_set(&B, s6);
	insert_set(&B, s7);
	insert_set(&B, s7);
	
	printf("\n\n");
	mostrar_generico(B);
	
	insert_set(&C, s1);
	insert_set(&C, B);
	
	printf("\n\n");
	mostrar_generico(C);
	
	
	Tdata UNION1 = union_set(A, B);
	printf("\n\nUnion (A U B)= ");
	mostrar_generico(UNION1);
	printf("\n");
	
	Tdata UNION2 = union_set(A, C);
	printf("\n\nUnion (A U C)= ");
	mostrar_generico(UNION2);
	printf("\n");
	
	
	Tdata INTERSECCION1 = intersection_set(A, B);
	printf("\nInterseccion (A n B)= ");
	print_set(INTERSECCION1);
	
	Tdata INTERSECCION2 = intersection_set(A, C);
	printf("\n\nInterseccion (A n C)= ");
	mostrar_generico(INTERSECCION2);
	
	
	
	

	
	return 0;
}
