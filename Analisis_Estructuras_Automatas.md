# Estructuras de Automatas Finitos en C

## Introduccion

Ya disponemos de un conjunto de TAD generico: 
* **AST ->** es el TAD encargado de gestionar de manera dinamica los otros TAD´s, a traves de un tipo de dato generico **Tdata** que maneja las operaciones "mostrar_generico", "compara_generico" y "destruir_generico". Cuando operamos el TAD_AST, el mismo, primero mira de que tipo de dato (subyacente) es mi **Tdata**; ¿es un STR?, ¿es un SET? o ¿es una LIST?, para delegar las operaciones correspondientes.  De esta manera se puede realizar un anidamineto entre las estructuras permitiendo administrar de forma segura la memoria y evitando posibles fallos criticos durante el tiempo de ejecucion. 

* **SET ->** es el TAD conjunto. Esta estructura se rige bajo los principios matematicos que operan sobre un conjunto. Por definicion, un conjunto no admite elementos repetidos (unicidad) y no tiene un orden definido. Matematicamente las operaciones definidas para el mismo van a ser: *Union, Interseccion, Diferencia, Contencion (Subconjunto)* y *Pertenencia*. El TAD_SET sera quien nos permitira modelar **Q:** el conjunto finitos de estados, **$\Sigma$:** el alfabeto, y **F:** el conjunto de estados finales de un automata. 
  
* **LIST ->** es el TAD lista. El TAD_LIST, a diferencia del TAD_SET conserva un orden posicional respecto de sus elemento y admite elementos repetidos.
  
* **STR ->** es el TAD cadena. El TAD_STR  es el encargado de implementar las cadenas de caracteres utilizando asignacion dinamica de memoria. Este TAD es un sustituto de la libreria estandar de **C** *string.h*. Se encarga de gestionar de forma secuencial los caracteres puros (**char**). El mismo, va a representar los simbolos de un alfabeto o los nombre de los estados de un automata.

Ahora el objetivo es construir estructuras para representar: 
* AFD (Automata Finito Determinista).
* AFND (Automata Finito No Determinista).

utilizando la definicion formal de un Automata Finito:

* <ins>***Definicion</ins>:*** Un automata finito es un dispositivo que acepta lenguajes regulares, y se define mediante la siguiente 5-upla: **A = (Q, Σ, δ, q0, F)**, donde:
  * **Q:** es un conjunto finito, no vacio, de estados.
  * **Σ:** es un conjunto finito, no vacio, de simbolos denominado *alfabeto*.
  * **δ:** es una funcion o relacion de transicion (dependiendo de si es un AFD o un AFND).
  * **q0:** es el estado inicial.
  * **F:** es un conjunto finito, no vacio, de estados de aceptacion.

Vamos a realizar un analisis de cada una de las estructuras propuestas por la catedra *"Teoria de la Computacion 1"*  basandonos en los siguientes enfoques:
  1. <ins>Manejo de memoria</ins>: cual de ellos es menos propenso a generar una fuga de memoria a la hora de crear las transiciones. 
  2. <ins>Flexibilidad</ins>: cual sera el mas optimo para operar tanto AFND como AFD.
  3. <ins>Integracion</ins>: cual de ellos es mas conveniente de usar teniendo en cuenta el codigo que se posee.

## Analisis de las Propuestas 

### Propuesta 1: δ como Lista de Transiciones

#### ¿Cual es la idea de la estructura?
Esta estructura propone que las transiciones del automata tenga su propia lista enlazada. Es decir, representa a la funcion de transicion **δ** como una cadena secuencial de reglas, en donde agarra cada transicion (si fuera un grafico, seria cada arista) y la guarda de manera individual en un nodo que contiene un campo que almacena  el dato de la transicion, y  otro que almacena el puntero next que dirige hacia el siguiente nodo. 

```C
//La transicion 
typedef struct{
    State from;  //Estado de origen, donde comieza. Ejemplo: "q0"
    Symbol symbol;  //Es el simbolo leido. 

    Tdata to; //Es un 
} Transition;
```




