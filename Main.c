#include <iostream>

typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;


Nodo* cabeza = NULL;
Nodo* cola = NULL;


Nodo* crearNodo(int valor) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}


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


void recorrerAdelante() {
    Nodo* actual = cabeza;
    cout << "Lista hacia adelante: ";
    while (actual != NULL) {
        cout << actual->dato << " ";
        actual = actual->siguiente;
    }
    cout << endl;
}


void recorrerAtras() {
    Nodo* actual = cola;
    cout << "Lista hacia atrás: ";
    while (actual != NULL) {
        cout << actual->dato << " ";
        actual = actual->anterior;
    }
    cout << endl;
}

void eliminarNodo(int valor) {
    Nodo* actual = cabeza;

    while (actual != NULL && actual->dato != valor) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "Valor no encontrado.\n";
        return;
    }

    
    if (actual == cabeza) {
        
        cabeza = actual->siguiente;
        if (cabeza != NULL)
            cabeza->anterior = NULL;
    } else if (actual == cola) {
        
        cola = actual->anterior;
        if (cola != NULL)
            cola->siguiente = NULL;
    } else {
        
        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
    }

    delete actual;
}


void liberarLista() {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = NULL;
    cola = NULL;
}


int main() {
    insertarAlFinal(10);
    insertarAlFinal(20);
    insertarAlInicio(5);
    insertarAlFinal(30);

    recorrerAdelante();
    recorrerAtras();

    eliminarNodo(20);
    recorrerAdelante();

    liberarLista();
    return 0;
}