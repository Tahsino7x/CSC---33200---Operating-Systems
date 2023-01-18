#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{   
    //command arguments array
    char *args[] = 
    {   
        "ls",
        "-la",    // flags to show files in dir with info
        "/bin/",
        NULL
    };
    int child1;
    child1 = fork(); // cretae child process

      //child 1
    if (child1 == 0)
    {
        printf ("Child pid is: %d\n", getpid());
        if( execvp(args[0],args)<0) //execute the command
            printf("ERROR exec failed\n");
    }
}