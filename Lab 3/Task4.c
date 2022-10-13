#include <sys/types.h>
#include<stdio.h>
#include <unistd.h> 
#include <sys/wait.h>

int main()
{
    const int maxBufSize = 2000; // max buffer size for txt file

    int fd[2]; // pipe file descriptor
    // fd[0] // read
    // fd[1] // write

    if(pipe(fd) == -1)  // create file
    {
        printf("error opening pipe\n");
        return 1;
    }

    int child1;
    child1 = fork();  // cretae child process
    wait(NULL);

    //Child process
    if (child1 == 0)
     {
        close(fd[0]);
        FILE* ptr;
        ptr = fopen("Readme.txt", "r"); // Opening file in reading mode
        char Buffer[maxBufSize];

        if (ptr==NULL) 
        {
            printf("file can't be opened \n");
            return -1;
        }

        int index =0;
        // read to end of file
        while (!feof(ptr)) 
            Buffer[index++] = fgetc(ptr);
        fclose(ptr); 
        Buffer[index-1]  = '\0';

        write(fd[1],Buffer,sizeof(Buffer)); // write to pipe for parent process
        close(fd[1]);
     }

    //Parent process
     else
     {
        close(fd[1]);
        char val[maxBufSize];
        FILE* ptr;
        ptr = fopen("Readme.txt", "w+"); // Opening file in write mode
        fprintf(ptr,"Parent is writing:\n");
        read(fd[0],val,sizeof(val));  // read from child process
        fprintf(ptr,"%s",val);
        close(fd[0]);
        fclose(ptr); // close file
        printf("%s\n",val);
     }
}