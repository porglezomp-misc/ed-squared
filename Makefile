edsq: main.c string_util.c string_util.h buffer.h buffer.c
	gcc -o edsq -g main.c string_util.c buffer.c -Wall -Werror -std=c99

RunTest: test.c string_util.c string_util.h midunit.h midunit.c Makefile buffer.c buffer.h
	gcc -g -o RunTest test.c midunit.c string_util.c buffer.c -Wall -Werror -std=c99

test: RunTest
	./RunTest
