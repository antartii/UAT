# UAT - Useless (but) Adaptative Table

UAT files short for Useless (but) Adaptative Table is a type of file used for data storage purposes represented as a table.

It is inspired by .CSV files but handle some of it’s problems such as modifying the rows and columns separators and enabling the usage of comments but keeping it’s simplicity to parse and gather data.

## Initialisation

Every .UAT files starts with 2 characters, the first one being the rows separators and the second one being the columns separators.

```uat
|`
```

*Here the | character will be the row separator and the ` character will be the columns separators, but they can be changed to any other character you need or want.*

The only conditions will be to don’t have the same character for the row and the column separators.

## Row and cells separators

Rows and columns separators works as containers, being both the openers and the closers of a row or a columns.

| Line 1 | Cell 1 line 1 | Cell 2 line 1 |
| --- | --- | --- |
| Line 2 | Cell 1 line 2 | Cell 2 line 2 |

```uat
|`
|`Cell 1 line 1` `Cell 2 line 1`|
|`Cell 1 line 2` `Cell 2 line 2`|
```

Always make sure that row and cells opener have their closers later on.

## Exceptions

Row separator character won’t be used as a separator if they are contained inside of a cell, meaning you can use thoses character for you values.

| Line 1 | Cell with | character | Cell 2 line 1 |
| --- | --- | --- |
| Line 2 | Cell 1 line 2 | Cell 2 line 2 |

```uat
|`
|`Cell with | character` `Cell 2 line 1`|
|`Cell 1 line 2` `Cell 2 line 2`|
```

## Commentary

Every character written outside of the rows or cells separators won’t be considered as data therefore they will be commentary.

| Line 1 | Cell with | character | Cell 2 line 1 |
| --- | --- | --- |
| Line 2 | Cell 1 line 2 | Cell 2 line 2 |

```uat
|` This is a comment before the table
|`Cell with | character` This is a comment between cells `Cell 2 line 1`| This is a comment between rows
|`Cell 1 line 2` `Cell 2 line 2`|
This is a comment at the end of the table
```

## Parsing and usage

We recommend to parse the table of data from .UAT into array of array inside of your code :

- **C :** char *** (array of array of string)
- **C++ :** vector<vector<string>> (array of array of string)

We’ve developped some libs to handle .UAT files for the C language, but you can always improve our functions by changing the open-source functions or you can make a parser by yourself !

# CUAT - C library for .UAT files handling

C library for .UAT datas and files handling.
Version 1.0.0

## Usage

You’ll first need to download the libraries from the Github repository

```bash
git clone etc... or https etc..
```

Copy the `C/cuat/` folder from the `uat_libraries` you just downloaded into your project folder.

```bash
cp C:/users/Downloads/uat_libraries/C/cuat/ path/to/your/project/folder
```

Generate the static library `cuat.a` using the makefile of the `cuat/` folder

```bash
make -C cuat/
```

Compile your C project including the `cuat.a` and `includes/cuat.h` files from the `cuat/` folder

```bash
gcc -Icuat/includes/ cuat.a main.c -o program
```

## Functions

- **Conversions**
    - **table_to_uat :** Convert a str table into a uat string.
        
        ```c
        char *table_to_uat(const char ***table, const unsigned char row_separator, const unsigned char column_separator)
        ```
        
    - **uat_line_to_cells :** splits a uat line into an array of string of the cells from this row
        
        ```c
        char **uat_line_to_cells(const char *uat_line, unsigned char column_separator)
        ```
        
    - **uat_string_to_rows :** convert a uat string into an array of strings of the rows from this uat string
        
        ```c
        char **uat_string_to_rows(const char *uat_string)
        ```
        
    - **uat_string_to_table :** split a uat string into a table of string forming an uat table
        
        ```c
        char ***uat_string_to_table(char *uat_string)
        ```
        
- **Count**
    - **count_uat_cells_from_line :** Count the number of cells from the row of an uat table
        
        ```c
        int count_uat_cells_from_row(const char *uat_line, unsigned char column_separator)
        ```
        
    - **count_uat_row :** Count the number of rows inside of a uat string
        
        ```c
        int count_uat_row(const char *uat_string)
        ```
        
- **String**
    - **char_to_string :** convert a char to a malloced string
        
        ```c
        char *char_to_string(const unsigned char c)
        ```
        
    - **strcat_char :** append a char to a string
        
        ```c
        char *strcat_char(char *str, char c)
        ```
        
- **Array of string**
    - **append_str_arr :** Append an str into an array of str
        
        ```c
        int append_str_arr(char ***str_arr_address, const char *new_str)
        ```
        
    - **str_arr_dup :** duplicate the content of a string array
        
        ```c
        char **str_arr_dup(const char **str_arr)
        ```
        
- **Array of pointers**
    - **get_ptr_arr_size :** Get the count of elements inside of an array of pointers.
        
        ```c
        int get_ptr_arr_size(const void **array)
        ```
        
    - **free_ptr_arr_content :** free every elements of an array of pointers.
        
        ```c
        int free_ptr_arr_content(void **array)
        ```
        
    - **free_ptr_arr :** Free an array of pointers and the content of it's elements.
        
        ```c
        int free_ptr_arr(void **array)
        ```
        
    - **free_ptr_table :** free a table (2D array) of pointers and the subcontent of it.
        
        ```c
        int free_ptr_table(void ***table)
        ```
        
- **Table of string**
    - **append_str_table :** append an array of string to a table of string (2D array)
        
        ```c
        int append_str_table(char ****str_table_address, const char **new_str_arr)
        ```
    ## Example
    **Converting a uat file to a uat table**
    ```C
    #include "cuat.h"

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

    int main(void)
    {
        char file_path[] = "../example.uat";
        char *file_content = read_file_content(file_path);
        char ***uat_table = NULL;

        if (!file_content)
            return 1;

        // This is where we're converting the uat string into a table [row][column]
        uat_table = uat_string_to_table(file_content);

        puts(file_content);

        // we can show each cells here
        for (int i = 0; uat_table[i]; i += 1) {
            for (int j = 0; uat_table[i][j]; j += 1)
                puts(uat_table[i][j]);
        }
        
        // We're freeing everything
        free_ptr_table((void ***) uat_table);
        free(file_content);
        return 0;
    }
    ```
    **Converting a string table to a uat string
    ```C
    int main(void)
    {
        char ***str_table = NULL;
        char **str_row_1 = NULL;
        char **str_row_2 = NULL;
        char *uat_string = NULL;

        // we're initializing the rows
        append_str_arr(&str_row_1, "This");
        append_str_arr(&str_row_1, "is");
        append_str_arr(&str_row_1, "a");
        append_str_arr(&str_row_1, "test");

        append_str_arr(&str_row_2, "for");
        append_str_arr(&str_row_2, "example");
        append_str_arr(&str_row_2, "purposes");

        // We're adding the rows to the table
        append_str_table(&str_table, (const char **) str_row_1);
        append_str_table(&str_table, (const char **) str_row_2);

        // We're converting the table to a uat string
        uat_string = table_to_uat((const char ***) str_table, '|', '`');

        // We're showing the uat string
        puts(uat_string);

        // We're freeing or destorying eveything
        free(uat_string);
        free_ptr_arr((void **) str_row_1);
        free_ptr_arr((void **) str_row_2);
        free_ptr_table((void ***) str_table);
    }
    ```
        

# To do list

- [ ]  C++ base uat library
- [ ]  Python base uat library
- [ ]  Epitech’s coding style library (C programming language)

# Team

Anta - Dev for the C, C++ and python libraries