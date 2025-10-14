#include <stdio.h>
#include <stdlib.h>

// Estructura del nodo doblemente ligado
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

// Punteros globales a la cabeza y cola
Nodo* cabeza = NULL;
Nodo* cola = NULL;

// Crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

// Insertar nodo al final
void insertarAlFinal(int valor) {
    Nodo* nuevo = crearNodo(valor);

    if (cabeza == NULL) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

// Insertar nodo al inicio
void insertarAlInicio(int valor) {
    Nodo* nuevo = crearNodo(valor);

    if (cabeza == NULL) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
}

// Insertar en una posición específica (0 = inicio)
void insertarEnPosicion(int valor, int posicion) {
    if (posicion <= 0 || cabeza == NULL) {
        insertarAlInicio(valor);
        return;
    }

    Nodo* actual = cabeza;
    int i = 0;
    while (actual->siguiente != NULL && i < posicion - 1) {
        actual = actual->siguiente;
        i++;
    }

    if (actual->siguiente == NULL) {
        insertarAlFinal(valor);
    } else {
        Nodo* nuevo = crearNodo(valor);
        nuevo->siguiente = actual->siguiente;
        nuevo->anterior = actual;
        actual->siguiente->anterior = nuevo;
        actual->siguiente = nuevo;
    }
}

// Eliminar nodo por valor
void eliminarPorValor(int valor) {
    Nodo* actual = cabeza;

    while (actual != NULL && actual->dato != valor) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("Valor %d no encontrado.\n", valor);
        return;
    }

    if (actual == cabeza && actual == cola) {
        cabeza = cola = NULL;
    } else if (actual == cabeza) {
        cabeza = actual->siguiente;
        cabeza->anterior = NULL;
    } else if (actual == cola) {
        cola = actual->anterior;
        cola->siguiente = NULL;
    } else {
        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
    }

    free(actual);
    printf("Nodo con valor %d eliminado.\n", valor);
}

// Recorrer lista hacia adelante
void recorrerAdelante() {
    Nodo* actual = cabeza;
    printf("Lista hacia adelante: ");
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

// Recorrer lista hacia atrás
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
        Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    cabeza = NULL;
    cola = NULL;
    printf("Memoria liberada correctamente.\n");
}

// Ejemplo de uso
int main() {
    insertarAlFinal(10);
    insertarAlFinal(20);
    insertarAlInicio(5);
    insertarEnPosicion(15, 2); // inserta 15 en la posición 2

    recorrerAdelante();
    recorrerAtras();

    eliminarPorValor(20);
    recorrerAdelante();

    liberarLista();
    return 0;
}