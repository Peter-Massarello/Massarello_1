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

void ignore_option(int argc, char **argv){
	//extern char **environ;
	char **ptr;
	bool foundUtil = false;

	environ = &argv[2];
	


	print_env();

}

int main(int argc, char* argv[]){
	
	int opt;

	if(argc == 1)
	{
		print_env();
		printf("Program called with no arguments, use ./doenv -h for help\n");
		return 0;
	}
	while((opt = getopt(argc, argv, "ih")) != -1)
	{
		switch(opt)
		{
			case 'i':
				ignore_option(argc,argv);
				break;
			case 'h':
				help_menu();
				break;

		}
	}

	print_env();
	return 0;
}