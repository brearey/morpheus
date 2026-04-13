#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define OK 0
#define INCORRECT_MATRIX 1
#define CALC_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(const matrix_t *A, const matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void fill_matrix(matrix_t *A, double value);
bool is_matrix_valid(const matrix_t *matrix);
void free_partial_rows(matrix_t *result, int current_row);
void fill_matrix(matrix_t *A, double value);
int sum_helper(matrix_t *A, matrix_t *B, matrix_t *result, int signer);
void calc_minor(matrix_t *A, matrix_t *temp, int ex_row, int ex_col);
int copy_submatrix(matrix_t *src, matrix_t *dst, int skip_row, int skip_col);
int compute_determinant(matrix_t *A, double *result);
int compute_complements(matrix_t *A, matrix_t *result);

#endif
