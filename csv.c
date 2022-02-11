#include <stdio.h>

int main(int argc, char *argv[]) {

   	// wenhui
   	FILE * inFile = NULL;

  	printf("argc: %d\n",argc);
    inFile = fopen(argv[argc - 1], "r");  // open file for reading
  	if (inFile == NULL) {
    	exit(EXIT_FAILURE);
 	}
 
    return 0;
}



// -f haonao
int num_columns() {
	return 0;
}

// -r jiaqian
int num_rows() {
	return 0;
}

// -h jingjing
int check_header() {
	return 0;
}

// max wenhui
int max_data() {
	return 0;
}

// min jiaqian
int min_data() {
	return 0;
}

// mean haonan
int mean_data() {
	return 0;
}

// records jingjing
int find_data() {
	return 0;
}



