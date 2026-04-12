#include "./s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows < 1 || columns < 1) return INCORRECT_MATRIX;

  int status = OK;
  result->rows = rows;
  result->columns = columns;
  result->matrix = malloc(sizeof(double *) * rows);
  if (result->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < rows && status == OK; i++) {
      result->matrix[i] = malloc(sizeof(double) * columns);
      if (result->matrix[i] == NULL) {
        for (int j = 0; j < i; j++) {
          free(result->matrix[j]);
        }
        free(result->matrix);
        result->matrix = NULL;
        status = INCORRECT_MATRIX;
      } else {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = 0.0;
        }
      }
    }
  }
  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL || is_matrix_valid(A) == false) return;

  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(const matrix_t *A, const matrix_t *B) {
  int not_equals_count = 0;
  bool is_size_equals = A->columns == B->columns && A->rows == B->rows;
  bool matrixes_are_valid = is_matrix_valid(A) && is_matrix_valid(B);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.0000001)
        not_equals_count++;
    }
  }
  return not_equals_count == 0 && is_size_equals && matrixes_are_valid
             ? SUCCESS
             : FAILURE;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_helper(A, B, result, 1);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_helper(A, B, result, -1);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (is_matrix_valid(A) == false) return INCORRECT_MATRIX;
  int status = OK;
  int creating_result = s21_create_matrix(A->rows, A->columns, result);
  if (creating_result == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
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

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_matrix_valid(A) == false || is_matrix_valid(B) == false)
    return INCORRECT_MATRIX;

  int status = OK;
  if (A->columns != B->rows) status = CALC_ERROR;

  int creating_result = s21_create_matrix(A->rows, B->columns, result);
  if (status == OK && creating_result == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          if (!isfinite(result->matrix[i][j])) {
            status = INCORRECT_MATRIX;
          }
        }
      }
    }
  } else {
    status = (status == CALC_ERROR) ? CALC_ERROR : INCORRECT_MATRIX;
  }
  if (status != OK) {
    s21_remove_matrix(result);
  }
  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (is_matrix_valid(A) == false) return INCORRECT_MATRIX;

  int status = OK;
  int creating_result = s21_create_matrix(A->columns, A->rows, result);
  if (creating_result == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    status = INCORRECT_MATRIX;
  }
  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!is_matrix_valid(A) || A->columns != A->rows || result == NULL) {
    if (!is_matrix_valid(A) || result == NULL) return INCORRECT_MATRIX;
    return CALC_ERROR;
  }

  int status = INCORRECT_MATRIX;
  if (A->rows == 1) {
    status = s21_create_matrix(1, 1, result);
    if (status == OK) result->matrix[0][0] = 1;
  } else {
    status = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && status == OK; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor_matrix;
        double minor_determinant = 0.0;

        if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor_matrix) ==
            OK) {
          calc_minor(A, &minor_matrix, i, j);
          s21_determinant(&minor_matrix, &minor_determinant);
          s21_remove_matrix(&minor_matrix);
        }

        int sign = ((i + j) % 2 == 0) ? 1 : -1;
        result->matrix[i][j] = sign * minor_determinant;
        if (!isfinite(result->matrix[i][j])) {
          status = INCORRECT_MATRIX;
        }
      }
    }
  }

  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  if (!is_matrix_valid(A) || result == NULL) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALC_ERROR;

  int status = OK;
  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    *result = 0;
    matrix_t minor;

    for (int j = 0; j < A->columns && status == OK; j++) {
      status = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      if (status != OK) break;

      calc_minor(A, &minor, 0, j);
      double minor_det;
      status = s21_determinant(&minor, &minor_det);
      s21_remove_matrix(&minor);
      *result += (j % 2 == 0 ? 1 : -1) * A->matrix[0][j] * minor_det;
    }
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_matrix_valid(A) == false || result == NULL) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALC_ERROR;

  int status = OK;
  double determinant = 0.0;
  matrix_t complements_matrix = {0};
  matrix_t transposed_matrix = {0};

  status = s21_determinant(A, &determinant);
  if (status != OK || fabs(determinant) < 1e-12) {
    status = (status != OK) ? status : CALC_ERROR;
  } else {
    status = s21_calc_complements(A, &complements_matrix);
    if (status == OK) {
      status = s21_transpose(&complements_matrix, &transposed_matrix);
      if (status == OK) {
        status = s21_mult_number(&transposed_matrix, 1.0 / determinant, result);
      }
    }
  }

  s21_remove_matrix(&complements_matrix);
  s21_remove_matrix(&transposed_matrix);

  return status;
}
