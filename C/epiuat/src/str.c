/*
** EPITECH PROJECT, 2024
** epiuat
** File description:
** str
*/

#include "epiuat.h"

char *strcat_char(char *str, char c)
{
    int len = 0;
    char *new_str = NULL;

    if (!str)
        return NULL;
    len = strlen(str);
    new_str = realloc(str, len + 2);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return new_str;
}

char *char_to_string(const unsigned char c)
{
    char *str = NULL;

    str = malloc(sizeof(char) * 2);
    str[0] = c;
    str[1] = '\0';
    return str;
}
