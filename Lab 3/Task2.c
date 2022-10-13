#include <sys/types.h>
#include<stdio.h>
#include <unistd.h> 

int main()
{
    //parent P
    int a=10, b=25, fq=0, fr=0;
    fq=fork(); // fork a child - call it Process Q
    
    if(fq==0) // Child successfully forked
    {   
        a=a+b;
        printf("value of a %d\n",a);
        printf("value of b %d\n",b);
        printf("value of process %d\n\n",getpid());
        fr=fork(); // fork another child - call it Process R
      
        if(fr!=0)
        {
            b=b+20;
            printf("value of a %d\n",a);
            printf("value of b %d\n",b);
            printf("value of process %d\n\n",getpid());
        }

        else
        {
            a=(a*b)+30;
            printf("value of a %d\n",a);
            printf("value of b %d\n",b);
            printf("value of process %d\n\n",getpid());
        }
    }

    else
    {
        b = a+b-5;
        printf("value of a %d\n",a);
        printf("value of b %d\n",b);
        printf("value of process %d\n\n",getpid());    
    }
}