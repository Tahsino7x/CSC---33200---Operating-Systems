#include <stdio.h>
#include <unistd.h>
#include<fcntl.h> 
#include <errno.h>

int main (int argc, char* argv[])
{
char* filepath = argv[1];
int returnval;

// Check file existence
returnval = access (filepath, F_OK);
if (returnval == 0)
    printf ("\n %s exists\n", filepath);
else
{
    if (errno == ENOENT)
        printf ("%s does not exist\n", filepath);
    else if (errno == EACCES)
        printf ("%s is not accessible\n", filepath);
return 0;
}

// Check read access
returnval = 0;
returnval = access (filepath, R_OK);
if (returnval == 0)
    printf ("%s has Read permissions.\n", filepath);
else
{
    if (errno == ENOENT)
        printf ("%s No such file or directory.\n", filepath);
    else if (errno == EACCES)
        printf ("%s Read Permission denied.\n", filepath);
}

// Check write access
returnval = 0;
returnval = access (filepath, W_OK);
if (returnval == 0)
    printf ("%s has Write permissions\n", filepath);
else
{
    if (errno == ENOENT)
        printf ("%s No such file or directory.\n", filepath);
    else if (errno == EACCES)
        printf ("%s Write Permission denied.\n", filepath);
}

//Task1 1(b)
int fd = open("destination.txt", O_RDONLY | O_CREAT); // creates and open in read mode   
if(fd == -1)
    printf("open () failed with error [%s]\n", strerror(errno));
else 
    printf("\n Open() successful\n");

close(fd);

return 0;
}