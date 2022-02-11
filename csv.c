#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_header(char* argv);

int main(int argc, char *argv[]) {

   	// wenhui
   	FILE *inFile = NULL;

  	// printf("argc: %d\n",argc);
    inFile = fopen(argv[argc - 1], "r");  // open file for reading
  	if (inFile == NULL) {
    	return 0;
 	}
    printf("file name: %s\n", argv[argc - 1]);

    //Read file and assign to pointer
 	fseek(inFile, 0, SEEK_END); 
 	int size_file = ftell(inFile);
 	printf("size of file is %d\n", size_file);
 	rewind(inFile); 
 	void* pointer = malloc(size_file);
 	fread(pointer, sizeof(char), size_file, inFile);


 	char first_argument[3] = {'-', 'h', '\0'};
 	int header = strcmp(module, argv);
 	

 	int len = 0;
 	while (*(char *)pointer != ',') {
 		len += 1;
 		pointer += 1;
 	}

 	char *str = malloc(len);
 	memcpy(str, pointer - len, len);
 	puts(str);

 	printf("%d\n", 1);

    return 1;
}



// -f haonao
int num_columns(void* pointer) {
	return 0;
}

// -r jiaqian
int num_rows() {
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



