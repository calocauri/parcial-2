#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
	int dato;
	struct Nodo* siguiente;
	struct Nodo* anterior;
} Nodo;

Nodo* cabeza = NULL;
Nodo* cola = NULL;


void insertar_inicio(int valor) {
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	nuevo->dato = valor;
	nuevo->siguiente = cabeza;
	nuevo->anterior = NULL;
	if (cabeza != NULL)
		cabeza->anterior = nuevo;
	else
		cola = nuevo;
	cabeza = nuevo;
}


void insertar_final(int valor) {
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	nuevo->dato = valor;
	nuevo->siguiente = NULL;
	nuevo->anterior = cola;
	if (cola != NULL)
		cola->siguiente = nuevo;
	else
		cabeza = nuevo;
	cola = nuevo;
}

// Insertar en posición específica (0-based)
void insertar_posicion(int valor, int posicion) {
	if (posicion <= 0) {
		insertar_inicio(valor);
		return;
	}
	Nodo* actual = cabeza;
	int i = 0;
	while (actual != NULL && i < posicion - 1) {
		actual = actual->siguiente;
		i++;
	}
	if (actual == NULL || actual->siguiente == NULL) {
		insertar_final(valor);
		return;
	}
	Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
	nuevo->dato = valor;
	nuevo->siguiente = actual->siguiente;
	nuevo->anterior = actual;
	actual->siguiente->anterior = nuevo;
	actual->siguiente = nuevo;
}


void eliminar_valor(int valor) {
	Nodo* actual = cabeza;
	while (actual != NULL) {
		if (actual->dato == valor) {
			if (actual->anterior)
				actual->anterior->siguiente = actual->siguiente;
			else
				cabeza = actual->siguiente;
			if (actual->siguiente)
				actual->siguiente->anterior = actual->anterior;
			else
				cola = actual->anterior;
			free(actual);
			return;
		}
		actual = actual->siguiente;
	}
}


void eliminar_posicion(int posicion) {
	if (cabeza == NULL) return;
	Nodo* actual = cabeza;
	int i = 0;
	while (actual != NULL && i < posicion) {
		actual = actual->siguiente;
		i++;
	}
	if (actual == NULL) return;
	if (actual->anterior)
		actual->anterior->siguiente = actual->siguiente;
	else
		cabeza = actual->siguiente;
	if (actual->siguiente)
		actual->siguiente->anterior = actual->anterior;
	else
		cola = actual->anterior;
	free(actual);
}


void recorrer_adelante() {
	Nodo* actual = cabeza;
	printf("Lista hacia adelante: ");
	while (actual != NULL) {
		printf("%d ", actual->dato);
		actual = actual->siguiente;
	}
	printf("\n");
}

void recorrer_atras() {
	Nodo* actual = cola;
	printf("Lista hacia atrás: ");
	while (actual != NULL) {
		printf("%d ", actual->dato);
		actual = actual->anterior;
	}
	printf("\n");
}

void liberar_lista() {
	Nodo* actual = cabeza;
	while (actual != NULL) {
		Nodo* temp = actual;
		actual = actual->siguiente;
		free(temp);
	}
	cabeza = NULL;
	cola = NULL;
}

int main() {
	
	insertar_final(10);
	insertar_inicio(5);
	insertar_final(20);
	insertar_posicion(15, 2); 
	recorrer_adelante();
	recorrer_atras();

	eliminar_valor(10);
	recorrer_adelante();

	eliminar_posicion(1); 
	recorrer_adelante();

	liberar_lista();
	return 0;
}
