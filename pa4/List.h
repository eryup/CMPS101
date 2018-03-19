// List.h
// Eric Yup
// eyup@ucsc.edu
// pa4
// Header file for List.c

#if !defined(_LIST_H_INCLUDE_)
#define _LIST_H_INCLUDE_
typedef struct ListObj* List;
typedef struct NodeObj* Node;
// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeNode(Node* pN);
void freeList(List* pL);
// Access functions -----------------------------------------------------------
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);
// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);
#endif	