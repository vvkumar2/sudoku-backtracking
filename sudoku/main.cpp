//
//  main.cpp
//  sudoku
//
//  Created by Varun Kumar on 1/1/22.
//

#include <iostream>
using namespace std;


    //assigning frequently used values
const int UNASSIGNED = 0;
const int NUM_ROWS = 9;
const int NUM_COLS = 9;


void showGrid (int gridArray[NUM_ROWS][NUM_COLS]);
bool isSafe (int gridArray[NUM_ROWS][NUM_COLS], int row, int col, int num);
bool solveSudoku (int gridArray[NUM_ROWS][NUM_COLS]);
bool inCol (int gridArray[NUM_ROWS][NUM_COLS], int col, int num);
bool inRow (int gridArray[NUM_ROWS][NUM_COLS], int row, int num);
bool inBox (int gridArray[NUM_ROWS][NUM_COLS], int startRow, int startCol, int num);
bool findEmptyLocation (int gridArray[NUM_ROWS][NUM_COLS], int &row, int &col);



void swapNumbers (int gridArray[NUM_ROWS][NUM_COLS])
{
    for (int i = 1; i < 10; i++)
    {
        int ranNum = (rand() % 9) + 1;
        
        for (int row = 0; row < NUM_ROWS; row++)
        {
            for (int col = 0; col < NUM_COLS; col++)
            {
                if (gridArray[row][col] == i)
                {
                    gridArray[row][col] = ranNum;
                }
                else if (gridArray[row][col] == ranNum)
                {
                    gridArray[row][col] = i;
                }
            }
        }
    }
}

void swapRows(int gridArray[NUM_ROWS][NUM_COLS], int r1, int r2)
{
    for (int k = 0; k < 9; k++)
    {
        int row [NUM_COLS];
        row [k] = gridArray [r1][k];
        gridArray [r1][k] = gridArray [r2][k];
        gridArray [r2][k] = row [k];
    }
}

void shuffleRows (int gridArray[NUM_ROWS][NUM_COLS])
{
    for (int i = 0; i < 9; i++)
    {
        int ranNum = (rand() % 3);
        int blockNumber = i/3;
        swapRows(gridArray, i, blockNumber*3 + ranNum);
    }
        
}

void swapCols(int gridArray[NUM_ROWS][NUM_COLS], int r1, int r2)
{
    for (int k = 0; k < 9; k++)
    {
        int col [NUM_ROWS];
        col [k] = gridArray [k][r1];
        gridArray [k][r1] = gridArray [k][r2];
        gridArray [k][r2] = col [k];
    }
}

void shuffleCols (int gridArray[NUM_ROWS][NUM_COLS])
{
    for (int i = 0; i < 9; i++)
    {
        int ranNum = (rand() % 3);
        int blockNumber = i/3;
        swapCols(gridArray, i, blockNumber*3 + ranNum);
    }
}

void swapRowBlocks (int gridArray[NUM_ROWS][NUM_COLS])
{
    for (int i = 0; i < 3; i++)
    {
        int ranNum = (rand() % 2);
        for (int j = 0; j < 3; j++)
        {
            swapRows(gridArray, i * 3 + j, ranNum * 3 + j);
        }
    }
}


void swapColBlocks (int gridArray[NUM_ROWS][NUM_COLS])
{
    for (int i = 0; i < 3; i++)
    {
        int ranNum = (rand() % 2);
        for (int j = 0; j < 3; j++)
        {
            swapCols(gridArray, i * 3 + j, ranNum * 3 + j);
        }
    }
}

