#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



// Compare string and return true/false
bool nucleotide_compare(char,char);

// Open FASTA file and return ptr to contents 
void open_file(char*,char*);

// Find sile size
void file_sizer(long int*,char*);

// Write results to a file 
void write_file(char*,int*,int);

int main () {

	// file location 
	char filepath[] = "brca.fasta";
	char out_path[] = "brca.ppm";
	
	// Open file and return size 	
	long int file_size = 0;
	file_sizer(&file_size, filepath);

	// Allocate space and re-open (just allocate in file opener and return ptr?)
	char* seq = (char*) malloc(file_size);
	open_file(filepath,seq);
	
	int seq_size = strlen(seq);
	//printf("%i",seq_size);

	// Use malloc to reserve chunk of memory as 2d array
	int *matrix = (int *)malloc(seq_size * seq_size * sizeof(int)); 

	// Compare sequence to self
	int i, j;
	for (i = 0; i < seq_size; i++){
   		for (j = 0; j < seq_size; j++){
				//printf(" i:%c==j:%c ",seq[i],seq[j]);
				if(seq[i] == seq[j]){		
					*(matrix + i*seq_size + j) = 255;
				}
				else{
					*(matrix + i*seq_size + j) = 0;
				}
		}
	}

	// write to file
	write_file(out_path,matrix,seq_size);

	free(matrix);
	free(seq);
	
	return 0;
}

// Open FASTA file and add contents to seq memmory address 
void open_file(char *file_Path, char *seq){

	FILE *fptr;

	// Open a file in read mode
	fptr = fopen(file_Path, "r");

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
				*(seq+memoryloc+i) = seq_buffer[i];
				}

			}
		memoryloc += stringlen;
		}
	}
	
	fclose(fptr); 

}

// Find sile size
void file_sizer(long int* file_size,char* file_Path){

	FILE *fptr;

	 // Open a file in read mode
	fptr = fopen(file_Path, "r");

	// Get file size
	fseek(fptr, 0L, SEEK_END);
	*file_size = ftell(fptr);
	
	fclose(fptr); 

}

// Write results to a ppm file 
void write_file(char* file_name,int* matrix,int string_size){

	FILE *f = fopen(file_name, "wb");
	fprintf(f, "P6\n%i %i 255\n", string_size, string_size);

		// Create image file
	for (int i = 0; i < string_size; i++) {
   		for (int j = 0; j < string_size; j++) {
      		// 3 colours for future degree of similarity?
			fputc(*(matrix + i*string_size + j), f);   
        	fputc(*(matrix + i*string_size + j), f); 
        	fputc(*(matrix + i*string_size + j), f); 
   		}
	}
	
	fclose(f);
}