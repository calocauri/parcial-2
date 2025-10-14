#include <stdio.h>
#include <stdlib.h>

// Lista doblemente ligada, cada nodo apunta al anterior y al siguiente
typedef struct Nodo {
    int dato;              
    struct Nodo* siguiente; 
    struct Nodo* anterior;  
} Nodo;

// punteros al inicio y al final de la lista
Nodo* cabeza = NULL;
Nodo* cola = NULL;

// Recorrer la lista de fin a inicio
void recorrerAtras() {
    Nodo* actual = cola;
    printf("Lista al revés: ");
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->anterior;
    }
    printf("\n");
}

// Crear un nodo nuevo con valor dado
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("Error de memoria :(\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

// Insertar nodo al final de la lista
void insertarAlFinal(int valor) {
    Nodo* nuevo = crearNodo(valor);
    if (!cabeza) { 
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
}

// Insertar nodo en posición específica (0 = inicio)
void insertarEnPosicion(int valor, int posicion) {
    if (!cabeza || posicion <= 0) {
        insertarAlInicio(valor);
        return;
    }

    Nodo* actual = cabeza;
    int i = 0;
    while (actual->siguiente && i < posicion - 1) {
        actual = actual->siguiente;
        i++;
    }

    if (!actual->siguiente) {
        insertarAlFinal(valor);
    } else {
        Nodo* nuevo = crearNodo(valor);
        nuevo->siguiente = actual->siguiente;
        nuevo->anterior = actual;
        actual->siguiente->anterior = nuevo;
        actual->siguiente = nuevo;
    }
}

// Insertar nodo al inicio
void insertarAlInicio(int valor) {
    Nodo* nuevo = crearNodo(valor);
    if (!cabeza) {
        cabeza = cola = nuevo;
    } else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
}

// Eliminar nodo por valor
void eliminarPorValor(int valor) {
    Nodo* actual = cabeza;

    while (actual && actual->dato != valor) {
        actual = actual->siguiente;
    }

    if (!actual) {
        printf("No encontré el valor %d :(\n", valor);
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
    printf("Se borró %d de la lista\n", valor);
}

// Mostrar la lista hacia adelante
void recorrerAdelante() {
    Nodo* actual = cabeza;
    printf("Lista de inicio a fin: ");
    while (actual) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

// Limpiar toda la lista y liberar memoria
void liberarLista() {
    Nodo* actual = cabeza;
    while (actual) {
        Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    cabeza = NULL;
    cola = NULL;
    printf("Lista borrada, memoria libre 👍\n");
}

// probando todo
int main() {
    insertarAlFinal(10);
    insertarAlFinal(20);
    insertarAlInicio(5);
    insertarEnPosicion(15, 2); 

    recorrerAdelante();
    recorrerAtras();

    eliminarPorValor(20);
    recorrerAdelante();

    liberarLista();
    return 0;
}
