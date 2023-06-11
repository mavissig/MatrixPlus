CC=g++
SOURCES_LIB=matrix_oop
CFLAG=-Wall -Werror -Wextra
LIB_FLAG=ar rvs
CFLAGS_TEST= -lcheck -lgtest -lgtest_main -pthread
VALGRIND_FLAGS=valgrind --tool=memcheck --leak-check=yes

#Dir
TEST_DIR=./Test/
BUILD_DIR=./Build/
TMP_DIR=./Tmp/
GTEST_DIR =./Tests/

#File
CPPFILE=*.cc
HFILE=*.h
TESTFILE=$(TEST_DIR)test.cc
OUT_TEST=matrix_test

#Git
AUTOSAVEBRANCH=$(shell git rev-parse --abbrev-ref HEAD)
AUTOSAVECOMMIT="auto save"

all: matrix_oop.a

matrix_oop.o:
	@$(CC) $(CPPFILE) -c *.cc

matrix_oop.a: matrix_oop.o
	@$(LIB_FLAG) $(SOURCES_LIB).a *.o
	@rm -f ./*.o

test: matrix_oop.a
	@$(CC) -g $(CPPFILE) $(TESTFILE) $(CFLAGS_TEST) -L /usr/local/lib -o $(OUT_TEST)

run:
	@clear
	@ echo "\n\n-------------------- Test --------------------\n"
	@./$(OUT_TEST) --gtest_repeat=1

leaks: test
	$(VALGRIND_FLAGS) ./$(OUT_TEST)

open:
ifeq ($(OS), Linux)
	xdg-open report/index.html
else
	open -a "Google Chrome" report/index.html
endif

clean:
	@rm -f $(TMPDIR)*.o ./*.o *.a
	@rm -f *.out *.gcda *.gcno $(OUT_TEST) *.info
	@rm -rf *.dSYM report

clang: clang-format clang-check

clang-format:
	@cp ../materials/linters/.clang-format .
	@clang-format -i $(CPPFILE) $(HFILE) $(TESTFILE)
	@rm -f .clang-format

clang-check:
	@cp ../materials/linters/.clang-format .
	@clang-format -n $(CPPFILE) $(HFILE) $(TESTFILE)
	@rm -f .clang-format

save: clang clean
	git add . && git commit -m $(AUTOSAVECOMMIT) && git push origin $(AUTOSAVEBRANCH)
	echo push in branch: $(AUTOSAVEBRANCH)