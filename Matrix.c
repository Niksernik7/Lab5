#include "Matrix.h"
// 30.05.2022
int AssertOpenFile(FILE* file)
{
    if (file == NULL)
    {
        printf("Failure of opening the file. Try another file.\n");
        scanf("%*c");
        return ERROR_FILE_OPEN;
    }
}
// 30.05.2022
MatrixInteger* CreateMatrixInteger(size_t n, size_t m) // not test
{
    MatrixInteger* res = (MatrixInteger*)malloc(sizeof(MatrixInteger));
    res->Rows = (int**)malloc(sizeof(int*) * n);
    for (size_t i = 0; i < n; i++)
        (res->Rows)[i] = (int*)malloc(sizeof(int) * m);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            ((res->Rows)[i])[j] = (int)0;
    res->RowCount = n;
    res->ColumnCount = m;

    return res;
}
// 30.05.2022
MatrixInteger* CopyMatrixInteger(MatrixInteger* matrix) 
{
    MatrixInteger* res = (MatrixInteger*)malloc(sizeof(MatrixInteger));
    int n = matrix->RowCount, m = matrix->ColumnCount;
    res->Rows = (int**)malloc(sizeof(int*) * n);
    for (size_t i = 0; i < n; i++)
        (res->Rows)[i] = (int*)malloc(sizeof(int) * m);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            ((res->Rows)[i])[j] = matrix->Rows[i][j];
    res->RowCount = n;
    res->ColumnCount = m;

    return res;
}
// 30.05.2022
void AssertMatrixInteger(MatrixInteger* matrix)
{
    assert(matrix);
    assert(matrix->Rows);

}
// 30.05.2022
void FreeMatrixInteger(MatrixInteger* matrix) // not test
{
    for (size_t i = 0; i < matrix->RowCount; i++)
    {
        free((matrix->Rows)[i]);
    }
    free(matrix->Rows);

}
// 30.05.2022
void MatrixIntegerPrintf(MatrixInteger* matrix)
{
    AssertMatrixInteger(matrix);

    for (size_t i = 0; i < matrix->RowCount; i++)
    {
        for (size_t j = 0; j < matrix->ColumnCount; j++)
        {
            printf("%d \\ ", *((matrix->Rows)[i] + j));
        }
        printf("\n");
    }

}
// 30.05.2022
MatrixInteger* MatrixIntegerScanf(size_t n, size_t m)
{
    MatrixInteger* res = CreateMatrixInteger(n, m);
    AssertMatrixInteger(res);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            scanf("%d", (res->Rows)[i] + j);
        }
    }

    return res;
}
// 30.05.2022
void MatrixIntegerFwrite(MatrixInteger* matrix, const char* fileName)
{
    AssertMatrixInteger(matrix);

    FILE* output = NULL;
    output = fopen(fileName, "wb");
    if (AssertOpenFile(output) == ERROR_FILE_OPEN)
    {
        return;
    }

    fwrite(&(matrix->RowCount), sizeof(size_t), 1, output);
    fwrite(&(matrix->ColumnCount), sizeof(size_t), 1, output);
    for (size_t i = 0; i < matrix->RowCount; i++)
    {
        fwrite((matrix->Rows)[i], sizeof(int), matrix->ColumnCount, output);
    }

    fclose(output);

}
// 30.05.2022
MatrixInteger* MatrixIntegerFread(const char* fileName)
{
    size_t n = 0, m = 0;
    MatrixInteger* res = NULL;
    FILE* input = NULL;

    input = fopen(fileName, "rb");
    if (AssertOpenFile(input) == ERROR_FILE_OPEN)
    {
        return NULL;
    }

    fread(&n, sizeof(size_t), 1, input);
    fread(&m, sizeof(size_t), 1, input);
    res = CreateMatrixInteger(n, m);

    AssertMatrixInteger(res);

    for (size_t i = 0; i < n; i++)
    {
        fread((res->Rows)[i], sizeof(int), m, input);
    }

    fclose(input);

    return res;
}
// 30.05.2022
MatrixInteger* MatrixIntegerRand(size_t n, size_t m)
{
    MatrixInteger* res = CreateMatrixInteger(n, m);
    AssertMatrixInteger(res);

    srand(time(NULL));

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            *((res->Rows)[i] + j) = rand() - RAND_MAX / 2;
        }
    }

    return res;
}
// 30.05.2022
MatrixInteger* InsertRowMatrixInteger(MatrixInteger* matrix, int* row, size_t m, size_t i)
{
    AssertMatrixInteger(matrix);

    assert(row);
    assert(matrix->ColumnCount == m);
    assert(i <= matrix->RowCount + 1);

    MatrixInteger* res = CreateMatrixInteger(matrix->RowCount + 1, m);
    AssertMatrixInteger(res);

    for (size_t j = 0, k = 0; j < matrix->RowCount; j++, k++)
    {
        if (j == i)
        {
            memcpy((res->Rows)[k], row, sizeof(int) * m);
            k++;
        }
        memcpy((res->Rows)[k], (matrix->Rows)[j], sizeof(int) * m);
    }

    return res;
}
// 30.05.2022
MatrixInteger* InsertColumnMatrixInteger(MatrixInteger* matrix, int* column, size_t n, size_t j)
{
    AssertMatrixInteger(matrix);

    assert(column);
    assert(matrix->RowCount == n);
    assert(j <= matrix->ColumnCount + 1);

    MatrixInteger* res = CreateMatrixInteger(n, matrix->ColumnCount + 1);
    AssertMatrixInteger(res);

    for (size_t i = 0; i < res->RowCount; i++)
    {
        memcpy((res->Rows)[i], (matrix->Rows)[i], sizeof(int) * j);
        memcpy((res->Rows)[i] + j, column + i, sizeof(int));
        memcpy((res->Rows)[i] + j + 1, (matrix->Rows)[i] + j, sizeof(int) * (matrix->ColumnCount - j));
    }

    return res;
}
// 30.05.2022
MatrixInteger* EraseRowMatrixInteger(MatrixInteger* matrix, size_t i) {
    AssertMatrixInteger(matrix);
    assert(i < matrix->RowCount);
    MatrixInteger* res = CreateMatrixInteger(matrix->RowCount - 1, matrix->ColumnCount);
    AssertMatrixInteger(res);
    for (size_t j = 0, k = 0; j < res->RowCount; j++, k++) {
        if (j == i)
            k++;
        memcpy(res->Rows[j], matrix->Rows[k], sizeof(int) * matrix->ColumnCount);
    }
    return res;
}
// 30.05.2022
MatrixInteger* EraseColumnMatrixInteger(MatrixInteger* matrix, size_t j) {
    AssertMatrixInteger(matrix);
    assert(j < matrix->ColumnCount);
    MatrixInteger* res = CreateMatrixInteger(matrix->RowCount, matrix->ColumnCount - 1);
    AssertMatrixInteger(res);
    for (size_t i = 0; i < res->RowCount; i++) {
        memcpy(res->Rows[i], matrix->Rows[i], sizeof(int) * j);
        memcpy(res->Rows[i] + j, matrix->Rows[i] + j + 1, sizeof(int) * (res->ColumnCount - j));
    }
    return res;
}
// 30.05.2022
int MatrixIntegerDeterminant(MatrixInteger* matrix)
{
    AssertMatrixInteger(matrix);
    AssertSquareMatrixInteger(matrix);

    return Determinant(matrix);
}
// 30.05.2022
void AssertSquareMatrixInteger(MatrixInteger* matrix)
{
    AssertMatrixInteger(matrix);
    assert(matrix->RowCount == matrix->ColumnCount);
}
// 30.05.2022
int Determinant(MatrixInteger* matrix) {

    AssertMatrixInteger(matrix);
    AssertSquareMatrixInteger(matrix);

    int i, j, d, k, n, m = matrix->RowCount;
    MatrixInteger* p = NULL;
    j = 0; d = 0;
    k = 1; //(-1) � ������� i
    n = m - 1;
    if (m == 1)
        return matrix->Rows[0][0];
    if (m == 2)
        return matrix->Rows[0][0] * matrix->Rows[1][1] - (matrix->Rows[1][0] * matrix->Rows[0][1]);
    if (m > 2)
        for (i = 0; i < m; i++) {
            p = MatrixIntegerWithoutRowColumn(matrix, i, 0);
            d += k * matrix->Rows[i][0] * Determinant(p);
            FreeMatrixInteger(p);
            k = -k;
        }
    return d;
}
// 30.05.2022 ��������� ������� ��� i-� ������ � j-�� ������� 
MatrixInteger* MatrixIntegerWithoutRowColumn(MatrixInteger* matrix, int i, int j)
{
    AssertMatrixInteger(matrix);

    MatrixInteger* res = NULL, * buf = NULL;

    buf = EraseRowMatrixInteger(matrix, i);
    res = EraseColumnMatrixInteger(buf, j);

    FreeMatrixInteger(buf);

    AssertMatrixInteger(res);

    return res;
}