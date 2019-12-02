#include <iostream>
#include <cstring>

class Sudoku {
private:
    int grid[9][9]{};

public:
    explicit Sudoku(int (*grid)[9]) {
        memcpy(this->grid, grid, 9 * 9 * sizeof(int));
    }

    bool operator ==(const int (*otherGrid)[9]) {
        for (int i=0; i<9*9; i++) {
            if (grid[i%9][i/9] != otherGrid[i%9][i/9]) {
                return false;
            }
        }
        return true;
    }

    bool operator ==(const Sudoku & other) {
        for (int i=0; i<9*9; i++) {
#ifdef PRINT
            printf("comparing grid(%d, %d)\n", i%9, i/9);
#endif
            if (grid[i%9][i/9] != other.grid[i%9][i/9]) {
                return false;
            }
        }
        return true;
    }

    int get(int i, int j) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j];
        }

        return -1;
    }

    int set(int i, int j, int val) {
        if (i >= 0 && i < 9 && j >= 0 && j < 9) {
            return grid[i][j] = val;
        }
        return -1;
    }

    void print() {
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                printf(" [%d] ", get(i, j));
                if (j == 8) {
                    printf("\n");
                }
            }
        }
    }

    bool solve() {
        // homework
        int row;
        int col;

        if (!findEmptySpace(row, col)) {
            return true;
        }

        for (int num = 1; num <= 9; num++) {
            if (isSafe(row, col, num)) {
                this->grid[row][col] = num;

                if (solve()) {
                    return true;
                }
                grid[row][col] = 0;
            }
        }
        return false;
    }

    bool findEmptySpace(int &row, int &col) {
        for (row = 0; row < 9; row++) {
            for (col = 0; col <9; col++) {
                if(this->grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isSafe(int row, int col, int num) {
        return !usedInRow(row, num) &&
        !usedInCol(col, num) &&
        !usedInBox(row - row % 3, col - col % 3, num) &&
        this->grid[row][col] == 0;
    }

    bool usedInRow(int row, int num) {
        for (int col = 0; col < 9; col++) {
            if (this->grid[row][col] == num) {
                return true;
            }
        }
        return false;
    }

    bool usedInCol(int col, int num) {
        for (int row = 0; row < 9; row++) {
            if (this->grid[row][col] == num) {
                return true;
            }
        }
        return false;
    }

    bool usedInBox(int boxStartRow, int boxStartCol, int num)
    {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (this->grid[row + boxStartRow][col + boxStartCol] == num)
                    return true;
        return false;
    }
};
