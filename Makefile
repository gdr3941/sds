all: sds-test

sds-test: sds_arena.c sds_arena.h testhelp.h
	$(CC) -o sds-test sds_arena.c arena.c -Wall -std=c23 -O2 -DSDS_TEST_MAIN
	@echo ">>> Type ./sds-test to run the sds.c unit tests."

debug: sds_arena.c sds_arena.h testhelp.h
	$(CC) -g -o sds-test sds_arena.c arena.c -Wall -std=c23 -DSDS_TEST_MAIN
	@echo ">>> Type ./sds-test to run the sds.c unit tests."

test: sds-test
	./sds-test

clean:
	rm -f sds-test
