# Sudoku Generator

## About
This Sudoku Generator was built with C++. The goal of this project is to create a reliable, unique Sudoku board with one solution and varying levels of difficulty.

## Instructions:
- Download and install the latest version of C++ from https://www.microsoft.com/en-us/download/details.aspx?id=5555
- Download the code from the github repository https://github.com/vvkumar2/sudoku-backtracking
- Compile and run the code on your computer

## Technologies:
- C++: The code is written in C++ and is used to generate a Sudoku puzzle. The main purpose of the code is to generate a random Sudoku puzzle, encrypt it, and then hide some of the numbers in the puzzle. The code uses the rand() function to generate random numbers, and the showGrid() function to display the Sudoku grid. The code also uses the inRow(), inCol(), and inBox() functions to check if a given number is already in a row, column, or 3x3 box. If the number is not in the row, column, or box, the code will place the number in the next available spot.
- Recursive backtracking algorithm: The code is a sudoku solver that can also encrypt and hide numbers in a sudoku grid. It uses a recursive backtracking algorithm to solve sudokus, and can shuffle rows, columns, and blocks in order to encrypt the grid. To hide numbers, it randomly removes numbers from the grid and solves the sudoku to see if there is only one solution. If there is more than one solution, the number is put back in.

## Important Files:
- main.cpp: This file contains the Sudoku Generator project's main function.
