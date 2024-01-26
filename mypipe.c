#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char* msg = "hello"; 

int main() {
    char inbuf[32];
    int pd[2];

    if(pipe(pd) == -1) {
        perror("Can't create pipe \nexiting\n");
        exit(1);
    }
    pid_t PID = fork();

    if (PID < 0) {
        perror(" Error in PID \nexiting\n");
        exit(1);
    }
    else if(PID == 0 ) {

        close(pd[0]);
        printf("enter message:\n");
        // char msg[32];
        // fgets(msg,sizeof(msg),stdin);
        write(pd[1],msg,sizeof(msg));
        close(pd[1]);
    }
    else {
        close(pd[1]);
        read(pd[0],inbuf,sizeof(inbuf));
        printf("the message is :  %s\n" , inbuf);
        

    }
    return 0;
}
