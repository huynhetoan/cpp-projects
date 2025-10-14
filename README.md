# C++ Projects

A pair of C++ applications demonstrating foundational programming skills in game logic, user input handling, and data management. These projects were built and tested using `g++` with support for C++11 and above.

## Overview

These programs showcase practical use of control flow, modular design, and command-line interaction. Each is designed to run in a terminal environment with clear user interaction and structured logic.

---

## Projects

### Rock–Paper–Scissors

A terminal-based game where the user competes against a computer opponent that randomly selects its move.

#### Features
- Command-line interface
- Randomized computer choice using `rand()`
- Win/loss/tie logic based on user input
- Replay option and input validation

#### How to Compile and Run:
    g++ Rock_Paper_Scissors.cpp -o Rock_Paper_Scissors.exe
    ./Rock_Paper_Scissors.exe

## Simple Address Book

A console-based address book application that allows users to manage contact information.

### Features
- Add, delete, search, and list contacts
- Stores contact data in memory using structs or classes
- Menu-driven interface with input validation
- Modular functions for each operation

### How to Compile and Run:
    g++ addressBook.cpp -o addressBook.exe
    ./addressBook.exe
    
## Technologies Used

- C++11 standard
- `iostream`, `vector`, `string`
- Command-line interaction
- Procedural and object-oriented design

## Notes

- All programs are tested using `g++` on Windows and Linux environments
- These projects are designed for educational and portfolio purposes
