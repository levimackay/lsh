#include <stdio.h>

int main(void){

	while (1){
		
		printf("lsh> ");
		char line[1024];
		if (fgets(line, sizeof line, stdin) == NULL){
			break;
		} else {
			printf("You said %s", line);
		}
	}
}
