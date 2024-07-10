/**
 * @file str.c
 * @author Tom SENG (Anta) [antarti.fr]
 * @brief Fuctions for string handlings
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "cuat.h"

/**
 * @brief append a char to a string
 * 
 * @param str source string
 * @param c character appended
 * @return Returns the string with the character appended or NULL if str is NULL from the start.
 */
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

/**
 * @brief convert a char to a malloced string
 * 
 * @param c character that will be converted
 * @return malloced string of the character, it ends with '\0' terminator.
 */
char *char_to_string(const unsigned char c)
{
    char *str = NULL;

    str = malloc(sizeof(char) * 2);
    str[0] = c;
    str[1] = '\0';
    return str;
}
