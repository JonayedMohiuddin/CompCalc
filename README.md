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
      
  _____                                    _                 _____               _                _
 | ____|__  __ _ __   _ __  ___  ___  ___ (_)  ___   _ __   | ____|__   __ __ _ | | _   _   __ _ | |_  ___   _ __ 
 |  _|  \ \/ /| '_ \ | '__|/ _ \/ __|/ __|| | / _ \ | '_ \  |  _|  \ \ / // _` || || | | | / _` || __|/ _ \ | '__|
 | |___  >  < | |_) || |  |  __/\__ \\__ \| || (_) || | | | | |___  \ V /| (_| || || |_| || (_| || |_| (_) || |   
 |_____|/_/\_\| .__/ |_|   \___||___/|___/|_| \___/ |_| |_| |_____|  \_/  \__,_||_| \__,_| \__,_| \__|\___/ |_|   
              |_|                     									BY JONAYED
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

## Current Version
`V.1.1.5 - Last Breath`
    
## Version History

2.0.0 Future Update (Resurgence)
- Deprecation of old algorithm
- Implementation of new Algorithm
- Lexer and Tokens restructured

`1.1.0 Feature Upgrade (Last Breath)`
- Improved Lexer
- Multiplication is default operator.
- Added brace/parantheses support

1.0.5 Feature Upgrade
- Added basic functions 
- More operators

1.0.0 Initial release to GitHub.
    
## License

X-Parser is licensed under the [MIT Licence][1] license. Permission is granted to anyone to use this software for any purpose, including commercial applications.

[1]: http://www.opensource.org/licenses/MIT




