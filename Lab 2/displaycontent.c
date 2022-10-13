#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char* argv[])
{
    char* filepath = argv[1];
    int returnval;
    returnval = access (filepath, F_OK);   // Check file existence
    if (returnval == 0)
    {
        FILE *fptr;
        char temp_ch;
        fptr = fopen(filepath,"r"); // read-only mode
        
        while (temp_ch != EOF)
        {
            temp_ch = fgetc(fptr);
            if(temp_ch!=EOF)
                printf("%c", temp_ch);
        }

        //close file
        fclose(fptr);
    }

    // error condition
    else
    {
     if (errno == ENOENT)
        printf ("%s does not exist\n", filepath);
    else if (errno == EACCES)
        printf ("%s is not accessible\n", filepath);
    return 0;
    }
}