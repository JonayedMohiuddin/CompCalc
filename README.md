# X-Parser (Advanced Expression Evaluator)
```
       ____     _____
      /\   \   //   /
      \ \   \ //   /         ______
       \ \   \/   /    ___  | |  _ \ __ _ _ __ ___  ___ _ __
        \ \       \   |___| | | |_) / _` | '__/ __|/ _ \ '__|
        / /   /\   \  |___| | |  __/ (_| | | \\__ \  __/ |
       / /   /\ \   \       |_|_|  \\__,_|_| ||___/\___|_|
      / /   /  \ \   \
      \/___/    \_\___\                                  
```
## Features
 - Lightweight and fast expression parser
 - New functions can easily be added
 - Compiled expressions are cached for performance and later use
 - Result types of STRING, NUMBER
 - Constants
 - Variables

## Requirements

This project uses C++ 21 and requires no additional libraries other than the ones provided by the GCC or Clang.

## Installation

### From source

Clone the repository from Github:

- `$ git clone https://github.com/JonayedMohiuddin/X-Parser_ExpressionEvaluator`
- or, Download the zip and unzip on your workspace folder.

Compile the project and run the object file:

#### Using Gcc
- Compiling : `g++ main.cpp -o main`
- Running : `./main`

#### Using Clang
- Compiling : `clang++ main.cpp -o main`
- Running : `./main`

## Data types

    NUMBER - All numbers are handled as Double

## Misc    

    EMPTY 
    
## Basic operations supplied by X-Parser 

    Evaluation  
    Assignment  =
    Operators   + - * / MOD % ^ POW
    Logical     < <= == != >= > AND OR NOT
    Ternary     ? :  
    Binary      << >> | &
    Constants   NULL PI
    Functions   CLEARMEMORY CLEARVARIABLES
   
## Optional functions supplied
 
    Functions   ABS ARCCOS ARCSIN ARCTAN ARRAYLEN AVERAGE CEILING CONTAINS CONTAINSALL CONTAINSANY
                COS DIGITSONLY ENDSWITH EXP FACTORIAL FIND FLOOR FORMAT FORMATBYLEN GUID HEX ISANYOF ISBLANK ISBOOLEAN ISDATE
                ISNONEOF ISNULL ISNUMBER LEFT LEFTOF LEN LOG LOG10 LOWER MAKEBOOLEAN MAKEDATE MATCH 
                MAX MID MIN NAMECASE RANDOM  REPLACE REPLACEALL REPLACEFIRST RIGHT RIGHTOF ROUND SIN 
                SPLIT SQR SQRT STARTSWITH STR STRING TAN TRIM TRIMLEFT TRIMRIGHT UPPER VAL
   
## Usage

Examples:
     
    
## Version History

1.0.0 Initial release to GitHub.
    
## License

X-Parser is licensed under the [MIT Licence][1] license. Permission is granted to anyone to use this software for any purpose, including commercial applications.

[1]: http://www.opensource.org/licenses/MIT




