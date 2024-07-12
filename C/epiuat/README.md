# EPIUAT - Epitech’s uat library

This uat library is specifically made for Epitech’s student that needs to have a program that follows some rules in their coding-style.

*/!\ The current team may not update this library after the end of the year 2025 /!\*
*Version 1.1.0*

---

# Installation

1. Copy the library folder into your project directory
    
    ```bash
    cp C:/user/Downloads/UAT/C/epiuat path/to/your/project/folder
    ```
    
2. Include the epiuat.h file into your project’s files
    
    ```c
    #include "epiuat.h"
    ```
    
3. Compile the epiuat library by using it’s Makefile
    
    ```c
    Make -C epiuat
    ```
    
4. Compile your project by including the header and .a files of the epiuat directory
    
    ```c
    gcc -Iepiuat/includes/ epiuat/epiuat.a main.c -o program
    ```

---

# Example
## Converting an uat file into a char *** (table of string)
```c
// main.c

#include "epiuat.h"

char *read_file_content(const char *file_path)
{
    char *file_content = NULL;
    FILE *file = NULL;
    long file_size = 0;

    if (!file_path)
        return NULL;
    file = fopen(file_path, "r");
    if (!file)
        return NULL;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }
    file_size = ftell(file);
    rewind(file);
    file_content = malloc(sizeof(char) * (file_size + 1));
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
    fclose(file);
    return file_content;
}

int example_uat_file_to_str_table(void)
{
    char file_path[] = "example.uat";
    char *file_content = read_file_content(file_path);
    char ***uat_table = NULL;

    if (!file_content)
        return 1;
    uat_table = uat_string_to_table(file_content);
    for (int i = 0; uat_table[i]; i += 1) {
        for (int j = 0; uat_table[i][j]; j += 1)
            puts(uat_table[i][j]);
        puts("----------------------");
    }
    free_ptr_table((void ***) uat_table);
    free(file_content);
    return 0;
}
```

## Converting a table of string to a uat string

