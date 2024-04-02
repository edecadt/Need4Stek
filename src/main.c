/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** main.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *write_command(const char *command, bool need_output)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    write(1, command, strlen(command));
    write(1, "\n", 1);
    read = getline(&line, &len, stdin);
    if (read == -1) {
        free(line);
        return NULL;
    }
    if (!need_output) {
        free(line);
        return NULL;
    }
    return line;
}

int main(void)
{
    write_command("START_SIMULATION", false);
    write_command("CAR_FORWARD:0.5", false);
    while (1) {
        char *line = write_command("GET_INFO_LIDAR", true);
        if (line == NULL)
            break;
        dprintf(2, "%s", line);
        free(line);
    }
    return (0);
}
