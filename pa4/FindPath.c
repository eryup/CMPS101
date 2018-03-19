// FindPath.c
// Eric Yup
// eyup@ucsc.edu
// pa4
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
	Graph G = newGraph(atoi(line));

	//Add edges to graph
	while(fgets(line, MAX_LEN, in) != NULL){
		sscanf(line, "%d %d", &vi, &vt);
		if(vi==0 && vt==0) break;
		addEdge(G, vi, vt);
	}
	printGraph(out, G);

	while( fgets(line, MAX_LEN, in) != NULL){
		sscanf(line, "%d %d", &vi, &vt);
		if(vi==0 && vt==0) break;

		BFS(G, vi);//Running BFS
		fprintf(out, "\nThe distance from %d to %d is ", vi, vt);
		if(getDist(G, vt) == INF) fprintf(out, "infinity\n");
		else fprintf(out, "%d\n", getDist(G, vt));

		List L = newList();
		getPath(L, G, vt);
		if(front(L) == NIL) fprintf(out, "No %d-%d path exists\n", vi, vt);
		else {
			fprintf(out, "A shortest %d-%d path is: ", vi, vt);
			printList(out, L);
			fprintf(out, "\n");
		}
		freeList(&L);
	}

	fclose(in);
	fclose(out);
	freeGraph(&G);

	return(0);
}