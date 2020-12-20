#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 1024
#define DELIMS " \t\r\n"

int main(int argc, char *argv[]) {
char *cmd;
char cmd_line[MAX];
char cwd[FILENAME_MAX];
char character[2];
char command[512];
char **arguments;
char SHELL_NAME[50] = "myShell";

while (1) 
	{
	
	if(getcwd(cwd, sizeof(cwd)) != NULL){ //Checks current Directory and prints it
		printf("%s$", cwd);
	}else{
		perror("getcwd() error");
	}
	character[0] = (char)fgetc(stdin);
	character[1] = '\0'; //null terminator
	while(character[0] != EOF && character[0] != '\n'){//while character is not equal to EOF or '\n'
		
		if(strlen(command) == 511){
			fprintf(stderr, "Too many characters");
		}
		int i = 0;
		char* line = strcat(command, character);
		for(i = 0; i < strlen(line); i++){//strings characters into command.
				command[i] = line[i];
		}
		character[0] = (char)fgetc(stdin);
	}
	
	#define token_bufsize 64
	#define token_delims " \t\r\n\a"
	char **parsing(char *command)// function that parses the command into tokens seperated by " "
	{
		int bufsize = token_bufsize;
		int position = 0;
		char **tokens = malloc(bufsize * sizeof(char*));
		char *token;
		
		if (!tokens){
			fprintf(stderr, "Token Error"); //Checks to see if Tokens is working properly 
			exit(EXIT_FAILURE);
		}
		token = strtok(command, token_delims);
		while(token != NULL)//tokenizes the command and checks for errors
		{
			tokens[position] = token;
			position++;
			
			if(position >= bufsize)//too many tokens for bufsize, must enlarge it.
			{
				bufsize += token_bufsize;
				tokens = realloc(tokens, bufsize * sizeof(char*));
				if(!tokens)
				{
					fprintf(stderr, "Error rellocating bufsize");
					exit(EXIT_FAILURE);
				}
			}
			
			token = strtok(NULL, token_delims);
		}
		tokens[position] = NULL;
		return tokens;	
	}
	
	arguments = parsing(command);//Passing the tokens to arguments, to see what they are.
	
	int ret;
	char *builtin_cmd[] = {"cd", "exit"};
	pid_t pid, wpid;
	int status;
	pid = fork();
	if (pid == 0) //Checks to see if a new child process was created
	{
		// The Child Process
		if (execvp(arguments[0], arguments) == -1)
		{
			perror("myShell: ");
		}
	exit(EXIT_FAILURE);
	}
	else if (pid < 0)// checks to see if child process was unsuccessful
	{
		//Forking Error
		perror("myShell: ");
	}
	else
	{
		// The Parent Process
		do 
		{
        	wpid = waitpid(pid, &status, WUNTRACED);
        	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	if (arguments[0] == NULL)
	{
		// Nothing was written
		return 1;
	}
	
	FILE *fptr;
	char line[200];
	char filename[100];
	fptr = fopen(filename, "r"); //Opens the file
	if (fptr == NULL)
	{
		printf("\nUnable to open file.");
	}
	else
	{
		printf("\nFile Opened. Parsing. Parsed commands displayed first.");
		while(fgets(line, sizeof(line), fptr)!= NULL) //while loop to read what's inside the file
		{
			printf("\n%s", line);
			arguments=parsing(line);
			//execShell(arguments);
		}
	}
	free(arguments);
	fclose(fptr);
	return 1;
  }//End of While(1)

return 1;
}
