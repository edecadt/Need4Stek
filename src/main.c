/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** main.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
    my_print(GREEN"Simulation stopped\n");
}

int main(void)
{
    ai_t ai;

    init_ai(&ai);
    while (ai.is_running) {
        ai.data = write_command("GET_INFO_LIDAR", true);
        if (ai.data == NULL) {
            ai.is_running = false;
            my_print(RED"Error: Couldn't get the lidar info\n");
            break;
        }
        ai.distance = lidar_info(ai.data);
        process_ai(&ai);
    }
    destroy_ai(&ai);
    return EXIT_SUCCESS;
}
