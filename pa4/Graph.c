// Graph.c
// Eric Yup
// eyup@ucsc.edu
// pa4
// Graph ADT using a list representation

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj{
	List* adjList; 
	int* parent;
	int* distance;
	int* color;
	int size; //edges
	int order; //vertices
	int source;

}GraphObj; 

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->adjList = calloc(n+1, sizeof(List));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->color = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	for(int i = 1; i < n+1; i++){
		G->adjList[i] = newList();
		G->parent[i] = NIL;
		G->color[i] = WHITE;
		G->distance[i] = INF;
		
	}return G;
}

void freeGraph(Graph* pG){
   int i = 0;
   for(i=1; i<=(*pG)->order; i++){
      freeList(&(*pG)->adjList[i]);
   }
      free((*pG)->adjList);
      free((*pG)->parent);
      free((*pG)->distance);
      free((*pG)->color);
      free(*pG);
}

int getOrder(Graph G){
   return G->order;
}

int getSize(Graph G){
	return G->size;
}

int getSource(Graph G){
	return G->source;
}

int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
	   printf("Graph Error: calling getParent() with a invalid vertex\n");
       exit(1);
	}
	return G->parent[u]; 

}

int getDist(Graph G, int u){
	if(!(u <= 1 || u<= getOrder(G))){
	   printf("Graph Error: calling getDist() with a invalid vertex\n");
       exit(1);
	}
        return G->distance[u]; 
}

void getPath(List L, Graph G, int u){
	if(u < 1 || u > getOrder(G)){
	  printf("Graph Error: calling getParent() with a invalid vertex\n");
          exit(1);
	}
        if(u == getSource(G) ){     
           append(L, u);
        }
        else if(getParent(G,u) == NIL)
           append(L , NIL); 
        else{
		getPath(L, G, getParent(G, u));
		append(L, u);
        }
}

void makeNull(Graph G){
	for(int i=1; i<=getOrder(G); i++){
		clear(G->adjList[i]);
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	G->size = 0;
}

void addEdge(Graph G, int u, int v){
	//equivalent to two addArc() calls
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}

void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addArc() on NULL Graph reference \n");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		printf("Graph Error: calling addArc() on invalid vertex u \n");
		exit(1);
	}
	if(v<1 || v>getOrder(G)){
		printf("Graph Error: calling addArc() on invalid vertex v \n");
		exit(1);
	}

	List A = G->adjList[u];
	if(length(A) == 0) append(A, v);
	else if(length(A) > 0){
		moveBack(A);
		while ( index(A) !=-1 && v<get(A) ) movePrev(A);
		if(index(A) !=-1 && v == get(A)) return;
		if(index(A) == -1) prepend(A, v);
		else insertAfter(A, v);
	}

	G->size++;
}

void BFS(Graph G, int s){
	if(G == NULL){
		printf("Graph Error: calling BFS() on NULL Graph reference \n");
		exit(1);
	}
	if(s<1 || s>getOrder(G)){
		printf("Graph Error: calling BFS() on invalid source vertex s \n");
		exit(1);
	}

	//Using algorithm BFS in section 22.2 of textbook
	for(int i=1; i <=getOrder(G); i++){
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	G->source = s;

	List Queue = newList();
	append(Queue, s);
	while(length(Queue)>0){
		int u = front(Queue);
		deleteFront(Queue);
		List adj = G->adjList[u];
		for(moveFront(adj); index(adj)>=0; moveNext(adj)){
			int v = get(adj);
			if(G->color[v] == WHITE){
				G->color[v] = GRAY;
				G->distance[v] = (getDist(G, u)+1);
				G->parent[v] = u;
				append(Queue, v);
			}
		}
		G->color[u] = BLACK;
	}//end of algorithm

	freeList(&Queue);
}

void printGraph(FILE* out, Graph G){
	for (int i=1; i<=getOrder(G); i++){
		fprintf(out, "%d: ", i);//Printing vertex label
		printList(out, G->adjList[i]);//Printing adjacency List of vertex label
		fprintf(out, "\n");
	}
}