void encrypt (int gridArray[NUM_ROWS][NUM_COLS])
{
    int ranNum1 = (rand() % 3) + 1;
    int ranNum2 = (rand() % 3) + 1;
    int ranNum3 = (rand() % 3) + 1;
    int ranNum4 = (rand() % 3) + 1;
    int ranNum5 = (rand() % 3) + 1;
    for (int i = 0; i <= ranNum1; i ++)
    {
        swapNumbers(gridArray);
    }
    for (int i = 0; i <= ranNum2; i ++)
    {
        shuffleRows(gridArray);
        
    }
    for (int i = 0; i <= ranNum3; i ++)
    {
        shuffleCols(gridArray);
    }
    for (int i = 0; i <= ranNum4; i ++)
    {
        swapRowBlocks(gridArray);
    }
    for (int i = 0; i <= ranNum5; i ++)
    {
        swapColBlocks(gridArray);
    }
    
}

void hideNumbersEasy (int gridArray[NUM_ROWS][NUM_COLS])
{
    
        int original[NUM_ROWS][NUM_COLS] =
        {
                        {1,2,3,4,5,6,7,8,9},
                        {4,5,6,7,8,9,1,2,3},
                        {7,8,9,1,2,3,4,5,6},
                        {2,3,1,5,6,4,8,9,7},
                        {5,6,4,8,9,7,2,3,1},
                        {8,9,7,2,3,1,5,6,4},
                        {3,1,2,6,4,5,9,7,8},
                        {6,4,5,9,7,8,3,1,2},
                        {9,7,8,3,1,2,6,4,5}
        };
    
    int numsLeft = 100;
    int gridSolved [NUM_ROWS][NUM_COLS];
    int gridToCompare [NUM_ROWS][NUM_COLS];
    
    for (int k = 0; k < 9; k++)
    {
        for (int j = 0; j < 9; j++)
        {
            gridSolved[k][j] = gridArray[k][j];
            gridToCompare[k][j] = gridArray[k][j];
        }
    }
    
    
    int compare = 0;
    while (compare == 0 && numsLeft > 31)
    {
        int oldNum = 0;
        int ranNumRow = (rand() % 9);
        int ranNumCol = (rand() % 9);
        oldNum = gridArray[ranNumRow][ranNumCol];
        gridArray[ranNumRow][ranNumCol] = 0;
        
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                gridToCompare[k][j] = gridArray[k][j];
            }
        }
        
        
        solveSudoku(gridToCompare);
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (gridSolved[k][j] != gridToCompare[k][j])
                {
                    for (int k = 0; k < 9; k++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            if (gridArray[k][j] != 0)
                            {
                                numsLeft++;
                            }
                        }
                    }
                    if (numsLeft < 32)
                    {
                        compare = 1;
                        gridArray[ranNumRow][ranNumCol] = oldNum;
                    }
                    else
                    {
                        for (int k = 0; k < 9; k++)
                        {
                            for (int j = 0; j < 9; j++)
                            {
                                gridArray[k][j] = original[k][j];
                            }
                        }
                        encrypt(gridArray);
                        for (int k = 0; k < 9; k++)
                        {
                            for (int j = 0; j < 9; j++)
                            {
                                gridToCompare[k][j] = gridArray[k][j];
                                gridSolved[k][j] = gridArray[k][j];
                            }
                        }
                        
                    }
                }
            }
        }
        
        numsLeft = 0;
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (gridArray[k][j] != 0)
                {
                    numsLeft++;
                }
            }
        }
        
    }
}


