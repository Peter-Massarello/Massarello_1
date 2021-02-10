/***************************************************************
 *
 *	Name: Peter Massarello
 *	Email: pmmmw@umsystem.edu <- School Email
 *	       pmassarello@gmail.com <- Git Hub Email
 *	Git Hub: github.com/Peter-Massarello
 *	Title: Environment Tool (Assignment 1) CMPSCI 4760
 *	Description: Create a tool that emulates the system
 *		call 'env' while demonstrating your proficiency
 *		with 'getopt' and 'perror'.
 *
 * ***********************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

extern char **environ; // Environment pointer
int indexOfEnv = 0; // Global index used to keep track of duplicates
extern int errno; // Errno variable

void print_env(){
/*************************************************************
 *
 * 	Prints enviornment by getting count of items and
 * 	prints to that count to stdout
 *
 * **********************************************************/
	
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
	printf("OPTION [blank]:\n");
	printf("            When called with no option but arguments given, will execute and append all name=value pairs\n");
	printf("            to the end of the original environment, while replacing any of the old pairs.\n");
	printf("            EX: ./doenv [name=value] ... [name=value] [cmd] ... [cmd]\n\n");										
}

bool check_for_pair(char **argv, int currentCount){
/*************************************************************
 *
 *	Checks string to see if it is a name=value pair by
 *	using '=' as a delimiter
 *
 * **********************************************************/
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


void check_for_system_call(char **argv,int  i){
/***********************************************************
 *
 *	Checks for a valid system call, if invalid returns
 *	perror with a errno of 3
 *
 * ********************************************************/
	if(system(argv[i]) != 0){
		errno = 3;
		perror("Error: ");
	}
}

void i_option(int argc, char ** argv){
/*********************************************************
 *
 *	Gathers all arguments given and searches to see 
 *	if either a name=value or a valid system call.
 *	Then it overwrites the eviron pointer
 *
 * ******************************************************/
	int index = 0;
	char **newEnv = malloc(sizeof(char*) * (argc + 1));
	newEnv[argc] = NULL;
	for(int i = 2; i < argc; i++)
	{
		if(check_for_pair(argv, i))
		{
			int size = strlen(argv[i]);
			newEnv[index] = (char *)malloc(sizeof(char *) * (size + 1));
			strcpy(newEnv[index], argv[i]);
			index++;
			newEnv[index] = NULL;
		}
		else
		{
			check_for_system_call(argv, i);
		}

	}
	environ = newEnv;
	print_env();
}

bool check_if_new(char **argv, int currentCount, int environCount){
/********************************************************
 *
 *	Checks a single argument key against all keys
 *	in the enviornment. If key already exists,
 *	return false, otherwise return true.
 *
 * *****************************************************/
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
/*****************************************************
 *
 *	Takes all arguments from both environ and
 *	argv and creates a new environment with all
 *	arguments combined. Replaces any repeats.
 *
 * **************************************************/
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
		if(check_for_pair(argv, i))
		{
			newArgCount++;
		}
	
	}
	totalArgs = envCount + newArgCount;
	char **newEnv = malloc(sizeof(char*) * (totalArgs + 1));
	newEnv[totalArgs] = NULL;
	for(int i = 0; i < envCount; i++)
	{
		int size = strlen(environ[i]);
		newEnv[index] = (char *)malloc(sizeof(char *) * (size + 1));
		strcpy(newEnv[index], environ[i]);
		index++;
		newEnv[index] = NULL;
	}
	for(int i = 1; i < argc; i++)
	{
		if(check_for_pair(argv, i))
		{
			if(check_if_new(argv, i, envCount))
			{
				int size = strlen(argv[i]);
				newEnv[index] = (char *)malloc(sizeof(char *) * (size + 1));
				strcpy(newEnv[index], argv[i]);
				index++;
				newEnv[index] = NULL;
			}
			else
			{
				strcpy(newEnv[indexOfEnv], argv[i]);
			}
		}
		else
		{
			check_for_system_call(argv, i);
		}
	}
	environ = newEnv;
	print_env();
}

bool no_i_args(int argc){
/*****************************************************
 *
 *	Checks to see if no other arguments were 
 *	given to -i, if so, returns true.
 *	
 * **************************************************/
	if(argc == 2){
		errno = 3;
		printf("Not enough arguments given\n");
		perror("ERROR: ");
		return true;
	}
	else
		return false;
	
}

int main(int argc, char* argv[]){
/***************************************************
 *
 *	Main function
 *
 * ************************************************/
	int opt;
	bool optFlag = false;	
	if(argc == 1)
	{
		system("clear");
		print_env();
		printf("Program called with no arguments, use ./doenv -h for options\n");
		return 0;
	}
	while((opt = getopt(argc, argv, "hi:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				system("clear");
				help_menu();
				optFlag = true;
				break;
			case 'i':
				system("clear");
				bool exitFlag = no_i_args(argc);
				if(exitFlag)
					exit(1);
				else
					i_option(argc, argv);
				optFlag = true;
				break;
			default:
				printf("Invalid option given\n");

		}
	}
	if(optFlag == false){
		update_env(argc,argv);
	}
	return 0;

}
	
