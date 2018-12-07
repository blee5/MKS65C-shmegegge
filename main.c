#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main()
{
    int shmid = shmget(0x1234, 201, 0644);
    if (shmid < 0)
    {
        printf("Shared memory not found, creating one.\n");
        shmid = shmget(0x1234, 201, 0644 | IPC_CREAT);
        if (shmid < 0)
        {
            printf("Error creating shared memory: %s", strerror(errno));
        }
    }
    char *data = shmat(shmid, NULL, 0);
    char input[256];
    for (;;)
    {
        printf("What should I do with the memory? (read/write/delete/exit)\n");
        fgets(input, 200, stdin);
        /* Strip newline */
        input[strlen(input) - 1] = 0;
        if (strcmp(input, "read") == 0)
        {
            printf("============================\nShared Memory Contents\n============================\n%s============================\n", data);
        }
        else if (strcmp(input, "write") == 0)
        {
            printf("Enter string to write:\n");
            fgets(input, 200, stdin);
            strcpy(data, input);
        }
        else if (strcmp(input, "delete") == 0)
        {
            shmctl(shmid, IPC_RMID, NULL);
            exit(0);
        }
        else if (strcmp(input, "exit") == 0)
        {
            exit(0);
        }
        else
        {
            printf("Invalid command.\n");
        }
    }
}
