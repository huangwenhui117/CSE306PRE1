#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num_columns(void* pointer);
int num_rows(void* pointer);
int argument_checker(char *argv);
int index_columnName(char* pointer, int exist_header, char* indexValue);
int max_data(void* pointer, int index_column);
int min_data(void* pointer, int index_column);
double mean_data(void* pointer, int index_column);
char* find_data(void* pointer, int index_column, char* target);
int str_cmp(char* str1, char* str2);

int main(int argc, char *argv[]) {

   	FILE *inFile = NULL;

  	printf("argc: %d\n",argc);
    inFile = fopen(argv[argc - 1], "r");  // open file for reading
  	if (inFile == NULL) {
    	return 0;
 	}

    //Read file and assign to pointer
 	fseek(inFile, 0, SEEK_END); 
 	int size_file = ftell(inFile);
 	rewind(inFile); 
 	void* pointer = malloc(size_file);
 	fread(pointer, sizeof(char), size_file, inFile);

 	/**
 	 * -h
 	 * if header != 0, not include header;
 	 * else, include header;
 	 **/
 	int header = 1;
 	int columns = num_columns(pointer);
 	char *header_values;
 	for (int i = 1; i < argc - 1; i++) {
 		if (argument_checker(argv[i]) == 0) {
 			exit(EXIT_FAILURE);
 		}
 		if (argument_checker(argv[i]) == 1) {
 			header = 0;
 			int len = 0;
		 	while (*(char *)pointer != '\n') {
		 		len += 1;
		 		pointer += 1;
		 	}
		 	*(char *)pointer = '\0';
		 	header_values = malloc(len + 1);
		 	strcpy(header_values, (pointer - len));
		 	pointer += 1;
		 	// test
		 	char indexValue[50];
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i + 1]);
		 	int i = index_columnName(header_values, 0, indexValue);
		 	printf("index is %d\n", i);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 2) {
 			printf("%d", columns);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 3) {
 			int rows = num_rows(pointer);
 			printf("%d", rows);
 			continue;
 		}
 		int index_column;
 		if (argument_checker(argv[i]) == 4) {
 			i += 1;
 			char indexValue[50];
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue);
 			if (index_column == -1) {
 				exit(EXIT_FAILURE);
 			}
 			int max = max_data(pointer, index_column);
 			printf("%d", max);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 5) {
 			i += 1;
 			char indexValue[50];
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue);
 			if (index_column == -1) {
 				exit(EXIT_FAILURE);
 			}
 			int min = min_data(pointer, index_column);
 			printf("%d", min);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 6) {
 			i += 1;
 			char indexValue[50];
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue);
 			if (index_column == -1) {
 				exit(EXIT_FAILURE);
 			}
 			double mean = mean_data(pointer, index_column);
 			printf("%f", mean);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 7) {
 			i += 1;
 			char indexValue[50];
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue);
 			if (index_column == -1) {
 				exit(EXIT_FAILURE);
 			}
 			i += 1;
 			char* target = find_data(pointer, index_column, argv[i]);
 			printf("%s", target);
 		}
 	}

 	// int len = 0;
 	// while (*(char *)pointer != ',') {
 	// 	len += 1;
 	// 	pointer += 1;
 	// }

 	// char *str = malloc(len);
 	// memcpy(str, pointer - len, len);
 	// puts(str);
 	

    exit(EXIT_SUCCESS);
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
	if (strcmp(argument, argv) == 0) {
		return 1;
	}
	argument[1] = 'f';
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

int index_columnName(char* nameArray, int exist_header, char* indexValue) { 
	int size_indexValue = strlen(indexValue);
	if (size_indexValue == 1 && *indexValue == '0') {
		return 0;
	} else {
		int value = atoi(indexValue);
		if (value > 0) {
			return value;
		} else if (value < 0) {
			return -1;
		} else {
			if (exist_header == 1) // header doesn't exist.
				return -1;
			else {
				char *token = strtok(nameArray, ",");
				char str[50];
				memset(str, '\0', 50);
				strcpy(str, token);
				// here has a bug. When the index value is the last column name.
				// and it doesn't return correct index value
				while (token != NULL) {
					// printf("str is %s\n", str);
					// printf("indexValue is %s\n", indexValue);
					// printf("%d\n", strcmp(str, indexValue));
					if (strcmp(str, indexValue) == 0) {
						return value;
					}
					memset(str, '\0', 50);
					token = strtok(NULL, ",");
					if (token != NULL) strcpy(str, token);
					value++;
					// printf("%d\n", value);
				}
			}
		}
	}
	return -1;
} 



// -f haonao
int num_columns(void* pointer) {
	return 0;
}

// -r jiaqian
int num_rows(void* pointer) {
	return 0;
}

// max jingjing
int max_data(void* pointer, int index_column) {
	return 0;
}

// min jiaqian
int min_data(void* pointer, int index_column) {
	return 0;
}

// mean haonan
double mean_data(void* pointer, int index_column) {
	return 0.0;
}

// records jingjing
char* find_data(void* pointer, int index_column, char* target) {
	return NULL;
}



