# include <stdio.h>
# include <stdlib.h>

typedef struct Nodo {
         int dato;
         struct Nodo* siguiente;
         struct Nodo* anterior;
    } Nodo;

    Nodo* cabeza = NULL;
    Nodo* cola = NULL;


    Nodo* crearNodo (int valor) {
         Nodo* nuevo = newNodo;
         nuevo ->dato = valor;
         nuevo -> siguiente = NULL;
         nuevo -> anterior = NULL;
         return nuevo;

    }

void insertarAlfinal ( int valor){
    Nodo* nuevo = creando (valor);

    if (cabeza == NULL) {
        cabeza = nuevo;
        cola = nuevo ;

    } else {
        cola -> siguiente = nuevo;
        nuevo ->anterior = cola;
        cola= nuevo;
    }
}

 void insertarAlinicio (int valor) {
    Nodo* nuevo = creando (valor);
     
    if (cola == NULL){
        cola = nuevo;
        cabeza= nuevo;
    }else {
        cabeza-> siguiente= nuevo;
        nuevo -> anterior = cabeza;
        cabeza = nuevo;
    }
 }

 void eliminarPorValor(Nodo** cabeza, int valor) {
    Nodo* actual = *cabeza;
    Nodo* anterior = NULL;

    while (actual != NULL && actual->dato != valor) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("Valor %d no encontrado en la lista.\n", valor);
        return;
    }

    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    printf("Nodo con valor %d eliminado.\n", valor);
}