# ➕➖✖️➗ExpressionConverter

A **C++ program** for converting between **Infix**, **Postfix**, and **Prefix** expressions using a custom **Stack** data structure.  
This project was created for educational purposes — particularly for practicing stack operations and expression parsing in Data Structures courses.

---

## About the Project

This program takes a mathematical expression as input and automatically detects its type  
(**infix**, **prefix**, or **postfix**).  
It then allows the user to convert it to another expression type.  
For example, if the input is **A+B**, it detects it as **infix**, and then shows the user two conversion options: **prefix** or **postfix**.

The conversion logic is implemented using a stack and follows  
operator precedence and associativity rules.

---

## How to Run

### 1. Compile
Use the following command to compile the program:
```bash
g++ main.cpp -o converter
```

---

## Example Usage

### example 1
#### input
insert the expression: A+B*C
#### output
infix 
Do you want convert to prefix or postfix? postfix
ABC*+
### example 2
#### input
insert the expression: +A*BC
#### output
prefix
Do you want convert to infix or postfix? infix
(A+(B*C))

---

## Features

- Automatically detects expression type (infix, prefix, postfix)
- Checks parentheses validity
- Converts between all three notations
- Uses a custom Stack class implementation
- Simple, interactive text-based interface

---

## Used Libraries

```cpp
#include <iostream>
#include <string>
#include <algorithm>
```

---

## Author

Mani Arab
2025 — All rights reserved.

---

## License

This project is licensed under the [MIT License](./LICENSE).  
You are free to use, modify, and share this code for educational and learning purposes.