void hideNumbersMedium (int gridArray[NUM_ROWS][NUM_COLS])
{
    
        int original[NUM_ROWS][NUM_COLS] =
        {
                        {1,2,3,4,5,6,7,8,9},
                        {4,5,6,7,8,9,1,2,3},
                        {7,8,9,1,2,3,4,5,6},
                        {2,3,1,5,6,4,8,9,7},
                        {5,6,4,8,9,7,2,3,1},
                        {8,9,7,2,3,1,5,6,4},
                        {3,1,2,6,4,5,9,7,8},
                        {6,4,5,9,7,8,3,1,2},
                        {9,7,8,3,1,2,6,4,5}
        };
    
    int numsLeft = 100;
    int gridSolved [NUM_ROWS][NUM_COLS];
    int gridToCompare [NUM_ROWS][NUM_COLS];
    
    for (int k = 0; k < 9; k++)
    {
        for (int j = 0; j < 9; j++)
        {
            gridSolved[k][j] = gridArray[k][j];
            gridToCompare[k][j] = gridArray[k][j];
        }
    }
    
    
    int compare = 0;
    while (compare == 0 && numsLeft > 27)
    {
        int oldNum = 0;
        int ranNumRow = (rand() % 9);
        int ranNumCol = (rand() % 9);
        oldNum = gridArray[ranNumRow][ranNumCol];
        gridArray[ranNumRow][ranNumCol] = 0;
        
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                gridToCompare[k][j] = gridArray[k][j];
            }
        }
        
        
        solveSudoku(gridToCompare);
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (gridSolved[k][j] != gridToCompare[k][j])
                {
                    for (int k = 0; k < 9; k++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            if (gridArray[k][j] != 0)
                            {
                                numsLeft++;
                            }
                        }
                    }
                    if (numsLeft < 28)
                    {
                        compare = 1;
                        gridArray[ranNumRow][ranNumCol] = oldNum;
                    }
                    else
                    {
                        for (int k = 0; k < 9; k++)
                        {
                            for (int j = 0; j < 9; j++)
                            {
                                gridArray[k][j] = original[k][j];
                            }
                        }
                        encrypt(gridArray);
                        for (int k = 0; k < 9; k++)
                        {
                            for (int j = 0; j < 9; j++)
                            {
                                gridToCompare[k][j] = gridArray[k][j];
                                gridSolved[k][j] = gridArray[k][j];
                            }
                        }
                        
                    }
                }
            }
        }
        
        numsLeft = 0;
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (gridArray[k][j] != 0)
                {
                    numsLeft++;
                }
            }
        }
        
    }
}



void hideNumbersHard (int gridArray[NUM_ROWS][NUM_COLS])
{
    
        int original[NUM_ROWS][NUM_COLS] =
        {
                        {1,2,3,4,5,6,7,8,9},
                        {4,5,6,7,8,9,1,2,3},
                        {7,8,9,1,2,3,4,5,6},
                        {2,3,1,5,6,4,8,9,7},
                        {5,6,4,8,9,7,2,3,1},
                        {8,9,7,2,3,1,5,6,4},
                        {3,1,2,6,4,5,9,7,8},
                        {6,4,5,9,7,8,3,1,2},
                        {9,7,8,3,1,2,6,4,5}
        };
    
    int numsLeft = 100;
    int gridSolved [NUM_ROWS][NUM_COLS];
    int gridToCompare [NUM_ROWS][NUM_COLS];
    
    for (int k = 0; k < 9; k++)
    {
        for (int j = 0; j < 9; j++)
        {
            gridSolved[k][j] = gridArray[k][j];
            gridToCompare[k][j] = gridArray[k][j];
        }
    }
    
    
    int compare = 0;
    while (compare == 0 && numsLeft > 23)
    {
        int oldNum = 0;
        int ranNumRow = (rand() % 9);
        int ranNumCol = (rand() % 9);
        oldNum = gridArray[ranNumRow][ranNumCol];
        gridArray[ranNumRow][ranNumCol] = 0;
        
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                gridToCompare[k][j] = gridArray[k][j];
            }
        }
        
        
        solveSudoku(gridToCompare);
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (gridSolved[k][j] != gridToCompare[k][j])
                {
                    for (int k = 0; k < 9; k++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            if (gridArray[k][j] != 0)
                            {
                                numsLeft++;
                            }
                        }
                    }
                    if (numsLeft < 24)
                    {
                        compare = 1;
                        gridArray[ranNumRow][ranNumCol] = oldNum;
                    }
                    else
                    {
                        for (int k = 0; k < 9; k++)
                        {
                            for (int j = 0; j < 9; j++)
                            {
                                gridArray[k][j] = original[k][j];
                            }
                        }
                        encrypt(gridArray);
                        for (int k = 0; k < 9; k++)
                        {
                            for (int j = 0; j < 9; j++)
                            {
                                gridToCompare[k][j] = gridArray[k][j];
                                gridSolved[k][j] = gridArray[k][j];
                            }
                        }
                        
                    }
                }
            }
        }
        
        numsLeft = 0;
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (gridArray[k][j] != 0)
                {
                    numsLeft++;
                }
            }
        }
        
    }
}




