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

| Line 1 | Cell with \| character | Cell 2 line 1 |
| --- | --- | --- |
| Line 2 | Cell 1 line 2 | Cell 2 line 2 |

```uat
|`
|`Cell with | character` `Cell 2 line 1`|
|`Cell 1 line 2` `Cell 2 line 2`|
```

## Commentary

Every character written outside of the rows or cells separators won’t be considered as data therefore they will be commentary.

| Line 1 | Cell with \| character | Cell 2 line 1 |
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
- **C++ :** vector<vector\<string>> (array of array of string)

We’ve developped some libs to handle .UAT files for the C language, but you can always improve our functions by changing the open-source functions or you can make a parser by yourself !

- **Epiuat** : Library for uat file handling in C made for the coding style of epitech
- **Pyuat** : Python library for uat file handling

# To do list

- [ ]  Fix the C1 coding style error somewhere
- [ ]  C base uat library (cleaned without epitech's coding style)
- [ ]  C++ base uat library

# Team

[DEV] Anta - Dev for the C, C++ and python libraries
