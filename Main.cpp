#include <iostream>
using namespace std;

void sudoku_3d_updater(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (sudoku_2d[row][col] > -1)
            {
                sudoku_3d[row][col][0] = sudoku_2d[row][col];
                for (int poss = 1; poss <= 9; poss++)
                {
                    sudoku_3d[row][col][poss] = -1;
                }
            }
        }
    }
}

void column_possibility_elimination(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{
    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {
            if (row < 3 || row < 6 || row < 9)
            {
                for (int poss = 0; poss < 10; poss++)
                {
                    if (sudoku_3d[row][col][poss] == sudoku_3d[row - 1][col][poss] && sudoku_3d[row][col][poss] == sudoku_3d[row - 2][col][poss])
                    {
                        for (int next_row = row + 1; next_row < 9; next_row++)
                        {
                            sudoku_3d[next_row][col][poss] = -1;
                        }
                    }
                    else if (sudoku_3d[row][col][poss] == sudoku_3d[row - 1][col][poss])
                    {
                        for (int next_row = row + 1; next_row < 9; next_row++)
                        {
                            sudoku_3d[next_row][col][poss] = -1;
                        }
                    }
                    else if (sudoku_3d[row][col][poss] == sudoku_3d[row - 2][col][poss])
                    {
                        for (int next_row = row + 1; next_row < 9; next_row++)
                        {
                            sudoku_3d[next_row][col][poss] = -1;
                        }
                    }
                }
            }
        }
    }
}

void row_possibility_elimination(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (col < 3 || col < 6 || col < 9)
            {
                for (int poss = 1; poss < 10; poss++)
                {
                    if (sudoku_3d[row][col][poss] == sudoku_3d[row][col - 1][poss] && sudoku_3d[row][col][poss] == sudoku_3d[row][col - 2][poss])
                    {
                        for (int next_col = col + 1; next_col < 9; next_col++)
                        {
                            sudoku_3d[row][next_col][poss] = -1;
                        }
                    }
                    else if (sudoku_3d[row][col][poss] == sudoku_3d[row][col - 1][poss])
                    {
                        for (int next_col = col + 1; next_col < 9; next_col++)
                        {
                            sudoku_3d[row][next_col][poss] = -1;
                        }
                    }
                    else if (sudoku_3d[row][col][poss] == sudoku_3d[row][col - 2][poss])
                    {
                        for (int next_col = col + 1; next_col < 9; next_col++)
                        {
                            sudoku_3d[row][next_col][poss] = -1;
                        }
                    }
                }
            }
        }
    }
    column_possibility_elimination(sudoku_2d, sudoku_3d);
}

void single_possibility_in_box(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            int box_start_row, box_start_col;

            if (row < 3)
            {
                box_start_row = 0;
            }
            else if (row < 6)
            {
                box_start_row = 3;
            }
            else
            {
                box_start_row = 6;
            }

            if (col < 3)
            {
                box_start_col = 0;
            }
            else if (col < 6)
            {
                box_start_col = 3;
            }
            else
            {
                box_start_col = 6;
            }
            
            for (int poss = 1; poss <= 9; poss++)
            {
                int count = 0;
                int last_row = 0, last_col = 0;
                for (int box_row = box_start_row; box_row < box_start_row + 3; box_row++)
                {
                    for (int box_col = box_start_col; box_col < box_start_col + 3; box_col++)
                    {
                        if (sudoku_3d[box_row][box_col][poss] == poss)
                        {
                            count++;
                            last_row = box_row;
                            last_col = box_col;
                        }
                    }
                }
                if (count == 1)
                {
                    sudoku_2d[last_row][last_col] = poss;
                }
            }
        }
    }
    sudoku_3d_updater(sudoku_2d, sudoku_3d);
}


void single_possibility_in_cell(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            int count = 0;
            int last_possibility = 0;
            for (int poss = 1; poss <= 9; poss++)
            {
                if (sudoku_3d[row][col][poss] > -1)
                {
                    count++;
                    last_possibility = sudoku_3d[row][col][poss];
                }
            }
            if (count == 1)
            {
                sudoku_2d[row][col] = last_possibility;
            }
        }
    }
    sudoku_3d_updater(sudoku_2d, sudoku_3d);
    single_possibility_in_box(sudoku_2d, sudoku_3d);
}

