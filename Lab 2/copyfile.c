#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char* argv[])
{
    char* filepath = argv[1];
    char* desFile = "destination.txt"; // des file
    int returnval;
    returnval = access (filepath, F_OK);   // Check file existence
    
    if (returnval == 0)
    {
        FILE *fptrSrc; // src file
        FILE *fptrDes;  // destination file
        char temp_ch;
        fptrSrc = fopen(filepath,"r"); // read-only mode
        fptrDes = fopen(desFile,"w"); // write mode

        // read all chars from file and write to des file
        while (temp_ch != EOF){
            temp_ch = fgetc(fptrSrc);
            if(temp_ch!=EOF)
                putc(temp_ch,fptrDes);
        }

        //close files
        fclose(fptrSrc);
        fclose(fptrDes);
    }

    // error condition
    else
    {
     if (errno == ENOENT)
        printf ("%s does not exist\n", filepath);
    else if (errno == EACCES)
        printf ("%s is not accessible\n", filepath);
    }
}