#include <check.h>

#include "../s21_matrix.h"

START_TEST(create_matrix_1) {
  matrix_t A;
  int result1 = s21_create_matrix(3, 3, NULL);
  int result2 = s21_create_matrix(0, 3, &A);
  int result3 = s21_create_matrix(3, 0, &A);
  ck_assert_int_eq(result1, INCORRECT_MATRIX);
  ck_assert_int_eq(result2, INCORRECT_MATRIX);
  ck_assert_int_eq(result3, INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  int result1 = s21_create_matrix(4, 4, &A);
  int result2 = s21_create_matrix(5, 4, &B);
  int result3 = s21_create_matrix(6, 5, &C);
  ck_assert_int_eq(result1, OK);
  ck_assert_int_eq(result2, OK);
  ck_assert_int_eq(result3, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(create_matrix_3) {
  matrix_t A;
  int result = s21_create_matrix(5, 5, &A);
  ck_assert_int_eq(result, OK);
  s21_remove_matrix(&A);

  result = s21_create_matrix(-5, 5, &A);
  ck_assert_int_eq(result, INCORRECT_MATRIX);

  result = s21_create_matrix(-5, 0, &A);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(equal_matrix_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.5;
  A.matrix[1][0] = 2.5;
  A.matrix[0][1] = 3.5;
  A.matrix[1][1] = 4.5;
  A.matrix[2][0] = 5.5;
  A.matrix[2][1] = 6.5;
  A.matrix[0][2] = 7.5;
  A.matrix[1][2] = 8.5;
  A.matrix[2][2] = 9.5;
  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1.5;
  B.matrix[1][0] = 2.5;
  B.matrix[0][1] = 3.5;
  B.matrix[1][1] = 4.5;
  B.matrix[2][0] = 5.5;
  B.matrix[2][1] = 6.5;
  B.matrix[0][2] = 7.5;
  B.matrix[1][2] = 8.5;
  B.matrix[2][2] = 9.5;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_matrix_2) {
  matrix_t A;
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.1;
  A.matrix[0][1] = 2.2;
  A.matrix[0][2] = 3.3;
  A.matrix[1][0] = 4.4;
  A.matrix[1][1] = 5.5;
  A.matrix[1][2] = 6.6;
  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1.1;
  B.matrix[1][0] = 2.2;
  B.matrix[0][1] = 3.3;
  B.matrix[1][1] = 4.4;
  B.matrix[2][0] = 5.5;
  B.matrix[2][1] = 6.6;
  B.matrix[0][2] = 7.7;
  B.matrix[1][2] = 8.8;
  B.matrix[2][2] = 9.9;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_matrix_3) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][1] = 5.0;
  matrix_t B;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[0][1] = 4.0;
  B.matrix[1][1] = 4.9;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(equal_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  A.rows = 0;
  A.columns = 0;
  B.rows = 0;
  B.columns = 0;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(sum_matrix_1) {
  matrix_t A, B, AB, shouldAB;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &shouldAB);
  fill_matrix(&shouldAB, 0);

  int sum_result = s21_sum_matrix(&A, &B, &AB);
  int is_equal = s21_eq_matrix(&AB, &shouldAB);
  ck_assert_int_eq(sum_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&AB);
  s21_remove_matrix(&shouldAB);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t A, B, AB;
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 3, &B);

  int sum_result = s21_sum_matrix(&A, &B, &AB);
  ck_assert_int_eq(sum_result, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t A, B, AB;
  s21_create_matrix(4, 3, &A);
  s21_create_matrix(3, 3, &B);

  int sum_result = s21_sum_matrix(&A, &B, &AB);
  ck_assert_int_eq(sum_result, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_4) {
  matrix_t A, B, AB, shouldAB;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &shouldAB);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 2 + j;
      shouldAB.matrix[i][j] = i * 2 + j;
    }
  }

  int sum_result = s21_sum_matrix(&A, &B, &AB);
  int is_equal = s21_eq_matrix(&AB, &shouldAB);
  ck_assert_int_eq(sum_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&AB);
  s21_remove_matrix(&shouldAB);
}
END_TEST

START_TEST(sum_matrix_5) {
  matrix_t A, B, AB, shouldAB;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &shouldAB);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j;
      B.matrix[i][j] = i * 3 + j;
      shouldAB.matrix[i][j] = (i * 3 + j) * 2;
    }
  }

  int sum_result = s21_sum_matrix(&A, &B, &AB);
  int is_equal = s21_eq_matrix(&AB, &shouldAB);
  ck_assert_int_eq(sum_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&AB);
  s21_remove_matrix(&shouldAB);
}
END_TEST

