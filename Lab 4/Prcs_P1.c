#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    // open file with read and write access and overwrite exsisting content
    open("destination1.txt", O_CREAT|O_RDWR|O_TRUNC,0777);   
    open("destination2.txt", O_CREAT|O_RDWR|O_TRUNC,0777);
}