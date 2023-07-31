#include <stdio.h> 
#include <stdlib.h>

// Create matrix and return it? 
int* matrix_maker(int);

// Compare string and return true/false
bool nucleotide_compare(char,char);


int main () {
	
	int string_size = 5;

	int* final_matrix = matrix_maker(string_size);

	for (int i = 0; i< string_size*string_size; i++){

		printf("%d\n",*(final_matrix+i));

			for (int a = 0; a< string_size; a++){


				//printf("%p\n",&final_matrix[i][a]);
			}	

	}	

	free(final_matrix);

	return 0;

}




int* matrix_maker(int string_size){

	// Initialise empty array of size n
	int array[] ={1,2,3,4,6};
	int matrix[string_size] = {};

	// Create square matrix using size  

	int row = string_size, col = string_size, i, j, count;
 
    int (*arr)[col] = calloc(row, sizeof *arr);
	
	// Code to make sure it works
    count = 0;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            arr[i][j] = ++count;
 
    for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
            printf("%d ", arr[i][j]);
		}
		printf("\n");
	}


	return *arr;
}



// Compare string and return true/false
bool nucleotide_compare(char row, char col){

	if (char == 






	return false
}