void generateBoardEasy (int gridArray[NUM_ROWS][NUM_COLS])
{
    encrypt(gridArray);
    hideNumbersEasy (gridArray);
}

void generateBoardMedium (int gridArray[NUM_ROWS][NUM_COLS])
{
    encrypt(gridArray);
    hideNumbersMedium (gridArray);
}

void generateBoardHard (int gridArray[NUM_ROWS][NUM_COLS])
{
    encrypt(gridArray);
    hideNumbersHard(gridArray);
}


//checks if num is present in col
bool inCol (int gridArray[NUM_ROWS][NUM_COLS], int col, int num)
{
    for (int row = 0; (row < NUM_ROWS); row++)
    {
        if (gridArray[row][col] == num)
            return true;
    }
    return false;
}

//checks if num is present in row
bool inRow (int gridArray[NUM_ROWS][NUM_COLS], int row, int num)
{
    for (int col = 0; (col < NUM_COLS); col++)
    {
        if (gridArray[row][col] == num)
            return true;
    }
    return false;
}

//checks if num is present in the 3x3 grid matrix of the position row, col
bool inBox (int gridArray[NUM_ROWS][NUM_COLS], int startRow, int startCol, int num)
{
    startRow = startRow - (startRow % 3);
    startCol = startCol - (startCol % 3);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (gridArray[row + startRow][col + startCol] == num)
            {
                return true;
            }
        }
    }
    return false;
}

