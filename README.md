# Instrucciones para crear una lista doblemente ligada en C

1. **Crear la estructura del nodo**
    ```c
    typedef struct Nodo {
         int dato;
         struct Nodo* siguiente;
         struct Nodo* anterior;
    } Nodo;
    ```

2. **Inicializar la lista**
    - Define un puntero para la cabeza y otro para la cola:
      ```c
      Nodo* cabeza = NULL;
      Nodo* cola = NULL;
      ```

3. **Agregar nodos**
    - Implementa funciones para insertar al inicio, al final o en una posición específica.

4. **Eliminar nodos**
    - Crea funciones para eliminar nodos por valor o posición.

5. **Recorrer la lista**
    - Implementa funciones para recorrer la lista hacia adelante y hacia atrás usando los punteros `siguiente` y `anterior`.

6. **Liberar memoria**
    - Asegúrate de liberar la memoria de cada nodo al finalizar el programa.

7. **Ejemplo de uso**
    - Incluye un `main()` donde se demuestre la inserción, eliminación y recorrido de la lista.

> Recuerda compilar tu programa con `gcc` y probar cada función para asegurar su correcto funcionamiento.