#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
int num_columns(void* pointer);
void num_rows(void* pointer);
int argument_checker(char *argv);
int index_columnName(char* nameArray, int exist_header, char* indexValue, int columns);
void max_data(void* pointer, int index_column);
void min_data(void* pointer, int index_column);
double helper(char *cur, int index_column);
double mean_data(void* pointer, int index_column);
char* find_data(void* pointer, int index_column, char* target);
int str_cmp(char* str1, char* str2);
bool flag_point;

int number_line = 0;

int main(int argc, char *argv[]) {

   	FILE *inFile = NULL;

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
		int checks = argument_checker(argv[i]);
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
 			continue;
 		}
 		if (argument_checker(argv[i]) == 3) {
 			 num_rows(pointer);
			 printf("%d\n",number_line);
 			continue;
 		}
 		int index_column;
 		if (argument_checker(argv[i]) == 4) {
 			i += 1;
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue, columns);
		 	
 			if (index_column == -1 || index_column >= columns) {
 				exit(EXIT_FAILURE);
 			}
			// for (int i = 0; i < 4; i++) {
			// 	printf("%c\n", *(char *)(pointer + i));
			// }
			printf("header_values at min %s\n",header_values);
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
			 printf("header_values at max %s\n",header_values);
 			max_data(pointer, index_column);
 			
 			continue;
 		}
 		if (argument_checker(argv[i]) == 6) {
			  
 			i += 1;
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
			
			printf("head array %s\n", header_values);
		 	index_column = index_columnName(header_values, header, indexValue, columns);
			 printf("%d\n",index_column);
 			if (index_column == -1 || index_column >= columns) {
 				exit(EXIT_FAILURE);
 			}
			printf("header_values at mean %s\n",header_values);
 			double mean = mean_data(pointer, index_column);
 			
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
 			//printf("%s\n", target);
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
	//printf("value %s\n", indexValue);
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
				printf("name array %s\n", nameArray);
				char *token = strtok(nameArray, ",");
				char str[50];
				memset(str, '\0', 50);
				strcpy(str, token);
				int len = strlen(str);
				
				while (token != NULL) {
					printf("token is %s.\n", token);
					printf("indexValue is %s.\n", indexValue);
					printf("value is %d.\n", value);
					if (value == columns - 1) len--;
					//printf("%d, %d\n", size_indexValue, len);
					if (strncmp(indexValue, str, size_indexValue) == 0 && size_indexValue == len) {
						//printf("value is229 %d.\n", value);
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

// -f haonan
int num_columns(void* pointer) {
	int quote = 0; 
	int count =0;
	//printf("target_len is %d\n", target_len);
	char *token = strtok(pointer, "\n");
	while ( token[0] != '\0' && token[0] != '\n' && token[0] != '\r'){
		if (quote%2==0 && token[0] == ','){
			count ++;
		}
		if (token[0] == '\"' ){
			quote +=1;
		}
		token ++;
	}
	return count;
}

// -r jiaqian
void num_rows(void* pointer) {
	char *token = strtok(pointer, "\n");

	while (token != NULL) {
         token = strtok(NULL, "\n");
		 number_line++;
	}
	printf("%d\n",number_line);
}

// max jingjing
void max_data(void* pointer, int index_column) {
	double max_value = helper((char *)pointer, index_column);
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
			if(value > max_value) max_value = value;
		}
		i ++;
	}
	if(flag_point == true)
		printf("%.2f\n", floorf(max_value * 100) / 100 );
	else 
		printf("%.0f\n", max_value);
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
	if(flag_point == true)
		printf("%.2f\n", floorf(min_value * 100) / 100);
	else 
		printf("%.0f\n", min_value);
}

double helper(char *cur, int index_column){
	bool flag = false;

	int i = 0;
	while(cur!= NULL && cur[0] != '\n' && i != index_column){
		if(cur[0] == '\0') exit(EXIT_FAILURE);
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
	
	int index_numbers = 0;
	flag_point = false;
	while( cur[0] != '\0' && cur[0] != '\r' && cur[0] != '\n' && cur[0] != ',' ){
		int a = cur[0]-'0';
		if(a>9){
			exit(EXIT_FAILURE);
		}
		else{
			if((a == -2 && flag_point == true ) || (a<0 && a!= -2)){
				exit(EXIT_FAILURE);
			}
			else if(a == -2) flag_point = true;
		}
		index_numbers++;
		cur ++;
	}
	cur -= index_numbers;
	if(flag_point == true){
		char *e;
		return strtod(cur, &e);
	}
	else return atoi(cur);
}

// mean haonan
double mean_data(void* pointer, int index_column) {
	printf("%s\n","Helllo");
    //get the data 
	double field_value = helper((char *)pointer, index_column);

	//initializa value
	int i = 1;
	int n = 0;
	double retVal = 0;

	//if there is no line
	if(number_line == 0) {
		num_rows(pointer);
	}

	//cal the average#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
int num_columns(void* pointer);
void num_rows(void* pointer);
int argument_checker(char *argv);
int index_columnName(char* nameArray, int exist_header, char* indexValue, int columns);
void max_data(void* pointer, int index_column);
void min_data(void* pointer, int index_column);
double helper(char *cur, int index_column);
double mean_data(void* pointer, int index_column);
char* find_data(void* pointer, int index_column, char* target);
int str_cmp(char* str1, char* str2);
bool flag_point;
bool flag_with_h = false;

int number_line = 0;

int main(int argc, char *argv[]) {

   	FILE *inFile = NULL;

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
		int checks = argument_checker(argv[i]);
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
 			continue;
 		}
 		if (argument_checker(argv[i]) == 3) {
 			 num_rows(pointer);
			 printf("%d\n",number_line);
 			continue;
 		}
 		int index_column;
 		if (argument_checker(argv[i]) == 4) {
 			i += 1;
			memset(indexValue, '\0', 50);
			strcpy(indexValue, argv[i]);
		 	index_column = index_columnName(header_values, header, indexValue, columns);
		 	
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
 			max_data(pointer, index_column);
 			
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
 			//printf("%s\n", target);
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

// -f haonan
int num_columns(void* pointer) {
	int quote = 0; 
	int count =0;
	//printf("target_len is %d\n", target_len);
	char *token = strtok(pointer, "\n");
	while ( token[0] != '\0' && token[0] != '\n' && token[0] != '\r'){
		if (quote%2==0 && token[0] == ','){
			count ++;
		}
		if (token[0] == '\"' ){
			quote +=1;
		}
		token ++;
	}
	return count;
}

// -r jiaqian
void num_rows(void* pointer) {
	char *token = strtok(pointer, "\n");

	while (token != NULL) {
         token = strtok(NULL, "\n");
		 number_line++;
	}
	//printf("%d\n",number_line);
}

// max jingjing
void max_data(void* pointer, int index_column) {
	bool flag = false;   //check if detect any numerical cell

	double max_value = helper((char *)pointer, index_column);
	
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
			if(flag_with_h ==  true){
				if(flag == true){
					if(value > max_value) max_value = value;
				}
				else{
					max_value = value;
					flag = true;
				}
			}
		}
		i ++;
	}
	if(flag){
		if(flag_point == true)
			printf("%.2f\n", floorf(max_value * 100) / 100);
		else 
			printf("%.0f\n", max_value);
	}
	exit(EXIT_FAILURE);
}

// min jiaqian
void min_data(void* pointer, int index_column) {

	bool flag = false;   //check if detect any numerical cell

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
			if(flag_with_h ==  true){
				if(flag == true){
					if(value < min_value) min_value = value;
				}
				else{
					min_value = value;
					flag = true;
				}
			}
		}
		i ++;
	}
	if(flag){
		if(flag_point == true)
			printf("%.2f\n", floorf(min_value * 100) / 100);
		else 
			printf("%.0f\n", min_value);
	}
	exit(EXIT_FAILURE);
}

