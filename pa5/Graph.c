// Graph.c
// Eric Yup
// eyup@ucsc.edu
// pa5
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
	int* discover;
	int* color;
	int* finish;
	int time;
	int size; //edges
	int order; //vertices
	
}GraphObj; 

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->adjList = calloc(n+1, sizeof(List));
	G->parent = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->color = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->time = 0;
	
	for(int i = 1; i < n+1; i++){
		G->adjList[i] = newList();
		G->parent[i] = NIL;
		G->color[i] = WHITE;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}return G;
}

void freeGraph(Graph* pG){
	int i = 0;
	for(i=1; i<=(*pG)->order; i++){
		freeList(&(*pG)->adjList[i]);
	}
	free((*pG)->adjList);
	free((*pG)->parent);
	free((*pG)->discover);
	free((*pG)->finish);
	free((*pG)->color);
	free(*pG);
}

int getOrder(Graph G){
	return G->order;
}

int getSize(Graph G){
	return G->size;
}

int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getParent() with a invalid vertex\n");
		exit(1);
	}
	return G->parent[u]; 

}

int getDiscover(Graph G, int u){
	if(!(u <= 1 || u<= getOrder(G))){
		printf("Graph Error: calling getDist() with a invalid vertex\n");
		exit(1);
	}
	return G->discover[u]; 
}

int getFinish(Graph G, int u){
	if(!(u <= 1 || u<= getOrder(G))){
		printf("Graph Error: calling getDist() with a invalid vertex\n");
		exit(1);
	}
	return G->finish[u];
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
// Algorithm given in class / textbook
void visit (Graph G, List S, int u){
	G->color[u] = GRAY;
	G->time++;
	G->discover[u] = G->time;
	List adj = G->adjList[u];
	for(moveFront(adj); index(adj)>=0; moveNext(adj)){
		int v = get(adj);
		if(G->color[v] == WHITE){
			G->parent[v] = u;
			visit(G, S, v);
		}
	}
	G->color[u] = BLACK;
	insertAfter(S, u);
	G->time++;
	G->finish[u] = G->time;

}
// Algorithm given in class / textbook
void DFS(Graph G, List S){
	if(length(S) != getOrder(G)){
		printf("Graph Error: calling DFS with a list of the wrong length: S->length != G->order \n");
		exit(1);
	}
	if(G == NULL){
		printf("Graph Error: calling DFS on a null graphReference\n");
		exit(1);
	}
	if(S == NULL){
		printf("Graph Error: calling DFS on a null ListReference\n");
		exit(1);
	}
	int i = 0;
	int x = 0;
	int order = getOrder(G);
	for(i = 1; i<=order;i++){
		G->color[i] = WHITE;
		G->parent[i] = NIL;
	}
	G->time = 0;
	moveBack(S);
	for(i = 1; i <= length(S); i++){
		x = front(S);
		if(G->color[x] == WHITE)
			visit(G, S, x);
		deleteFront(S);
	}
}

Graph transpose(Graph G){
	if(G == NULL){
		printf("Graph Error: calling transpose() on NULL Graph reference \n");
		exit(1);
	}

	Graph tranposeGraph = newGraph(getOrder(G));
	for(int i=1; i<=getOrder(G); i++){
		if(length(G->adjList[i])>0){
			//Travers3 adjList of vertex label
			for(moveFront(G->adjList[i]); index(G->adjList[i])!=-1; moveNext(G->adjList[i])){
				//add arc to new transpose of graph
				addArc(tranposeGraph, get(G->adjList[i]), i);
			}
		}
	}
	return tranposeGraph;
}

Graph copyGraph(Graph G){
	if(G == NULL){
		printf("Graph Error: calling copyGraph on a null graphReference\n");
		exit(1);
	}
	int order = getOrder(G);
	Graph Copy = newGraph(order);
	Copy->size = getSize(G);
	for(int i = 1; i <= order; i++){
		freeList(&(Copy->adjList[i]));
		Copy->adjList[i] = copyList(G->adjList[i]);
	}
	return Copy;
}

void printGraph(FILE* out, Graph G){
	for (int i=1; i<=getOrder(G); i++){
		fprintf(out, "%d: ", i);//Printing vertex label
		printList(out, G->adjList[i]);//Printing adjacency List of vertex label
		fprintf(out, "\n");
	}
}