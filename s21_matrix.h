#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
Две матрицы A, B совпадают |A = B|, если совпадают их размеры и соответствующие
элементы равны, то есть при всех i, j A(i,j) = B(i,j). Сравнение должно
происходить вплоть до шестого знака после запятой включительно. SUCCESS равны
FAILURE не равны
*/
#define SUCCESS 1
#define FAILURE 0
/*
Все операции (кроме сравнения матриц) должны возвращать результирующий код:

0 — OK;
1 — Ошибка, некорректная матрица;
2 — Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя
провести вычисления и т. д.).
*/
#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t* result);
void s21_remove_matrix(matrix_t* A);
int s21_eq_matrix(const matrix_t* A, const matrix_t* B);
int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_mult_number(matrix_t* A, double number, matrix_t* result);
int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s21_transpose(matrix_t* A, matrix_t* result);
int s21_calc_complements(matrix_t* A, matrix_t* result);
int s21_determinant(matrix_t* A, double* result);
int s21_inverse_matrix(matrix_t* A, matrix_t* result);

// Matrix lib functions
bool is_matrix_valid(const matrix_t* matrix);
void print_matrix(matrix_t A);
void fill_matrix(matrix_t* A, const double value);
int sum_helper(matrix_t* A, matrix_t* B, matrix_t* result, const int signer);
void calc_minor(matrix_t* A, matrix_t* temp, int ex_row, int ex_col);

#endif