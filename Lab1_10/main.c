#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int specPow(int a) {
    if (a%2 == 0) {
        return 1;
    } else {
        return -1;
    }
}

int generateRandomMass(int mass[], int count, int minimumValue, int maximumValue, int seedPlus) {
    //Пусть и простая, но зато своя цаца https://foxford.ru/wiki/informatika/generatsiya-psevdosluchaynyh-chisel
    unsigned long long seed;
    time(&seed);
    seed += seedPlus;
    for (int i = 0; i < count; ++i) {
        seed = 69069LU*seed + 5LU;
        mass[i] = (int)(seed%(maximumValue-minimumValue)) + minimumValue;
    }
    return 0;
}

int **createMatrix(int m, int n, int isRandom) {
    if (m <= 0 || n <= 0) {
        return NULL;
    }
    int **matrix = malloc(m*sizeof(int *));
    for (int M = 0; M < m; M++) {
        matrix[M] = malloc(n*sizeof(int));
    }
    if (isRandom == 1) {
        for (int M = 0; M < m; ++M) {
            generateRandomMass(matrix[M], n, -100, 100, M);
        }
    } else {
        printf("Write your data one for row\n");
        fflush (stdin);
        for (int M = 0; M < m; ++M) {
            for (int N = 0; N < n; ++N) {
                scanf("%d", &matrix[M][N]);
            }
        }
    }
    fflush (stdin);
    return matrix;
}

int printMatrix(int *matrix[], int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int **multiplyMatrix(int *matrix1[], int *matrix2[], int l, int m, int n) {
    int **result = malloc(l*sizeof(int *));
    for (int M = 0; M < l; ++M) {
        result[M] = malloc(n*sizeof(int));
    }
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = 0;
            for (int r = 0; r < m; ++r) {
                result[i][j] += matrix1[i][r] * matrix2[r][j];
            }
        }
    }
    return result;
}

int getDefinition(int *matrix[], int n) {

    if (n == 1) {
        return matrix[0][0];
    } else if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    } else {
        int res = 0;
        for (int a = 0; a < n; ++a) {
            int **newMatrix = malloc((n-1)*sizeof(int*));
            for (int N = 0; N < n-1; ++N) {
                newMatrix[N] = malloc((n-1)*sizeof(int));
            }
            for (int i = 0; i < n-1; ++i) {
                for (int j = 0; j < n-1; ++j) {
                    if (j < a) {
                        newMatrix[i][j] = matrix[i+1][j];
                    } else if (j >= a) {
                        newMatrix[i][j] = matrix[i+1][j+1];
                    }
                }
            }
            /*
            printf("______________\n");
            printMatrix(newMatrix, n-1, n-1);
            printf("%d %d\n", matrix[0][a], specPow(a) * matrix[0][a]);
             */
            res += specPow(a) * matrix[0][a] * getDefinition(newMatrix, n-1);
            free(newMatrix);
        }
        return res;
    }
}

int main() {
    char c;
    int m, n, m1 = 0, m2 = 0, n1 = 0, n2 = 0;
    int **matrix1, **matrix2;
    while (1) {
        printf("------------------------------------\n");
        printf("1 - Create first matrix\n");
        printf("2 - Create second matrix\n");
        printf("3 - Show first matrix\n");
        printf("4 - Show second matrix\n");
        printf("5 - show multiply of 2 matrix\n");
        printf("6 - show determinant of first matrix\n");
        printf("7 - exit\n");
        printf("------------------------------------\n");
        printf("Enter need command: ");
        fflush (stdin);
        scanf("%c", &c);
        if (c == '1') {
            printf("Enter height and length of matrix: ");
            fflush (stdin);
            if (scanf("%d %d", &m, &n) != 2) {
                printf("Enter valid values\n");
            } else {
                if (m > 0 && n > 0) {
                    printf("Would you like to randomize data in matrix [y/n]?: ");
                    fflush (stdin);
                    scanf("%c", &c);
                    if (c == 'y') {
                        matrix1 = createMatrix(m, n, 1);
                        m1 = m;
                        n1 = n;
                    } else if (c == 'n'){
                        matrix1 = createMatrix(m, n, 0);
                        m1 = m;
                        n1 = n;
                    } else {
                        printf("Invalid answer\n");
                    }
                } else {
                    printf("Entered size must be 1 or above\n");
                }
            }
        } else if (c == '2') {
            printf("Enter height and length of matrix: ");
            fflush (stdin);
            if (scanf("%d %d", &m, &n) != 2) {
                printf("Enter valid values\n");
            } else {
                if (m > 0 && n > 0) {
                    printf("Would you like to randomize data in matrix [y/n]?: \n");
                    fflush (stdin);
                    scanf("%c", &c);
                    if (c == 'y') {
                        matrix2 = createMatrix(m, n, 1);
                        m2 = m;
                        n2 = n;
                    } else if (c == 'n') {
                        matrix2 = createMatrix(m, n, 0);
                        m2 = m;
                        n2 = n;
                    } else {
                        printf("Invalid answer\n");
                    }
                } else {
                    printf("Entered size must be 1 or above\n");
                }
            }
        } else if (c == '3') {
            if (m1 == 0) {
                printf("Matrix doesn't create\n");
            } else {
                printMatrix(matrix1, m1, n1);
            }
        } else if (c == '4') {
            if (m2 == 0) {
                printf("Matrix doesn't create\n");
            } else {
                printMatrix(matrix2, m2, n2);
            }
        } else if (c == '5') {
            if (m1 == 0 || m2 == 0) {
                printf("One of matrix doesn't create\n");
            } else {
                if (n1 != m2) {
                    printf("Matrix can't be multiply. Set them correct size\n");
                } else {
                    printMatrix(multiplyMatrix(matrix1, matrix2, m1, n1, n2), m1, n2);
                }
            }
        } else if (c == '6') {
            if (m1 == 0) {
                printf("Matrix doesn't create\n");
            } else {
                if (m1 != n1) {
                    printf("Matrix is not square\n");
                } else {
                    printf("%d\n", getDefinition(matrix1, m1));
                }
            }
        } else if (c == '7') {
            free(matrix1);
            free(matrix2);
            break;
        }
    }
    return 0;
}