START_TEST(sum_matrix_6) {
  matrix_t A, B, AB;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  int sum_result = s21_sum_matrix(NULL, &B, &AB);
  ck_assert_int_eq(sum_result, INCORRECT_MATRIX);

  sum_result = s21_sum_matrix(&A, NULL, &AB);
  ck_assert_int_eq(sum_result, INCORRECT_MATRIX);

  sum_result = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(sum_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_1) {
  matrix_t A, B, AB, shouldAB;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &shouldAB);
  fill_matrix(&shouldAB, 0);

  int sub_result = s21_sub_matrix(&A, &B, &AB);
  int is_equal = s21_eq_matrix(&AB, &shouldAB);
  ck_assert_int_eq(sub_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&AB);
  s21_remove_matrix(&shouldAB);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t A, B, AB;
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 3, &B);

  int sub_result = s21_sub_matrix(&A, &B, &AB);
  ck_assert_int_eq(sub_result, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t AB;

  int sub_result = s21_sub_matrix(&A, &B, &AB);
  ck_assert_int_eq(sub_result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_matrix_4) {
  matrix_t A, B, AB, shouldAB;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &shouldAB);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 2 + j + 1;
      shouldAB.matrix[i][j] = i * 2 + j + 1;
    }
  }

  int sub_result = s21_sub_matrix(&A, &B, &AB);
  int is_equal = s21_eq_matrix(&AB, &shouldAB);
  ck_assert_int_eq(sub_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&AB);
  s21_remove_matrix(&shouldAB);
}
END_TEST

START_TEST(sub_matrix_5) {
  matrix_t A, B, AB, shouldAB;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &shouldAB);
  fill_matrix(&shouldAB, 0);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 2;
      B.matrix[i][j] = i * 3 + j + 2;
    }
  }

  int sub_result = s21_sub_matrix(&A, &B, &AB);
  int is_equal = s21_eq_matrix(&AB, &shouldAB);
  ck_assert_int_eq(sub_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&AB);
  s21_remove_matrix(&shouldAB);
}
END_TEST

