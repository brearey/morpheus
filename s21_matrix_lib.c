#include "./s21_matrix.h"

bool is_matrix_valid(const matrix_t* A) {
  return A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0;
}

void fill_matrix(matrix_t* A, const double value) {
  if (is_matrix_valid(A) == false) {
    printf("Matrix is not valid");
    return;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = value;
    }
  }
}

/***
 * @param {A} операнд 1
 * @param {B} операнд 2
 * @param {result} результат суммы
 * @param {signer} signer = 1 для суммы, signer = -1 для разности
 */
int sum_helper(matrix_t* A, matrix_t* B, matrix_t* result, const int signer) {
  if (is_matrix_valid(A) == false || is_matrix_valid(B) == false)
    return INCORRECT_MATRIX;
  if (A->rows != B->rows || A->columns != B->columns) return CALC_ERROR;

  int status = OK;
  int creating_result = s21_create_matrix(A->rows, A->columns, result);
  if (creating_result == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + (B->matrix[i][j] * signer);
        if (!isfinite(result->matrix[i][j])) {
          status = INCORRECT_MATRIX;
        }
      }
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

void calc_minor(matrix_t* A, matrix_t* temp, int ex_row, int ex_col) {
  int i = 0, j = 0;
  for (int row = 0; row < A->rows; row++) {
    if (row == ex_row) continue;
    for (int col = 0; col < A->columns; col++) {
      if (col == ex_col) continue;
      temp->matrix[i][j] = A->matrix[row][col];
      j++;
    }
    j = 0;
    i++;
  }
}