#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
     int value;
     struct Node* next;
     struct Node* prev;
} Node;

Node* head = NULL;
Node* tail = NULL;

//declare functions
Node* create_Node(int val);
void add_Node_at_head(Node **head, Node **tail, Node *n);
void add_Node_after(Node *ref_Node, Node* newNode, Node** tail);
void add_Node_at_tail(Node* n, Node** head, Node** tail);
void delete_Node(Node **head, Node **tail, Node *remove);
void printListFromHead(Node *head);
void printListFromTail(Node *tail);
void free_list(Node* li);

int main()
{
    printf("Crear y agregar nodos a una lista\n");
    add_Node_at_tail(create_Node(10), &head, &tail);
    add_Node_at_tail(create_Node(11), &head, &tail);
    add_Node_at_tail(create_Node(12), &head, &tail);
    printListFromHead(head);

    printf("Agregar un nodo al principio\n");
    add_Node_at_head(&head, &tail, create_Node(4));
    printListFromHead(head);
    printf("Agregar un nodo en medio\n");
    add_Node_after(head->next, create_Node(5), &tail);
    printListFromHead(head);
    printf("Agregar un nodo al final\n");
    add_Node_at_tail(create_Node(6), &head, &tail);
    printListFromHead(head);
    printf("Borrar un nodo\n");
    delete_Node(&head, &tail, head->next->next); 
    printListFromHead(head);
    printf("Lista de atras para adelante\n");
    printListFromTail(tail);

    free_list(head);
    return 0;
}

//function def
Node* create_Node(int val)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        return NULL;
    }
    newNode->value = val;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void add_Node_at_head(Node **head, Node **tail, Node *n)
{
    if (*head == NULL) {
        *head = n;
        *tail = n;
    } else {
        n->next = *head;
        (*head)->prev = n;
        *head = n;
    }
}
void add_Node_after(Node *ref_Node, Node* newNode, Node** tail)
{
    if (ref_Node == NULL || newNode == NULL) return;
    
    newNode->next = ref_Node->next;
    newNode->prev = ref_Node;
    
    if (ref_Node->next != NULL) {
        ref_Node->next->prev = newNode;
    } else {
        *tail = newNode;
    }
    
    ref_Node->next = newNode;
}
void add_Node_at_tail(Node* n, Node** head, Node** tail)
{
    if (*head == NULL) {
        *head = n;
        *tail = n;
        return;
    }
    
    Node* temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = n;
    n->prev = temp;
    *tail = n;
}
void delete_Node(Node **head, Node **tail, Node *remove)
{
    if (*head == NULL || remove == NULL) return;

    if (*head == remove) {
        *head = remove->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        } else {
            *tail = NULL;
        }
    } else {
        if (remove == *tail) {
            *tail = remove->prev;
        }
        remove->prev->next = remove->next;
        if (remove->next != NULL) {
            remove->next->prev = remove->prev;
        }
    }
    free(remove);
}
void printListFromHead(Node *head)
{
    Node *temp = head;
    while(temp != NULL){
        printf("%d - ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}
void printListFromTail(Node* head)
{
    Node* temp = head;
    if (temp == NULL) {
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (temp != NULL) {
        printf("%d - ", temp->value);
        temp = temp->prev;
    }
    printf("NULL\n");
}
void free_list(Node* li)
{
    while(li){
        Node* temp = li;
        li = li->next;
        free(temp);
    }
}
//lista ligada simple/singly linked list, datos ligados por su direccion
/*typedef struct Node
{
    int value;
    struct Node *next;
} Node;

//declarando funciones de lista ligada simple
Node* create_Node(int val);
Node *add_Node_at_head(Node **head, Node *n);
void *add_Node_after_another(Node *ref_Node, Node* newNode);
void try_add_Node(Node* n, Node* into);
void delete_Node();
Node *find_Node(Node *head, int val);
void printList(Node *head);
void free_list(Node* li);
Node *list = NULL;

int main()
{
    try_add_Node(create_Node(10), list);
    try_add_Node(create_Node(11), list);
    try_add_Node(create_Node(12), list);
    printList(list);
    printf("nodo con valor: %d \n", find_Node(list, 12)->value);
    add_Node_after_another(list, create_Node(5));
    delete_Node(&list, find_Node(list, 12)); 
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
Node *add_Node_at_head(Node **head, Node *n)
{
    n->next = *head;
    *head = n;
    return n;
}
void *add_Node_after_another(Node *ref_Node, Node* newNode)
{
    newNode->next = ref_Node->next;
    ref_Node->next = newNode;
}
void try_add_Node(Node* n, Node* into) //tail and for first node
{
    if(into == NULL){
        into = n;
        return;
    }
    if(into->next == NULL){
        into->next = n;
    }
    else{
        try_add_Node(n, into->next);
    }
}
void delete_Node(Node **head, Node *remove)
{
    if (*head == remove){
        *head = remove->next;
        return;
    } else {
        Node* temp = *head;
        while(temp != NULL && temp->next != remove){
            temp = temp->next;
        }
        if (temp == NULL) return;
        temp->next = remove->next;
        remove->next=NULL;
        free(temp);
    }
    return;
}
Node *find_Node(Node *head, int val)
{
    Node *temp = head;
    while(temp != NULL){
        if(temp->value == val) return temp;
        temp = temp->next;
    }
    return NULL;
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
}*/