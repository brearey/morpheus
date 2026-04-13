#include "./s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;

  if (result == NULL || rows < 1 || columns < 1) {
    status = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(sizeof(double *) * rows);
    if (result->matrix == NULL) {
      status = INCORRECT_MATRIX;
    } else {
      int i = 0;
      while (i < rows && status == OK) {
        result->matrix[i] = (double *)malloc(sizeof(double) * columns);
        if (result->matrix[i] == NULL) {
          free_partial_rows(result, i);
          status = INCORRECT_MATRIX;
        } else {
          for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = 0.0;
          }
          i++;
        }
      }
    }
  }

  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && is_matrix_valid(A)) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(const matrix_t *A, const matrix_t *B) {
  int result = SUCCESS;

  if (A == NULL || B == NULL || !is_matrix_valid(A) || !is_matrix_valid(B)) {
    result = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    result = FAILURE;
  } else {
    int i = 0;
    while (i < A->rows && result == SUCCESS) {
      int j = 0;
      while (j < A->columns && result == SUCCESS) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
          result = FAILURE;
        }
        j++;
      }
      i++;
    }
  }

  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_helper(A, B, result, 1);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_helper(A, B, result, -1);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;

  if (A == NULL || result == NULL || !is_matrix_valid(A)) {
    status = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    status = INCORRECT_MATRIX;
  } else {
    int i = 0;
    while (i < A->rows && status == OK) {
      int j = 0;
      while (j < A->columns) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        if (!isfinite(result->matrix[i][j])) {
          status = INCORRECT_MATRIX;
        }
        j++;
      }
      i++;
    }
    if (status != OK) {
      s21_remove_matrix(result);
    }
  }

  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;

  if (A == NULL || B == NULL || result == NULL || !is_matrix_valid(A) ||
      !is_matrix_valid(B)) {
    status = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    status = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    status = INCORRECT_MATRIX;
  } else {
    fill_matrix(result, 0.0);
    int i = 0;
    while (i < A->rows && status == OK) {
      int j = 0;
      while (j < B->columns && status == OK) {
        int k = 0;
        while (k < B->rows) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          k++;
        }
        if (!isfinite(result->matrix[i][j])) {
          status = INCORRECT_MATRIX;
        }
        j++;
      }
      i++;
    }
    if (status != OK) {
      s21_remove_matrix(result);
    }
  }

  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = OK;

  if (A == NULL || result == NULL || !is_matrix_valid(A)) {
    status = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->columns, A->rows, result) != OK) {
    status = INCORRECT_MATRIX;
  } else {
    int i = 0;
    while (i < A->rows) {
      int j = 0;
      while (j < A->columns) {
        result->matrix[j][i] = A->matrix[i][j];
        j++;
      }
      i++;
    }
  }

  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;

  if (A == NULL || result == NULL || !is_matrix_valid(A)) {
    status = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    status = CALC_ERROR;
  } else if (A->rows == 1) {
    status = s21_create_matrix(1, 1, result);
    if (status == OK) {
      result->matrix[0][0] = 1;
    }
  } else {
    status = compute_complements(A, result);
  }

  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;

  if (A == NULL || result == NULL || !is_matrix_valid(A)) {
    status = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    status = CALC_ERROR;
  } else {
    status = compute_determinant(A, result);
  }

  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;

  if (A == NULL || result == NULL || !is_matrix_valid(A)) {
    status = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    status = CALC_ERROR;
  } else {
    double determinant = 0.0;
    status = s21_determinant(A, &determinant);
    if (status == OK && fabs(determinant) < 1e-12) {
      status = CALC_ERROR;
    }
    if (status == OK) {
      matrix_t complements = {0};
      matrix_t transposed = {0};
      status = s21_calc_complements(A, &complements);
      if (status == OK) {
        status = s21_transpose(&complements, &transposed);
      }
      if (status == OK) {
        status = s21_mult_number(&transposed, 1.0 / determinant, result);
      }
      s21_remove_matrix(&complements);
      s21_remove_matrix(&transposed);
    }
  }

  return status;
}

