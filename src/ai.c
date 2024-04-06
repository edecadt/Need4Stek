/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** ai.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "n4s.h"

void moove_forward(ai_t *ai, const float speed)
{
    char *str = malloc(sizeof(char) * 50);

    snprintf(str, 50, "CAR_FORWARD:%f", speed);
    ai->data = write_command(str, true);
    check_end(ai);
    free(str);
}

void mooove_backward(ai_t *ai, const float speed)
{
    char *str = malloc(sizeof(char) * 50);

    snprintf(str, 50, "CAR_BACKWARDS:%f", speed);
    ai->data = write_command(str, true);
    check_end(ai);
    free(str);
}

void turn_wheels(ai_t *ai, double factor)
{
    char str[50];
    float angle = 0.0;
    size_t num_entries = sizeof(ANGLES) / sizeof(ANGLES[0]);

    for (size_t i = 0; i < num_entries; ++i) {
        if (ai->car.front < ANGLES[i].threshold) {
            angle = ANGLES[i].angle;
            break;
        }
    }
    if (angle > 0.1)
        ai->car.speed = 0.2;
    else
        ai->car.speed = DEFAULT_SPEED;
    snprintf(str, sizeof(str), "WHEELS_DIR:%f", angle * factor);
    ai->data = write_command(str, true);
    check_end(ai);
}

void process_ai(ai_t *ai)
{
    ai->car.left = ai->distance[LEFT_LIDAR];
    ai->car.right = ai->distance[RIGHT_LIDAR];
    ai->car.front = ai->distance[FRONT_LIDAR];
    if (ai->car.left > ai->car.right)
        turn_wheels(ai, TURN_LEFT);
    else
        turn_wheels(ai, TURN_RIGHT);
    if (ai->car.left == 0.0 || ai->car.right == 0.0 || ai->car.front == 0.0) {
        if (ai->car.left < ai->car.right)
            turn_wheels(ai, TURN_LEFT);
        else
            turn_wheels(ai, TURN_RIGHT);
        mooove_backward(ai, ai->car.speed);
    } else
        moove_forward(ai, ai->car.speed);
}
