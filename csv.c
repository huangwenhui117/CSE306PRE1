#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int num_columns(void* pointer);
int num_rows(void* pointer);
int argument_checker(char *argv);
int index_columnName(char* nameArray, int exist_header, char* indexValue, int columns);
int max_data(void* pointer, int index_column);
void min_data(void* pointer, int index_column);
double helper(char *cur, int index_column);
double mean_data(void* pointer, int index_column);
char* find_data(void* pointer, int index_column, char* target);
int str_cmp(char* str1, char* str2);

int number_line = 0;

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
 	//int columns = num_columns(pointer);
 	int columns = 8;
 	char *header_values;
 	char indexValue[50];
 	for (int i = 1; i < argc - 1; i++) {
 		printf("%d, %s\n", i, argv[i]);
		int checks = argument_checker(argv[i]);
		printf("check is: %d\n", checks);
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
		 	header_values = malloc(len);
		 	strcpy(header_values, (pointer - len));
		 	pointer += 1;
 			continue;
 		}
 		if (argument_checker(argv[i]) == 2) {
 			printf("%d\n", columns);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 3) {
 			int rows = num_rows(pointer);
 			printf("rows: %d\n", rows);
 			continue;
 		}
 		int index_column;
 		if (argument_checker(argv[i]) == 4) {
 			i += 1;
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue, columns);
		 	printf("index_column is %d\n", index_column);
 			if (index_column == -1 || index_column >= columns) {
 				exit(EXIT_FAILURE);
 			}
			// for (int i = 0; i < 4; i++) {
			// 	printf("%c\n", *(char *)(pointer + i));
			// }
 			min_data(pointer, index_column);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 5) {
 			i += 1;
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue, columns);
 			if (index_column == -1 || index_column >= columns) {
 				exit(EXIT_FAILURE);
 			}
 			int max = max_data(pointer, index_column);
 			printf("%d\n", max);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 6) {
 			i += 1;
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue, columns);
 			if (index_column == -1 || index_column >= columns) {
 				exit(EXIT_FAILURE);
 			}

 			double mean = mean_data(pointer, index_column);
 			printf("%f\n", mean);
 			continue;
 		}
 		if (argument_checker(argv[i]) == 7) {
 			i += 1;
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue, columns);
 			if (index_column == -1 || index_column >= columns) {
 				exit(EXIT_FAILURE);
 			}
 			i += 1;
 			char* target = find_data(pointer, index_column, argv[i]);
 			printf("%s\n", target);
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

int index_columnName(char* nameArray, int exist_header, char* indexValue, int columns) { 
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
				int len = strlen(str);
				
				while (token != NULL) {
					//printf("token is %s.\n", token);
					//printf("indexValue is %s.\n", indexValue);
					//printf("value is %d.\n", value);
					if (value == columns - 1) len--;
					//printf("%d, %d\n", size_indexValue, len);
					if (strncmp(indexValue, str, size_indexValue) == 0 && size_indexValue == len) {
						return value;
					}
					memset(str, '\0', 50);
					token = strtok(NULL, ",");
					if (token != NULL) {
						strcpy(str, token);
					}
					len = strlen(str);
					value++;
				}
			}
		}
	}
	return -1;
} 

// Ref_Datee Ref_Date

// -f haonao
int num_columns(void* pointer) {
	return 0;
}

// -r jiaqian
int num_rows(void* pointer) {
	char *token = strtok(pointer, "\n");

	while (token != NULL) {
         token = strtok(NULL, "\n");
		 number_line++;
	}
	return number_line;
}

// max jingjing
int max_data(void* pointer, int index_column) {
	int max_value = helper((char *)pointer, index_column);
	int i = -32768;
	if(number_line == 0) num_rows(pointer);

	while( i< number_line) {
		int j = 0;
        while(*(char *)pointer !='\n' && *(char *)pointer !='\0' ){
			pointer++;
		}
		pointer ++;
		if(pointer !=NULL){
			double value = helper((char *)pointer,index_column);
			if(value > max_value) max_value = value;
		}
		i ++;
	}
	//printf("max_value: %d", max_value);
	return max_value;
}

// min jiaqian
void min_data(void* pointer, int index_column) {
	
	double min_value = helper((char *)pointer, index_column);
	int i = 1;
	if(number_line == 0) num_rows(pointer);

	while( i< number_line) {
		int j = 0;
        while(*(char *)pointer !='\n' && *(char *)pointer !='\0' ){
			pointer++;
		}
		pointer ++;
		if(pointer !=NULL){
			double value = helper((char *)pointer,index_column);
			if(value < min_value) min_value = value;
		}
		i ++;
	}
	printf("min_value: %.3f.", min_value);
}

double helper(char *cur, int index_column){
	bool flag = false;

	int i = 0;
	while(cur!= NULL && cur[0] != '\n' && i != index_column){
		if(cur[0] == '\0') return 0;
		if(cur[0] == '\"'){
			
			if(flag == true) {
				flag = false;
			}
			else flag = true;
		}
		else if(cur[0] == ','){
			if(flag != true) i++;
		} 
		cur ++;
	}
	char *e;
	return strtod(cur, &e);
}

// mean haonan
double mean_data(void* pointer, int index_column) {
	return 0.0;
}

// records jingjing
char* find_data(void* pointer, int index_column, char* target) {
	return NULL;
}



