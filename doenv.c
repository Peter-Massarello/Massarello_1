#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

extern char **environ;
void print_env(){
	char **ptr;
	char *index;
	char tempStr[10000];
	int count = 0;
	const char delim[2] = "=";
	
	while(environ[count] != NULL){
		count++;
	}

	for(int i = 0; i < count; i++){
		strcpy(tempStr, environ[i]);
		index = strtok(tempStr, delim);
		printf("%s=%s\n", index, getenv(index));
	}
}

void help_menu(){
	system("clear");
	printf("HELP MENU:\n\n");
	printf("To display all current enviorment variables, call program with no arguments. EX './doenv'.\n\n");
	printf("OPTION [-i]:\n");
	printf("            When called, will replace current eviorment variables with given [name=value] pairs\n");
	printf("	    EX: ./doenv [-i] [name=value] ... [name=value]\n\n");
	printf("OPTION [-h]:\n");
	printf("            When called, will print out a help menu displaying functionality of program\n");
	printf("            EX: ./doenv [-h]\n\n");

		
}

void print_env_count(char **env){
	int count  = 0;
	while(env[count] != NULL){
		count++;
	}
	printf("%d", count);
}

void i_option(int argc, char **argv){
	char **ptr;
	int count = 0;
	int size;
	bool foundUtil = false;

	for(ptr = argv; ptr != NULL; ptr++){
		count++;
		if(strcmp(*ptr, "utility") == 0){
			printf("Utility found!");
			foundUtil = true;
			break;
		}
	}
	printf("Before new ENV\n");
	char **newEnv = malloc(sizeof(char *) * (count + 1));
	
	for(int i = 2; i < count; i++){
		size = strlen(argv[i]);
		newEnv[i] = (char *)malloc(sizeof(char *) * (size + 1));
		newEnv[i] = argv[i]; 
		printf("In loop\n");
	}
	newEnv[count] = NULL;
	printf("After newEnv\n");
	environ = newEnv;
	print_env();
	free(newEnv);
}

int main(int argc, char* argv[]){
	
	int opt;

	if(argc == 1)
	{
		print_env();
		printf("Program called with no arguments, use ./doenv -h for help\n");
		return 0;
	}
	while((opt = getopt(argc, argv, "i:h")) != -1)
	{
		switch(opt)
		{
			case 'i':
				printf("Inside I option");
				i_option(argc,argv);
				break;
			case 'h':
				help_menu();
				break;

		}
	}


	return 0;
}
