.PHONY: all rebuild test clean clangi clangn cppcheck valgrind gcov_report

CC := gcc
CFLAGS := -Wall -Wextra -Werror -Wpedantic -std=c11
TEST_FLAGS := -lcheck -lpthread -lsubunit -lrt -lm

GCOV_SRC_FILES := s21_matrix.c

SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(SRC_FILES:.c=.o)
STATIC_LIB := s21_matrix.a

TEST_DIR := tests
MAIN_TEST := $(TEST_DIR)/test

VALGRIND_REPORT := valgrind_report.txt
ERRORS_SUMMARY := errors_summary.txt

all: test

rebuild: clean all

test: main_test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJ_FILES)
	ar rcs $@ $^
	$(RM) $(OBJ_FILES)

main_test: $(STATIC_LIB)
	$(CC) $(CFLAGS) -o $(MAIN_TEST) $(TEST_DIR)/test.c $(STATIC_LIB) $(TEST_FLAGS)
	$(MAIN_TEST)

gcov_report: CFLAGS += -fprofile-arcs -ftest-coverage
gcov_report: clean $(STATIC_LIB)
	$(CC) $(CFLAGS) $(TEST_DIR)/test.c $(SRC_FILES) -o test.out $(TEST_FLAGS)
	./test.out
	
	gcov -f $(GCOV_SRC_FILES)
	lcov -c -d . -o coverage.info --rc lcov_branch_coverage=1 --include "*/s21_matrix.c"
	genhtml coverage.info -o report --branch-coverage

	$(RM) *.gcno *.gcda *.info *.out *.gcov $(OBJ_FILES)
	open ./report/index.html 2>/dev/null || xdg-open ./report/index.html 2>/dev/null || echo "Open report manually: ./report/index.html"

# for check all style errors
clangn:
	find . -name '*.h' -o -name '*.c' | xargs clang-format -n --style=Google

# for auto fix all style errors
clangi:
	find . -name '*.h' -o -name '*.c' | xargs clang-format -i --style=Google

cppcheck: clean $(STATIC_LIB)
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_FILES) $(wildcard *.h) tests/test.c

valgrind: rebuild
	valgrind --tool=memcheck --track-origins=yes --leak-check=full -s $(MAIN_TEST) > $(VALGRIND_REPORT) 2>&1
	grep "ERROR SUMMARY" $(VALGRIND_REPORT) > $(ERRORS_SUMMARY)

clean:
	$(RM) -rf *.o *.a *.out
	$(RM) $(OBJ_FILES) $(STATIC_LIB) $(MAIN_TEST)
	$(RM) -rf ./report coverage.info
	$(RM) *.gcno *.gcda *.gcov
	$(RM) $(VALGRIND_REPORT) $(ERRORS_SUMMARY)