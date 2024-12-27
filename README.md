# Decryption Program
The Decryption Program is a tool designed to decrypt text files based on Middle Eastern frequency method algorithm. It processes encrypted text and restores the original content. The program is flexible and allows customization of decryption logic to suit specific encryption schemes.

## How the Program Works
The program takes an encrypted text file as input and processes it using the implemented decryption algorithm.


## Structure

The project consists of the following files:
- `main.cpp`: Contains the user interface logic.
- `decrypt.hpp`: Header file defining the decryptor's functions.
- `decrypt.cpp`: Implementation of the decryptor's core logic.
 - `test.cpp`: Unit tests for the decryptor logic using 'doctest'.(https://github.com/doctest/doctest)  
- `CMakeLists.txt`: Build configuration for CMake.


## Steps to compile:

Clone the repository or copy the files.
Create a CMakeLists.txt file for easier compilation (the example is added in this repository ( CMakeLists.txt file))

## File Reading: Reads the encrypted file and loads its content into memory.
Decryption: Processes the encrypted text based on the specified algorithm .
Output Writing: Saves the decrypted text to a new file or outputs it to the console.
Features
Processes encrypted text files quickly and efficiently.
Lightweight, with no external dependencies.
Program Structure and Functions
Core Functions
This function reads the contents of the input file into a string for further processing.


 
Customization
You can modify the decryption algorithm by editing the decrypt function in the source code (main.cpp). For example, you can change letters using user_insert() (if you think that you can modify the decryption you can do it(example: hekko you can change to hello)).

