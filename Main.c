#include <stdio.h>
#include <stdlib.h>

// Estructura del nodo
typedef struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

// Crear nodo
Nodo* create_Node(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

// Agregar nodo al final
void add_Node_at_tail(Nodo* nuevo, Nodo** head, Nodo** tail) {
    if (*head == NULL) {
        *head = *tail = nuevo;
    } else {
        (*tail)->siguiente = nuevo;
        nuevo->anterior = *tail;
        *tail = nuevo;
    }
}

// Agregar nodo al inicio
void add_Node_at_head(Nodo** head, Nodo** tail, Nodo* nuevo) {
    if (*head == NULL) {
        *head = *tail = nuevo;
    } else {
        nuevo->siguiente = *head;
        (*head)->anterior = nuevo;
        *head = nuevo;
    }
}

// Agregar nodo después de un nodo dado
void add_Node_after(Nodo* nodoPrevio, Nodo* nuevo, Nodo** tail) {
    if (nodoPrevio == NULL) {
        printf("El nodo previo no puede ser NULL.\n");
        return;
    }
    nuevo->siguiente = nodoPrevio->siguiente;
    nuevo->anterior = nodoPrevio;
    nodoPrevio->siguiente = nuevo;
    if (nuevo->siguiente != NULL)
        nuevo->siguiente->anterior = nuevo;
    else
        *tail = nuevo; // si se insertó al final, actualiza la cola
}

// Eliminar un nodo por puntero
void delete_Node(Nodo** head, Nodo** tail, Nodo* eliminar) {
    if (eliminar == NULL) return;

    if (eliminar->anterior != NULL)
        eliminar->anterior->siguiente = eliminar->siguiente;
    else
        *head = eliminar->siguiente; // era la cabeza

    if (eliminar->siguiente != NULL)
        eliminar->siguiente->anterior = eliminar->anterior;
    else
        *tail = eliminar->anterior; // era la cola

    free(eliminar);
}

// Eliminar por valor
void delete_by_value(Nodo** head, Nodo** tail, int valor) {
    Nodo* actual = *head;
    while (actual != NULL) {
        if (actual->dato == valor) {
            delete_Node(head, tail, actual);
            printf("Nodo con valor %d eliminado.\n", valor);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Valor %d no encontrado.\n", valor);
}

// Imprimir lista desde la cabeza
void printListFromHead(Nodo* head) {
    Nodo* temp = head;
    printf("Lista de inicio a fin: ");
    while (temp != NULL) {
        printf("%d ", temp->dato);
        temp = temp->siguiente;
    }
    printf("\n");
}

// Imprimir lista desde la cola
void printListFromTail(Nodo* tail) {
    Nodo* temp = tail;
    printf("Lista de fin a inicio: ");
    while (temp != NULL) {
        printf("%d ", temp->dato);
        temp = temp->anterior;
    }
    printf("\n");
}

// Liberar memoria de toda la lista
void free_list(Nodo* head) {
    Nodo* temp;
    while (head != NULL) {
        temp = head;
        head = head->siguiente;
        free(temp);
    }
    printf("Memoria liberada correctamente.\n");
}

int main() {
    Nodo* head = NULL;
    Nodo* tail = NULL;

    printf("=== Crear y agregar nodos a la lista ===\n");
    add_Node_at_tail(create_Node(10), &head, &tail);
    add_Node_at_tail(create_Node(11), &head, &tail);
    add_Node_at_tail(create_Node(12), &head, &tail);
    printListFromHead(head);

    printf("\n=== Agregar un nodo al principio ===\n");
    add_Node_at_head(&head, &tail, create_Node(4));
    printListFromHead(head);

    printf("\n=== Agregar un nodo en medio (después del segundo nodo) ===\n");
    add_Node_after(head->siguiente, create_Node(5), &tail);
    printListFromHead(head);

    printf("\n=== Agregar un nodo al final ===\n");
    add_Node_at_tail(create_Node(6), &head, &tail);
    printListFromHead(head);

    printf("\n=== Borrar un nodo ===\n");
    delete_Node(&head, &tail, head->siguiente->siguiente); 
    printListFromHead(head);
    printf("\n=== Lista de atras para adelante ===\n");
    printListFromTail(tail);

    free_list(head);
    return 0;
}
