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

void print_env2(){
	char **ptr;
	char *index;
	char tempStr[10000];
	const char delim[2] = "=";
	
	for(ptr = environ; *ptr != NULL; ptr++){
		strcpy(tempStr, *ptr);
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



bool checkForPair(char **argv, int currentCount){
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
	if(system(argv[i]) != -1){
		
	}
	else{
		perror("Error: ");
		return -1;
	}
}
void i_option(int argc, char ** argv){
	int count = 0;
	char ** newEnv = malloc(sizeof(char*) * (argc + 1));
	for(int i = 2; i < argc; i++)
	{
		if(checkForPair(argv, i))
		{
			printf("Found name=value pair\n");
			int size = strlen(argv[i]);
			newEnv[i] = (char *)malloc(sizeof(char *) * (size + 1));
			newEnv[i] = argv[i];
			printf("%s\n", newEnv[i]);
			
		}
		else if(checkForSystemCall(argv, i) != -1)
		{

		}
		
	}
	environ = newEnv;
	print_env2();
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
