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
	char filepath[] = "/home/freddie/Documents/Projects/dot-plot/brca.fasta";
	char out_path[] = "/home/freddie/Documents/Projects/dot-plot/brca.ppm";
	


	// Open file and return size 	
	long int file_size = 0;
	file_sizer(&file_size, filepath);


	// printf("\n%i\n",file_size);

	char* seq = (char*) malloc(file_size);

	//char* seq1 = (char*) malloc(file_size);
	open_file(filepath,seq);
	
	//int string_size = strlen(seq);
	int string_size = file_size;
	//printf("%d\n",strlen(seq));


	// Use malloc to reserve chunk of memory as 2d array
	int *matrix = (int *)malloc( string_size * string_size * sizeof(int)); 

	// Fill 2d array with comparison data
	int i, j;
	for (i = 0; i < string_size; i++){
   		for (j = 0; j < string_size; j++){
      		
				if(nucleotide_compare(seq[i],seq[j])){
				
					*(matrix + i*string_size + j) = 255;

					// printf("%c==%c  col:%d row:%d\n",seq[i],seq[j],i,j);

				}
				else{

					*(matrix + i*string_size + j) = 0;

				}
			
		}
	}

	// Create file for numpy
	for (i = 0; i < string_size; i++) {
   		for (j = 0; j < string_size; j++) {
      		//printf("%d ", *(matrix + i*string_size + j)); 
			
			

   		}
   		//printf("\n");
	}


	// printf("\n%s\n",seq);

	// write to file
	write_file(out_path,matrix,string_size);


	free(matrix);
	free(seq);

	
	
	return 0;

}




// Compare string and return true/false
bool nucleotide_compare(char row, char col){

	if (row == col){
		return true;

	}
	else{
		return false;
	}

	return false;
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


			// append to seq
			for(int i = 0; i < stringlen; i++){

				*(seq+memoryloc+i) = seq_buffer[i];


			}
		memoryloc += stringlen;
		}
	}
	
	// Close the file
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
	
	// Close the file
	fclose(fptr); 

}

// Write results to a file 
void write_file(char* file_name,int* matrix,int string_size){

	// int width = 255,height = 255;

	FILE *f = fopen(file_name, "wb");
	fprintf(f, "P6\n%i %i 255\n", string_size, string_size);

		// Create file for numpy
	for (int i = 0; i < string_size; i++) {
   		for (int j = 0; j < string_size; j++) {
      		//printf("%d ", *(matrix + i*string_size + j)); 
			fputc(*(matrix + i*string_size + j), f);   // 0 .. 255
        	fputc(*(matrix + i*string_size + j), f); // 0 .. 255
        	fputc(*(matrix + i*string_size + j), f);  // 0 .. 255
			
			

   		}
   		//printf("\n");
	}


	
	fclose(f);

}