void box_elimination(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            int fixed_value = sudoku_2d[row][col];
            if (fixed_value > -1)
            {
                int box_start_row, box_start_col;

                if (row < 3)
                {
                    box_start_row = 0;
                }
                else if (row < 6)
                {
                    box_start_row = 3;
                }
                else
                {
                    box_start_row = 6;
                }

                if (col < 3)
                {
                    box_start_col = 0;
                }
                else if (col < 6)
                {
                    box_start_col = 3;
                }
                else
                {
                    box_start_col = 6;
                }

                for (int box_row = box_start_row; box_row < box_start_row + 3; box_row++)
                {
                    for (int box_col = box_start_col; box_col < box_start_col + 3; box_col++)
                    {
                        for (int poss = 1; poss <= 9; poss++)
                        {
                            if (sudoku_3d[box_row][box_col][poss] == fixed_value)
                            {
                                sudoku_3d[box_row][box_col][poss] = -1;
                            }
                        }
                    }
                }
            }
        }
    }
    single_possibility_in_cell(sudoku_2d, sudoku_3d);
}

void col_elimination(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{
    for (int col = 0; col < 9; col++)
    {
        for (int row = 0; row < 9; row++)
        {
            int fixed_value = sudoku_2d[row][col];
            if (fixed_value > -1)
            {
                for (int row_3d = 0; row_3d < 9; row_3d++)
                {
                    for (int poss = 1; poss <= 9; poss++)
                    {
                        if (sudoku_3d[row_3d][col][poss] == fixed_value)
                        {
                            sudoku_3d[row_3d][col][poss] = -1;
                        }
                    }
                }
            }
        }
    }
    box_elimination(sudoku_2d, sudoku_3d);
}

void row_elimination(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            int fixed_value = sudoku_2d[row][col];
            if (fixed_value > -1)
            {
                for (int col_3d = 0; col_3d < 9; col_3d++)
                {
                    for (int poss = 1; poss <= 9; poss++)
                    {
                        if (sudoku_3d[row][col_3d][poss] == fixed_value)
                        {
                            sudoku_3d[row][col_3d][poss] = -1;
                        }
                    }
                }
            }
        }
        
    }
    col_elimination(sudoku_2d, sudoku_3d);
}

void cell_selection(int sudoku_2d[9][9], int sudoku_3d[9][9][10])
{

    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (sudoku_2d[row][col] < 1)
            {
                cout << "Cell [" << row << "][" << col << "] has no fixed value (Multiple possibilities)\n";
                row_elimination(sudoku_2d, sudoku_3d);
            }
            else
            {
                cout << "Cell [" << row << "][" << col << "] has fixed value: " << sudoku_2d[row][col] << "\n";
            }
            cout << "2d sudoku: " << sudoku_2d[row][col] << "\n";
            cout << "3d sudoku: ";
            for (int poss = 0; poss < 10; poss++)
            {
                cout << sudoku_3d[row][col][poss] << "\t";
            }
            cout << "\n";
        }
    }
}

int main()
{
    int sudoku_2d[9][9] = {
        { 3, -1,  2, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1,  5,  8, -1, -1,  1},
        { 1, -1, -1, -1,  4, -1,  5, -1,  9},
        {-1,  9, -1, -1, -1, -1, -1, -1,  8},
        {-1, -1,  7, -1, -1, -1,  1, -1, -1},
        {-1, -1, -1, -1,  6, -1, -1,  2, -1},
        {-1, -1, -1,  6, -1,  2, -1,  4, -1},
        { 9, -1, -1,  3, -1, -1, -1, -1, -1},
        {-1,  4, -1, -1,  1, -1, -1, -1, -1}
    };

        int sudoku_3d[9][9][10] = {
            {
                {  3, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8, -1},
                {  2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
             },
             {
                { -1,  1,  2,  3,  4,  5,  6,  7,  8, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8, -1},
                { -1, -1, -1, -1,  4, -1,  6, -1, -1,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  5, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {  8, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
             },
             {
                {  1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  4, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  5, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  9, -1, -1, -1, -1, -1, -1, -1, -1, -1},
             },
             {
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  9, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  8, -1, -1, -1, -1, -1, -1, -1, -1, -1},
             },
             {
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  7, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
             },
             {
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  6, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {  1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
             },
             {
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  6, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  2, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  4, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                {  1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
             },
             {
                {  9, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  3, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
             },
             {
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  4, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                {  1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
                { -1,  1,  2,  3,  4,  5,  6,  7,  8,  9},
             },
        };
    cell_selection(sudoku_2d, sudoku_3d);
    
}