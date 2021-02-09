/***********************************************************************
 * 
 *	Name: Peter Massarello
 *	Email: pmmmw@umsystem.edu <- School email
 *	       pmassarello@gmail.com <- Git Hub email
 *	Title: Enviornment Assignment 1 CMPSCI 4760
 *	Description: Create a tool that emulates the system call
 *		'env' while demonstrating your proficiency with
 *		getopt and perror.
 *
 * ********************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

extern char **environ;
void print_env(){
/**************************************************
 *	
 *	Prints enviorment by getting count of items
 *	and prints to that count to stdout
 *
 * ***********************************************/
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

void help_menu(){ // Help menu
	system("clear");
	printf("HELP MENU:\n\n");
	printf("To display all current enviorment variables, call program with no arguments. EX './doenv'.\n\n");
	printf("OPTION [-i]:\n");
	printf("            When called, will replace current eviorment variables with given [name=value] pairs\n");
	printf("	    EX: ./doenv [-i] [name=value] ... [name=value] [cmd] ... [cmd]\n\n");
	printf("OPTION [-h]:\n");
	printf("            When called, will print out a help menu displaying functionality of program\n");
	printf("            EX: ./doenv [-h]\n\n");

		
}



bool checkForPair(char **argv, int currentCount){
/**************************************************
 *
 *	Checks string to see if it is a name=value 
 *	pair by using '=' as a delmiter
 *
 **************************************************/
	char *s;
	char **ptr;
	char buf[1000];
	
	ptr = argv;
	strcpy(buf, ptr[currentCount]);
	s = strchr(buf, '=');
	if(s != NULL)
		return true;
	else
		return false;
 		
}

void createEnv(){
	

}

int checkForSystemCall(char ** argv,int  i){
/*************************************************
 *
 *	Checks for valid system call, otherwise
 *	it returns error message using perror
 *
 * ***********************************************/
	int systemCheck = system(argv[i]);
	if(systemCheck == 0){
		system(argv[i]);
	}
	else{
		perror("Error: Unknown Command entered\n ");
		return -1;
	}
}
void i_option(int argc, char ** argv){
/************************************************
 *
 *	Gathers all arguments given and searches
 *	to see if either name=value pair or
 *	a valid system call. Then overwrites
 *	eviron ptr
 *
 * **********************************************/
	int count = 0;
	int index = 0;
	char ** newEnv = malloc(sizeof(char*) * (argc + 1));
	for(int i = 2; i < argc; i++)
	{
		if(checkForPair(argv, i))
		{
			//printf("Found name=value pair\n");
			int size = strlen(argv[i]);
			newEnv[index] = (char *)malloc(sizeof(char *) * (size + 1));
			newEnv[index] = argv[i];
			//printf("%s\n", newEnv[index]);
			index++;
			
		}
		else if(checkForSystemCall(argv, i) != -1)
		{
			printf("IN else if loop\n");
		}
		
	}
	newEnv[argc] = NULL;
	environ = newEnv;
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
	while((opt = getopt(argc, argv, "ih:")) != -1)
	{
		switch(opt)
		{
			case 'i':
				i_option(argc,argv);
				break;
			case 'h':
				help_menu();
				break;

		}
	}
	

	return 0;
}
