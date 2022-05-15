#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <stdbool.h>


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

void limpiarArreglo (int* arreglo, int tamano)
{
  for (int i =0; i < tamano; i++)
  {
    arreglo[i] = 0;
  }
}

int is_valid(Node* n)
{
  int histograma[10];
  limpiarArreglo(histograma, 10);

  //No se repitan números en las filas
  for (int i =0; i < 9; i++)
  {
    limpiarArreglo(histograma, 10);
    for (int j =0; j < 9; j++)
    {
      int numero = n->sudo[i][j];
      if (numero != 0)
      {
        if (histograma[numero] == 0)
        {
          histograma[numero] = 1;
        }
        else
        {
          //el numero no es valido
          return 0;
        }
      }
    }
  }

  //No se repitan números en las columnas
  for (int j =0; j < 9; j++)
  {
    limpiarArreglo(histograma, 10);
    for (int i =0; i < 9; i++)
    {
      int numero = n->sudo[i][j];
      if (numero != 0)
      {
        if (histograma[numero] == 0)
        {
          histograma[numero] = 1;
        }
        else
        {
          //el numero no es valido
          return 0;
        }
      }
    }
  }

  //No se repitan números en las submatrices de 3x3
  for (int k =0; k < 9; k++)
  {
    limpiarArreglo(histograma, 10);
    int p; 
    for(p=0;p<9;p++)
    {
      int i=3*(k/3) + (p/3);
      int j=3*(k%3) + (p%3);
      int numero = n->sudo[i][j];
      if (numero != 0)
      {
        if (histograma[numero] == 0)
        {
          histograma[numero] = 1;
        }
        else
        {
          //el numero no es valido
          return 0;
        }
      }
    }
  }
  return 1;
}

bool buscarCasillaVacia(Node* n, int* indiceI, int* indiceJ)
{
  //buscar indice primera casilla vacía
  for(int i=0; i < 9; i++)
  {
    for(int j=0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
      {
        *indiceI = i;
        *indiceJ = j;
        return true;
      }
    }
  }
  return false;
}

List* get_adj_nodes(Node* n){
    List* list=createList();
    //buscar indice primera casilla vacía
    int indiceI = -1;
    int indiceJ = -1;
    if (buscarCasillaVacia(n, &indiceI, &indiceJ) == false) return list;
    for (int i=1; i < 10; i++)
    {
      Node* nuevoNodo = copy(n);
      nuevoNodo->sudo[indiceI][indiceJ] = i;
      if (is_valid(nuevoNodo) == 1)
      {
        pushBack(list, nuevoNodo);
      }
    }
    return list;
}


int is_final(Node* n){
  int indiceI = 0;
  int indiceJ = 0;
  if (buscarCasillaVacia(n, &indiceI, &indiceJ) == false) return 1;
  return 0;
}

Node* DFS(Node* initial, int* cont){
  //1. Cree un stack S (pila) e inserte el nodo.
  Stack* stack = createStack();
  push(stack, initial);

  //2. Mientras el stack S no se encuentre vacío:
  while (is_empty(stack) != 0)
  {
    //a) Saque y elimine el primer nodo de S.
    Node* nodo = top(stack);
    pop(stack);

    // b) Verifique si corresponde a un estado final, si es así retorne el nodo.
    print_node(nodo);
    if (is_final(nodo) == 1)
    {
      return nodo;
    }
    else
    {
      //    c) Obtenga la lista de nodos adyacentes al nodo.
      List* nodosAdyacentes = get_adj_nodes(nodo);
      //    d) Agregue los nodos de la lista (uno por uno) al stack S.
      Node* nodoLista = first(nodosAdyacentes);
      while (nodoLista != NULL)
      {
        push(stack, nodoLista);
        nodoLista = next(nodosAdyacentes);
      }

    }
    *cont++;
  }
//    e) Libere la memoria usada por el nodo.
   
// 3. Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/