#include <stdio.h>
#include "LineParser.c"
#include <linux/limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#ifndef NULL
    #define NULL 0
#endif

void execute(cmdLine *pCmdLine) {

    if (strcmp(pCmdLine->arguments[0], "cd") == 0) {
        // Handle 'cd' command
        if (chdir(pCmdLine->arguments[1]) == -1) {
            perror("Error in chdir");
            exit(1);
        }
        return;
    }
    if (strcmp(pCmdLine->arguments[0], "wakeup") == 0) {
        // Handle 'wakeup' command
        pid_t pid = atoi(pCmdLine->arguments[1]);
        if (kill(pid, SIGCONT) == -1) {
            perror("Error in wakeup");
            exit(1);
        }
        else {
            printf("wakeup succeded\n");
        }
        return;
    }

    if (strcmp(pCmdLine->arguments[0], "nuke") == 0) {
        // Handle 'nuke' command
        pid_t pid = atoi(pCmdLine->arguments[1]);
        if (kill(pid, SIGINT) == -1) {
            perror("Error in nuke\n");
            exit(1);
        }
        else {
            printf("nuke succeded\n");
            
        }
        return;
    }

    pid_t PID = fork();
    if (PID==0) { // child
  
        if (pCmdLine->inputRedirect) {
        int inputFile = open(pCmdLine->inputRedirect, O_RDONLY);
        if (inputFile == -1) {
            perror("Error in open for input");
            exit(1);
        }

        dup2(inputFile,STDIN_FILENO);
    }
     if (pCmdLine->outputRedirect) {
        int outputFile = open(pCmdLine->outputRedirect, O_WRONLY);
        if (outputFile == -1) {
            perror("Error in open for output");
            exit(1);
        }
        
        dup2(outputFile,STDOUT_FILENO);
        
    }
     if (execvp(pCmdLine->arguments[0], pCmdLine->arguments) == -1){
            perror("Error in execv");
            exit(1);
        }
    }

    else if (PID > 0) { //parent
        fprintf(stderr, "PID: %d\n", PID);
        fprintf(stderr, "Executing command: %s\n", pCmdLine->arguments[0]);

        if(pCmdLine->blocking) {
            int status;
            waitpid(PID, &status, 0);
        }
        else {
            
            fprintf(stderr, "Background process started with PID: %d\n", PID);
            return;  
        }

    }
    else { // error
            perror("Error in fork");
            exit(1);
        }

}


int main(int argc, char **argv) {
    while(1) {

        char cwd[PATH_MAX];
        char input[2048];
        if (getcwd(cwd, PATH_MAX) != NULL) {
            printf("current working directory: %s\n", cwd);
        } else {
            perror("error in getcwd function");
        }
        printf("enter input\n");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Exit the loop on EOF
            printf("Exiting\n");
            exit(1);
        }

        cmdLine *lineFromInput = parseCmdLines(input);

         if (strcmp(input, "quit") == 0) {
            printf("Exiting myshell\n");
            break;  // Exit the infinite loop if the user enters "quit"
        }
        else {
            execute(lineFromInput);
            freeCmdLines(lineFromInput);
        }

    }
    return 0;
}







