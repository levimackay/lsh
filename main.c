#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void){
	char *line = NULL;
	size_t cap = 0;
	while (1){
		printf("lsh> ");
		if (getline(&line, &cap, stdin) == -1){
			break;
		} else {
			char *word = strtok(line, " \t\n");
			if (word != NULL && strcmp(word, "exit") == 0){
				break;
			}
			char *args[64];
			int count = 0;

			while(word != NULL && count < 63){
				args[count] = word;
				count++;
				word = strtok(NULL, " \t\n");
			}
			args[count] = NULL;

			if (count > 0 && strcmp(args[0], "cd") == 0){
				char *dir;
				if (args[1] == NULL || strcmp(args[1], "~") == 0){
					dir = getenv("HOME");
				} else {
					dir = args[1];
				}

				if (dir == NULL){
					printf("No Home directory found\n");
				} else {
					if (chdir(dir) != 0){
						perror("lsh");
					}

				}
				continue;

			}

			if (count > 0 && strcmp(args[0], "help") == 0){
				printf("\n~~~~~~~~~~~\n");
				printf("cd: with nothing after it, or ~, it goes home. With a folder, it goes there, and .. goes up one\n");
				printf("help: it shows this list.\n");
				printf("exit: it quits lsh. Ctrl-D does the same.\n");
				printf("\nEverything else is a program on your PATH, and man plus the name shows how to use it.");
				printf("\n~~~~~~~~~~~\n");
				continue;
			}

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
	free(line);
}