START_TEST(sub_matrix_6) {
  matrix_t A, B, AB;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  int sub_result = s21_sub_matrix(NULL, &B, &AB);
  ck_assert_int_eq(sub_result, INCORRECT_MATRIX);

  sub_result = s21_sub_matrix(&A, NULL, &AB);
  ck_assert_int_eq(sub_result, INCORRECT_MATRIX);

  sub_result = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(sub_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_number_1) {
  matrix_t A, calculated, should;
  double number = 3.5;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &should);
  fill_matrix(&should, 0);

  int mult_result = s21_mult_number(&A, number, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(mult_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t A, calculated, should;
  double number = -2.5;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &should);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 2 + j;
      should.matrix[i][j] = (i * 2 + j) * number;
    }
  }

  int mult_result = s21_mult_number(&A, number, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(mult_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t A, calculated, should;
  double number = 0;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &should);
  fill_matrix(&should, 0);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1;
    }
  }

  int mult_result = s21_mult_number(&A, number, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(mult_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(mult_number_4) {
  matrix_t A, calculated, should;
  double number = 5;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &should);

  int mult_result = s21_mult_number(NULL, number, &calculated);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(mult_number_5) {
  matrix_t A, should;
  double number = 5;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &should);

  int mult_result = s21_mult_number(&A, number, NULL);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(mult_matrix_1) {
  matrix_t A, B, calculated, should;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &should);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 2;
  B.matrix[0][1] = 0;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = 2;

  should.matrix[0][0] = 4;
  should.matrix[0][1] = 4;
  should.matrix[1][0] = 10;
  should.matrix[1][1] = 8;

  int mult_result = s21_mult_matrix(&A, &B, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(mult_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(mult_matrix_2) {
  matrix_t A, B, calculated, should;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &should);
  fill_matrix(&should, 0);

  int mult_result = s21_mult_matrix(&A, &B, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(mult_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t A, B, calculated;
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(2, 3, &B);

  int mult_result = s21_mult_matrix(&A, &B, &calculated);
  ck_assert_int_eq(mult_result, CALC_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_4) {
  matrix_t A, B, calculated;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  int mult_result = s21_mult_matrix(NULL, &B, &calculated);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  mult_result = s21_mult_matrix(&A, NULL, &calculated);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  mult_result = s21_mult_matrix(&A, &B, NULL);
  ck_assert_int_eq(mult_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(transpose_matrix_1) {
  matrix_t A, calculated, should;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &should);

  A.matrix[0][0] = 1.1;
  A.matrix[0][1] = 2.2;
  A.matrix[0][2] = 3.3;
  A.matrix[1][0] = 4.4;
  A.matrix[1][1] = 5.5;
  A.matrix[1][2] = 6.6;
  A.matrix[2][0] = 7.7;
  A.matrix[2][1] = 8.8;
  A.matrix[2][2] = 9.9;

  should.matrix[0][0] = 1.1;
  should.matrix[0][1] = 4.4;
  should.matrix[0][2] = 7.7;
  should.matrix[1][0] = 2.2;
  should.matrix[1][1] = 5.5;
  should.matrix[1][2] = 8.8;
  should.matrix[2][0] = 3.3;
  should.matrix[2][1] = 6.6;
  should.matrix[2][2] = 9.9;

  int transpose_result = s21_transpose(&A, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(transpose_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(transpose_matrix_2) {
  matrix_t A, calculated, should;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &should);

  double matrix[2][3] = {{1.5, 2.5, 3.5}, {4.5, 5.5, 6.5}};
  double res[3][2] = {{1.5, 4.5}, {2.5, 5.5}, {3.5, 6.5}};

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      should.matrix[i][j] = res[i][j];
    }
  }

  int transpose_result = s21_transpose(&A, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(transpose_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(transpose_matrix_3) {
  matrix_t A, calculated, should;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &should);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = i * 2 + j + 1;
    }
  }

  should.matrix[0][0] = 1;
  should.matrix[0][1] = 3;
  should.matrix[0][2] = 5;
  should.matrix[1][0] = 2;
  should.matrix[1][1] = 4;
  should.matrix[1][2] = 6;

  int transpose_result = s21_transpose(&A, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(transpose_result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(transpose_matrix_4) {
  matrix_t calculated = {NULL, 0, 0};

  int transpose_result = s21_transpose(NULL, &calculated);
  ck_assert_int_eq(transpose_result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(transpose_matrix_5) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int transpose_result = s21_transpose(&A, NULL);
  ck_assert_int_eq(transpose_result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_1) {
  matrix_t A;
  double calculated, should = -3.0;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 10;

  int result = s21_determinant(&A, &calculated);
  ck_assert_int_eq(result, OK);
  ck_assert_double_eq_tol(calculated, should, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_2) {
  double calculated;

  int result = s21_determinant(NULL, &calculated);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_matrix_3) {
  matrix_t A;
  double calculated;

  s21_create_matrix(4, 3, &A);
  int result = s21_determinant(&A, &calculated);
  ck_assert_int_eq(result, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_4) {
  matrix_t A;
  double calculated;

  s21_create_matrix(3, 4, &A);
  int result = s21_determinant(&A, &calculated);
  ck_assert_int_eq(result, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_5) {
  matrix_t A;
  double calculated, should = -23;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 3;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = -1;

  int result = s21_determinant(&A, &calculated);
  ck_assert_int_eq(result, OK);
  ck_assert_double_eq_tol(calculated, should, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_6) {
  matrix_t A;
  double calculated, should = 7.5;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 7.5;

  int result = s21_determinant(&A, &calculated);
  ck_assert_int_eq(result, OK);
  ck_assert_double_eq(calculated, should);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_7) {
  double calculated;

  int result = s21_determinant(NULL, &calculated);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(determinant_matrix_8) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int result = s21_determinant(&A, NULL);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_1) {
  matrix_t A, calculated, should;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &should);

  double m[3][3] = {{2, 3, 1}, {1, 4, 2}, {3, 2, 1}};
  double r[3][3] = {{0, 5, -10}, {-1, -1, 5}, {2, -3, 5}};

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = m[i][j];
      should.matrix[i][j] = r[i][j];
    }
  }

  int result = s21_calc_complements(&A, &calculated);
  int is_equal = s21_eq_matrix(&should, &calculated);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t A, calculated, should;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &should);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 3;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 4;

  should.matrix[0][0] = 4;
  should.matrix[0][1] = -1;
  should.matrix[1][0] = -3;
  should.matrix[1][1] = 2;

  int result = s21_calc_complements(&A, &calculated);
  int is_equal = s21_eq_matrix(&should, &calculated);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t A, calculated, should;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &should);

  A.matrix[0][0] = 5;
  should.matrix[0][0] = 1;

  int result = s21_calc_complements(&A, &calculated);
  ck_assert_int_eq(result, OK);

  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t A, calculated;
  s21_create_matrix(3, 2, &A);

  int result = s21_calc_complements(&A, &calculated);
  ck_assert_int_eq(result, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_5) {
  matrix_t A, calculated;
  s21_create_matrix(2, 3, &A);

  int result = s21_calc_complements(&A, &calculated);
  ck_assert_int_eq(result, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_6) {
  matrix_t calculated;

  int result = s21_calc_complements(NULL, &calculated);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(calc_complements_7) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int result = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_8) {
  matrix_t A, calculated, should;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &should);

  double m[3][3] = {{1, 2, 3}, {2, 4, 6}, {3, 6, 9}};
  double r[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = m[i][j];
      should.matrix[i][j] = r[i][j];
    }
  }

  int result = s21_calc_complements(&A, &calculated);
  int is_equal = s21_eq_matrix(&should, &calculated);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(inverse_matrix_1) {
  matrix_t A, calculated, should;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &should);

  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double r[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = m[i][j];
      should.matrix[i][j] = r[i][j];
    }
  }

  int result = s21_inverse_matrix(&A, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(inverse_matrix_2) {
  matrix_t A, calculated, should;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &should);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  should.matrix[0][0] = 0.6;
  should.matrix[0][1] = -0.7;
  should.matrix[1][0] = -0.2;
  should.matrix[1][1] = 0.4;

  int result = s21_inverse_matrix(&A, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(inverse_matrix_3) {
  matrix_t A, calculated;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;

  int result = s21_inverse_matrix(&A, &calculated);
  ck_assert_int_eq(result, OK);
  ck_assert_double_eq_tol(calculated.matrix[0][0], 0.2, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
}
END_TEST

START_TEST(inverse_matrix_4) {
  matrix_t A, calculated;
  s21_create_matrix(3, 2, &A);

  int result = s21_inverse_matrix(&A, &calculated);
  ck_assert_int_eq(result, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_5) {
  matrix_t calculated;

  int result = s21_inverse_matrix(NULL, &calculated);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_matrix_6) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int result = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(result, INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_7) {
  matrix_t A, calculated;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;

  int result = s21_inverse_matrix(&A, &calculated);
  ck_assert_int_eq(result, CALC_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_8) {
  matrix_t A, calculated, should;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &should);

  double m[3][3] = {{1, 2, 3}, {0, 1, 4}, {5, 6, 0}};
  double r[3][3] = {{-24, 18, 5}, {20, -15, -4}, {-5, 4, 1}};

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = m[i][j];
      should.matrix[i][j] = r[i][j];
    }
  }

  int result = s21_inverse_matrix(&A, &calculated);
  int is_equal = s21_eq_matrix(&calculated, &should);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
  s21_remove_matrix(&should);
}
END_TEST

START_TEST(inverse_matrix_9) {
  matrix_t A = {NULL, 0, 0};
  matrix_t calculated;

  int result = s21_inverse_matrix(&A, &calculated);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(inverse_matrix_10) {
  matrix_t A, calculated;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;

  int result = s21_inverse_matrix(&A, &calculated);
  ck_assert_int_eq(result, OK);

  int is_equal = s21_eq_matrix(&A, &calculated);
  ck_assert_int_eq(is_equal, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&calculated);
}
END_TEST

Suite *s21_unit_tests(void) {
  Suite *s;
  TCase *tc_matrix_tests;

  s = suite_create("Suite");
  tc_matrix_tests = tcase_create("matrix tests");

  tcase_add_test(tc_matrix_tests, create_matrix_1);
  tcase_add_test(tc_matrix_tests, create_matrix_2);
  tcase_add_test(tc_matrix_tests, create_matrix_3);

  tcase_add_test(tc_matrix_tests, equal_matrix_1);
  tcase_add_test(tc_matrix_tests, equal_matrix_2);
  tcase_add_test(tc_matrix_tests, equal_matrix_3);
  tcase_add_test(tc_matrix_tests, equal_matrix_4);

  tcase_add_test(tc_matrix_tests, sum_matrix_1);
  tcase_add_test(tc_matrix_tests, sum_matrix_2);
  tcase_add_test(tc_matrix_tests, sum_matrix_3);
  tcase_add_test(tc_matrix_tests, sum_matrix_4);
  tcase_add_test(tc_matrix_tests, sum_matrix_5);
  tcase_add_test(tc_matrix_tests, sum_matrix_6);

  tcase_add_test(tc_matrix_tests, sub_matrix_1);
  tcase_add_test(tc_matrix_tests, sub_matrix_2);
  tcase_add_test(tc_matrix_tests, sub_matrix_3);
  tcase_add_test(tc_matrix_tests, sub_matrix_4);
  tcase_add_test(tc_matrix_tests, sub_matrix_5);
  tcase_add_test(tc_matrix_tests, sub_matrix_6);

  tcase_add_test(tc_matrix_tests, mult_number_1);
  tcase_add_test(tc_matrix_tests, mult_number_2);
  tcase_add_test(tc_matrix_tests, mult_number_3);
  tcase_add_test(tc_matrix_tests, mult_number_4);
  tcase_add_test(tc_matrix_tests, mult_number_5);

  tcase_add_test(tc_matrix_tests, mult_matrix_1);
  tcase_add_test(tc_matrix_tests, mult_matrix_2);
  tcase_add_test(tc_matrix_tests, mult_matrix_3);
  tcase_add_test(tc_matrix_tests, mult_matrix_4);

  tcase_add_test(tc_matrix_tests, transpose_matrix_1);
  tcase_add_test(tc_matrix_tests, transpose_matrix_2);
  tcase_add_test(tc_matrix_tests, transpose_matrix_3);
  tcase_add_test(tc_matrix_tests, transpose_matrix_4);
  tcase_add_test(tc_matrix_tests, transpose_matrix_5);

  tcase_add_test(tc_matrix_tests, determinant_matrix_1);
  tcase_add_test(tc_matrix_tests, determinant_matrix_2);
  tcase_add_test(tc_matrix_tests, determinant_matrix_3);
  tcase_add_test(tc_matrix_tests, determinant_matrix_4);
  tcase_add_test(tc_matrix_tests, determinant_matrix_5);
  tcase_add_test(tc_matrix_tests, determinant_matrix_6);
  tcase_add_test(tc_matrix_tests, determinant_matrix_7);
  tcase_add_test(tc_matrix_tests, determinant_matrix_8);

  tcase_add_test(tc_matrix_tests, calc_complements_1);
  tcase_add_test(tc_matrix_tests, calc_complements_2);
  tcase_add_test(tc_matrix_tests, calc_complements_3);
  tcase_add_test(tc_matrix_tests, calc_complements_4);
  tcase_add_test(tc_matrix_tests, calc_complements_5);
  tcase_add_test(tc_matrix_tests, calc_complements_6);
  tcase_add_test(tc_matrix_tests, calc_complements_7);
  tcase_add_test(tc_matrix_tests, calc_complements_8);

  tcase_add_test(tc_matrix_tests, inverse_matrix_1);
  tcase_add_test(tc_matrix_tests, inverse_matrix_2);
  tcase_add_test(tc_matrix_tests, inverse_matrix_3);
  tcase_add_test(tc_matrix_tests, inverse_matrix_4);
  tcase_add_test(tc_matrix_tests, inverse_matrix_5);
  tcase_add_test(tc_matrix_tests, inverse_matrix_6);
  tcase_add_test(tc_matrix_tests, inverse_matrix_7);
  tcase_add_test(tc_matrix_tests, inverse_matrix_8);
  tcase_add_test(tc_matrix_tests, inverse_matrix_9);
  tcase_add_test(tc_matrix_tests, inverse_matrix_10);

  suite_add_tcase(s, tc_matrix_tests);

  return s;
}

int main(void) {
  int fail;
  Suite *s;
  SRunner *sr;

  s = s21_unit_tests();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  fail = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}