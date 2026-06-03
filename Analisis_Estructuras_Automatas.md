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
1. Idea de la estructura.
2. Funcionamiento de **δ**
3. Ventajas y desventajas de utilizar la estructura propuesta.
   
## Analisis de las Propuestas 

### Propuesta 1: δ como Lista de Transiciones

#### ¿Cual es la idea de la estructura?
Esta estructura propone que las transiciones del automata tenga su propia lista enlazada. Es decir, representa a la funcion de transicion **δ** como una cadena secuencial de reglas, en donde agarra cada transicion (si fuera un grafico, seria cada arista) y la guarda de manera individual en un nodo que contiene un campo que almacena  el dato de la transicion, y  otro que almacena el puntero next que dirige hacia el siguiente nodo. 

##### Estado y simbolo
```C
typedef str State;
typedef str Symbol;
```
##### Transicion
```C
typedef struct{
    State from;
    Symbol symbol;

    Tdata to; // SET de estados destino
} Transition;
```
##### Nodo de Transicion
```C
typedef struct transitionNode{
    Transition t;
    struct transitionNode* next;
} TransitionNode;
```
##### Automata
```C
typedef struct{
    Tdata Q;
    Tdata Sigma;

    TransitionNode* Delta;

    State q0;

    Tdata F;

    int deterministic;
} Automata;
```
#### ¿Como funciona delta?

##### La funcion δ:
```C
Tdata delta(Automata* A, State q, Symbol a);
```
El algoritmo hace lo siguiente:
1. Se para en el primer elemento de la lista (A->Delta).

2. Mira el campo ***from*** y ***symbol***, y pregunta:

```C
from == q
symbol == a
```

3. Si la respuesta es NO, usa el puntero next para pasar al siguiente nodo y vuelve a preguntar.

4. Si la respuesta es SÍ, detiene la búsqueda y devuelve el **Tdata** *to*. 

5. Si llega al final de la lista (**next == NULL**) y no encontró nada, significa que no existe una transicion entre **"q"** y *a*. Puede devolver un conjunto vacio.

Es decir, la funcion **δ** va a actuar como un buscador secuencial. 

#### ¿Cuales son las ventajas de utilizar esta estructura?


#### ¿Y las desventajas?



### Propuesta 2: δ Indexado por Estado

#### ¿Cual es la idea de la estructura?
Esta estructura representa al automata conmo un grafo que utiliza una lista de adyacencia. Trata de descentralizar la informacion y darsela a cada estado. Es decir, que en lugar de que el automata tenga una funcion **δ** gigante y centralizada, la funcion de transicion sera fragmentada y metida adentro de cada estado. Los estados pasan a guardar todas las flechas (aristas del grafo) que salen de el (en este caso, hacia donde deben ir), su nombre y su tipo (si es final o no). 

Por lo tanto, el automata ya no sabe como estan conectados los estados (de manera general), solo conoce la lista de estados existentes en donde cada uno de esos estados tiene almacenada la informacion de hacia donde debe ir. 

##### Transicion
```C
typedef struct transition{
    Symbol symbol;                //Simbolo que se va leer.

    Tdata to;                     //SET de estados destino.

    struct transition* next;      //Puntero a la siguiente transicion de este estado.
} Transition;
```
##### Estado
```C
typedef struct stateNode{
    State name;                   //Nombre del estado. 

    Transition* transitions;      //La lista enlazada de sus propias transiciones.

    int isFinal;                  //El tipo de estado que es (final(1) o no(0))

    struct stateNode* next;       //Puntero al siguiente estado general del automata
} StateNode;
```
##### Automata
```C
typedef struct{
    StateNode* states;            //Puntero al nodo inicial de  de la lista que contiene a todos los estados.

    State q0;                     //Estado inicial

    int deterministic;            //De que tipo es AFND o AFD (0 o 1)
} Automata;
```

#### ¿Como funciona?

Para procesar una cadena: 

Sea el estado actual **"q0"** y el simbolo *b*:

1. Buscar el estado actual: se recorre la lista general de estados (A->states) hasta encontrar el estado cuyo nombre sea **"q0"**. 
2. Acceder directamente a su lista de transiciones: una vez parado en **"q0"**, debemos acceder a su lista interna y recorrerla hasta encontrar el nodo cuyo ***symbol*** sea *b*.
3. Obtener conjunto destino: devolvemos el destino *to*. 


#### ¿Cuales son las ventajas de utilizar esta estructura?


