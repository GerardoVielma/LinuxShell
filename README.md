# LinuxShell
Design overview: This program takes the users commands character by character and stringing them 
		along into an array named command. The code would then take that array into a function named parsing so it could
		seperate the commands by the token_delims. The commands are tokenized into a variable named arguments which is used
		by execvp.
    The shell has two states it run on: interactive and batch. While in interactive mode the shell displays a prompt and 
    waits for the user to type in commands. Batch mode starts when one of the commands is a batchfile. While in batch mode
    the shell will echo and execute the commands written inside the batchfile.
