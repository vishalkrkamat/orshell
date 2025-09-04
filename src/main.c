#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char **tokenize(char *input);
int create_process(char **argv);

int main()
{
    char buff[400] = "";
    while (strcmp(buff, "exit") != 0)
    {
        printf("$ ");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = 0;
        char **arr                = tokenize(buff);
        int size                  = 0;
        for (; arr[size] != NULL; size++)
        {
        }
        create_process(arr);
        for (int i = 0; arr[i] != NULL; i++)
        {
            free(arr[i]);
        }
        free(arr);
    }
}

char **tokenize(char *input)
{
    char **arr = NULL;
    int size   = 0;
    char *tok  = strtok(input, " ");
    int i      = 0;
    while (tok != NULL)
    {
        arr = realloc(arr, (size + 1) * sizeof(char *));

        arr[size] = malloc(strlen(tok) + 1);

        strcpy(arr[size], tok);
        size++;

        i++;
        tok = strtok(NULL, " ");
    }

    arr       = realloc(arr, (size + 1) * sizeof(char *));
    arr[size] = NULL;

    return arr;
}

int create_process(char *argv[])
{

    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(argv[0], argv);
        perror("execvp failed");
        _exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        printf("fork failed\n");
        exit(1);
    }
    return 0;
}
