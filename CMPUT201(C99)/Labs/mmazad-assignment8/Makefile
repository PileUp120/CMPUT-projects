CC=gcc
GCC=gcc
CLANG=clang
CFLAGS=-std=c99 -pedantic -Wall -Wextra -ftrapv -ggdb3
LDFLAGS=$(CFLAGS)
CHECKS=--checks=*,-cert-err34-c,-cert-msc30-c,-cert-msc50-cpp
LINTR=--disable-rule=UselessParentheses
CLANGTIDY=clang-tidy
OCLINT=oclint
Q1ADIFF=q1a-test1-diff q1a-test2-diff q1a-test3-diff q1a-test4-diff q1a-test5-diff q1a-test6-diff q1a-test7-diff q1a-test8-diff
Q1BFAIL=q1b-test1-fail q1b-test2-fail
VFLAGS=--leak-check=full --track-origins=yes

.PHONY: q1a run-parameters-test lint-parameters lint-parameters-test run-question1 valgrind-question1 lint-%.c tests 

# you need to compile parameters.o and parameters-test.o here


lint-question1: question1.c combo.o parameters.o
	$(CLANGTIDY) $(CHECKS) \
		$< -- \
		$(CFLAGS) -c $^ $(LDFLAGS)	
	$(OCLINT) $(LINTR) parameters-test.c \
		-- $(CFLAGS) -c $^ $(LDFLAGS)

lint-%.c: %.c
	$(CLANGTIDY) $(CHECKS) \
		$< -- \
		$(CFLAGS) -o $<
	$(OCLINT) $(LINTR) $< \
		-- $(CFLAGS) -o $<


run-question1: question1
	./question1


valgrind-question1: question1
	valgrind --leak-check=full --track-origins=yes ./question1

# you need to compile question1.c as question1 properly here
# you need to compile combo.o from combo.c and combo.h
# if combo.h is modified combo.o must be recompiled
# you need to build:
# - combo-test
# - ppd-test
# - question1



valgrind-%: %
	valgrind --leak-check=full --track-origins=yes ./$<

valgrind-q1a-test1: q1a-test1-input.txt question1
	valgrind $(VFLAGS) ./question1 < q1a-test1-input.txt

valgrind-q1a-test2: q1a-test2-input.txt question1
	valgrind $(VFLAGS) ./question1 < q1a-test2-input.txt

valgrind-q1a-test3: q1a-test3-input.txt question1
	valgrind $(VFLAGS) ./question1 < q1a-test3-input.txt

valgrind-q1a-test4: q1a-test4-input.txt question1
	valgrind $(VFLAGS) ./question1 < q1a-test4-input.txt

valgrind-q1a-test: q1a-test5-input.txt question1
	valgrind $(VFLAGS) ./question1 < q1a-test5-input.txt

%-output.txt: %-input.txt question1
	./question1 < $< > $@

%-fail: %-input.txt question1
	./question1 < $< > $*-output.txt  ; test $$? -eq 1

%-diff: %-output.txt
	diff $< $*-expected-output.txt

run-%-test: %-test
	./$<

qtests: $(Q1ADIFF) $(Q1BFAIL)

tests:  run-ppd-test run-parameters-test run-combo-test qtests

lints: lint-checkinput.c  lint-combo-test.c  lint-combo.c  lint-parameters-test.c  lint-parameters.c  lint-ppd-test.c  lint-ppd.c  lint-question1.c  

clean:
	rm -f *.o question1 combo-test ppd-test parameters-test
