#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char* argv[])
{
    char* filepath = argv[1];
    char* desFile = "destination.txt";
    int returnval;
    returnval = access (filepath, F_OK);   // Check file existence
    
    if (returnval == 0)
    {
        FILE *fptrSrc; // src file
        FILE *fptrDes; // destination file
        
        fptrSrc = fopen(filepath,"r"); // read-only mode
        fptrDes = fopen(desFile,"w"); // write mode

        char temp_ch;
        int count = 0; // count to track char read
        int max = 100; // read 100 per iteration

        // read all chars from file
        while (temp_ch != EOF)
        {
            temp_ch = fgetc(fptrSrc);
            if(temp_ch!=EOF)
            {
                ++count;
                if(temp_ch == '1')  
                    temp_ch = 'L'; // replace 1 with L
                putc(temp_ch,fptrDes);  
                if(count == max)  // if count equals 100
                {
                    fprintf(fptrDes,"XYZ");
                    count =0; // reset count to 0
                }
            }
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