#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    bool isrunning = true;
    char buffer[30];
    char temp;
    char *args[30];
    int child;

    while (isrunning)
    {
        printf("Command:");
        fgets(buffer, sizeof(buffer), stdin); // get command from user
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "exit") == 0)
        { // stop program
            isrunning = false;
            break;
        }

        int index = 0;
        char *token = strtok(buffer, " "); // spilt the string by " "
        args[index] = token;

        while (token != NULL)
        {
            token = strtok(NULL, " ");
            ++index;
            if (token != NULL) // parse the spilt string to an args cstring array
                args[index] = token;
        }
        args[index] = NULL;

        child = fork(); // create child process

        if (child == 0)
        {
            execvp(args[0], args); // execute the parser string as the cmd argument
            exit(1);
        }
        wait(NULL);
    }
}