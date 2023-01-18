#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
     FILE *fptrSrc; // src file
     FILE *fptrDes1; // destination file
     FILE *fptrDes2; // destination file

     fptrSrc = fopen("Source.txt","r"); // read-only mode
     fptrDes1 = fopen("destination1.txt","w"); // write mode
     fptrDes2 = fopen("destination2.txt","w"); // write mode

    char temp_ch;
    int count = 0; // count to track char read

      // read all chars from file
        while (temp_ch != EOF)
        {
            temp_ch = fgetc(fptrSrc);
            if(temp_ch!=EOF)
            {
                ++count; 
                if(count <=100)  // if count equals 100
                {
                    if(temp_ch == '1')  
                        temp_ch = 'L'; // replace 1 with L
                    putc(temp_ch,fptrDes1); 
                }//
                else if(count>100 && count<=150)
                {
                    if(temp_ch == '3')  
                        temp_ch = 'E'; // replace 1 with L
                    putc(temp_ch,fptrDes2); 
                }//
                else if(count>150)
                    count=0;
            }//
        }//
        
    //close files
    fclose(fptrSrc);
    fclose(fptrDes1);
    fclose(fptrDes2);
}