```c
// main.c

#include "epiuat.h"

int example_str_table_to_uat_string(void)
{
    char ***str_table = NULL;
    char **str_row_1 = NULL;
    char **str_row_2 = NULL;
    char *uat_string = NULL;

    // we're initing the table
    append_str_arr(&str_row_1, "This");
    append_str_arr(&str_row_1, "is");
    append_str_arr(&str_row_1, "a");
    append_str_arr(&str_row_1, "test");

    append_str_arr(&str_row_2, "for");
    append_str_arr(&str_row_2, "example");
    append_str_arr(&str_row_2, "purposes");

    append_str_table(&str_table, (const char **) str_row_1);
    append_str_table(&str_table, (const char **) str_row_2);

    uat_string = table_to_uat_str((const char ***) str_table, '|', '`');

    puts(uat_string);
    
    free(uat_string);
    free_ptr_arr((void **) str_row_1);
    free_ptr_arr((void **) str_row_2);
    free_ptr_table((void ***) str_table);
}
```

---

# Functions

## Conversions

**uat_rows_from_str**

Extracts rows from a uat string

```c
char **uat_rows_from_str(char *uat_str, char row_separator, char col_separator)
{
    char **uat_rows = NULL;
    int is_in_cell = 0;
    int stamp = 0;
    char *temp_row = NULL;

    if (!uat_str)
        return NULL;
    for (int i = 2; uat_str[i]; i += 1) {
        if (uat_str[i] == col_separator && stamp)
            is_in_cell = !is_in_cell;
        if (uat_str[i] == row_separator && !is_in_cell && stamp) {
            temp_row = strndup(uat_str + stamp, i - stamp);
            append_str_arr(&uat_rows, temp_row);
            free(temp_row);
            stamp = 0;
        } else if (uat_str[i] == row_separator && !is_in_cell && !stamp) // C1 conditional branching
            stamp = i + 1;
    }
    return uat_rows;
}
```

**uat_cells_from_row**

Extract cells from a uat row

```c
char **uat_cells_from_row(char *uat_row, char col_separator)
{
    char **uat_cells = NULL;
    int stamp = 0;
    char *temp_cell = NULL;

    if (!uat_row)
        return NULL;
    for (int i = 0; uat_row[i]; i += 1) {
        if (uat_row[i] == col_separator && stamp) {
            temp_cell = strndup(uat_row + stamp, i - stamp);
            append_str_arr(&uat_cells, temp_cell);
            free(temp_cell);
            stamp = -1;
        }
        if (uat_row[i] == col_separator && !stamp)
            stamp = i + 1;
        if (stamp == -1)
            stamp = 0;
    }
    return uat_cells;
}
```

**uat_string_to_table**

Convert a uat string to a table of string

```c
char ***uat_string_to_table(char *uat_str)
{
    char ***uat_table = NULL;
    char **uat_rows = NULL;
    char **temp_row = NULL;
    char row_separator = '\0';
    char col_separator = '\0';

    if (!uat_str)
        return NULL;
    row_separator = uat_str[0];
    col_separator = uat_str[1];
    uat_rows = uat_rows_from_str(uat_str, row_separator, col_separator);
    for (int i = 0; uat_rows[i]; i += 1) {
        temp_row = uat_cells_from_row(uat_rows[i], '`');
        append_str_table(&uat_table, temp_row);
        free_ptr_arr(temp_row);
        free(uat_rows[i]);
    }
    free(uat_rows);
    return uat_table;
}
```

**table_to_uat_str**

Convert a table of string into a uat string.

```c
char *table_to_uat_str(char ***table, char row_separator, char col_separator)
{
    char *uat_str = NULL;
    int len_str = 0;

    uat_str = char_to_string(row_separator);
    uat_str = strcat_char(uat_str, col_separator);
    len_str += 2;
    for (int i = 0; table[i]; i += 1) {
        uat_str = strcat_char(uat_str, row_separator);
        len_str += 1;
        for (int j = 0; table[i][j]; j += 1) {
            uat_str = strcat_char(uat_str, col_separator);
            len_str += 2 + strlen(table[i][j]);
            uat_str = realloc(uat_str, len_str);
            strcat(uat_str, table[i][j]);
            uat_str = strcat_char(uat_str, col_separator);
        }
        uat_str = strcat_char(uat_str, row_separator);
        len_str += 1;
    }
    return uat_str;
}
```

## Others

**get_ptr_arr_size**

Get the size of an array of pointers with a NULL terminator

```c
int get_ptr_arr_size(const void **array)
{
    int count = 0;

    if (!array)
        return 0;
    for (; array[count] != NULL; count += 1);
    return count;
}
```

**free_ptr_arr_content**

Free the content of an array of pointer without freeing the array itself

```c
int free_ptr_arr_content(void **array)
{
    if (!array)
        return -1;
    for (int i = 0; array[i] != NULL; i += 1)
        free(array[i]);
    return 0;
}
```

**free_ptr_arr**

Free an array of pointer and it’s content

```c
int free_ptr_arr(void **array)
{
    if (!array)
        return -1;
    free_ptr_arr_content(array);
    free(array);
    return 0;
}
```

**free_ptr_table**

Free a table of pointer and it’s content

```c
int free_ptr_table(void ***table)
{
    if (!table)
        return -1;
    for (int i = 0; table[i]; i += 1)
        free_ptr_arr(table[i]);
    free(table);
    return 0;
}
```

**append_str_arr**

Add a string to an array of string

```c
int append_str_arr(char ***str_arr_address, const char *new_str)
{
    char **str_arr_copy = NULL;
    int str_arr_size = 0;

    if (!str_arr_address || !new_str)
        return -1;
    str_arr_size = get_ptr_arr_size((const void **) *str_arr_address);
    str_arr_copy = malloc(sizeof(char *) * (str_arr_size + 2));
    for (int i = 0; i < str_arr_size; i += 1)
        str_arr_copy[i] = (*str_arr_address)[i];
    str_arr_copy[str_arr_size] = strdup(new_str);
    str_arr_copy[str_arr_size + 1] = NULL;
    free(*str_arr_address);
    *str_arr_address = str_arr_copy;
    return 0;
}
```

**str_arr_dup**

Duplicate an array of string

```c
char **str_arr_dup(const char **str_arr)
{
    char **duplicate = NULL;
    int arr_size = 0;

    if (!str_arr)
        return NULL;
    arr_size = get_ptr_arr_size((const void **) str_arr);
    duplicate = malloc(sizeof(char *) * (arr_size + 1));
    for (int i = 0; i < arr_size; i += 1)
        duplicate[i] = strdup(str_arr[i]);
    duplicate[arr_size] = NULL;
    return duplicate;
}
```

**append_str_table**

Add an array of string to a table of string

```c
int append_str_table(char ****str_table_address, const char **new_str_arr)
{
    char ***new_str_table = NULL;
    int curr_size = 0;

    if (!str_table_address || !new_str_arr)
        return -1;
    curr_size = get_ptr_arr_size((const void **) *str_table_address);
    new_str_table = malloc(sizeof(char **) * (curr_size + 2));
    for (int i = 0; i < curr_size; i += 1)
        new_str_table[i] = (*str_table_address)[i];
    new_str_table[curr_size] = str_arr_dup(new_str_arr);
    new_str_table[curr_size + 1] = NULL;
    free(*str_table_address);
    *str_table_address = new_str_table;
    return 0;
}
```

**strcat_char**

Add a char to a string

```c
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
```

**char_to_string**

convert a character into a string

```c
char *char_to_string(const unsigned char c)
{
    char *str = NULL;

    str = malloc(sizeof(char) * 2);
    str[0] = c;
    str[1] = '\0';
    return str;
}
```

---

# Team
[DEV] Tom SENG (Anta) - Student in software engineering