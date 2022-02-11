#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

   	// wenhui
   	FILE *inFile = NULL;

  	// printf("argc: %d\n",argc);
    inFile = fopen(argv[argc - 1], "r");  // open file for reading
  	if (inFile == NULL) {
    	return 0;
 	}
    printf("file name: %s\n", argv[argc - 1]);
 	fseek(inFile, 0, SEEK_END); // put the postion at the end
 	int size_file = ftell(inFile);
 	printf("file size: %d\n", size_file); 
 	char buffer[100];
 	// fscanf(inFile, "%s", buffer);
 	// printf("%s", buffer);

 	while (fgets(buffer, sizeof(buffer), inFile)) {
 		char *token;
 		token = strtok(buffer, ",");
 		while (token != NULL) {
 			printf("%s", token);
 			token = strtok(NULL, ",");
 		}
 		printf("\n");
 	}

 	printf("%d\n", 1);

    return 1;
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