//finds any positions where the grid value is 0 and is thus unassigned
bool findEmptyLocation (int gridArray[NUM_ROWS][NUM_COLS], int &row, int &col)
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (gridArray[i][j] == UNASSIGNED)
            {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

    //displays 9x9 grid of numbers
void showGrid (int gridArray[NUM_ROWS][NUM_COLS])
{
    for (int row = 0; row < NUM_ROWS; row++)
    {
        for (int col = 0; col < NUM_COLS; col++)
        {
            if (col == 3 || col == 6)
            {
                cout << "|";
            }
            cout << gridArray[row][col];
        }
        if (row == 2 || row == 5)
        {
            cout << endl;
            for (int i = 0; i < NUM_COLS+2; i++)
               cout << "-";
        }
        cout << endl;
    }
}

    //checks if int num can be inserted into position at row, col
bool isSafe (int gridArray[NUM_ROWS][NUM_COLS], int row, int col, int num)
{
    return !inCol(gridArray, col, num) && !inRow(gridArray, row, num) && !inBox(gridArray, row, col, num) && gridArray[row][col] == UNASSIGNED;;
}

    //main function that solves the grid
    //returns true if a solution exists, and returns false if no solution exists
bool solveSudoku (int gridArray[NUM_ROWS][NUM_COLS])
{
    int row1, col1 = 0;
    if (!findEmptyLocation(gridArray, row1, col1))
    {
        return true;
    }

    for (int digit = 1; digit <= 9; digit++)
    {
        if (isSafe(gridArray, row1, col1, digit))
        {
            gridArray[row1][col1] = digit;
            
            if (solveSudoku(gridArray))
            {
                return true;
            }
            else
            {
                gridArray[row1][col1] = UNASSIGNED;
            }
        }
    }
    return false;
}

int main()
{
    int original[NUM_ROWS][NUM_COLS] =
    {
                    {1,2,3,4,5,6,7,8,9},
                    {4,5,6,7,8,9,1,2,3},
                    {7,8,9,1,2,3,4,5,6},
                    {2,3,1,5,6,4,8,9,7},
                    {5,6,4,8,9,7,2,3,1},
                    {8,9,7,2,3,1,5,6,4},
                    {3,1,2,6,4,5,9,7,8},
                    {6,4,5,9,7,8,3,1,2},
                    {9,7,8,3,1,2,6,4,5}
    };
    encrypt(original);

    
    int stay = 1;
    
    while (stay == 1)
    {
        int original[NUM_ROWS][NUM_COLS] =
        {
                        {1,2,3,4,5,6,7,8,9},
                        {4,5,6,7,8,9,1,2,3},
                        {7,8,9,1,2,3,4,5,6},
                        {2,3,1,5,6,4,8,9,7},
                        {5,6,4,8,9,7,2,3,1},
                        {8,9,7,2,3,1,5,6,4},
                        {3,1,2,6,4,5,9,7,8},
                        {6,4,5,9,7,8,3,1,2},
                        {9,7,8,3,1,2,6,4,5}
        };

        encrypt(original);
        
        
        cout << "Do you want me to generate a new Sudoku board (1), or solve one for you? (2)" << endl;
        int answer1;
        cin >> answer1;
        
        if (answer1 == 1)
        {
            cout << "Do you want an easy (1), medium (2), or hard (3) Sudoku board?" << endl;
            int answer2;
            cin >> answer2;
            cout << endl << endl;
            
            if (answer2 == 1)
            {
                generateBoardEasy(original);
                showGrid(original);
                cin.ignore();
                cout << endl << endl << "Press enter to let me know when you are ready to see the answer";
                string answer3;
                getline (cin, answer3);
                cout << endl << endl;
                if (answer3 == "")
                {
                    solveSudoku(original);
                    showGrid(original);
                }
            }
            
            else if (answer2 == 2)
            {
                generateBoardMedium(original);
                showGrid(original);
                cin.ignore();
                cout << endl << endl << "Press enter to let me know when you are ready to see the answer";
                string answer3;
                getline (cin, answer3);
                cout << endl << endl;
                if (answer3 == "")
                {
                    solveSudoku(original);
                    showGrid(original);
                }
            }
            
            else if (answer2 == 3)
            {
                generateBoardHard(original);
                showGrid(original);
                cin.ignore(); 
                cout << endl << endl << "Press enter to let me know when you are ready to see the answer";
                string answer3;
                getline (cin, answer3);
                cout << endl << endl;
                if (answer3 == "")
                {
                    solveSudoku(original);
                    showGrid(original);
                }
            }
        }
        else if (answer1 == 2)
        {
            cout << "Enter each entry in the board you want to solve from left to right substituting 0s for each blank space." << endl;
            int grid [NUM_ROWS][NUM_COLS];
            
            int input;
            for (int i = 0; i < NUM_ROWS; i++)
            {
                for (int j = 0; j < NUM_COLS; j++)
                {
                    cin >> input;
                    grid [i][j] = input;
                }
            }
            cout << endl << endl << "This is the board you submitted, if you want to change it type 0, if it is correct type 1" << endl << endl;
            showGrid(grid);
            
            int answer4;
            cin >> answer4;
            
            while (answer4 == 0)
            {
                cout << "Enter each entry in the board you want to solve from left to right substituting 0s for each blank space." << endl;
                
                for (int i = 0; i < NUM_ROWS; i++)
                {
                    for (int j = 0; j < NUM_COLS; j++)
                    {
                        cin >> input;
                        grid [i][j] = input;
                    }
                }
                
                cin.ignore();
                cout << endl << endl << "This is the board you submitted, if you want to change it type 0, if it is correct type 1" << endl << endl;
                showGrid(grid);

                cin >> answer4;
            }

            if (answer4 == 1)
            {
                cout << endl << endl << "This is the solution:" << endl << endl;
                if (solveSudoku(grid))
                    showGrid(grid);
                else
                    cout << "There is no solution";
            }
        }
        
        cout << "Do you want to get a new board or find another solution (1), or exit (0)"  << endl;
        cin >> stay;
        cout << "\n\n\n\n";
    }
    cout << "BYE!!" << "\n\n\n\n";
}
