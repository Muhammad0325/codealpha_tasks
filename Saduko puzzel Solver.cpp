#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

using namespace std;

class Sudoku {
private:
    static const int SIZE = 9;
    int grid[SIZE][SIZE];
    int original[SIZE][SIZE];

    bool isValid(int row, int col, int num) {
        for (int i = 0; i < SIZE; ++i) {
            if (grid[row][i] == num || grid[i][col] == num)
                return false;
        }

        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (grid[startRow + i][startCol + j] == num)
                    return false;

        return true;
    }

    bool solveRecursive(int g[SIZE][SIZE]) {
        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                if (g[row][col] == 0) {
                    for (int num = 1; num <= 9; ++num) {
                        if (isValidAt(g, row, col, num)) {
                            g[row][col] = num;
                            if (solveRecursive(g))
                                return true;
                            g[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    bool isValidAt(int g[SIZE][SIZE], int row, int col, int num) {
        for (int i = 0; i < SIZE; ++i) {
            if (g[row][i] == num || g[i][col] == num)
                return false;
        }

        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (g[startRow + i][startCol + j] == num)
                    return false;

        return true;
    }

public:
    Sudoku(int input[9][9]) {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j) {
                grid[i][j] = input[i][j];
                original[i][j] = input[i][j];
            }
    }

    void print() const {
        cout << "+-------+-------+-------+" << endl;
        for (int i = 0; i < SIZE; ++i) {
            cout << "| ";
            for (int j = 0; j < SIZE; ++j) {
                if (grid[i][j] == 0)
                    cout << ". ";
                else
                    cout << grid[i][j] << " ";
                if ((j + 1) % 3 == 0) cout << "| ";
            }
            cout << endl;
            if ((i + 1) % 3 == 0)
                cout << "+-------+-------+-------+" << endl;
        }
    }

    bool makeMove(int row, int col, int num) {
        if (original[row][col] != 0) {
            cout << "? You cannot change the original numbers!" << endl;
            return false;
        }

        if (isValid(row, col, num)) {
            grid[row][col] = num;
            return true;
        } else {
            cout << "? Invalid move!" << endl;
            return false;
        }
    }

    bool isComplete() {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (grid[i][j] == 0)
                    return false;
        return true;
    }

    void resetPuzzle(int input[9][9]) {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j) {
                grid[i][j] = input[i][j];
                original[i][j] = input[i][j];
            }
    }
};

void loadRandomPuzzle(int puzzle[9][9]) {
    int puzzles[2][9][9] = {
        {
            {5,3,0, 0,7,0, 0,0,0},
            {6,0,0, 1,9,5, 0,0,0},
            {0,9,8, 0,0,0, 0,6,0},
            {8,0,0, 0,6,0, 0,0,3},
            {4,0,0, 8,0,3, 0,0,1},
            {7,0,0, 0,2,0, 0,0,6},
            {0,6,0, 0,0,0, 2,8,0},
            {0,0,0, 4,1,9, 0,0,5},
            {0,0,0, 0,8,0, 0,7,9}
        },
        {
            {0,0,0, 2,6,0, 7,0,1},
            {6,8,0, 0,7,0, 0,9,0},
            {1,9,0, 0,0,4, 5,0,0},
            {8,2,0, 1,0,0, 0,4,0},
            {0,0,4, 6,0,2, 9,0,0},
            {0,5,0, 0,0,3, 0,2,8},
            {0,0,9, 3,0,0, 0,7,4},
            {0,4,0, 0,5,0, 0,3,6},
            {7,0,3, 0,1,8, 0,0,0}
        }
    };
    srand((unsigned)time(0));
    int r = rand() % 2;
    memcpy(puzzle, puzzles[r], sizeof(puzzles[r]));
}

int main() {
    int puzzle[9][9];
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        loadRandomPuzzle(puzzle);
        Sudoku game(puzzle);

        int chances = 3;
        int row, col, num;

        cout << "?? Welcome to Sudoku Game!" << endl;

        while (chances > 0 && !game.isComplete()) {
            game.print();
            cout << "You have " << chances << " chances remaining." << endl;
            cout << "Enter your move (row [1-9], column [1-9], number [1-9]): ";
            cin >> row >> col >> num;

            if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
                cout << "? Invalid input. Try again.\n";
                continue;
            }

            if (!game.makeMove(row - 1, col - 1, num)) {
                chances--;
            }

            if (game.isComplete()) {
                cout << "\n?? Congratulations! You completed the puzzle!\n";
                break;
            }
        }

        if (chances == 0) {
            cout << "\n? Game Over! You've used all your chances.\n";
        }

        cout << "\nFinal Sudoku Board:\n";
        game.print();

        cout << "Would you like to play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "\nThanks for playing Sudoku! ??\n";
    return 0;
}

