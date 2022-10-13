#include <sys/types.h>
#include<stdio.h>
#include <unistd.h> 

int main()
{
    int child1;
    int child2;
    child1 = fork(); // cretae child process
    
    //child 1
    if (child1 == 0)
        printf ("I am child one, my pid is: %d\n", getpid());
    
    else
    {   
        child2 = fork();// cretae child process
        //child 2
        if(child2==0)
            printf ("I am child two, my pid is: %d\n", getpid());
    }
}