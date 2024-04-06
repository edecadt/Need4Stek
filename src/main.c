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
#include "n4s.h"

static void init_ai(ai_t *ai)
{
    ai->data = write_command("START_SIMULATION", true);
    if (ai->data == NULL || atoi(ai->data) != 1) {
        free(ai->data);
        my_print(RED"Error: Couldn't start the simulation\n");
        exit(EXIT_ERROR);
    }
    ai->is_running = true;
    ai->car.speed = DEFAULT_SPEED;
    ai->car.direction = 0.0;
    my_print(GREEN"Simulation started\n");
}

static void destroy_ai(ai_t *ai)
{
    free(ai->data);
}

void check_end(ai_t *ai)
{
    char *end = strrchr(ai->data, ':') + 2;
    if (strcmp(end, "No further info\n") == 0) {
        return;
    }
    if (atoi(end + 1) == -1) {
        ai->data = write_command("STOP_SIMULATION", true);
        fprintf(stderr, "%s", ai->data);
        ai->is_running = false;
    }
}

int main(void)
{
    ai_t ai;

    init_ai(&ai);
    while (ai.is_running) {
        ai.data = write_command("GET_INFO_LIDAR", true);
        check_end(&ai);
        ai.distance = lidar_info(ai.data);
        process_ai(&ai);
    }
    destroy_ai(&ai);
    return EXIT_SUCCESS;
}
