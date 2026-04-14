#include <check.h>

#include "../s21_matrix.h"

static void set_matrix(matrix_t *M, const double *data) {
  int idx = 0;
  for (int i = 0; i < M->rows; i++) {
    for (int j = 0; j < M->columns; j++) {
      M->matrix[i][j] = data[idx++];
    }
  }
}

START_TEST(test_create_remove) {
  matrix_t M;

  ck_assert_int_eq(s21_create_matrix(3, 3, &M), OK);
  ck_assert_int_eq(M.rows, 3);
  ck_assert_int_eq(M.columns, 3);
  ck_assert_ptr_nonnull(M.matrix);
  s21_remove_matrix(&M);

  ck_assert_int_eq(s21_create_matrix(3, 3, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(0, 3, &M), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(3, 0, &M), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(-1, 3, &M), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_eq_matrix) {
  matrix_t A, B;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  set_matrix(&A, (double[]){1.0, 2.0, 3.0, 4.0});
  set_matrix(&B, (double[]){1.0, 2.0, 3.0, 4.0});
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), OK);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  set_matrix(&A, (double[]){1.0, 2.0, 3.0, 4.0});
  set_matrix(&B, (double[]){1.0, 2.0, 3.0, 5.0});
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_eq_matrix(NULL, &B), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  matrix_t C = {NULL, 0, 0};
  ck_assert_int_eq(s21_eq_matrix(&A, &C), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_sum_matrix) {
  matrix_t A, B, R, expected;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  fill_matrix(&expected, 0);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4});
  set_matrix(&B, (double[]){5, 6, 7, 8});
  set_matrix(&expected, (double[]){6, 8, 10, 12});
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 3, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 2, &B), OK);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_sum_matrix(NULL, &B, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix) {
  matrix_t A, B, R, expected;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4});
  set_matrix(&B, (double[]){1, 2, 3, 4});
  fill_matrix(&expected, 0);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){10, 20, 30, 40});
  set_matrix(&B, (double[]){1, 2, 3, 4});
  set_matrix(&expected, (double[]){9, 18, 27, 36});
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(3, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 3, &B), OK);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_number) {
  matrix_t A, R, expected;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4});
  fill_matrix(&expected, 0);
  ck_assert_int_eq(s21_mult_number(&A, 0.0, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4});
  set_matrix(&expected, (double[]){3, 6, 9, 12});
  ck_assert_int_eq(s21_mult_number(&A, 3.0, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4});
  set_matrix(&expected, (double[]){-2, -4, -6, -8});
  ck_assert_int_eq(s21_mult_number(&A, -2.0, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  ck_assert_int_eq(s21_mult_number(NULL, 5.0, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_number(&A, 5.0, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_matrix) {
  matrix_t A, B, R, expected;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4});
  set_matrix(&B, (double[]){2, 0, 1, 2});
  set_matrix(&expected, (double[]){4, 4, 10, 8});
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(3, 4, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 3, &B), OK);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  ck_assert_int_eq(s21_mult_matrix(NULL, &B, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_transpose) {
  matrix_t A, R, expected;

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &expected), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4, 5, 6, 7, 8, 9});
  set_matrix(&expected, (double[]){1, 4, 7, 2, 5, 8, 3, 6, 9});
  ck_assert_int_eq(s21_transpose(&A, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 3, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 2, &expected), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4, 5, 6});
  set_matrix(&expected, (double[]){1, 4, 2, 5, 3, 6});
  ck_assert_int_eq(s21_transpose(&A, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_transpose(NULL, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_transpose(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant) {
  matrix_t A;
  double det;

  ck_assert_int_eq(s21_create_matrix(1, 1, &A), OK);
  A.matrix[0][0] = 7.5;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, 7.5, 1e-7);
  s21_remove_matrix(&A);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  set_matrix(&A, (double[]){3, 4, 5, -1});
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, -23, 1e-7);
  s21_remove_matrix(&A);

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);
  set_matrix(&A, (double[]){1, 2, 3, 4, 5, 6, 7, 8, 10});
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq_tol(det, -3, 1e-7);
  s21_remove_matrix(&A);

  ck_assert_int_eq(s21_create_matrix(2, 3, &A), OK);
  ck_assert_int_eq(s21_determinant(&A, &det), CALC_ERROR);
  s21_remove_matrix(&A);

  ck_assert_int_eq(s21_determinant(NULL, &det), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_determinant(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements) {
  matrix_t A, R, expected;

  ck_assert_int_eq(s21_create_matrix(1, 1, &A), OK);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(s21_calc_complements(&A, &R), OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 1, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){2, 3, 1, 4});
  set_matrix(&expected, (double[]){4, -1, -3, 2});
  ck_assert_int_eq(s21_calc_complements(&A, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &expected), OK);
  set_matrix(&A, (double[]){2, 3, 1, 1, 4, 2, 3, 2, 1});
  set_matrix(&expected, (double[]){0, 5, -10, -1, -1, 5, 2, -3, 5});
  ck_assert_int_eq(s21_calc_complements(&A, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 3, &A), OK);
  ck_assert_int_eq(s21_calc_complements(&A, &R), CALC_ERROR);
  s21_remove_matrix(&A);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_calc_complements(NULL, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix) {
  matrix_t A, R, expected;

  ck_assert_int_eq(s21_create_matrix(1, 1, &A), OK);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), OK);
  ck_assert_double_eq_tol(R.matrix[0][0], 0.2, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  set_matrix(&A, (double[]){4, 7, 2, 6});
  set_matrix(&expected, (double[]){0.6, -0.7, -0.2, 0.4});
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &expected), OK);
  set_matrix(&A, (double[]){2, 5, 7, 6, 3, 4, 5, -2, -3});
  set_matrix(&expected, (double[]){1, -1, 1, -38, 41, -34, 27, -29, 24});
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&expected);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  set_matrix(&A, (double[]){1, 0, 0, 1});
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), OK);
  ck_assert_int_eq(s21_eq_matrix(&R, &A), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  set_matrix(&A, (double[]){1, 2, 2, 4});
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), CALC_ERROR);
  s21_remove_matrix(&A);

  ck_assert_int_eq(s21_create_matrix(2, 3, &A), OK);
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), CALC_ERROR);
  s21_remove_matrix(&A);

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &expected), OK);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &R), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);

  matrix_t C = {NULL, 0, 0};
  ck_assert_int_eq(s21_inverse_matrix(&C, &R), INCORRECT_MATRIX);
}
END_TEST

Suite *s21_unit_tests(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_matrix");
  tc = tcase_create("matrix operations");

  tcase_add_test(tc, test_create_remove);
  tcase_add_test(tc, test_eq_matrix);
  tcase_add_test(tc, test_sum_matrix);
  tcase_add_test(tc, test_sub_matrix);
  tcase_add_test(tc, test_mult_number);
  tcase_add_test(tc, test_mult_matrix);
  tcase_add_test(tc, test_transpose);
  tcase_add_test(tc, test_determinant);
  tcase_add_test(tc, test_calc_complements);
  tcase_add_test(tc, test_inverse_matrix);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int failures;
  Suite *s;
  SRunner *sr;

  s = s21_unit_tests();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  failures = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
