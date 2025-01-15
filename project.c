#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {  
    int child_num; 
    pid_t pid;     
    int pipe_fd[2];
} ChildInfo;



int main(int argc, char *argv){

    ChildStruct *children=NULL;
    int numofchild;
    printf("Give number of childer");
    scanf("%d",numofchild);
    ChildInfo *children = malloc(numofchild * sizeof(ChildInfo));
    pid_t child_pid = -1;
    child_pid=fork();if(child_pid<0){return 1};
    int i=0;
    while(child_pid>0){
        if(i>=numofchild){
            exit;
        }else{
            i++;
            children[i].pid=child_pid;
            children[i].child_num=i;
            if (pipe(children[i].pipe_fd) == -1) {
                free(children);
                return 1;
            }
            char message[256];
            snprintf(message, sizeof(message), "Hello child, i call you %d", child_pid);
            write(children[i].pipe_fd[1], message, strlen(message));
            close(pipe_fd[0]);
            child_pid=fork();
            if(child_pid<0){return 1};
        }
    }
    if(child_pid==0){
        FILE *fptr;

        fptr = fopen((getpid+".txt"), "w");

        fprintf(fptr, "Child proccess %d",getpid);

        fclose(fptr);
        write(children[i+1].pipe_fd[0],"Done",sizeof(char*4));
        close(pipe_fd[1]);
    }
    printf("proccess id:%d, parent pid:%d\n",getpid(),getppid());
    for (int j = 0; j < numofchild; j++) {
        wait(NULL);
    }
    free(children);
    return 0;   

}