bool is_matrix_valid(const matrix_t *matrix) {
  return matrix != NULL && matrix->matrix != NULL && matrix->rows > 0 &&
         matrix->columns > 0;
}

void free_partial_rows(matrix_t *result, int current_row) {
  for (int i = 0; i < current_row; i++) {
    free(result->matrix[i]);
  }
  free(result->matrix);
  result->matrix = NULL;
}

void fill_matrix(matrix_t *A, double value) {
  if (A != NULL && is_matrix_valid(A)) {
    int i = 0;
    while (i < A->rows) {
      int j = 0;
      while (j < A->columns) {
        A->matrix[i][j] = value;
        j++;
      }
      i++;
    }
  }
}

int sum_helper(matrix_t *A, matrix_t *B, matrix_t *result, int signer) {
  int status = OK;

  if (A == NULL || B == NULL || result == NULL || !is_matrix_valid(A) ||
      !is_matrix_valid(B)) {
    status = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    status = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    status = INCORRECT_MATRIX;
  } else {
    int i = 0;
    while (i < A->rows && status == OK) {
      int j = 0;
      while (j < A->columns) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j] * signer;
        if (!isfinite(result->matrix[i][j])) {
          status = INCORRECT_MATRIX;
        }
        j++;
      }
      i++;
    }
    if (status != OK) {
      s21_remove_matrix(result);
    }
  }

  return status;
}

void calc_minor(matrix_t *A, matrix_t *temp, int ex_row, int ex_col) {
  int dst_row = 0;
  for (int row = 0; row < A->rows; row++) {
    if (row != ex_row) {
      int dst_col = 0;
      for (int col = 0; col < A->columns; col++) {
        if (col != ex_col) {
          temp->matrix[dst_row][dst_col] = A->matrix[row][col];
          dst_col++;
        }
      }
      dst_row++;
    }
  }
}

int copy_submatrix(matrix_t *src, matrix_t *dst, int skip_row, int skip_col) {
  int status = OK;
  matrix_t temp;
  if (s21_create_matrix(src->rows - 1, src->columns - 1, &temp) != OK) {
    status = INCORRECT_MATRIX;
  } else {
    calc_minor(src, &temp, skip_row, skip_col);
    for (int i = 0; i < temp.rows && status == OK; i++) {
      for (int j = 0; j < temp.columns; j++) {
        dst->matrix[i][j] = temp.matrix[i][j];
      }
    }
    s21_remove_matrix(&temp);
  }
  return status;
}

int compute_determinant(matrix_t *A, double *result) {
  int status = OK;

  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    *result = 0;
    int j = 0;
    while (j < A->columns && status == OK) {
      matrix_t minor;
      if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != OK) {
        status = INCORRECT_MATRIX;
      } else {
        copy_submatrix(A, &minor, 0, j);
        double minor_det = 0.0;
        status = compute_determinant(&minor, &minor_det);
        s21_remove_matrix(&minor);
        if (status == OK) {
          double sign = (j % 2 == 0) ? 1.0 : -1.0;
          *result += sign * A->matrix[0][j] * minor_det;
        }
      }
      j++;
    }
  }

  return status;
}

int compute_complements(matrix_t *A, matrix_t *result) {
  int status = s21_create_matrix(A->rows, A->columns, result);

  int i = 0;
  while (i < A->rows && status == OK) {
    int j = 0;
    while (j < A->columns && status == OK) {
      matrix_t minor;
      if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) == OK) {
        copy_submatrix(A, &minor, i, j);
        double minor_det = 0.0;
        int det_status = compute_determinant(&minor, &minor_det);
        if (det_status == OK) {
          double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
          result->matrix[i][j] = sign * minor_det;
          if (!isfinite(result->matrix[i][j])) {
            status = INCORRECT_MATRIX;
          }
        } else {
          status = det_status;
        }
        s21_remove_matrix(&minor);
      } else {
        status = INCORRECT_MATRIX;
      }
      j++;
    }
    i++;
  }

  if (status != OK) {
    s21_remove_matrix(result);
  }

  return status;
}