double helper(char *cur, int index_column){
	bool flag = false;

	int i = 0;
	while(cur!= NULL && cur[0] != '\n' && i != index_column){
		if(cur[0] == '\0') exit(EXIT_FAILURE);
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
	
	int index_numbers = 0;
	flag_point = false;
	while( cur[0] != '\0' && cur[0] != '\r' && cur[0] != '\n' && cur[0] != ',' ){
		int a = cur[0]-'0';
		if(a>9){
			flag_with_h = false;
			return 0;
		}
		else{
			if((a == -2 && flag_point == true ) || (a<0 && a!= -2)){
				flag_with_h = false;
				return 0;
			}
			else if(a == -2) {
				flag_point = true;
				flag_with_h = true;
			}
			flag_with_h = true;
		}
		index_numbers++;
		cur ++;
	}
	cur -= index_numbers;
	if(flag_point == true){
		char *e;
		return strtod(cur, &e);
	}
	else return atoi(cur);
}

// mean haonan
double mean_data(void* pointer, int index_column) {
    //get the data 
	double field_value = helper((char *)pointer, index_column);

	//initializa value
	int i = 1;
	int n = 0;
	double retVal = 0;

	//if there is no line
	if(number_line == 0) {
		num_rows(pointer);
	}

	//cal the average
	while( i < number_line) {
		int j = 0;
        while(*(char *)pointer !='\n' && *(char *)pointer !='\0' ){
			pointer++;
		}
		pointer ++;
		n += 1;
		if(pointer != NULL){
			double value = helper((char *)pointer,index_column);
			field_value += value;
			retVal = field_value/n;
		}
		i ++;
	}
	printf("%.2f\n", floorf(retVal * 100) / 100);
	
	return retVal;
}

bool read_col(char *token ,int index_column,char* target){
	int quote = 0; 
	int count =0;
	int target_len = strlen(target);
	//printf("target_len is %d\n", target_len);
	while ( token[0] != '\0' && token[0] != '\n' && token[0] != '\r'){
		if (count == index_column ){
			int len = 0;
			char *ptr = token;
			//printf("%s\n", ptr);
			while (token[0] != '\0' && token[0] != '\n' && token[0] != '\r') {
				len++;
				token++;
			}
			//printf("len is %d\n", len);
			if (len == target_len) {
				for (int i = 0; i < len; i++) {
					if (target[i] != ptr[i]) {
						return false;
					}
				}
			} else {
				return false;
			}
		}
		if (quote%2==0 && token[0] == ','){
			count ++;
		}
		if (token[0] == '\"' ){
			quote +=1;
		}
		token ++;
	}
	return true;
}
// records jingjing
char* find_data(void* pointer, int index_column, char* target) {
	//printf("pointer is %s\n", (char *)pointer);
	char *token = strtok(pointer, "\n");
	
	while( token != NULL ){
		bool value = read_col(token, index_column, target);
		
		if (value) {
			printf("%s\n",token);
		}
		token = strtok(NULL, "\n");
	}
	return NULL;
}




	while( i < number_line) {
		int j = 0;
        while(*(char *)pointer !='\n' && *(char *)pointer !='\0' ){
			pointer++;
		}
		pointer ++;
		n += 1;
		if(pointer != NULL){
			double value = helper((char *)pointer,index_column);
			field_value += value;
			retVal = field_value/n;
		}
		i ++;
	}
	printf("%.2f\n", floorf(retVal * 100) / 100);
	
	return retVal;
}

bool read_col(char *token ,int index_column,char* target){
	int quote = 0; 
	int count =0;
	int target_len = strlen(target);
	//printf("target_len is %d\n", target_len);
	while ( token[0] != '\0' && token[0] != '\n' && token[0] != '\r'){
		if (count == index_column ){
			int len = 0;
			char *ptr = token;
			//printf("%s\n", ptr);
			while (token[0] != '\0' && token[0] != '\n' && token[0] != '\r') {
				len++;
				token++;
			}
			//printf("len is %d\n", len);
			if (len == target_len) {
				for (int i = 0; i < len; i++) {
					if (target[i] != ptr[i]) {
						return false;
					}
				}
			} else {
				return false;
			}
		}
		if (quote%2==0 && token[0] == ','){
			count ++;
		}
		if (token[0] == '\"' ){
			quote +=1;
		}
		token ++;
	}
	return true;
}
// records jingjing
char* find_data(void* pointer, int index_column, char* target) {
	//printf("pointer is %s\n", (char *)pointer);
	char *token = strtok(pointer, "\n");
	
	while( token != NULL ){
		bool value = read_col(token, index_column, target);
		
		if (value) {
			printf("%s\n",token);
		}
		token = strtok(NULL, "\n");
	}
	return NULL;
}



