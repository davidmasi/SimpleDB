#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 100

typedef struct programmingLanguage {
	int id;
	char* language;
	int year;
	char* creator;
	char* paradigm;
	double popularityIndex;
	int isDeleted; // internal field, not accessible to user
} language_t;

// step 1: create structs for the other two tables: operatingSystems
// and databases
// include internal field
typedef struct operatingSystem {
	int id;
	char* name;
	int year;
	char* developer;
	char* kernelType;
	int isDeleted;
} system_t;

typedef struct database {
	int id;
	char* name;
	int year;
	char* type;
	char* developer;
	int isDeleted;
} database_t;

// step 2: create typedef struct for storing metadata
typedef struct metadata {
	int count;
	int nextIndex;
	int maxCount;
} metadata_t;

// step 3: declare the two other arrays of structs
// programmingLanguages has been defined for you already
// TODO: add operatingSystems and databases
language_t* programmingLanguages;
system_t* operatingSystems;
database_t* databases;

// step 4: declare 3 metadata structs, one for each table
metadata_t programmingLang;
metadata_t operatingSys;
metadata_t datab;
// step 5: jump to L167

// This function takes the user's input and splits it by spaces
// into an array of strings, ignoring spaces that are wrapped in quotes
// There is no need to modify this code.
// You do not need to understand this code
// but you are welcome to research its application
void splitInput(char* input, char** args, int* arg_count) {
    *arg_count = 0;
    int in_quotes = 0; // Flag to track whether we are inside quotes
    char* token_start = input;

    for (char* ptr = input; *ptr != '\0'; ptr++) {
        if (*ptr == '"') {
            in_quotes = !in_quotes; // Toggle the in_quotes flag when a quote is encountered
        }

        if ((*ptr == ' ' || *ptr == '\n') && !in_quotes) {
            // If not inside quotes and a space or newline is found, consider it as a separator
            *ptr = '\0'; // Replace space or newline with null terminator
            args[(*arg_count)++] = token_start;
            token_start = ptr + 1; // Start of the next token
        }
    }

    // Add the last token (if any) after the loop
    if (*token_start != '\0') {
        // Remove leading and trailing double quotes if they exist
        if (token_start[0] == '"' && token_start[strlen(token_start) - 1] == '"') {
            token_start[strlen(token_start) - 1] = '\0'; // Remove trailing quote
            args[(*arg_count)++] = token_start + 1; // Remove leading quote
        } else {
            args[(*arg_count)++] = token_start;
        }
    }
    args[*arg_count] = NULL;
}

// step 7: implement setup function
// this function is responsible for dynamically allocating the
// particular table. Use the tables declared on L27.
void setup(char* table, int numRows) {
    if (strcmp(table, "programmingLanguages") == 0) {
        programmingLang.maxCount = numRows;
        programmingLanguages = (language_t *)malloc(numRows * sizeof(language_t));
    } else if (strcmp(table, "operatingSystems") == 0) {
        operatingSys.maxCount = numRows;
        operatingSystems = (system_t *)malloc(numRows * sizeof(system_t));
    } else if (strcmp(table, "databases") == 0) {
        datab.maxCount = numRows;
        databases = (database_t *)malloc(numRows * sizeof(database_t));
    }
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("setup complete\n");
}

// step 8: implement insert function
// this function is responsible for updating the corresponding
// fields of the struct located at the next available index
// make sure to use and update your metadata.

// autograder print for insufficient capacity:
// fprintf(stderr, "cannot insert due to insufficient capacity.\n");
void insert(char** args) {	
    char* tableName = args[1];
    if (strcmp(tableName, "programmingLanguages") == 0) {
        if (programmingLang.count < programmingLang.maxCount) {
            int index = programmingLang.nextIndex;
            programmingLanguages[index].id = atoi(args[2]);
            programmingLanguages[index].language = strdup(args[3]);
            programmingLanguages[index].year = atoi(args[4]);
            programmingLanguages[index].creator = strdup(args[5]);
            programmingLanguages[index].paradigm = strdup(args[6]);
            programmingLanguages[index].popularityIndex = atof(args[7]);
            programmingLanguages[index].isDeleted = 0;
            programmingLang.count++;
            programmingLang.nextIndex = (index + 1);
        } else {
            fprintf(stderr, "cannot insert due to insufficient capacity.\n");
            return;
        }
    } else if (strcmp(tableName, "operatingSystems") == 0) {
        if (operatingSys.count < operatingSys.maxCount) {
            int index = operatingSys.nextIndex;
            operatingSystems[index].id = atoi(args[2]);
            operatingSystems[index].name = strdup(args[3]);
            operatingSystems[index].year = atoi(args[4]);
            operatingSystems[index].developer = strdup(args[5]);
            operatingSystems[index].kernelType = strdup(args[6]);
            operatingSystems[index].isDeleted = 0;
            operatingSys.count++;
            operatingSys.nextIndex = (index + 1);
        } else {
            fprintf(stderr, "cannot insert due to insufficient capacity.\n");
            return;
        }
    } else if (strcmp(tableName, "databases") == 0) {
        if (datab.count < datab.maxCount) {
            int index = datab.nextIndex;
            databases[index].id = atoi(args[2]);
            databases[index].name = strdup(args[3]);
            databases[index].year = atoi(args[4]);
            databases[index].type = strdup(args[5]);
            databases[index].developer = strdup(args[6]);
            databases[index].isDeleted = 0;
            datab.count++;
            datab.nextIndex = (index + 1);
        } else {
            fprintf(stderr, "cannot insert due to insufficient capacity.\n");
            return;
        }
    }
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("insert complete\n");
}


