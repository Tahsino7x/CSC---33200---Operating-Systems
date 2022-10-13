#include <sys/types.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int s1=0,s2=0,s3=0; 

    if(argc>1)
    {
        int val = atoi(argv[1]); // convert alpha to int
        int child1;
        int child2;
        child1 = fork(); // cretae child process
    
    //child 1
        if (child1 == 0)
        {
            for(int i=2;i<val;i+=2)
                s1+=i;
            printf("Child one s1: %d\n",s1);
        }

        //child 2
        else
        {
            child2 = fork(); // cretae child process
            wait(NULL);
            if(child2==0)
            {
                for(int i=1;i<val;i+=2)
                    s2+=i;
                 printf("Child two s2: %d\n",s2);
            }

            //parent process
            if(child1!=0 && child2!=0)
            {
                for(int i=1;i<val;i+=1)
                    s3+=i;
                 printf("Parent s3: %d\n",s3);
            }
        }//
    }
    else
        printf("input argument\n");
}