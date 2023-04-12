#include <stdio.h>
#include <stdlib.h>
#include <string.h>





typedef struct Grafos Vertex;
typedef struct fila Fila;
 struct Grafos{

  Vertex* prox;
  int key;
  
};

struct fila{
Vertex* primeiro;
int indice;
};





Vertex* vertice_cria(int key){
 Vertex* v;
  v = (Vertex *)malloc(sizeof(Vertex));
  v->key  = key ;

  v->prox = NULL;

  return v;
}

Fila* fila_cria(){

  Fila* origem = (Fila *)malloc(sizeof(Fila));
  origem->primeiro = NULL;
   origem->indice = 0;
  return origem;
}



int fila_insere(Fila* fila, Vertex* no){
  if(fila == NULL || no== NULL) return -1;



  if (fila->primeiro ==NULL){ 
   
    
    no->prox = NULL;
    fila->primeiro = no;  
    
    
  }
  else{
    Vertex* ultimo = fila->primeiro;
    while(ultimo->prox != NULL){
      ultimo = ultimo->prox;
    }
 ultimo->prox = no;
    no->prox = NULL;
   
  }
  return 1;
}


void fila_remove(Fila* fila){
  if(fila == NULL || fila->primeiro == NULL) return ;
  Vertex* aux;
 aux = fila->primeiro;
  fila->primeiro = fila->primeiro->prox;
  
  aux = NULL;
  free(aux);


}


Fila* concatena_filas(Fila* fila1, Fila* fila2, Fila* vetor[]){
  
 if( fila1->primeiro == NULL || fila2->primeiro == NULL) return NULL ;
  

  Vertex* aux3 = NULL;
  Vertex* aux2 = fila2->primeiro;
   
int i = fila1->indice;
  


   while(aux2!= NULL){
    vetor[aux2->key]->indice =  i;
    aux3 = aux2;
    aux2 = aux2->prox;
     
    fila_remove(fila2);
    fila_insere(fila1, aux3); 
   
   
    }
return fila1;
}

Vertex* MergeList(Vertex *v1, Vertex* v2){
 
  if(v1 == NULL ){
    return v2;
    
  }
  if(v2==  NULL) {
    return v1;
  }
  
  
  if(v1->key < v2->key ){
     
     v1->prox = MergeList(v1->prox, v2);
     return v1;
  }
  else{
   
    v2->prox = MergeList(v1, v2->prox);
    return v2;
  }
   
    
}

void splitList(Vertex *primeiro, Vertex** v1, Vertex**v2 ){
  if(primeiro == NULL || primeiro->prox == NULL){
    *v1 = primeiro;
    *v2 = NULL;
    return;
  }

  Vertex *slow, *fast;
  slow = primeiro;
  fast = primeiro->prox;


  while(fast != NULL){
    fast = fast->prox;
  
  if(fast!= NULL){
    slow = slow->prox;
    fast = fast->prox;
    
  }
}
*v1 = primeiro;
*v2 = slow->prox;
  
 //dividindo
 slow->prox = NULL; 
}

void MergeSort(Vertex** primeiro){
  Vertex* head = *primeiro;
  
  Vertex* v1, *v2;

  if(head == NULL || head->prox ==NULL) return;

  splitList(head, &v1, &v2);
  MergeSort(&v1);
  MergeSort(&v2);

  *primeiro = MergeList(v1, v2);
  
}



int main(int argc, char* argv[]){
int n;



 fscanf(stdin,"dl\nformat=edgelist1\nn=%d\ndata:\n", &n); 
 
  
  Fila* vetor[n];

for(int i = 1; i<=n; i++){

  Fila* novo = fila_cria();
  
 Vertex* no = vertice_cria(i);
  
  vetor[i] = novo;
  vetor[i]->indice = i;
  fila_insere(vetor[i], no);
 
}


int aux1 = 0, aux2 = 0;

 while(fscanf(stdin, "%d %d", &aux1, &aux2) == 2 ){
   

   Fila* fila1 = vetor[aux1], *fila2 = vetor[aux2];
     if(fila2->indice != aux2 && fila1->indice != aux1){
      int i = fila1->indice;

      fila1 =  vetor[i];
    
       int j = fila2->indice;
      fila2 =  vetor[j];

   }
       
   else if(fila2->indice != aux2){
     int j = fila2->indice;
    
      fila2 =  vetor[j];
   }
    

   else if(fila1->indice != aux1){
         int i = fila1->indice;
   
      fila1 =  vetor[i];
   }
  

  if(fila1 != fila2){
    

 if(fila1->primeiro->key < fila2->primeiro->key){
    
   fila1 =  concatena_filas(fila1, fila2,vetor);

  }  
  

  else {
   fila2 = concatena_filas(fila2, fila1, vetor);
    
  }  

  } 

}



for(int j = 1; j<=n; j++){

    if( vetor[j]->primeiro == NULL) continue;
  

   
   Vertex* aux = vetor[j]->primeiro;  
     
    MergeSort(&aux);

 
    while(aux->prox!=NULL){
     
      printf("%d ",aux->key);
      aux = aux->prox;
     
    }
     
    if(aux->prox==NULL){
      printf("%d",aux->key);
    }
    printf("\n");
  }
 
  return 0;
} 