// step 9: implement soft delete function
// this function is responsible for marking a record as deleted
// you should be updating an internal field flag so that get will
// not display this record. 
// You should not be attempting to free/overwrite this record - it remains alloc
// with a updated field
// make use of your metadata
void delete(char* table, int id) {
	if (strcmp(table, "programmingLanguages") == 0) {
        for (int i = 0; i < programmingLang.maxCount; i++) {
            if (programmingLanguages[i].id == id) {
                programmingLanguages[i].isDeleted = 1;
            }
        }
    } else if (strcmp(table, "operatingSystems") == 0) {
        for (int i = 0; i < operatingSys.maxCount; i++) {
            if (operatingSystems[i].id == id) {
                operatingSystems[i].isDeleted = 1;
            }
        }
    } else if (strcmp(table, "databases") == 0) {
        for (int i = 0; i < datab.maxCount; i++) {
            if (databases[i].id == id) {
                databases[i].isDeleted = 1;
            }
        }
    }
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("delete complete\n");
}

// step 10: implement modify function
// this function is responsible for overwriting all of the contents of all
// records that match an ID.
// make use of your metadata
// !!!NOTE: The structs store pointers. Make sure to free any allocated
// memory before overwriting it!!!
void modify(char** args) {
	int id = atoi(args[2]);
    if (strcmp(args[1], "programmingLanguages") == 0) {
        for (int i = 0; i < programmingLang.maxCount; i++) {
            if (programmingLanguages[i].id == id) {
                free(programmingLanguages[i].language);
                free(programmingLanguages[i].creator);
                free(programmingLanguages[i].paradigm);
                programmingLanguages[i].id = atoi(args[3]);
                programmingLanguages[i].language = strdup(args[4]);
                programmingLanguages[i].year = atoi(args[5]);
                programmingLanguages[i].creator = strdup(args[6]);
                programmingLanguages[i].paradigm = strdup(args[7]);
                programmingLanguages[i].popularityIndex = atof(args[8]);
            }
        }
    } else if (strcmp(args[1], "operatingSystems") == 0) {
        for (int i = 0; i < operatingSys.maxCount; i++) {
            if (operatingSystems[i].id == id) {
                free(operatingSystems[i].name);
                free(operatingSystems[i].developer);
                free(operatingSystems[i].kernelType);
                operatingSystems[i].id = atoi(args[3]);
                operatingSystems[i].name = strdup(args[4]);
                operatingSystems[i].year = atoi(args[5]);
                operatingSystems[i].developer = strdup(args[6]);
                operatingSystems[i].kernelType = strdup(args[7]);
                operatingSystems[i].isDeleted = 0;
            }
        }
    } else if (strcmp(args[1], "databases") == 0) {
        for (int i = 0; i < datab.maxCount; i++) {
            if (databases[i].id == id) {
                free(databases[i].name);
                free(databases[i].type);
                free(databases[i].developer);
                databases[i].id = atoi(args[3]);
                databases[i].name = strdup(args[4]);
                databases[i].year = atoi(args[5]);
                databases[i].type = strdup(args[6]);
                databases[i].developer = strdup(args[7]);
                databases[i].isDeleted = 0;
            }
        }
    }
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("modify complete\n");
}

