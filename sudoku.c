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

int is_valid(Node* n){

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
    printf("indice i = %d, indice j = %d\n", indiceI, indiceJ);
    for (int i=1; i < 10; i++)
    {
      Node* nuevoNodo = copy(n);
      nuevoNodo->sudo[indiceI][indiceJ] = i;
      pushBack(list, nuevoNodo);
    }
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
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