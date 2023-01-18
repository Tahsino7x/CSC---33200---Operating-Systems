#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{   
    int child1;
    child1 = fork(); // cretae child process

      //child 1
    if (child1 == 0)
    {
        printf ("Child pid is: %d\n", getpid());
        execlp("/bin/date","/bin/date","+%s",NULL); //execute the command
    }
}