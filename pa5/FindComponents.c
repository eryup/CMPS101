// FindComponents.c
// Eric Yup
// eyup@ucsc.edu
// pa5
// Client file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 200

int main(int argc, char * argv[]) {

	char line[MAX_LEN];
	
	int vi = 0;
	int vt = 0;

	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	fgets(line, MAX_LEN, in);
	int order = atoi(line);
	Graph G = newGraph(order);
	List S = newList();
	for(int i=1; i<=order; i++)
		append(S, i);

	//Add edges to graph
	while(fgets(line, MAX_LEN, in) != NULL){
		sscanf(line, "%d %d", &vi, &vt);
		if(vi==0 && vt==0) break;
		addArc(G, vi, vt);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");

	DFS(G,S);
	Graph T = transpose(G);
	DFS(T,S);

	int nSCC = 0;

	for(moveBack(S); index(S)!=-1; movePrev(S))
		if(getParent(T, get(S)) == NIL) nSCC++;
	
	fprintf(out, "G contains %d strongly connected components:\n", nSCC);

	List* SCC = calloc(nSCC+1, sizeof(List));
	for(int i = 1; i <= nSCC; i++)
		SCC[i] = newList();
	int iSCC = 1;
	for(moveBack(S); index(S)!=-1; movePrev(S)){
		prepend(SCC[iSCC], get(S));
		if(getParent(T, get(S)) == NIL){
			fprintf(out, "Component %d: ", iSCC);
			printList(out, SCC[iSCC]);
			fprintf(out, "\n");
			iSCC++;
		}
	}

	fclose(in);
	fclose(out);
	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);
	for(int i=1; i<=nSCC; i++) freeList(&SCC[i]);
		free(&(*SCC));
	return(0);
}