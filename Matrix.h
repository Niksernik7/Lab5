#ifndef MatrixIntegerH
#define MatrixIntegerH
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#define ERROR_FILE_OPEN -3
// 30.05.2022
typedef struct MatrixInteger {
    int** Rows;

    size_t RowCount;
    size_t ColumnCount;
} MatrixInteger;
// 30.05.2022
int AssertOpenFile(FILE* file);
// 30.05.2022
MatrixInteger* CreateMatrixInteger(size_t n, size_t m);
MatrixInteger* CopyMatrixInteger(MatrixInteger* matrix);
void AssertMatrixInteger(MatrixInteger* matrix);
void FreeMatrixInteger(MatrixInteger* matrix);
// 30.05.2022
void MatrixIntegerPrintf(MatrixInteger* matrix);
MatrixInteger* MatrixIntegerScanf(size_t n, size_t m);
// 30.05.2022
void MatrixIntegerFwrite(MatrixInteger* matrix, const char* fileName);
MatrixInteger* MatrixIntegerFread(const char* fileName);
// 30.05.2022
MatrixInteger* MatrixIntegerRand(size_t n, size_t m);
// 30.05.2022
MatrixInteger* InsertRowMatrixInteger(MatrixInteger* matrix, int* row, size_t m, size_t i);
MatrixInteger* InsertColumnMatrixInteger(MatrixInteger* matrix, int* column, size_t n, size_t j);
// 30.05.2022
MatrixInteger* EraseRowMatrixInteger(MatrixInteger* matrix, size_t i);
MatrixInteger* EraseColumnMatrixInteger(MatrixInteger* matrix, size_t j);
// 30.05.2022
int MatrixIntegerDeterminant(MatrixInteger* matrix);
void AssertSquareMatrixInteger(MatrixInteger* matrix);
int Determinant(MatrixInteger* matrix);
// 30.05.2022��������� ������� ��� i-� ������ � j-�� ������� 
MatrixInteger* MatrixIntegerWithoutRowColumn(MatrixInteger* matrix, int i, int j);
#endif
