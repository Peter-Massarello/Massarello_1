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
#include <errno.h>

extern char **environ;
int indexOfEnv = 0;
extern int eerno;
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
	char *buf;
	int size = strlen(argv[currentCount]);

	//if(size < 3) //if less than 3 cannot be name=value pair
	//	return false;
	
/*	int index = size - 1;
	buf = strncpy(buf, argv[currentCount], index);
	s = strchr(buf, "=");
	if(s == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
*/
	ptr = argv;
	strcpy(buf, ptr[currentCount]);
	s = strchr(buf, '=');
	if(s != NULL)
		return true;
	else
	{
		/*printf("Found a potential system call\n\n");
		if(system(argv[currentCount]) != 0)
		{
			errno = 22;
			perror("Error: ");
			printf("\n\n");
		}*/
		return false;
	}
 		
}

int checkForSystemCall(char ** argv,int  i){
/*************************************************
 *
 *	Checks for valid system call, otherwise
 *	it returns error message using perror
 *
 * ***********************************************/
	int systemCheck = system(argv[i]);
	if(systemCheck == 0)
	{
		
	}
	else
	{
		perror("Error: ");
		return -1;
	}

	/*if(system(argv[i]) != 0){
		errno = 22;
		perror("Error: ");
		printf("\n\n");
		return -1;
	}
	else{
		return 0;
	}*/
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
	int index = 0;
	char ** newEnv = malloc(sizeof(char*) * (argc + 1));
	for(int i = 2; i < argc; i++)
	{
		if(checkForPair(argv, i))
		{
			int size = strlen(argv[i]);
			newEnv[index] = (char *)malloc(sizeof(char *) * (size + 1));
			newEnv[index] = argv[i];
			index++;
			
		}
		else{
			checkForSystemCall(argv, i);
		}
		
	}
	newEnv[argc] = NULL;
	environ = newEnv;
	print_env();
	free(newEnv);
}

bool checkIfNew(char **argv, int currentCount, int environCount){
	char tempEnvStr[10000];
	char tempArgStr[10000];
	char *envKey;
	char *argKey;
	const char delim[2] = "=";

	int size = strlen(argv[currentCount]);
	strcpy(tempArgStr, argv[currentCount]);
	argKey = strtok(tempArgStr, delim);

	for(int i = 0; i < environCount; i++){
		strcpy(tempEnvStr, environ[i]);
		envKey = strtok(tempEnvStr, delim);
		if(*envKey == *argKey)
		{
			indexOfEnv = i;
			return false;
		}

	}
	return true;	

}
void update_env(int argc, char **argv){
	int envCount = 0;
	int newArgCount = 0;
	int totalArgs = 0;
	int index = 0;
	while(environ[envCount] != NULL)
	{
		envCount++;
	}
	for(int i = 2; i < argc; i++)
	{
		if(checkForPair(argv, i))
		{
			newArgCount++;		
		}
	}
	totalArgs = envCount + newArgCount;
	char **newEnv = malloc(sizeof(char*) * (totalArgs + 1));

	for(int i = 0; i < envCount; i++)
	{
		int size = strlen(environ[i]);
		newEnv[index] = (char *)malloc(sizeof(char *) * (size + 1));
		newEnv[index] = environ[i];
		index++;

	}
	for(int i = 1; i < argc; i++)
	{
		if(checkForPair(argv, i))
		{
			if(checkIfNew(argv, i, envCount))
			{
				int size = strlen(argv[i]);
				newEnv[index] = (char *)malloc(sizeof(char *) * (size + 1));
				newEnv[index] = argv[i];
				index++;
	
			}
			else
			{

				newEnv[indexOfEnv] = argv[i];

			}
		}
		else
		{
			checkForSystemCall(argv, i);
		}
	
	}
	newEnv[index] = NULL;
	environ = newEnv;
	print_env();
//	free(newEnv);

}

int main(int argc, char* argv[]){
	
	int opt;

	if(argc == 1)
	{
		system("clear");
		print_env();
		printf("Program called with no arguments, use ./doenv -h for help\n");
		return 0;
	}
	while((opt = getopt(argc, argv, "ih:")) != -1)
	{
		switch(opt)
		{
			case 'i':
				system("clear");
				i_option(argc,argv);
				break;
			case 'h':
				system("clear");
				help_menu();
				break;

		}
	}
	system("clear");
	update_env(argc, argv);
	return 0;
}
