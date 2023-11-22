#include <stdio.h>
#include <stdbool.h>

#define MAX_N 10 // Adjust the maximum value as needed

void printSolution(int board[MAX_N][MAX_N], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isSafe(int board[MAX_N][MAX_N], int row, int col, int N) {
    // Check this row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i] == 1) {
            return false;
        }
    }

    // Check upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // Check lower diagonal on the left side
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

bool solveNQueensUtil(int board[MAX_N][MAX_N], int col, int N) {
    if (col == N) {
        // All queens are placed successfully
        printSolution(board, N);
        return true; // Uncomment this line to find only one solution
    }

    bool res = false;
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1;

            // Uncomment the following line to find only one solution
            // if (solveNQueensUtil(board, col + 1, N)) {
            //     return true;
            // }

            res = solveNQueensUtil(board, col + 1, N) || res;
            
            board[i][col] = 0; // Backtrack
        }
    }

    return res;
}

void solveNQueens(int N) {
    int board[MAX_N][MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            board[i][j] = 0;
        }
    }

    if (!solveNQueensUtil(board, 0, N)) {
        printf("No solution exists.\n");
    }
}

int main() {
    int N;

    printf("Enter the number of queens (N): ");
    scanf("%d", &N);

    if (N > MAX_N) {
        printf("N is too large. Please choose a smaller value.\n");
        return 1; // Exit with an error code
    }

    solveNQueens(N);

    return 0;
}
