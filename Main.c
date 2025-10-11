#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
     int dato;
     struct node *sig;
     struct node *ant;
} node;

node *cola = NULL;
node *cabeza = NULL;

node *crear_nodo(int n)
{
     node *nuevoNodo = (node *)malloc(sizeof(node));
     nuevoNodo->dato = n;
     nuevoNodo->sig = NULL;
     nuevoNodo->ant = NULL;
     return nuevoNodo;
}

void agregar_nodo_cola(node *n)
{
     if (!cola && !cabeza) // La cola y cabeza apuntan al nodo si la lista está vacía
     {
          cola = n;
          cabeza = n;
          return;
     }
     else // Si la lista tiene 1+ nodos, el nodo se crea después del último nodo y la cola apunta a él
     {
          cola->sig = n;
          n->ant = cola;
          cola = n;
          return;
     }
}

void agregar_nodo_cabeza(node *n)
{
     if (!cola && !cabeza) // La cola y cabeza apuntan al nodo si la lista está vacía
     {
          cola = n;
          cabeza = n;
          return;
     }
     else // Si la lista tiene 1+ nodos, el nodo se crea antes del primer nodo y la cabeza apunta a él
     {
          cabeza->ant = n;
          n->sig = cabeza;
          cabeza = n;
          return;
     }
}

void agregar_nodo_pos(node *n, int pos)
{
     if (pos < 1) // Error si la posición es 0 o negativo
     {
          printf("Err: La posición debe de ser <= 1");
          return;
     }
     else if (pos == 1) // Agregar a la cabeza si es la primera posición
     {
          agregar_nodo_cabeza(n);
          return;
     }
     else // Crear un apuntador temporal y desplazarse por la lista hasta encontrar la posición
     {
          // Se recorre por la lista hasta llegar a la posición
          node *posNodo = cabeza;
          for (int i = 1; i < pos; i++)
          {
               if (posNodo->sig == NULL) // Si se encuentra en el último nodo
               {
                    if (i < pos - 1) // Si la posicón es mayor al total de nodos
                    {
                         printf("Err: La posición es mayor a la cantidad de nodos");
                    }
                    else // Agregar a la cola si es la última posición
                    {
                         agregar_nodo_cola(n);
                    }
                    return;
               }
               posNodo = posNodo->sig;
          }
          // Retroceder un nodo, añadir el nuevo después de el y enlazarlo por ambos lados
          posNodo = posNodo->ant;
          n->sig = posNodo->sig;
          posNodo->sig = n;
          n->ant = posNodo;
          n->sig->ant = n;
          return;
     }
}

void borrar_nodo(node *n)
{
     if (n->sig != NULL) // Si no se encuentra en la cola
     {
          n->sig->ant = n->ant;
     }
     else
     {
          cola = n->ant;
     }
     if (n->ant != NULL) // Si no se encuentra en la cabeza
     {
          n->ant->sig = n->sig;
     }
     else
     {
          cabeza = n->sig;
     }
     return;
}

void borrar_nodo_val(int val)
{
     if (!cola && !cabeza) // Si la cola y la cabeza no apuntan a ningun nodo
     {
          printf("La lista ya está vacía");
          return;
     }
     // Se desplaza por la lista hasta encontrar el nodo con el valor
     node *temp = cabeza;
     while (temp)
     {
          if (temp->dato == val)
          {
               borrar_nodo(temp);
               return;
          }
          temp = temp->sig;
     }
     printf("No existe un nodo con ese valor");
     return;
}

void borrar_nodo_pos(int pos)
{
     // Se desplaza por la lista hasta llegar a la posición
     node *temp = cabeza;
     for (int i = 1; i < pos; i++)
     {
          if (temp->sig == NULL && i < pos - 1)
          {
               printf("Err: La posición es mayor a la cantidad de nodos");
               return;
          }
          temp = temp->sig;
     }
     borrar_nodo(temp);
     free(temp);
     return;
}

void recorrer_adelante()
{
     // Se desplaza por la lista hacia la derecha y se imprime cada dato de nodo
     node *temp = cabeza;
     while (temp)
     {
          printf("%d ", temp->dato);
          temp = temp->sig;
     }
     printf("\n");
}

void recorrer_atras()
{
     // Se desplaza por la lista hacia la izquierda y se imprime cada dato de nodo
     node *temp = cola;
     while (temp)
     {
          printf("%d ", temp->dato);
          temp = temp->ant;
     }
     printf("\n");
}

void liberar_nodos()
{
     cola = NULL;
     while (cabeza)
     {
          node *temp = cabeza;
          cabeza = cabeza->sig;
          free(temp);
     }
}

int main()
{
     printf("Agregar a cola (1): ");
     agregar_nodo_cola(crear_nodo(1)); // 1
     recorrer_adelante();

     printf("Agregar a cabeza (2): ");
     agregar_nodo_cabeza(crear_nodo(2)); // 2 1
     recorrer_adelante();

     printf("Agregar a cola (3): ");
     agregar_nodo_cola(crear_nodo(3)); // 2 1 3
     recorrer_adelante();

     printf("Agregar a posición (4, 2): ");
     agregar_nodo_pos(crear_nodo(4), 2); // 2 4 1 3
     recorrer_adelante();

     printf("Agregar a posición (5, 4): ");
     agregar_nodo_pos(crear_nodo(5), 4); // 2 4 1 5 3
     recorrer_adelante();

     printf("Borrar por valor (3): ");
     borrar_nodo_val(3); // 2 4 1 5
     recorrer_adelante();

     printf("Borrar por posición (2): ");
     borrar_nodo_pos(2); // 2 1 5
     recorrer_adelante();

     printf("Recorrido hacia atras: ");
     recorrer_atras(); // 5 1 2

     liberar_nodos();
}