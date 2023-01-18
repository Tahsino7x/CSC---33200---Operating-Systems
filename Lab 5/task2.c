#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int getColCount(char const *str)
{
    int colCount = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == ' ')
            ++colCount;
    }
    return colCount + 1;
}

int main(int argc, char *argv[])
{
    FILE *ptr;
    int index = 0;
    char buffer[200];
    char *args[200];
    char tempCh;
    ptr = fopen("quiz_grades.txt", "r"); // open file in read mode

    if (NULL == ptr)
        printf("file can't be opened \n");

    while (!feof(ptr)) // read file to end
    {
        tempCh = fgetc(ptr);
        buffer[index++] = tempCh;
    }
    buffer[index - 1] = '\0';
    fclose(ptr);

    index = 0;
    char *token = strtok(buffer, "\n"); // spilt file by "\n"
    args[index] = token;

    while (token != NULL)
    {
        token = strtok(NULL, "\n");
        ++index;
        if (token != NULL)
            args[index] = token;
    }
    args[index] = NULL;
    int colCount = getColCount(args[0]);
    int grades[index + 1][colCount]; // grades array to hold grades; index is student count

    for (int i = 0; i < index; ++i)
    {
        int col = 0;
        token = strtok(args[i], " "); // spilt the txt by " " to get the column
        grades[i][col] = atoi(token);

        while (token != NULL)
        {
            token = strtok(NULL, " ");
            ++col;
            if (token != NULL)
                grades[i][col] = atoi(token); // convert numstring to int
        }
    }

    int fd[2]; // pipe file descriptor
    // fd[0] // read
    // fd[1] // write

    if (pipe(fd) == -1) // create file
    {
        printf("error opening pipe\n");
        return 1;
    }

    write(fd[1], grades, sizeof(grades)); // write to pipe for child process

    for (int i = 0; i < (colCount / 2); ++i)
    {
        if (fork() == 0) // creating master processes
        {
            for (int j = i; j < colCount; j += 2)
            {
                if (fork() == 0) // creating worker processes
                {
                    int tempgrades[index + 1][colCount];
                    read(fd[0], tempgrades, sizeof(tempgrades)); // read from pipe
                    int sum = 0;
                    for (int c = 0; c < index; ++c)
                        sum += tempgrades[c][j];
                    tempgrades[index][j] = sum;
                    write(fd[1], tempgrades, sizeof(tempgrades)); // write to pipe
                    exit(1);
                }
                wait(NULL);
            }
            exit(1);
        }
        wait(NULL);
    }

    read(fd[0], grades, sizeof(grades)); // read from pipe
    close(fd[0]);
    close(fd[1]);

    printf("\t");
    for (int r = 0; r < index + 1; ++r) // display the grades and average
    {
        if (r == index)
            printf("\nOutput: ");

        for (int c = 0; c < colCount; ++c)
            printf("%d\t", grades[r][c]);

        if (r + 1 != index)
            printf("\n\t");
    }
}