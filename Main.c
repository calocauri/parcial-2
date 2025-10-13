#include <stdio.h>
#include <stdlib.h>

// Estructura del nodo
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

// Punteros globales a cabeza y cola
Nodo* cabeza = NULL;
Nodo* cola = NULL;

// Crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

// Insertar al inicio
void insertarInicio(int valor) {
    Nodo* nuevo = crearNodo(valor);
    if (cabeza == NULL) {
        cabeza = cola = nuevo;
    } else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
}

// Insertar al final
void insertarFinal(int valor) {
    Nodo* nuevo = crearNodo(valor);
    if (cola == NULL) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

// Eliminar por valor
void eliminarValor(int valor) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (actual->dato == valor) {
            if (actual->anterior != NULL)
                actual->anterior->siguiente = actual->siguiente;
            else
                cabeza = actual->siguiente; // era la cabeza

            if (actual->siguiente != NULL)
                actual->siguiente->anterior = actual->anterior;
            else
                cola = actual->anterior; // era la cola

            free(actual);
            printf("Nodo con valor %d eliminado.\n", valor);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Valor %d no encontrado.\n", valor);
}

// Recorrer hacia adelante
void recorrerAdelante() {
    Nodo* actual = cabeza;
    printf("Lista hacia adelante: ");
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

// Recorrer hacia atrás
void recorrerAtras() {
    Nodo* actual = cola;
    printf("Lista hacia atrás: ");
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->anterior;
    }
    printf("\n");
}

// Liberar toda la memoria
void liberarLista() {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    cabeza = cola = NULL;
    printf("Memoria liberada.\n");
}

// Ejemplo de uso
int main() {
    insertarInicio(10);
    insertarInicio(20);
    insertarFinal(5);
    insertarFinal(15);

    recorrerAdelante();
    recorrerAtras();

    eliminarValor(20);
    recorrerAdelante();

    eliminarValor(100); // valor no existente

    liberarLista();
    return 0;
}
