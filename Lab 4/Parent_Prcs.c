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
        execlp("./Prcs_P1","./Prcs_P1","",NULL); // create destinations files
    
    else
    {   
        child2 = fork();// cretae child process
        //child 2
        if(child2==0)
            execlp("./Prcs_P2","./Prcs_P2","",NULL);   // write to files
    }
}