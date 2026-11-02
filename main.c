// Headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void){
	// C doesn't have True, so you have to use 1 instead
	while (1){
		// Prints the initial text of the shell. Checks to make sure that input is actually something
		printf("lsh> ");
		char line[1024];
		if (fgets(line, sizeof line, stdin) == NULL){
			break;
		} else {
			// Makes all the characters into a string
			char *word = strtok(line, " \t\n");
			// I coded this in Nvim and sometimes the program wouldn't close when I did Cntr^c/d 
			if (word != NULL && strcmp(word, "exit") == 0){
				break;
			}
			// Now that we have words, we need to 
			char *args[64];
			int count = 0;

			while(word != NULL && count < 63){
				args[count] = word;
				count++;
				word = strtok(NULL, " \t\n");
			}
			args[count] = NULL;

			// Need to add something here so the shell checks for cd

			if (count > 0){
				pid_t pid = fork();
				if (pid == 0){
					execvp(args[0], args);
					perror("lsh");
					exit(1);
				} else {
					waitpid(pid, NULL, 0);
				}
			}
		}
	}
}
