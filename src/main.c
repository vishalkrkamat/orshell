#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *get_input(char *buff, size_t size);
char **tokenize(char *input);
int create_process(char **argv);

int main()
{
    size_t sizebuf = 16;
    char *buff     = malloc(sizebuf);

    while (strcmp(buff, "exit") != 0)
    {
        buff                      = get_input(buff, sizebuf);
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

char *get_input(char *buff, size_t size)
{
    size_t len = 0;
    int c;

    printf("$ ");
    while ((c = getchar()) != EOF && c != '\n')
    {
        if (len + 1 >= size)
        {
            size      = 2 * size;
            char *tmp = realloc(buff, size);
            if (!tmp)
            {
                free(buff);
                fprintf(stderr, "Failed allocation");
                return NULL;
            }
            buff = tmp;
        }
        buff[len++] = (char)c;
    }
    buff[len] = '\0';
    return buff;
}

char **tokenize(char *input)
{
    char **arr = NULL;
    int size   = 0;
    char *tok  = strtok(input, " ");
    while (tok != NULL)
    {
        arr = realloc(arr, (size + 1) * sizeof(char *));

        arr[size] = malloc(strlen(tok) + 1);

        strcpy(arr[size], tok);
        size++;

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
