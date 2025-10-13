#include<stdio.h>
#include<stdlib.h>

/*typedef struct Node {
     int value;
     struct Node* next;
     struct Node* prev;
} Node;

Node* head = NULL;
Node* tail = NULL;

Node* create_Node(int val)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = val;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}*/

//lista ligada simple/singly linked list, datos ligados por su direccion
typedef struct Node
{
    int value;
    struct Node *next;
} Node;

//declarando funciones de lista ligada simple
Node* create_Node(int val);
void try_add_Node(Node* n, Node* into);
void delete_Node();
void printList(Node *head);
void free_list(Node* li);
Node *list = NULL;

int main()
{
    try_add_Node(create_Node(10), list);
    try_add_Node(create_Node(11), list);
    try_add_Node(create_Node(12), list);
    printList(list);
    delete_Node(list); 
    printList(list);

    free_list(list);
    return 0;
}
//definiendo funciones
Node* create_Node(int val)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = val;
    newNode->next = NULL;
    return newNode;
}
void try_add_Node(Node* n, Node* into)
{
    if(list == NULL){
        list = n;
        return;
    }
    if(into->next == NULL){
        into->next = n;
    }
    else{
        try_add_Node(n, into->next);
    }
}
void delete_Node()
{

    if(list == NULL){
        printf("No hay elementos en la lista");
        return;
    }
    if(list->next == NULL){
        printf("Elemento unico");
        Node *temp = list;
        list = NULL;
        free(temp);
        return;
    }
    Node *penultimo = list;
    while(penultimo->next->next){
        penultimo = penultimo->next;
    }
    Node *temp = penultimo->next;
    penultimo->next = NULL;
    free(temp);
    printf("Ultimo elemento borrado\n");
}
void printList(Node *head)
{
    Node *temp = head;
    while(temp != NULL){
        printf("%d - ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}
void free_list(Node* li)
{
    while(li){
        Node* temp = li;
        li = li->next;
        free(temp);
    }
}