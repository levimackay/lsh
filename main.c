#include <stdio.h>
#include <string.h>

int main(void){

	while (1){
		
		printf("lsh> ");
		char line[1024];
		if (fgets(line, sizeof line, stdin) == NULL){
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
		}
	}
}
