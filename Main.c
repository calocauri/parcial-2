#include <stdio.h>
#include <stdlib.h>


struct Nodo {
    int dato;
    struct Nodo *anterior;
    struct Nodo *siguiente;
};


struct Nodo *inicio = NULL;
struct Nodo *fin = NULL;


struct Nodo* crearNodo(int dato) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo->dato = dato;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}


void insertarFinal(int dato) {
    struct Nodo* nuevo = crearNodo(dato);
    if (inicio == NULL) { 
        inicio = fin = nuevo;
    } else {
        fin->siguiente = nuevo;
        nuevo->anterior = fin;
        fin = nuevo;
    }
}


void mostrarAdelante() {
    struct Nodo* actual = inicio;
    printf("Lista (adelante): ");
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}


void mostrarAtras() {
    struct Nodo* actual = fin;
    printf("Lista (atrás): ");
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->anterior;
    }
    printf("\n");
}


void eliminarNodo(int valor) {
    struct Nodo* actual = inicio;

    while (actual != NULL) {
        if (actual->dato == valor) {
            if (actual->anterior != NULL)
                actual->anterior->siguiente = actual->siguiente;
            else
                inicio = actual->siguiente; 

            if (actual->siguiente != NULL)
                actual->siguiente->anterior = actual->anterior;
            else
                fin = actual->anterior; 

            free(actual);
            printf("Nodo con valor %d eliminado.\n", valor);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Nodo con valor %d no encontrado.\n", valor);
}


int main() {
    insertarFinal(10);
    insertarFinal(20);
    insertarFinal(30);
    insertarFinal(40);

    mostrarAdelante();
    mostrarAtras();

    eliminarNodo(20);
    mostrarAdelante();
    mostrarAtras();

    return 0;
}