// step 11: implement get function
// this function is responsible for fetching all non-deleted records
// make use of your metadata
// Make sure to follow guidelines for format in writeup
// see examples as well
// Use %lf for formatting double data type
void get(char* table) {
	if (strcmp(table, "programmingLanguages") == 0) {
        printf("id,language,year,creator,paradigm,popularityIndex\n");
        for (int i = 0; i < programmingLang.maxCount; i++) {
            if (!programmingLanguages[i].isDeleted) {
                printf("%d,%s,%d,%s,%s,%.6lf\n",
                    programmingLanguages[i].id,
                    programmingLanguages[i].language,
                    programmingLanguages[i].year,
                    programmingLanguages[i].creator,
                    programmingLanguages[i].paradigm,
                    programmingLanguages[i].popularityIndex);
            }
        }
    } else if (strcmp(table, "operatingSystems") == 0) {
        printf("id,name,year,developer,kernelType\n");
        for (int i = 0; i < operatingSys.maxCount; i++) {
            if (!operatingSystems[i].isDeleted) {
                printf("%d,%s,%d,%s,%s\n",
                    operatingSystems[i].id,
                    operatingSystems[i].name,
                    operatingSystems[i].year,
                    operatingSystems[i].developer,
                    operatingSystems[i].kernelType);
            }
        }
    } else if (strcmp(table, "databases") == 0) {
        printf("id,name,year,type,developer\n");
        for (int i = 0; i < datab.maxCount; i++) {
            if (!databases[i].isDeleted) {
                printf("%d,%s,%d,%s,%s\n",
                    databases[i].id,
                    databases[i].name,
                    databases[i].year,
                    databases[i].type,
                    databases[i].developer);
            }
        }
    }
}

// step 12: implement exit function
// this function should free all allocated memory
// Make sure to avoid memory leaks by freeing any allocated memory
// inside a struct (char*) before freeing the struct pointer
void exitProgram() {
    if (programmingLanguages != NULL) {
        for (int i = 0; i < programmingLang.maxCount; i++) {
            free(programmingLanguages[i].language);
            free(programmingLanguages[i].creator);
            free(programmingLanguages[i].paradigm);
        }
        free(programmingLanguages);
    }
    if (operatingSystems != NULL) {
        for (int i = 0; i < operatingSys.maxCount; i++) {
            free(operatingSystems[i].name);
            free(operatingSystems[i].developer);
            free(operatingSystems[i].kernelType);
        }
        free(operatingSystems);
    }
    if (databases != NULL) {
        for (int i = 0; i < datab.maxCount; i++) {
            free(databases[i].name);
            free(databases[i].type);
            free(databases[i].developer);
        }
        free(databases);
    }
}

// this code is responsible for parsing the user's
// input, and determining based on the command
// which function to send it to.
// You do not have to modify this code, but you should
// understand it.
void execute_cmd(char** args, int arg_count) {
	char* cmd = args[0];
	if (strcmp(cmd, "setup") == 0) {
		setup(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "insert") == 0) {
		insert(args);
	} else if (strcmp(cmd, "delete") == 0) {
		delete(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "modify") == 0) {
		modify(args);
	} else if (strcmp(cmd, "get") == 0) {
		get(args[1]);
	} else if (strcmp(cmd, "exit") == 0) {
		exitProgram();
	} else {
		printf("\n");
	}
}

// step 6: initialize the default metadata values here
// jump to L76
void initializeMetadata() {
    programmingLang.count = 0;
    programmingLang.nextIndex = 0;
    operatingSys.count = 0;
    operatingSys.nextIndex = 0;
    datab.count = 0;
    datab.nextIndex = 0;
}

// this code creates the interactive shell
// you do not need to modify this
// You do not need to understand this code
// but you are welcome to research its application
void cmd_loop() {
	char input[MAX_INPUT_SIZE];
    ssize_t bytes_read;
	printf("Usage: \n");
	printf("setup {table} {numRows}\n");
	printf("insert {table} {data}\n");
	printf("delete {table} {id}\n");
	printf("modify {table} {id} {data}\n");
	printf("get {table}\n\n");
	initializeMetadata();
    while (1) {
        printf("CS211> ");
		fflush(stdout);
        
        // Read user input using the read() system call
        bytes_read = read(STDIN_FILENO, input, sizeof(input));
        
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        if (bytes_read == 0) {
			printf("\n");
            break;
        }
        
        // Null-terminate the input
        input[bytes_read] = '\0';

		char** args = (char**)malloc(MAX_ARGS_SIZE * sizeof(char*));
		int arg_count;

		splitInput(input, args, &arg_count);
        
        // Execute the user's command
        execute_cmd(args, arg_count);
		free(args);
    }
}

int main() {
	cmd_loop();
}
