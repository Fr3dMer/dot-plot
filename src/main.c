#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



// Open FASTA file and return ptr to contents 
char* import_file(char*, long int*);

// Write results to a file 
void write_file(char*,int*,int);

int main () {

	// file location 
	char filepath[] = "fasta/zincfinger.fasta";
	char out_path[] = "dot-plots/zincfinger.ppm";
	
	// Open file and return size 	
	long int str_len = 0;

	// Allocate space import sequence in char array, returning pointer to char array
	char* seq = import_file(filepath,&str_len);

	// Use malloc to reserve chunk of memory as 2d array
	int *matrix = (int *)malloc(str_len * str_len * sizeof(int)); 

	// Compare sequence to self
	int i, j;
	for (i = 0; i < str_len; i++){
   		for (j = 0; j < str_len; j++){

				if(seq[i] == seq[j]){		
					*(matrix + i*str_len + j) = 255;
				}
				else{
					*(matrix + i*str_len + j) = 0;
				}
		}
	}

	// write to file
	write_file(out_path,matrix,str_len);

	free(matrix);
	free(seq);
	
	return 0;
}

// Open FASTA file and add contents to seq memmory address 
char* import_file(char *file_Path, long int *str_len){

	FILE *fptr;

	// Open a file in read mode
	fptr = fopen(file_Path, "r");

	// Get file size by going to end and finding position
	fseek(fptr, 0L, SEEK_END);
	long int filesize = ftell(fptr);

	// Set file position back to begining
	fseek(fptr, 0L, SEEK_SET); //rewind(fptr);

	// Allocate space for sequence string
	char* seq = (char*) malloc(filesize);
	
	// seq buffer 
	char seq_buffer[150] = {};

	int stringlen = 0;
	int memoryloc = 0;

	// Read the content and store it inside myString
	while(fgets(seq_buffer, 150, fptr)){

		// Ignore any line that begins with > 
		if('>' != *(seq_buffer)){

			stringlen = strlen(seq_buffer);
			
			// append to seq and grab only nucleotides
			for(int i = 0; i < stringlen; i++){
				
				if(('A' == seq_buffer[i]) | ('T' == seq_buffer[i] )| ('C' == seq_buffer[i]) | ('G' == seq_buffer[i])){
				seq[memoryloc+i] = seq_buffer[i];
				
				}

			}
		memoryloc += stringlen;
		}
		
	}
	
	// Return length of actualy used char array
	*str_len = memoryloc;

	fclose(fptr); 

	return seq;
}


// Write results to a ppm file 
void write_file(char* file_name,int* matrix,int string_size){

	FILE *fptr = fopen(file_name, "wb");
	fprintf(fptr, "P6\n%i %i 255\n", string_size, string_size);

	// Create image file
	for (int i = 0; i < string_size; i++) {
		for (int j = 0; j < string_size; j++) {
			// 3 colours for future degree of similarity?
			fputc(*(matrix + i*string_size + j), fptr);   
			fputc(*(matrix + i*string_size + j), fptr); 
			fputc(*(matrix + i*string_size + j), fptr); 
		}
	}

	fclose(fptr);
}

