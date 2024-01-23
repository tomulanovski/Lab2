#include <stdio.h>
#include "LineParser.c"
#include <linux/limits.h>
#include <unistd.h>

void execute(cmdLine *pCmdLine) {
    if (execvp(pCmdLine->arguments[0], pCmdLine->arguments) == -1) {
        perror("Error in execv");
        exit(1);
    }
}

int main() {
    while(1) {

        char cwd[PATH_MAX];
        char input[2048];
        if (getcwd(cwd, PATH_MAX) != NULL) {
            printf("current working directory: %s\n", cwd);
        } else {
            perror("error in getcwd function");
        }
        if (strcmp(input, "quit") == 0) {
            printf("Exiting myshell\n");
            break;  // Exit the infinite loop if the user enters "quit"
        }
        printf("enter input\n");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Exit the loop on EOF
            printf("Exiting\n");
            exit(1);
        }
        cmdLine *lineFromInput = parseCmdLines(input);
        execute(lineFromInput);
        freeCmdLines(lineFromInput);

    }
    return 0;
}



