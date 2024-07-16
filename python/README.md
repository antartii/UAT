# Python - Python uat library

Python library for uat files handlings.
*Version 1.0.0*

---

# Installation

1. Copy the library folder into your project directory
    
    ```bash
    cp C:/user/Downloads/UAT/python/pyuat path/to/your/project/folder
    ```
    
2. Import the pyuat module into your project’s files
    ```python
    from pyuat.pyuat import everything
    ```

---

# Example
## Converting an uat file into a char *** (table of string)
```python
from pyuat.pyuat import *

def read_file_content(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            return file.read()
    except FileNotFoundError or IOError:
        return ""

file_content = read_file_content("../example.uat")
uat_table = Pyuat.uat_string_to_table(test1)
print(uat_table)
```

## Converting a table of string to a uat string

```python
table = [
    ["This", "is", "a|"],
    ["test", "for", "test", "purposes"]
]
uat_string = Pyuat.table_to_uat_string(test, '|', '`')
puts(uat_string)
```

---

# Functions
All of the functions are stored under the **Pyuat** class.

**Pyuat.uat_string_to_table** : Convert a uat string into a table of string

```python
def uat_string_to_table(uat_string):
    uat_table = []
    row_separator = uat_string[0]
    col_separator = uat_string[1]
    reading_a_row = False
    reading_a_col = False
    row_index = 0
    col_index = 0
    for i in range(2, len(uat_string)):
        if uat_string[i] == row_separator and not reading_a_col:
            reading_a_row = not reading_a_row
            if not reading_a_row:
                row_index += 1
                col_index = 0
            else : uat_table.append([])
        if uat_string[i] == col_separator and reading_a_row:
            reading_a_col = not reading_a_col
            if not reading_a_col: col_index += 1
            else : uat_table[row_index].append("")
        if reading_a_row and reading_a_col and uat_string[i]!=col_separator:
            uat_table[row_index][col_index] += uat_string[i]
    return uat_table
```

**Pyuat.table_to_uat_string** : Convert a table into a uat string
```python
def table_to_uat_string(table, row_separator, col_separator):
    uat_string = row_separator + col_separator

    for row in table:
        uat_string += row_separator
        for cell in row:
            uat_string += col_separator + cell + col_separator
        uat_string += row_separator
    return uat_string
```
---

# Team
[DEV] Tom SENG (Anta) - Student in software engineering