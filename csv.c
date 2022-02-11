#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num_columns(void* pointer);
int num_rows(void* pointer);
int argument_checker(char *argv);

int main(int argc, char *argv[]) {

   	FILE *inFile = NULL;

  	printf("argc: %d\n",argc);
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

 	/**
 	 * -h
 	 * if header != 0, not include header;
 	 * else, not include header;
 	 **/
 	int header = 1;
 	for (int i = 1; i < argc - 1; i++) {
 		if () {

 		}
 	}
 	if (header != 0) {
 		first_argument[1] = 'f';
 		// call -f
 		if (strcmp(first_argument, argv[0]) == 0) {
 			int columns = num_columns(pointer);
 		}
 		// call -r
 		first_argument[1] = 'r';
 		if (strcmp(first_argument, argv[0]) == 0) {
 			int rows = num_rows(pointer);
 			if (header == 0) {
 				printf("%d", rows - 1);
 			} else {
 				printf("%d", rows);
 			}
 		}
 	}
 	

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

/** 
 * check and match the argument
 * if argument is h, return 1;
 * if argument is f, return 2;
 * if argument is r, return 3;
 * if argument is min, return 4;
 * if argument is max, return 5;
 * if argument is mean, return 6;
 * if argument is records, return 7;
 * Otherwise, not match all of these arguments, return 0;
 **/ 
int argument_checker(char *argv) {
	char argument[9] = {'-','h','\0','\0','\0','\0','\0','\0','\0'};
	// check if -h
	if (strcmp(argument, argv) == 0) {
		return 1;
	}
	argument[1] = 'f';
	// check if -f
	if (strcmp(argument, argv) == 0) {
		return 2;
	}
	argument[1] = 'r';
	if (strcmp(argument, argv) == 0) {
		return 3;
	}
	argument[1] = 'm';
	argument[2] = 'i';
	argument[3] = 'n';
	if (strcmp(argument, argv) == 0) {
		return 4;
	}
	argument[2] = 'a';
	argument[3] = 'x';
	if (strcmp(argument, argv) == 0) {
		return 5;
	}
	argument[2] = 'e';
	argument[3] = 'a';
	argument[4] = 'n';
	if (strcmp(argument, argv) == 0) {
		return 6;
	}
	argument[1] = 'r';
	argument[2] = 'e';
	argument[3] = 'c';
	argument[4] = 'o';
	argument[5] = 'r';
	argument[6] = 'd';
	argument[7] = 's';
	if (strcmp(argument, argv) == 0) {
		return 7;
	}
	return 0;
}

// -f haonao
int num_columns(void* pointer) {
	return 0;
}

// -r jiaqian
int num_rows(void* pointer) {
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