#### ¿Y las desventajas?


### Propuesta 3: δ como Matriz Dispersa

#### ¿Cual es la idea de la estructura?
En la teoria, a un automata se lo puede simular como una tabla de transiciones en donde se tienen filas (estados) y columnas (simbolos). Por ejemplo, si cruzo a la fila **"q0"** con la columna *a*, la celda resultante te dice hacia donde se debe ir (estado destino). Pero, ¿que pasa si el automata tiene muchos estados y un alfabeto grande, y encima hay pocas transiciones entre los estados? En este caso, pasariamos a tener una matriz gigante llena de espacios vacios. Pera evitar eso, esta estructura propone guardar solo las celdas que tienen datos, usando "coordenadas numericas enteras en lugar de nombres *strings*. 

La idea de esta propuesta es que a cada estado y a cada simbolo se le asigne un id entero (indice), creando asi un sistema de coordenadas. Para eso se propone ademas usar un puntero simple: **TransitionEntry * delta**, es decir, un arreglo dinamico que va a contener las coordenas de las transiciones que si existen. 

##### Entrada de transicion
Esta parte serian las coordenas de mi transicion: (fila 0, columna 0) -> destinos.
```C
typedef struct{
    int from;        //Id numerico del estado origen. Ejemplo: si tengo "q0" pasaria a ser 0

    int symbol;      //Id numerico del simbolo. Ejemplo: si tengo "a" pasaria a ser 0

    Tdata to;        //SET de estados destinos
} TransitionEntry;
```
##### Automata
```C
typedef struct{
    Tdata Q;

    Tdata Sigma;

    TransitionEntry* delta;     //Arreglo dinamico de coordenadas

    int deltaSize;              //Cantidad de transiciones 

    int q0;                     //Id del estado inicial

    Tdata F;                    //SET de estados finales.
} Automata;
```

#### ¿Como funciona delta?
Llamamos a **Delta** pasandole el automata, el estado y el simbolo como parametros. Luego dentro de este metodo se va a recorrer el arreglo dinamico *delta* para ver si hay coincidencias (*delta* va a tener que traducir el estado y simbolo recibido a un **int**). 
Para acceder a los campos de *delta* lo hacemos normalmente como cuando trabajabamos con arrays estaticos. Ejemplo: **delta[id].from** (Dependiendo del contexto). 

##### Acceso a δ: 
```C
Delta(A, estado, simbolo);
```

1. Treducir el estado y simbolo original a un id entero (esto formaria una coordenada).
2. Recorrer *delta*, buscando el **TransitionEntry** que tenga **from== id_estado** y **symbol== id_simbolo**.
3. Retorna *to* si es que lo encontro. 


#### ¿Cuales son las ventajas de utilizar esta estructura?
...

#### ¿Y las desventajas?
...

### Propuesta 4: δ Funcional

/*Se va a utilizar esta estructura, es la que mejor se adapta al codigo que se tiene*/
/*

#### ¿Cual es la idea de la estructura?
Esta estructura representa a la funcion de transicion δ utilizando un "diccionario" implementado como una arreglo dinamico. 

##### Entrada Funcional
```C
typedef struct{
    State from;

    Symbol symbol;

    Tdata destinations;
} DeltaEntry;
```
##### Automata
```C
typedef struct{
    Tdata Q;

    Tdata Sigma;

    DeltaEntry* delta;

    int deltaCount;

    State q0;

    Tdata F;
} Automata;
```
#### ¿Como funciona delta?

##### La funcion δ:
```C
buscar (estado, simbolo)
```


#### ¿Cuales son las ventajas de utilizar esta estructura?

#### ¿Y las desventajas?
...


### Propuesta 5: Estados Compuestos para Determinacion

#### ¿Cual es la idea de la estructura?

##### Estado Compuesto
```C
typedef struct{
    Tdata subset;
} CompositeState;
```
##### Transicion determinizada
```C
typedef struct{
    CompositeState from;

    Symbol symbol;

    CompositeState to;
} DFA_Transition;
```
##### AFD resultante
```C
typedef struct{
    Tdata states;

    DFA_Transition* delta;

    int deltaCount;

    CompositeState q0;

    Tdata F;
} DFA;
```
#### ¿Como funciona delta?

##### La funcion δ:
```C
nuevo_estado = unión de destinos posibles
```


#### ¿Cuales son las ventajas de utilizar esta estructura?
...

#### ¿Y las desventajas?
...


