// Lex.c
// Eric Yup
// eyup@ucsc.edu
// pa2
// arranges input text in alphabetical order 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160

int main (int argc, const char * argv[]) {
    FILE *in, *out;
	char line[MAX_LEN];
    
	//char* token;
	int nlines = 0;
    int count = 0;
    if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
    
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	while(fgets(line, MAX_LEN, in) != NULL){
        nlines	++;
    }
    

	char* A[nlines];
	rewind(in);
   //second while loop to iterate the count 
   while(fgets(line, MAX_LEN, in) != NULL){
        A[count] = malloc((strlen(line)) * sizeof(char *));
        strcpy(A[count], line);                       
        count++;                                      
   }

   List B = newList();
   if (count > 0) append(B, 0);
   for(int i = 1; i < nlines; i++){                                              
         moveFront(B);

        while(index(B) >= 0){

         if(strcmp(A[get(B)] ,  A[i]) > 0){
            insertBefore(B, i);
            break;
         }

         moveNext(B); 
      }
      if(index(B) < 0)
      		append(B,i);
   }

   moveFront(B);

   while(index(B)>=0){
      fprintf(out, "%s", A[get(B)]);
      moveNext(B);
   }
   // close files
   fclose(in);
   fclose(out);
   //free memory
   for(int i = 0; i < count; i++){         
      free(A[i]);
   }
   freeList(&B);
   return (0);
}