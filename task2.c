#include <stdio.h>

#define MAX 10 // Maximum size of the matrix

// Function to input a matrix
void inputMatrix(int matrix[MAX][MAX], int rows, int cols) {
    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to print a matrix
void printMatrix(int matrix[MAX][MAX], int rows, int cols) {
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function for matrix addition
void addMatrices(int matrix1[MAX][MAX], int matrix2[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// Function for matrix multiplication
void multiplyMatrices(int matrix1[MAX][MAX], int matrix2[MAX][MAX], int result[MAX][MAX], int rows1, int cols1, int rows2, int cols2) {
    if (cols1 != rows2) {
        printf("Matrix multiplication is not possible. Columns of matrix 1 must equal rows of matrix 2.\n");
        return;
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Function to find the transpose of a matrix
void transposeMatrix(int matrix[MAX][MAX], int result[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

int main() {
    int matrix1[MAX][MAX], matrix2[MAX][MAX], result[MAX][MAX];
    int rows1, cols1, rows2, cols2, choice;

    // Menu for the operations
    printf("Matrix Operations Menu:\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Matrix Addition
            printf("Enter dimensions for Matrix 1 (rows columns): ");
            scanf("%d %d", &rows1, &cols1);
            printf("Enter dimensions for Matrix 2 (rows columns): ");
            scanf("%d %d", &rows2, &cols2);

            if (rows1 == rows2 && cols1 == cols2) {
                inputMatrix(matrix1, rows1, cols1);
                inputMatrix(matrix2, rows2, cols2);
                addMatrices(matrix1, matrix2, result, rows1, cols1);

                printf("\nMatrix 1:\n");
                printMatrix(matrix1, rows1, cols1);
                printf("\nMatrix 2:\n");
                printMatrix(matrix2, rows2, cols2);
                printf("\nResultant Matrix after Addition:\n");
                printMatrix(result, rows1, cols1);
            } else {
                printf("Matrix dimensions do not match for addition.\n");
            }
            break;

        case 2:
            // Matrix Multiplication
            printf("Enter dimensions for Matrix 1 (rows columns): ");
            scanf("%d %d", &rows1, &cols1);
            printf("Enter dimensions for Matrix 2 (rows columns): ");
            scanf("%d %d", &rows2, &cols2);

            if (cols1 == rows2) {
                inputMatrix(matrix1, rows1, cols1);
                inputMatrix(matrix2, rows2, cols2);
                multiplyMatrices(matrix1, matrix2, result, rows1, cols1, rows2, cols2);

                printf("\nMatrix 1:\n");
                printMatrix(matrix1, rows1, cols1);
                printf("\nMatrix 2:\n");
                printMatrix(matrix2, rows2, cols2);
                printf("\nResultant Matrix after Multiplication:\n");
                printMatrix(result, rows1, cols2);
            } else {
                printf("Matrix multiplication is not possible. Columns of Matrix 1 must equal rows of Matrix 2.\n");
            }
            break;

        case 3:
            // Matrix Transpose
            printf("Enter dimensions for Matrix (rows columns): ");
            scanf("%d %d", &rows1, &cols1);

            inputMatrix(matrix1, rows1, cols1);
            transposeMatrix(matrix1, result, rows1, cols1);

            printf("\nMatrix:\n");
            printMatrix(matrix1, rows1, cols1);
            printf("\nTranspose of Matrix:\n");
            printMatrix(result, cols1, rows1);
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
