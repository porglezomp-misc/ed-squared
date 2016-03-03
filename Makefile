edsq: main.c string_util.c string_util.h
	gcc -o edsq -g main.c string_util.c -Wall -Werror -std=c99

RunTest: test.c string_util.c string_util.h midunit.h Makefile
	gcc -g -o RunTest test.c string_util.c -Wall -Werror -std=c99

test: RunTest
	./RunTest
