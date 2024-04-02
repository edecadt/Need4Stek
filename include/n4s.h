/*
** EPITECH PROJECT, 2024
** Need4Stek
** File description:
** n4s.h
*/

#ifndef N4S_H
    #define N4S_H

    #include <stdbool.h>

    #define UNUSED __attribute__((unused))
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0

    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define RESET "\033[0m"

    #define TURN_LEFT 1
    #define TURN_RIGHT -1

    #define LEFT_LIDAR 0
    #define RIGHT_LIDAR 31
    #define FRONT_LIDAR 15

    #define DEFAULT_SPEED 0.6

typedef struct angle_s {
    float threshold;
    float angle;
} angle_t;

typedef struct car_s {
    float speed;
    float direction;
    float left;
    float right;
    float front;
} car_t;

typedef struct ai_s {
    char *data;
    float *distance;
    bool is_running;
    car_t car;
} ai_t;

static const angle_t ANGLES[] = {
    {400, 0.38},
    {500, 0.34},
    {700, 0.29},
    {1000, 0.25},
    {1300, 0.07},
    {0, 0.01}
};

char *write_command(const char *command, const bool need_output);
void my_print(char *str);
float *lidar_info(char *data);
void process_ai(ai_t *ai);

#endif //N4S_H
