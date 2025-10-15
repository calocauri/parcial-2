Parcial 2 

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

Nodo* cabeza = NULL;
Nodo* cola = NULL;

Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

void insertarAlInicio(int valor) {
    Nodo* nuevo = crearNodo(valor);
    if (cabeza == NULL) {
        cabeza = cola = nuevo;
    } else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
}

void insertarAlFinal(int valor) {
    Nodo* nuevo = crearNodo(valor);
    if (cola == NULL) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

void eliminarPorValor(int valor) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (actual->dato == valor) {
            if (actual == cabeza && actual == cola) {
                cabeza = cola = NULL;
            } else if (actual == cabeza) {
                cabeza = cabeza->siguiente;
                cabeza->anterior = NULL;
            } else if (actual == cola) {
                cola = cola->anterior;
                cola->siguiente = NULL;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            free(actual);
            printf("Nodo con valor %d eliminado.\n", valor);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Valor %d no encontrado en la lista.\n", valor);
}

void recorrerAdelante() {
    Nodo* actual = cabeza;
    printf("Recorrido hacia adelante: ");
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

void recorrerAtras() {
    Nodo* actual = cola;
    printf("Recorrido hacia atrás: ");
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->anterior;
    }
    printf("\n");
}

void liberarMemoria() {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    cabeza = cola = NULL;
    printf("Memoria liberada.\n");
}

int main() {
    printf("=== Lista doblemente ligada ===\n");

    insertarAlInicio(10);
    insertarAlInicio(5);
    insertarAlFinal(20);
    insertarAlFinal(30);

    recorrerAdelante();
    recorrerAtras();

    eliminarPorValor(20);
    recorrerAdelante();

    eliminarPorValor(5);
    recorrerAtras();

    liberarMemoria();
    return 0;
}
