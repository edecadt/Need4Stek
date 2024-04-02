/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** utils.c
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "n4s.h"

void my_print(char *str)
{
    fprintf(stderr, "%s"RESET, str);
}

char *write_command(const char *command, const bool need_output)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

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

float *lidar_info(char *data)
{
    const char *token = NULL;
    float *lidar = malloc(sizeof(float) * 32);

    if (lidar == NULL)
        return NULL;
    token = strtok(data, ":");
    if (token == NULL)
        return NULL;
    for (int i = 0; i < 2; i++) {
        token = strtok(NULL, ":");
        if (token == NULL)
            return NULL;
    }
    for (int i = 0; i < 32; i++) {
        token = strtok(NULL, ":");
        if (token == NULL)
            return NULL;
        lidar[i] = atof(token);
    }
    return lidar;
}
