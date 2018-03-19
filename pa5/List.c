// List.c
// Eric Yup
// eyup@ucsc.edu
// pa5
// List ADT implementation

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
 int data;
 struct NodeObj* next;
 struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
 Node head;
 Node tail;
 Node cursor;
 int length;
} ListObj;
typedef ListObj* List;

// Constructors-Destructors ---------------------------------------------------

Node newNode(int data){
 Node N = malloc(sizeof(NodeObj));
 N->data = data;
 N->next = NULL;
 N->prev = NULL;
 return(N);
}

void freeNode(Node* pN){
 if( pN!=NULL && *pN!=NULL ){
  free(*pN);
  *pN = NULL;
}
}

List newList(void){
 List L;
 L = malloc(sizeof(ListObj));
 L->head = L->tail = L->cursor = NULL;
 L->length = 0;
 return(L);
}

void freeList(List* pL){
 if( pL!=NULL && *pL!=NULL ){
  if(length(*pL) > 0 )
   clear(*pL);
 free(*pL);
 *pL = NULL;
}
}

// Access functions -----------------------------------------------------------
int length(List L){
 if( L == NULL ){
  printf("List Error: calling length() on NULL List reference\n");
  exit(1);
}
int length = 0;
if (L->head == NULL){
  return length;
}
Node M = L->head;
while(M != NULL){
  length++;
  M = M->next;
}
return length;
}

int index(List L){
  if(L->cursor == NULL) return -1;
  Node temp = L->head;
  int ind = 0;
  while( temp != NULL ){
   if( temp->data == L->cursor->data) return ind;
   ind++;
   temp= temp->next;
 }
 return -1;

}


int front(List L){
  if( L==NULL ){
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
  }
  if( length(L) > 0) 
   return L->head->data;
 return -1;
}

int back(List L){
	if( L==NULL ){
    printf("List Error: calling back() on NULL List reference\n");
    exit(1);
  }
  if ( length(L) > 0) 
   return L->tail->data;
 return -1;
}

int get(List L){
	if(L == NULL){
    fprintf(stderr, "List Error: calling get() on NULL List reference\n");
      exit(0); //exit out of this stamtement if true  
    }
    if(length(L) > 0 && index(L) >= 0) return L->cursor->data;
    return -1;
  }

  int equals(List A, List B){
    if( length(A) != length(B)) return 0;
    Node tempA = A->head;
    Node tempB = B->head;

    while( tempA != NULL){
     if( tempA->data != tempB->data) return 0;
     tempA = tempA->next;
     tempB = tempB->next;
   }
   return 1;
 }

// Manipulation procedures ----------------------------------------------------
 void clear(List L){
  L->cursor = NULL;
  while(length(L)>0){
    deleteFront(L);
  }
  L->length = 0;
}

void moveFront(List L){
	if(length > 0)
		L->cursor = L->head;
}

void moveBack(List L){
	if(length > 0)
   L->cursor = L->tail;
}

void movePrev(List L){
  if(index(L) == -1) 
   return;
 if(index(L) == 0) 
  L->cursor = NULL;
if ( index(L) > 0 && index(L) <= length(L) -1)
 L->cursor = L->cursor->prev;
}

void moveNext(List L){
  if(index(L) == -1) 
   return;
 if(index(L) == length(L)-1) 
   L->cursor = NULL;
 if (index(L) >= 0 && index(L) <= length(L) -1) 
   L->cursor = L->cursor->next;
}

void prepend(List L, int data){
  Node temp = newNode(data);
  if(length(L) == 0){
   L->head = L->tail = temp;   
   return;
 }           
 temp->next = L->head;
 L->head->prev = temp;
 L->head = L->head->prev;
}

void append(List L, int data){
  Node temp = newNode(data);
  if(length(L) == 0){
   L->head = L->tail = temp;   
   return;
 }  
 temp->prev = L->tail;
 L->tail->next = temp;
 L->tail = L->tail->next;
}

void insertBefore(List L, int data){  
  if(length(L)>0 && index(L)>=0){
   if(index(L)== 0){
    prepend(L,data);
    return;
  }
  Node ins = newNode(data);
  ins->next = L->cursor;
  ins->prev = L->cursor->prev;
  L->cursor->prev->next = ins;
  L->cursor->prev = ins;
}
}

void insertAfter(List L, int data){
  if(length(L)>0 && index(L)>=0){ 
   if(index(L)== length(L)-1){
    append(L,data);
    return;
  }  
  Node ins = newNode(data);                      
  ins->next = L->cursor->next;  
  ins->prev = L->cursor;        
  L->cursor->next->prev = ins;
  L->cursor->next = ins;
}
}

void deleteFront(List L){
  if( length(L) < 0) return;
  if(index(L) == 0)
   L->cursor = NULL;
 if(length(L) == 1){
  Node delF = L->head;
  L->head = NULL;
  L->tail= NULL;
  freeNode(&delF);
  return;
}
Node delF = L->head;
L->head = L->head->next;
L->head->prev = NULL;
freeNode(&delF);
}

void deleteBack(List L){
  if( length(L) < 0) return;
  if(index(L) == length(L)-1)
   L->cursor = NULL;
 if( length(L) == 1){
         //clear(L);
   Node delB = L->tail;
   L->head = NULL;
   L->tail= NULL;
   freeNode(&delB);
         //delB = NULL;
   return;
 }
 Node delB = L->tail;
 L->tail = L->tail->prev;
 L->tail->next = NULL;
 freeNode(&delB);
}

void delete(List L){
 Node del = L->cursor;
 if(length(L)== 0){
  printf("List Error: calling delete() on empty list\n");
  exit(1);
}
if(L->head == L->cursor){
  deleteFront(L);
  return;
}
if(L->tail == L->cursor){
  deleteBack(L);
  return;
}
if(length(L)>0 && index(L)>=0){      
 if(del != NULL){
  L->cursor->prev->next = L->cursor->next;
  L->cursor->next->prev = L->cursor->prev;
  L->cursor = NULL;
}
}
freeNode(&del);
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
  Node traverse = L->head;
  while( traverse != NULL){
    fprintf(out,"%d ", traverse->data);
    traverse = traverse->next;
  }
}

List copyList(List L){
  List N = newList();
  Node traverse = L->head;

  while( traverse!=NULL ){
   append(N, traverse->data);
   traverse = traverse->next;
 }
 return N;
}
